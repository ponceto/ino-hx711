/*
 * HX711.h - Copyright (c) 2014-2025 - Olivier Poncet
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
#ifndef __INO_HX711_HX711_h__
#define __INO_HX711_HX711_h__

// ---------------------------------------------------------------------------
// HX711_Traits
// ---------------------------------------------------------------------------

struct HX711_Traits
{
    struct Setup
    {
        static constexpr uint8_t DATA_PINMODE = INPUT_PULLUP;
        static constexpr uint8_t SCLK_PINMODE = OUTPUT;
    };

    struct ChannelA
    {
        static constexpr uint8_t GAIN_MED =  64;
        static constexpr uint8_t GAIN_MAX = 128;
    };

    struct ChannelB
    {
        static constexpr uint8_t GAIN_MIN =  32;
    };

    struct Default
    {
        static constexpr long    DATA = 0L;
        static constexpr uint8_t GAIN = 128;
    };
};

// ---------------------------------------------------------------------------
// HX711_Wiring
// ---------------------------------------------------------------------------

struct HX711_Wiring
{
    uint8_t sclkPin;
    uint8_t dataPin;
};

// ---------------------------------------------------------------------------
// HX711_Values
// ---------------------------------------------------------------------------

struct HX711_Values
{
    long    data;
    uint8_t gain;
};

// ---------------------------------------------------------------------------
// HX711
// ---------------------------------------------------------------------------

class HX711
{
public: // public interface
    HX711 ( const uint8_t sclkPin
          , const uint8_t dataPin
          , const uint8_t pgaGain );

    void begin();
    void reset();
    void end();

    bool read();

    long value() const
    {
        return _values.data;
    }

    void powerDown() const;
    bool dataReady() const;
    long readValue() const;

protected: // protected interface
    using Traits = HX711_Traits;
    using Wiring = HX711_Wiring;
    using Values = HX711_Values;

protected: // protected data
    Wiring const _wiring;
    Values       _values;
};

// ---------------------------------------------------------------------------
// End-Of-File
// ---------------------------------------------------------------------------

#endif /* __INO_HX711_HX711_h__ */
