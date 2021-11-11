#ifndef effect_alarm_h
#define effect_alarm_h

class Alarm {
    private:
        unsigned long timer;

    public:
        HSVColor loop(HSVColor, int);
};

HSVColor Alarm::loop(HSVColor color, int speed) {
    if(timer + 50 > millis() && timer + 100 < millis()) return {0, 255, color.v};
    else return {0, 255, 0};
    // return {0, 255, 0};

    if(timer + 2000 > millis()) timer = millis();

}

#endif