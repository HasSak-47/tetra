#pragma once
#ifndef __PIECE_RENDERER_H__
#define __PIECE_RENDERER_H__
#include <piece_data.h>
#include <renderer.h>

class piece_render : public renderee, protected piece_data {
protected:
    void set_rectangles() override;
    

};

#endif