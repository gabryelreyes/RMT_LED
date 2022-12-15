# RMT_LED
Control of a single addressable LED (WS2812) using the RMT Peripheral of the ESP32

## Table of contents
- [Overview](#overview)
- [Installation](#installation)
- [Quick Start](#quick-start)
- [Issues, Ideas And Bugs](#issues-ideas-and-bugs)
- [License](#license)
- [Contribution](#contribution)


## Overview
This library is created with the intention of controlling an status LED using the RMT Peripheral. This takes care of the timing and the pulses that the addressable LED requires for its communication protocol.

The RMT_LED Class requires only the Number of the Pin where the LED is connected to.

The library provides a number of Presets that can be used and modified by the user: RED, GREEN, BLUE, WHITE and CLEAR. There are also 3 USER_PRESETs which the user can set using the `setPreset` function. 

The user can also set colors using their RGB values. However,using the RGB values (extensively) can have a negative impact on performance, as the data array for the RMT has to be recalculated.

It is possible to set a maximum brightness level (0 - 255) by using the argument in the constructor.

## Installation
Just copy the library into your source files, or if using PlatformIO, add the URL to the Github Repository to your platformio.ini file.

```ini
lib_deps=
    https://github.com/gabryelreyes/RMT_LED.git
```

## Quick Start
```cpp

#include "RMT_LED"

RMT_LED addressableLed(48U);

void setup()
{
    addressableLed.setColor(statusLed.GREEN);
}

```

## Issues, Ideas And Bugs
If you have further ideas or you found some bugs, great! Create a [issue](https://github.com/gabryelreyes/RMT_LED/issues) or if you are able and willing to fix it by yourself, clone the repository and create a pull request.


## License
The whole source code is published under the [MIT license](http://choosealicense.com/licenses/mit/).
Consider the different licenses of the used third party libraries too!

## Contribution
Unless you explicitly state otherwise, any contribution intentionally submitted for inclusion in the work by you, shall be licensed as above, without any additional terms or conditions.