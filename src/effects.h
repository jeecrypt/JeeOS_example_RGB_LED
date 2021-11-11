
#include "effects/rainbow.h"
#include "effects/waves.h"
#include "effects/color.h"
#include "effects/random.h"
#include "effects/noise.h"
#include "effects/alarm.h"

class Effects {
private:
    bool start = true; 
    HSVColor color = {255,255,255};
    unsigned long test_timer;
    unsigned long change_timer;
    int effect_num;
    int effect_speed;

    bool test_effect = false;
    int test_saturation = 0;
    int test_brightness = 0;
    int test_s = 0;
    int test_v = 0;

    int fill_effect_hue = -1;
    int effect_brightness = -1;
    int effect_saturation = -1;

    int next_fill_effect_hue;
    int next_effect_brightness;
    int next_effect_saturation;

    int night_brightness = 100;
    bool night_mode = false;

    int brightness_calculate(int);
    int saturation_calculate(int);

    Rainbow rainbow;
    Waves waves;
    Color fillcolor;
    Random random;
    Noise noise;
    Alarm alarm;

public:
    void fill_hue(int);
    void speed(int);
    void saturation(int);
    void brightness(int);
    void nightBrightness(int);
    void nightMode(bool);
    void effect(int);
    void test();
    void loop();
};

void Effects::test(){
    if(test_effect) return;
    test_timer = millis();
    test_effect = true;
    test_saturation = effect_saturation;
    test_brightness = effect_brightness;
    next_effect_saturation = 0;
    next_effect_brightness = 255;
    test_s = color.s;
    test_v = color.v;
}

void Effects::fill_hue(int v){
    next_fill_effect_hue = v;
}

void Effects::saturation(int v){
    next_effect_saturation = v;
}

void Effects::brightness(int v){
    next_effect_brightness = v;
}

void Effects::nightBrightness(int v){
    night_brightness = v;
}

void Effects::nightMode(bool v){
    night_mode = v;
}

void Effects::speed(int v){
    effect_speed = v;
}

void Effects::effect(int v){
    effect_num = v;
}

int Effects::brightness_calculate(int v){
    double double_brightness = v;
    double double_brightness_current = color.v;
    double result = double_brightness_current / 255 * double_brightness;
    if(night_mode){
        result = (result / (double) 100) * (double) night_brightness;
    }
    return result;
}

int Effects::saturation_calculate(int v){
    double double_saturation = v;
    double double_saturation_current = color.s;
    return double_saturation_current / 255 * double_saturation;
}

void Effects::loop(){

    if(change_timer + (test_effect ? 0 : 3) < millis()){
        change_timer = millis();

        if(test_effect && effect_saturation == next_effect_saturation && effect_brightness == next_effect_brightness){
            if(test_timer + 1500 < millis()){
                next_effect_saturation = test_saturation;
                next_effect_brightness = test_brightness;
                
            }
        }

        if(test_timer + 3000 < millis() && test_effect){
            test_effect = false;
        }

        if(effect_saturation == next_effect_saturation){
            if(effect_brightness < next_effect_brightness) effect_brightness++;
            if(effect_brightness > next_effect_brightness) effect_brightness--;
        }

        if(effect_saturation < next_effect_saturation) effect_saturation++;
        if(effect_saturation > next_effect_saturation) effect_saturation--;

        if(fill_effect_hue < next_fill_effect_hue) fill_effect_hue++;
        if(fill_effect_hue > next_fill_effect_hue) fill_effect_hue--;

        if(effect_num != 4 || effect_num != 5 || test_effect){
            if(effect_brightness < color.v) color.v--;
            if(effect_brightness > color.v) color.v++;
        }

    }

    switch (effect_num) {
        case 0:
            color = fillcolor.loop({fill_effect_hue, color.s, color.v});
            break;
        case 1:
            color = rainbow.loop(color, effect_speed);
            break;
        case 2:
            color = noise.loop(color, effect_speed);
            break;
        case 3:
            color = random.loop(color, effect_speed);
            break;
        case 4:
            color = waves.loop(color, effect_speed);
            break;
        case 5:
            color = alarm.loop(color, effect_speed);
            break;
        
        default:
            break;
    }

    HSVColor final_color = (HSVColor){
        h: color.h,
        s: saturation_calculate(effect_saturation),
        v: brightness_calculate(effect_brightness)
    };

    jeeOS.drivers.rgbLed.values(final_color);
    
}