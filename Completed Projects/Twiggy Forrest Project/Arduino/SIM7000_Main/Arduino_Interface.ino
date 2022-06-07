String status = "";
void checkMotorStatus() {
  String newStatus = "";
  if (!digitalRead(COM_PIN_1) && (status != "Offline")) {
    status = "Offline";
    serverSetStatus("Offline");
  }
  if (digitalRead(COM_PIN_1)) {
    if (!digitalRead(COM_PIN_2) && !digitalRead(COM_PIN_3) && (status != "Online")) {
      status = "Online";
      serverSetStatus("Online");
    }
    if (!digitalRead(COM_PIN_2) && !digitalRead(COM_PIN_3) && (status != "Fixing Clog")) {
      status = "Fixing Clog";
      serverSetStatus("Fixing Clog");
    }
    if (!digitalRead(COM_PIN_2) && !digitalRead(COM_PIN_3) && (status != "Clogged")) {
      status = "Clogged";
      serverSetStatus("Clogged");
    }
    if (!digitalRead(COM_PIN_2) && !digitalRead(COM_PIN_3) && (status != "Full")) {
      status = "Full";
      serverSetStatus("Full");
    }
  }
}