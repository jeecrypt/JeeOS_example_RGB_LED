#ifndef effect_waves_h
#define effect_waves_h

class Waves {
    private:
        unsigned long timer;
        HSVColor color;
        bool up = false;
        uint8_t value = 0;

    public:
        HSVColor loop(HSVColor, int);
};

HSVColor Waves::loop(HSVColor color, int speed) {
    if(timer + ((3 - (speed / 50))) > millis()) return color;
    timer = millis();

    if(up)color.v++;
    else color.v--;

    if(color.v >= 255) up = false;
    if(color.v <= 0) up = true;

    if(color.v == 0){
        color.h = random(360);
    }
    
    return color;
}

#endif