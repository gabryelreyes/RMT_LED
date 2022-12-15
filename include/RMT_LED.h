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

#ifndef RMT_LED_H_
#define RMT_LED_H_

/******************************************************************************
 * Includes
 *****************************************************************************/

#include <stddef.h>
#include <inttypes.h>
#include "esp32-hal-rmt.h"

/******************************************************************************
 * Macros
 *****************************************************************************/

/******************************************************************************
 * Types and Classes
 *****************************************************************************/

/**
 * Instance of a single LED controlled through the RMT Peripheral
 */
class RMT_LED
{
public:

    /**
     *  Enum of possible presets.
     */
    enum PRESETS : uint8_t
    {
        USER_PRESET_0 = 0,
        USER_PRESET_1,
        USER_PRESET_2,
        RED,
        GREEN,
        BLUE,
        WHITE,
        CLEAR
    };

    /**
     *  RMT LED Constructor
     *  @param[in] ledPin Pin Number of LED
     *  @param[in] maxBrightness Maximum allowed brightness
     */
    RMT_LED(const uint8_t ledPin, const uint8_t maxBrightness = UINT8_MAX);

    /**
     *  Default Destructor
     */
    ~RMT_LED();

    /**
     *  Set a Color using the RGB Values.
     *  @param[in] red Value for Red Channel.
     *  @param[in] green Value for Green Channel.
     *  @param[in] blue Value for Blue Channel.
     */
    void setColor(const uint8_t red, const uint8_t green, const uint8_t blue);

    /**
     *  Set LED Color to preset.
     *  @param[in] presetNumber Preset to be defined (0, 1, or 2)
     */
    void setColor(PRESETS presetNumber);

    /**
     *  Clear the current LED Color. Turn Off the LED.
     */
    void clear();

    /**
     *  Define a preset color.
     *  @param[in] presetNumber Preset to be defined (0, 1, or 2)
     *  @param[in] red Value for Red Channel.
     *  @param[in] green Value for Green Channel.
     *  @param[in] blue Value for Blue Channel.
     */
    void setPreset(PRESETS presetNumber, const uint8_t red, const uint8_t green, const uint8_t blue);

private:

    /**
     *  Send RMT Data Packet to the LED.
     *  @param[in] dataArray Array containing RMT Data for LED.
     *  @return If correctly configured to send, returns true. Otherwise, false.
     */
    bool sendData(rmt_data_t *dataArray);

    /**
     *  Parse the values of the RGB Values into the lower 24 bits of an uint32_t.
     *  @param[in] red Value for Red Channel.
     *  @param[in] green Value for Green Channel.
     *  @param[in] blue Value for Blue Channel.
     *  @return Parsed color value as interger.
    */
    uint32_t parseRgbValue(const uint8_t red, const uint8_t green, const uint8_t blue);

private:

    /**
     *  Instance of the RMT
     */
    rmt_obj_t *m_rmtInstance;

    /**
     *  Brightness Limit.
     *  Default set to 255
     */
    uint8_t m_maxBrightness;

private:

    /**
     *  Default Constructor.
     *  Set to private as it should not be used.
     */
    RMT_LED();

    /**
     *  An instance shall not be copied.
     */
    RMT_LED(const RMT_LED &prot);

    /**
     *  An instance shall not assigned.
     */
    RMT_LED &operator=(const RMT_LED &prot);
};

#endif /* RMT_LED_H_ */