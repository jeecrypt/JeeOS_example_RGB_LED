#ifndef effect_rainbow_h
#define effect_rainbow_h

class Rainbow {
    private:
        unsigned long timer;
        HSVColor color;

    public:
        HSVColor loop(HSVColor, int);
};

HSVColor Rainbow::loop(HSVColor v, int speed) {
    if(timer + (106 - speed) > millis()) return color;
    timer = millis();
    color = v;
    if(color.h >= 360) color.h = 0;
    color.h += 2;
    return color;
}

#endif