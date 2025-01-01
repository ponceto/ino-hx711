/*
 * HX711Test.ino - Copyright (c) 2014-2025 - Olivier Poncet
 *
 * This file is part of the HX711 library
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <Arduino.h>
#include <HX711.h>

// ---------------------------------------------------------------------------
// Setup
// ---------------------------------------------------------------------------

struct Setup
{
    static constexpr unsigned long SERIAL_SPEED   = 9600UL;
    static constexpr unsigned long LOOP_DELAY     = 1000UL;
    static constexpr uint8_t       HX711_SCLK_PIN = 8;
    static constexpr uint8_t       HX711_DATA_PIN = 9;
    static constexpr uint8_t       HX711_PGA_GAIN = 128;
};

// ---------------------------------------------------------------------------
// globals
// ---------------------------------------------------------------------------

HX711 sensor ( Setup::HX711_SCLK_PIN
             , Setup::HX711_DATA_PIN
             , Setup::HX711_PGA_GAIN );

// ---------------------------------------------------------------------------
// setup
// ---------------------------------------------------------------------------

void setup()
{
    Serial.begin(Setup::SERIAL_SPEED);
    sensor.begin();
}

// ---------------------------------------------------------------------------
// loop
// ---------------------------------------------------------------------------

void loop()
{
    if(sensor.read()) {
        Serial.print(F("sensor value : "));
        Serial.println(sensor.value());
    }
    ::delay(Setup::LOOP_DELAY);
}

// ---------------------------------------------------------------------------
// End-Of-File
// ---------------------------------------------------------------------------
