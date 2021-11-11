#ifndef effect_noise_h
#define effect_noise_h

class Noise {
    private:
        int hue;
        int next_hue;
        unsigned long timer;

    public:
        HSVColor loop(HSVColor, int);
};

HSVColor Noise::loop(HSVColor color, int speed) {

    if(timer + (12 - (speed / 10)) > millis()) return color;
    timer = millis();

    if(hue < next_hue) hue++;
    if(hue > next_hue) hue--;
    if(hue == next_hue) next_hue = random(360);
    
    return (HSVColor){
        h: hue,
        s: color.s,
        v: color.v
    };
}

#endif