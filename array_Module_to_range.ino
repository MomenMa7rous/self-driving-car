#include<QTRSensors.h>

QTRSensors qtr;

// Initializing the main variables: Number of sensors, Pins used in ESP 32, Values taken from sensor
const uint8_t num_of_sensors = 8;
const uint8_t  sensor_pins[num_of_sensors] = {13, 14, 27, 26, 25, 33, 32, 15}; // With same order in array: sensor 1 = 13, sensor 2 = 14.... 
uint16_t sensor_values[num_of_sensors];


void setup() {
  serial.begin(115200);
  delay(500);

  qtr.setTypeRC();
  qtr.setSensorPins(sensor_pins,num_of_sensors);//
  qtr.setTimeout(2500);

  Serial.println("Calibrating QTR-8RC... Move sensors over black line and white surface.");
  for (uint16_t i = 0; i < 200; i++) {
    qtr.calibrate();
    delay(20);
  }
  Serial.println("Calibration done!");
}


}

void loop() {
  uint16_t position = qtr.readLineBlack(sensor_values);

  int error = (int)position - 3500;

  Serial.print("Position: ");
  Serial.print(position);
  Serial.print(" | Error: ");
  Serial.println(error);

  delay(50);
}
