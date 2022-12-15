/* MIT License

Copyright (c) 2022 Gabryel Reyes <gabryelrdiaz@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

/*******************************************************************************
    DESCRIPTION
*******************************************************************************/
/**
 *  @brief  Control of a single LED through RMT
 *  @author Gabryel Reyes <gabryelrdiaz@gmail.com>
 */

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "RMT_LED.h"

/******************************************************************************
 * Macros
 *****************************************************************************/

/******************************************************************************
 * Prototypes
 *****************************************************************************/

/******************************************************************************
 * Local Variables
 *****************************************************************************/

/**
 *  Number of Data Bits.
 *  Derived from 3 Channels (RGB), each width an 8 Bit Channel-Width.
 */
static const size_t NUMBER_OF_DATA_BITS = 3U * 8U;

/**
 *  Number of possible Presets.
 */
static const size_t NUMBER_OF_PRESETS = 8U;
/**
 * Tick Duration in Nanoseconds.
 */
static const float TICK_DURATION = 100.0F;

/**
 *  Color Data Array
 */
static rmt_data_t colorData[NUMBER_OF_DATA_BITS];

/**
 *  Data Array containing preset data.
 */
static rmt_data_t presets[NUMBER_OF_PRESETS][NUMBER_OF_DATA_BITS];

/**
 *  Set Bit definition
 *
 *  .val = 294920 is analog to:
 *  .level0 = 1;
 *  .duration0 = 4;
 *  .level1 = 0;
 *  .duration1 = 8;
 */
static const uint32_t setBitValue = 294920U;

/**
 *  Unset Bit definition
 *
 *  .val = 557060 is analog to:
 *  .level0 = 1;
 *  .duration0 = 8;
 *  .level1 = 0;
 *  .duration1 = 4;
 */
static const uint32_t unsetBitValue = 557060U;

/******************************************************************************
 * Public Methods
 *****************************************************************************/

RMT_LED::RMT_LED(const uint8_t ledPin, const uint8_t maxBrightness) : m_rmtInstance(nullptr), m_maxBrightness(maxBrightness)
{
    m_rmtInstance = rmtInit(ledPin, RMT_TX_MODE, RMT_MEM_64);

    if (nullptr != m_rmtInstance)
    {
        // Initialize Tick
        rmtSetTick(m_rmtInstance, TICK_DURATION);

        // Initialize Preset Data Arrays
        setPreset(RED,      005U, 000U, 000U);
        setPreset(GREEN,    000U, 005U, 000U);
        setPreset(BLUE,     000U, 000U, 005U);
        setPreset(WHITE,    005U, 005U, 005U);
        setPreset(CLEAR,    000U, 000U, 000U);
    }
}

RMT_LED::~RMT_LED()
{
    
    if (nullptr != m_rmtInstance)
    {
        rmtDeinit(m_rmtInstance);
    }
}

void RMT_LED::setColor(const uint8_t red, const uint8_t green, const uint8_t blue)
{
    uint32_t colorArray = parseRgbValue(red, green, blue);

    for (uint8_t bit = 0; bit < NUMBER_OF_DATA_BITS; bit++)
    {
        if ((1 << (NUMBER_OF_DATA_BITS - bit - 1U)) & colorArray)
        {
            colorData[bit].val = setBitValue;
        }
        else
        {
            colorData[bit].val = unsetBitValue;
        }
    }

    sendData(colorData);
}

void RMT_LED::setColor(PRESETS presetNumber)
{
    sendData(presets[presetNumber]);
}

void RMT_LED::clear()
{
    sendData(presets[CLEAR]);
}

void RMT_LED::setPreset(PRESETS presetNumber, const uint8_t red, const uint8_t green, const uint8_t blue)
{
    uint32_t colorArray = parseRgbValue(red, green, blue);

    for (uint8_t bit = 0; bit < NUMBER_OF_DATA_BITS; bit++)
    {
        if ((1 << (NUMBER_OF_DATA_BITS - bit - 1U)) & colorArray)
        {
            presets[presetNumber][bit].val = setBitValue;
        }
        else
        {
            presets[presetNumber][bit].val = unsetBitValue;
        }
    }
}

/******************************************************************************
 * Private Methods
 *****************************************************************************/

bool RMT_LED::sendData(rmt_data_t *dataArray)
{
    bool isSuccess = false;

    if (nullptr != dataArray)
    {
        isSuccess = rmtWrite(m_rmtInstance, dataArray, NUMBER_OF_DATA_BITS);
    }

    return isSuccess;
}

uint32_t RMT_LED::parseRgbValue(const uint8_t red, const uint8_t green, const uint8_t blue)
{
    // Check and Set Max Brightness.
    uint8_t maxRed      = !(red   < m_maxBrightness) ? m_maxBrightness : red;
    uint8_t maxGreen    = !(green < m_maxBrightness) ? m_maxBrightness : green;
    uint8_t maxBlue     = !(blue  < m_maxBrightness) ? m_maxBrightness : blue;

    return uint32_t((maxGreen << 16) + (maxRed << 8) + maxBlue);
}

/******************************************************************************
 * Local Functions
 *****************************************************************************/
