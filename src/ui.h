

int brightness = 200;
int bgbrightness = 25;
int night_brightness = 70;
bool night_mode = false;

int color_hue = 145;
int bgcolor_hue = 0;

int saturation = 255;
int bgsaturation = 255;

int speed = 70;
int bgspeed = 70;

int effect = 1;
int bgeffect = 2;

int dev_num = 0;
int dev_count = 0;
long delay_time = 1000;
long action_time = 5000;
bool action = false;

bool emergency = true;

int tz;

tm sunrise;
tm sunset;

void ui_callback(){

  jeeOS.ui.page.add({
    label: F("Основное"),
    icon: icon_auto_awesome
  });

  jeeOS.ui.slider.add({
    id: F("brightness"),
    label: F("Яркость"),
    postfix: "",
    min: 0,
    max: 255,
    step: 1,
    value: brightness,
    callback: [](int v){
      brightness = v;
      effects.brightness(v);
    }
  });

  jeeOS.ui.select.add({
    id: F("effect"),
    label: F("Эффект"),
    value: effect,
    items: {
      {F("Цвет"), 0},
			{F("Rainbow"), 1},
			{F("Noise"), 2},
			{F("Random"), 3},
      {F("Waves"), 4},
      {F("Alarm"), 5}
    },
    callback: [](int v){
      effect = v;
      effects.effect(v);
    }
  });

  jeeOS.ui.colorHsvSlider.add({
    id: F("color"),
    label: F("Цвет"),
    value: color_hue,
    callback: [](int v){
      color_hue = v;
      effects.fill_hue(v);
    }
  });
  
  jeeOS.ui.slider.add({
    id: F("sat"),
    label: F("Насыщенность"),
    postfix: "",
    min: 0,
    max: 255,
    step: 1,
    value: saturation,
    callback: [](int v){
      saturation = v;
      effects.saturation(v);
    }
  });

  jeeOS.ui.slider.add({
    id: F("speed"),
    label: F("Скротость эффектов"),
    postfix: "%",
    min: 0,
    max: 100,
    step: 1,
    value: speed,
    callback: [](int v){
      speed = v;
      effects.speed(v);
    }
  });

  jeeOS.ui.page.add({
    label: F("Фон"),
    icon: icon_blur_on
  });

  jeeOS.ui.slider.add({
    id: F("bgbrightness"),
    label: F("Яркость"),
    postfix: "",
    min: 0,
    max: 255,
    step: 1,
    value: bgbrightness,
    callback: [](int v){
      bgbrightness = v;
      bgeffects.brightness(v);
    }
  });

  jeeOS.ui.select.add({
    id: F("bgeffect"),
    label: F("Эффект"),
    value: bgeffect,
    items: {
      {F("Цвет"), 0},
			{F("Rainbow"), 1},
			{F("Noise"), 2},
			{F("Random"), 3},
      {F("Waves"), 4},
      {F("Alarm"), 5}
    },
    callback: [](int v){
      bgeffect = v;
      bgeffects.effect(v);
    }
  });

  jeeOS.ui.colorHsvSlider.add({
    id: F("bgcolor"),
    label: F("Цвет"),
    value: bgcolor_hue,
    callback: [](int v){
      bgcolor_hue = v;
      bgeffects.fill_hue(v);
    }
  });

  jeeOS.ui.slider.add({
    id: F("bg_sat"),
    label: F("Насыщенность"),
    postfix: "",
    min: 0,
    max: 255,
    step: 1,
    value: bgsaturation,
    callback: [](int v){
      bgsaturation = v;
      bgeffects.saturation(v);
    }
  });

  jeeOS.ui.slider.add({
    id: F("bgspeed"),
    label: F("Скротость эффектов"),
    postfix: "%",
    min: 0,
    max: 100,
    step: 1,
    value: bgspeed,
    callback: [](int v){
      bgspeed = v;
      bgeffects.speed(v);
    }
  });

  jeeOS.ui.page.add({
    label: F("Ночной режим"),
    icon: icon_nightlight
  });

  jeeOS.ui.timezone.add({
    id: F("tz"),
    label: F("Часовой пояс"),
    value: tz,
    callback: [](int v){
      tz = v;
      jeeOS.service.time.tz(v);
    }
  });

  jeeOS.ui.time.add({
    id: "sunset",
    label: "Закат",
    type: TIME_mm_hh,
    value: sunset,
    callback: [](tm v){
      sunset = v;
      jeeOS.service.time.event((TimeService::timer_event_update_t){
        id: "sunset",
        time: sunset
      });
    }
  });

  jeeOS.ui.time.add({
    id: "sunrise",
    label: "Рассвет",
    type: TIME_mm_hh,
    value: sunrise,
    callback: [](tm v){
      sunrise = v;
      jeeOS.service.time.event((TimeService::timer_event_update_t){
        id: "sunrise",
        time: sunrise
      });
    }
  });

  jeeOS.ui.slider.add({
    id: F("night_brightness"),
    label: F("Яркость ночью"),
    postfix: "%",
    min: 0,
    max: 100,
    step: 1,
    value: night_brightness,
    callback: [](int v){
      night_brightness = v;
      bgeffects.nightBrightness(night_brightness);
    }
  });

  jeeOS.ui.button.add({
    id: F("night_on"),
    label: F("Включить ночной режим сейчас"),
    icon: icon_refresh,
    color: color_white,
    bgcolor: color_deepPurple,
    callback: [](){
      night_mode = true;
      bgeffects.nightMode(true);
    }
  });

  jeeOS.ui.button.add({
    id: F("night_off"),
    label: F("Отключить ночной режим"),
    icon: icon_refresh,
    color: color_white,
    bgcolor: color_deepPurple,
    callback: [](){
      night_mode = false;
      bgeffects.nightMode(false);
    }
  });

  jeeOS.ui.page.add({
    label: F("Группа"),
    icon: icon_settings_ethernet
  });

  jeeOS.ui.text.add({
    id: F("dev_num"),
    label: F("Номер в группе"),
    lines: 1,
    length: 5,
    value: dev_num,
    callback: [](int v){
      dev_num = v;
    }
  });

  jeeOS.ui.text.add({
    id: F("dev_count"),
    label: F("количество устройств в группе"),
    lines: 1,
    length: 5,
    value: dev_count,
    callback: [](int v){
      dev_count = v;
    }
  });

  jeeOS.ui.slider.add({
    id: F("delay_time"),
    label: F("Задержка перез активацией"),
    postfix: " секунд",
    min: 0,
    max: 5,
    step: .5,
    value: (float)((double)delay_time / 1000),
    callback: [](float v){
      delay_time = v * 1000;
    }
  });

  jeeOS.ui.slider.add({
    id: F("action_time"),
    label: F("Таймаут активности"),
    postfix: " секунд",
    min: 5,
    max: 120,
    step: 5,
    value: (int)(action_time / 1000),
    callback: [](int v){
      action_time = v * 1000;
    }
  });

  jeeOS.ui.onoff.add({
    id: F("emergency"),
    label: F("Режим дежурки"),
    value: emergency,
    callback: [](bool v){
      emergency = v;
    }
  });

  jeeOS.ui.button.add({
    id: F("action"),
    label: F("Активация"),
    icon: icon_refresh,
    color: color_white,
    bgcolor: color_deepPurple,
    callback: [](){
      Serial.println(F("ACTION..."));
    }
  });

  jeeOS.ui.page.add({
    label: F("Служебное"),
    icon: icon_settings
  });

  jeeOS.ui.button.add({
    id: F("test"),
    label: F("Тест"),
    icon: icon_refresh,
    color: color_white,
    bgcolor: color_blue_900,
    callback: [](){
      Serial.println(F("TEST..."));
      bgeffects.test();
      effects.test();
    }
  });

  jeeOS.ui.button.add({
    id: F("reboot"),
    label: F("Перезагрузка"),
    icon: icon_refresh,
    color: color_white,
    bgcolor: color_deepPurple,
    callback: [](){
      Serial.println(F("REBOOT..."));
      ESP.restart();
      delay(5000);
    }
  });
  
  jeeOS.ui.button.add({
    id: F("update"),
    label: F("Обновить прошивку"),
    icon: icon_upgrade,
    color: color_white,
    bgcolor: color_deepPurple_800,
    callback: [](){
      for (int i = 0; i < 255; i++){
        jeeOS.drivers.rgbLed.values(RGBColor{0, 0, i});
        delay(5);
      }
      Serial.println(F("UPGRADE..."));
      jeeOS.service.ota.update();
    }
  });
}