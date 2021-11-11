#ifndef effect_random_h
#define effect_random_h

class Random {
    private:
        unsigned long timer;

    public:
        HSVColor loop(HSVColor, int);
};

HSVColor Random::loop(HSVColor color, int speed) {
    if(timer + (106 - speed) * 100 > millis()) return color;
    timer = millis();
    color.h = random(360);
    return color;
}

#endif