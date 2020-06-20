# BLE Exposure Notification Beeper

Allows you to build a simple device that beeps and flashes an LED whenever someone using a COVID-19 warning/tracing app that uses [Bluetooth LE Exposure Notifications](https://en.wikipedia.org/wiki/Exposure_Notification), like the german [Corona-Warn-App](https://www.coronawarn.app/en/), is seen nearby.

Notifiers (nearby devices with a warning app) are remembered for 20 minutes so it only beeps for newly detected ones. Note that the IDs will change every 15 minutes or so for privacy reasons, triggering new beeps.

## Build your own
### You need
1. Any ESP32 board (like a WEMOS D32 or TTGO ESP32, preferrably with a LiPo battery controller).
2. A 3V piezo buzzer (a simple speaker or headphones will also work).
3. Optionally a LED.
4. Optionally a small 1-cell LiPo battery.
5. A nice case :)

### Wiring

| ESP32 pin | goes to             |
|:----------|:--------------------|
| GPIO 0    | LED (+)             |
| GPIO 2    | Buzzer (+)          |
| GND       | LED (-), Buzzer (-) |

- Pins can easily be changed in code (`src/main.cpp`).

### Flashing the ESP32
If you don't have [PlatfomIO](https://platformio.org/platformio-ide) installed, you can flash precompiled binaries directly with [esptool.py](https://github.com/espressif/esptool).

#### Using PlatfomIO
- Simply open the project and upload.
- Or via command line: `platformio run -t upload`
- You may need to install the [arduino-esp32](https://github.com/espressif/arduino-esp32) platform and the [lbernstone/Tone](https://github.com/lbernstone/Tone) library first. 

#### Using esptool.py
- Install esptool.py: `pip install esptool`
  - On Windows, you might need to [install python](https://www.python.org/downloads/windows/) (2 or 3) first.
- Download the [latest binaries](https://github.com/kmetz/BLEExposureNotificationBeeper/releases).
- `cd` into the directory where the (unzipped) binaries are located.
- Flash using the following command:
```
esptool.py \
--chip esp32 \
--baud 460800 \
--before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size detect \
0x1000 bootloader_dio_40m.bin \
0x8000 partitions.bin \
0xe000 boot_app0.bin \
0x10000 firmware.bin
```
- You may need to define your serial port with something like `--port "/dev/cu.usbserial-0001"` if esptool.py doesn't automatically find it.
- Some ESP32 boards require you to press (and hold) the flash button until flashing begins.
