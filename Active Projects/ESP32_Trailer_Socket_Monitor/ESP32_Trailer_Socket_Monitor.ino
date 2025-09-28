// ESP32 Dual-Core Trailer Socket Tester (Optocouplers, no shift register)
// Core 0: sample GPIOs; Core 1: Wi-Fi AP + HTTP server.
//
// Tested with ESP32 Arduino core. Drop-in for PlatformIO or Arduino IDE.

#include <WiFi.h>
#include <WebServer.h>

// ===== USER CONFIG =====
const char* AP_SSID     = "TrailerTester";
const char* AP_PASS     = "trailer123";

// If your opto stage makes the GPIO LOW when the trailer line is active, set ACTIVE_LOW = true
const bool ACTIVE_LOW   = true;

// Name your channels (order must match SENSE_PINS)
const char* SIGNAL_NAMES[] = {
  "Left Indicator",
  "Right Indicator",
  "Brake",
  "Tail",
  "Reverse",
  "Aux / Fog"
};
constexpr uint8_t NUM_SIGNALS = sizeof(SIGNAL_NAMES)/sizeof(SIGNAL_NAMES[0]);

// Choose safe input pins (avoid 0, 2, 15). 34–39 are input-only (great for sensing).
constexpr uint8_t SENSE_PINS[NUM_SIGNALS] = {34, 35, 32, 33, 25, 26};

// Polling cadence (ms)
constexpr uint16_t SAMPLE_PERIOD_MS = 10;   // fast enough to catch blinkers cleanly

// =======================

WebServer server(80);

// Shared state written by Core 0, read by Core 1
volatile bool signalState[NUM_SIGNALS] = {false};
portMUX_TYPE stateMux = portMUX_INITIALIZER_UNLOCKED;

// --- Core 0 task: sample inputs ---
void samplerTask(void* pv) {
  TickType_t last = xTaskGetTickCount();
  for (;;) {
    for (uint8_t i = 0; i < NUM_SIGNALS; ++i) {
      int raw = digitalRead(SENSE_PINS[i]);
      bool active = ACTIVE_LOW ? (raw == LOW) : (raw == HIGH);

      // Commit atomically
      portENTER_CRITICAL(&stateMux);
      signalState[i] = active;
      portEXIT_CRITICAL(&stateMux);
    }
    vTaskDelayUntil(&last, pdMS_TO_TICKS(SAMPLE_PERIOD_MS));
  }
}

// --- Web UI ---
const char INDEX_HTML[] PROGMEM = R"HTML(
<!doctype html>
<html>
<head>
<meta charset="utf-8"/>
<meta name="viewport" content="width=device-width,initial-scale=1"/>
<title>Trailer Socket Tester</title>
<style>
  :root { --ok:#18a558; --off:#555; --bg:#0e1117; --card:#161b22; --txt:#e6edf3; --warn:#eab308; }
  *{box-sizing:border-box} html,body{margin:0;background:var(--bg);color:var(--txt);font-family:system-ui,-apple-system,Segoe UI,Roboto,Inter,Arial}
  .wrap{max-width:720px;margin:0 auto;padding:20px}
  h1{font-size:1.25rem;margin:0 0 10px}
  .grid{display:grid;grid-template-columns:repeat(auto-fit,minmax(180px,1fr));gap:12px}
  .card{background:var(--card);border-radius:14px;padding:14px 16px;box-shadow:0 4px 20px rgba(0,0,0,.25)}
  .sig{display:flex;align-items:center;gap:12px;font-weight:600}
  .dot{width:18px;height:18px;border-radius:999px;background:var(--off);box-shadow:0 0 0 2px rgba(255,255,255,0.06) inset;transition:background .1s ease, box-shadow .1s ease, transform .1s ease}
  .dot.on{background:var(--ok);box-shadow:0 0 14px rgba(24,165,88,.6);transform:translateY(-1px)}
  .meta{opacity:.8;font-size:.9rem;margin-top:10px;display:flex;justify-content:space-between;gap:10px;flex-wrap:wrap}
  .warn{color:var(--warn);font-size:.9rem}
</style>
</head>
<body>
<div class="wrap">
  <h1>Trailer Socket Tester</h1>
  <div id="grid" class="grid"></div>
  <div class="card meta">
    <div>Refresh: <span id="rt">—</span> ms</div>
    <div>Device: 192.168.4.1</div>
  </div>
  <div class="card warn">Automotive lines are spiky. Keep the optos + TVS diodes in play to protect the ESP32.</div>
</div>
<script>
const names = %NAMES%;
const grid = document.getElementById('grid');
const rt = document.getElementById('rt');
let dots = [];

function build() {
  grid.innerHTML = '';
  dots = names.map(n=>{
    const c=document.createElement('div'); c.className='card';
    const r=document.createElement('div'); r.className='sig';
    const d=document.createElement('div'); d.className='dot';
    const l=document.createElement('div'); l.textContent=n;
    r.appendChild(d); r.appendChild(l); c.appendChild(r); grid.appendChild(c);
    return d;
  });
}
async function tick(){
  const t0=performance.now();
  try{
    const res = await fetch('/state',{cache:'no-store'});
    const dat = await res.json();
    (dat.states||[]).forEach((v,i)=>{
      if(!dots[i]) return;
      dots[i].classList.toggle('on', !!v);
    });
  }catch(e){}
  rt.textContent = Math.round(performance.now()-t0);
}
build();
setInterval(tick, 200);
tick();
</script>
</body>
</html>
)HTML";

String renderIndex() {
  String s(INDEX_HTML);
  String js = "[";
  for (uint8_t i=0;i<NUM_SIGNALS;++i){
    js += "\""; js += SIGNAL_NAMES[i]; js += (i+1<NUM_SIGNALS) ? "\"," : "\"";
  }
  js += "]";
  s.replace("%NAMES%", js);
  return s;
}

void handleRoot(){
  String page = renderIndex();
  server.setContentLength(page.length());
  server.send(200, "text/html; charset=utf-8", page);
}

void handleState(){
  String json = "{\"states\":[";
  portENTER_CRITICAL(&stateMux);
  for (uint8_t i=0;i<NUM_SIGNALS;++i){
    json += signalState[i] ? "1":"0";
    if (i+1<NUM_SIGNALS) json += ",";
  }
  portEXIT_CRITICAL(&stateMux);
  json += "]}";
  server.send(200, "application/json", json);
}

void setupWiFiAP(){
  WiFi.mode(WIFI_AP);
  WiFi.softAP(AP_SSID, (strlen(AP_PASS)?AP_PASS:nullptr));
  delay(100);
}

void setup(){
  // Configure inputs
  for (uint8_t i=0;i<NUM_SIGNALS;++i){
    // External pull-up used in opto stage; set plain INPUT (not pullup) to avoid fighting.
    pinMode(SENSE_PINS[i], INPUT);
  }

  setupWiFiAP();

  // HTTP server
  server.on("/", handleRoot);
  server.on("/state", handleState);
  server.begin();

  // Spawn sampler on Core 0
  xTaskCreatePinnedToCore(
    samplerTask, "samplerTask",
    4096, nullptr, 1, nullptr, 0
  );
}

void loop(){
  server.handleClient();
  delay(2);
}
