
#include "JeeOS.h"

#if defined (ESP32)
#define PIN_RED 21
#define PIN_GREEN 22
#define PIN_BLUE 3
#define CHIP_NAME "ESP32"
#else
#define PIN_RED 4
#define PIN_GREEN 5
#define PIN_BLUE 3
#define CHIP_NAME "ESP8266"
#endif

void ui_callback();

AppConfig appConfig = {
  name: "JeeOS Example",
  type: DEVICE_TYPE::TYPE_LED,
  subtype: DEVICE_LED_SUBTYPE::LED_SUBTYPE_RGB_STAIRS,
  version_number: 1,
  version_name: "0.0.1",
  ui: ui_callback,
  update_url: "http://files.jeegit.ru/firmwares/jeeos",
  chip: CHIP_NAME
};

JeeOS jeeOS(appConfig);

#include "effects.h"

Effects effects;
Effects bgeffects;

#include "ui.h"

void setup() {
  Serial.begin(115200);
  
  jeeOS.init();

  jeeOS.drivers.rgbLed.init({PIN_RED, PIN_GREEN, PIN_BLUE});
  jeeOS.drivers.rgbLed.setInverse(true);

  Serial.println("night_brightness: " + String(night_brightness));

  jeeOS.service.time.event({
    id: "sunset",
    periodic: PERIODIC_DAY,
    time: sunset,
    callback: [](){
      Serial.println("sunset callback!");
      night_mode = true;
      bgeffects.nightMode(night_mode);
      effects.nightMode(night_mode);
    }
  });

  jeeOS.service.time.event({
    id: "sunrise",
    periodic: PERIODIC_DAY,
    time: sunrise,
    callback: [](){
      Serial.println("sunrise callback!");
      night_mode = false;
      bgeffects.nightMode(night_mode);
      effects.nightMode(night_mode);
    }
  });

  jeeOS.service.buttons.add({
    gpio: 0,
    level: LOW,
    debounce: 50,
    callback: [](){
      Serial.println("Button callback");
      if(effect < 4) effect++;
      else effect = 0;
      effects.effect(effect);

      if(bgeffect < 4) bgeffect++;
      else bgeffect = 0;
      bgeffects.effect(bgeffect);
    },
    lpTimeout: 10000,
    lpCallback: [](){
      Serial.println("Button long press callback");
      jeeOS.service.fs.erase();
    },
  });


  Serial.println("Updated!");
}

void loop() {
  jeeOS.loop();

  if(emergency) bgeffects.loop();
  else effects.loop();

}
