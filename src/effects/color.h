#ifndef effect_color_h
#define effect_color_h

class Color {
    private:
        unsigned long timer;
        HSVColor color;

    public:
        HSVColor loop(HSVColor);
};

HSVColor Color::loop(HSVColor v) {
    if(color.h != v.h || color.s != v.s || color.v != v.v){
        color = v;
    }
    return color;
}

#endif