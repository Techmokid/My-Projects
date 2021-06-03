//Temperatures
#define heater_on_temp            20
#define heater_off_temp           25
#define cooler_off_temp           40
#define cooler_on_temp            45
#define overheat_warning_temp     46
#define overheat_shutdown_temp    50

//Digital Pins
#define heater_LED_pin            2
#define cooler_LED_pin            3
#define overheat_warning_LED_pin  4
#define overheat_shutdown_LED_pin 5

//Analog Pins
#define thermistor_pin_1          0
#define thermistor_pin_2          1

void setup() {}
void loop() {
  float sensor_temp_1 = ConvertAnalogToTemp(analogRead(thermistor_pin_1));
  float sensor_temp_2 = ConvertAnalogToTemp(analogRead(thermistor_pin_2));
  
  if (sensor_temp_1 > cooler_on_temp) { digitalWrite(cooler_LED_pin,HIGH); }
  if (sensor_temp_2 < heater_on_temp) { digitalWrite(heater_LED_pin,HIGH); }
  if (sensor_temp_1 < cooler_off_temp) { digitalWrite(cooler_LED_pin,LOW); }
  if (sensor_temp_2 > heater_off_temp) { digitalWrite(heater_LED_pin,LOW); }
  
  digitalWrite(overheat_warning_LED_pin,  sensor_temp_1 > overheat_warning_temp);
  digitalWrite(overheat_shutdown_LED_pin, sensor_temp_1 > overheat_shutdown_temp);
}

//Convert the incoming analogVoltage to a temperature reading that we can work with
float ConvertAnalogToTemp(float analogInput) {
  //This is important. We turn the input voltage into a sensor resistance calculation for later use
  float R2 = voltageToResistance(analogInput,1);
  
  // Original Formula:    B = ln(R1/R2)/(1/T1 - 1/T2)
  // Modified Formula 1:  T1 = B*T2 / (T2*ln(R1/R2) + B)
  // Modified Formula 2:  T2 = -B*T1 / (T1*ln(R1/R2) - B)
  float B = 3970;
  float T1 = 298.15;
  float R1 = 10000;
  float T2 = (-B*T1) / (T1*log(R1/R2) - B);
  
  return T2;
}

//Convert the incoming analog voltage into the resistance of the thermistor depending on the type of circuit we are using
float voltageToResistance(float Vout, int circuitType) {
  if (circuitType == 1) {
    //This is the simplest circuit with just a single resistor and the sensor in a voltage divider arrangement
    float Vin = 5.00f;
    float R2 = 10000;
    float R1 = R2*Vout/(Vin-Vout);  //Simple voltage-divider resistor calculation
    return R1;
  } else if (circuitType == 2) {
    // INCOMPLETE!!!
    // THIS IS A W.I.P FOR THE OPAMP CIRCUIT AND DOES NOT WORK YET!
  }
}
