#pragma once
#ifndef __RECT_H__
#define __RECT_H__
#include<renderer.h>

class rect : public renderee{
private:
    void set_rectangles() override;
protected:
    vec2i size {};
    vec2i padding {};

    vec2i b_pos = {};
public:

    rect();
    ~rect();

    rect(float x, float y, int w, int h, color c);

    rect(const rect& r) = delete;
    rect(rect&& r);

    rect& operator=(rect&& r);
    vec2i get_padding();
};

#endif