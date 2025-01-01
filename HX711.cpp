/*
 * HX711.cpp - Copyright (c) 2014-2025 - Olivier Poncet
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
#include "HX711.h"

// ---------------------------------------------------------------------------
// HX711
// ---------------------------------------------------------------------------

HX711::HX711 ( const uint8_t sclkPin
             , const uint8_t dataPin
             , const uint8_t pgaGain )
    : _wiring { sclkPin
              , dataPin }
    , _values { Traits::Default::DATA
              , pgaGain }
{
}

void HX711::begin()
{
    /* setup */ {
        ::pinMode(_wiring.sclkPin, Traits::Setup::SCLK_PINMODE);
        ::pinMode(_wiring.dataPin, Traits::Setup::DATA_PINMODE);
    }
    /* reset */ {
        reset();
    }
}

void HX711::reset()
{
    /* reset pulse */ {
        ::digitalWrite(_wiring.sclkPin, 0x0);
        ::digitalWrite(_wiring.sclkPin, 0x1);
        ::delayMicroseconds(100);
        ::digitalWrite(_wiring.sclkPin, 0x0);
    }
}

void HX711::end()
{
    /* power-down */ {
        powerDown();
    }
}

bool HX711::read()
{
    const bool ready = dataReady();

    if(ready != false) {
        _values.data = readValue();
    }
    return ready;
}

void HX711::powerDown() const
{
    ::digitalWrite(_wiring.sclkPin, 0x0);
    ::digitalWrite(_wiring.sclkPin, 0x1);
    ::delayMicroseconds(100);
}

bool HX711::dataReady() const
{
    if(::digitalRead(_wiring.dataPin) == 0x0) {
        return true;
    }
    return false;
}

long HX711::readValue() const
{
    constexpr uint8_t bits   = 24;
    constexpr int32_t sign   = 1UL << (bits - 1);
    uint8_t           pulses = 1;
    int32_t           value  = 0;

    /* compute the number of extra pulses */ {
        switch(_values.gain) {
            case Traits::ChannelB::GAIN_MIN:
                pulses = 2;
                break;
            case Traits::ChannelA::GAIN_MED:
                pulses = 3;
                break;
            case Traits::ChannelA::GAIN_MAX:
                pulses = 1;
                break;
            default:
                pulses = 1;
                break;
        }
    }
    /* shift read */ {
        uint8_t count = bits;
        do {
            ::digitalWrite(_wiring.sclkPin, 0x1);
            value = (value << 1) | ::digitalRead(_wiring.dataPin);
            ::digitalWrite(_wiring.sclkPin, 0x0);
        } while(--count != 0);
    }
    /* set gain */ {
        uint8_t count = pulses;
        do {
            ::digitalWrite(_wiring.sclkPin, 0x1);
            ::digitalWrite(_wiring.sclkPin, 0x0);
        } while(--count != 0);
    }
    /* extend the sign from 24bits to 32bits */ {
        value = ((value ^ sign) - sign);
    }
    return value;
}

// ---------------------------------------------------------------------------
// End-Of-File
// ---------------------------------------------------------------------------
