[![PlatformIO](https://github.com/hpsaturn/MultiFuncShield-Library/workflows/PlatformIO/badge.svg)](https://github.com/hpsaturn/MultiFuncShield-Library/actions/) ![ViewCount](https://views.whatilearened.today/views/github/hpsaturn/MultiFuncShield-Library.svg) 

# Multi Function Shield Library

A curated, community-maintained library for the popular Multi Function Shield (buttons, LEDs, displays, sensors, and more).

![Shield](https://raw.githubusercontent.com/hpsaturn/MultiFuncShield-Library/refs/heads/master/images/shield00.jpg)

# Library Features

- Timer configuration
- LED digit display handling (text, int, float)
- Manual LED digits refresh
- LED digit blinks and selection
- Beeper handling (also inverted polarity fix)
- Buttons handling
- Sonar reading feature
- LM35 sensor support
- MPU6050 support
- LED brightness handling

## Extra features

Here some features contributed by the community regarding the original one:

- [x] Reverse Beeper Polarity Support
- [x] Missing digits supported
- [x] Removed warnnings and improved size casts
- [x] Support for Atmega328
- [x] PlatformIO support
- [x] CI Unit tests
- [x] ESP8266 basic support (it has less pins, see branch)
- [x] Fixed conflic issues on ATmega328P (i.e Axiometa SPARK board)

Please see the examples for details.

## PlatformIO full Demo project

Please install first [PlatformIO](http://platformio.org/) open source ecosystem for IoT development compatible with **Arduino** IDE and its command line tools (Windows, MacOs and Linux). Also, you may need to install [git](http://git-scm.com/) in your system.

For run a [complete demo](https://github.com/hpsaturn/mfstimer.git) of this library using PlatformIO, please follow the next steps:

```bash
git clone https://github.com/hpsaturn/mfstimer.git
cd mfstimer
pio run -e uno --target upload
```

This is a [full PlatformIO project](https://github.com/hpsaturn/mfstimer.git) of countdown timer with some improvements than the original sample of this library.

[![Multi Function Shield Library Demo](https://raw.githubusercontent.com/hpsaturn/MultiFuncShield-Library/refs/heads/master/images/mfs_demo_video.jpg)](https://youtu.be/_Wlip01aUAY)

# Credits

- First version by [Hackatronics - Cohesive Computing](http://www.cohesivecomputing.co.uk/hackatronics/arduino-multi-function-shield/) 
- Reverse beeper polarity support by [@partsdept](https://github.com/partsdept)
- Improved digits support by [@hugodopradofernandes](https://github.com/hugodopradofernandes)
- Atmega328 support by [@victor1115](https://github.com/victor1115)
