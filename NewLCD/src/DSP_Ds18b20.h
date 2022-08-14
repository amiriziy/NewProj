// Include the libraries we need
#pragma once
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 14

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

DeviceAddress deviceAddress;
float GetTemp(void)
{
  sensors.requestTemperatures(); // Send the command to get temperatures

  return sensors.getTempCByIndex(0);
}
