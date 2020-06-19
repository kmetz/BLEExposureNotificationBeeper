#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include "Tone32.h"


// Pin where the + of an LED is connected.
#define LED_PIN 0

// Pin where the + of a piezo buzzer is connected.
#define BUZZER_PIN 2

// Tone to play.
#define BEEP_NOTE NOTE_C6

// Tone duration in milliseconds.
#define BEEP_DURATION_MS 100

// Scan update time, 5 seems to be a good value.
#define SCAN_TIME_SECONDS 5

// When to forget old senders.
#define FORGET_AFTER_MINUTES 20


BLEScan *scanner;
std::map<std::string, unsigned long> seenNotifiers;


/**
 * Called when a new exposure notifier is seen.
 */
void onNewNotifierFound() {
  Serial.println("BEEP");
  digitalWrite(LED_PIN, HIGH);
  tone(BUZZER_PIN, BEEP_NOTE, BEEP_DURATION_MS, 0);
  digitalWrite(LED_PIN, LOW);
}


class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
  /**
   * Called when a BLE device is discovered.
   */
  void onResult(BLEAdvertisedDevice advertisedDevice) override {
    if (!advertisedDevice.haveServiceUUID()
        || !advertisedDevice.getServiceUUID().equals(BLEUUID((uint16_t) 0xfd6f))
      ) {
      return;
    }

    if (!seenNotifiers.count(advertisedDevice.getAddress().toString())) {
      // New notifier found.
      Serial.printf("+   %s \r\n", advertisedDevice.getAddress().toString().c_str());
      onNewNotifierFound();
    }
    else {
      // We've already seen this one.
      Serial.printf("... %s \r\n", advertisedDevice.getAddress().toString().c_str());
    }

    // Remember, with time.
    seenNotifiers[advertisedDevice.getAddress().toString()] = millis();
  }
};


/**
 * Remove notifiers last seen over FORGET_AFTER_MINUTES ago.
 */
void forgetOldNotifiers() {
  for (auto const &notifier : seenNotifiers) {
    if (notifier.second + (FORGET_AFTER_MINUTES * 60 * 1000) < millis()) {
      Serial.printf("-   %s \r\n", notifier.first.c_str());
      seenNotifiers.erase(notifier.first);
    }
  }
}


void setup() {
  Serial.begin(115200);
  Serial.println("Hi.");

  // Initialize pins.
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Initialize scanner.
  BLEDevice::init("ESP");
  scanner = BLEDevice::getScan();
  scanner->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  scanner->setActiveScan(true); // Active scan uses more power, but gets results faster.
  scanner->setInterval(100);
  scanner->setWindow(99);

  Serial.println("Scanning ...");
}


void loop() {
  Serial.println("-----");

  // Scan.
  scanner->start(SCAN_TIME_SECONDS, false);

  // Cleanup.
  scanner->clearResults();
  forgetOldNotifiers();

  Serial.printf("Count: %d \r\n", seenNotifiers.size());
}
