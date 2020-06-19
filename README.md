# BLE Exposure Notification Beeper

Allows you to build a simple device that beeps and flashes an LED whenever someone using a COVID-19 warning/tracing app that uses [Bluetooth LE Exposure Notifications](https://en.wikipedia.org/wiki/Exposure_Notification), like the german [Corona-Warn-App](https://www.coronawarn.app/en/), is seen nearby.

Notifiers (nearby devices with a warning app) are remembered for 20 minutes so it only beeps for newly detected ones. Note that the IDs will change every 15 minutes or so for privacy reasons, triggering new beeps.

## Build your own
### You need
1. Any ESP32 board (like a WEMOS D32 or TTGO ESP32, preferrably with a LiPo battery controller).
2. A 3V piezo buzzer (other buzzer types might also work).
3. Optionally a LED.
4. Optionally a small 1-cell LiPo battery.
5. A nice case :)

### Wiring

| ESP32 pin | goes to             |
|:----------|:--------------------|
| 0         | LED (+)             |
| 2         | Buzzer (+)          |
| GND       | LED (-), Buzzer (-) |

- Pins can easily be changed in code.

### Flashing the ESP32
- Easiest is to upload the [latest binary](https://github.com/kmetz/BLEExposureNotificationBeeper/releases), using [NodeMCU PyFlasher
](https://github.com/marcelstoer/nodemcu-pyflasher).
- If you have [platform.io](https://platformio.org/platformio-ide) installed, simply open the project and upload.
  - You also need the [arduino-esp32](https://github.com/espressif/arduino-esp32) platform and the [lbernstone/Tone](https://github.com/lbernstone/Tone) library. 
