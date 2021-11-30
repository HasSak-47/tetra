#include <renderer.h>
#include <complex.h>

class piece{
private:
    uint32_t speed = 250;
    complexi mass_center = {0, 0};
    size_t type = 0;

    enum dir_m{
        left = -1,
        right  = 1
    };

    enum class keys {
        right = SDL_KeyCode::SDLK_RIGHT,
        left = SDL_KeyCode::SDLK_LEFT,
        r_left = SDL_KeyCode::SDLK_UP,
        r_right = SDL_KeyCode::SDLK_DOWN,
        down = SDL_KeyCode::SDLK_SPACE
    };

    void rotate(complexi rotator);
    void move(dir_m move);
    void evaluate_down();

public:
    static const color l_color,s_color,z_color,t_color,j_color,i_color;
    
    color c = {0xff, 0xff, 0xff, 0xff};

    complexi center = {4, 14};
    complexi pieces[4] = {
        {-1, 1},
        { 0, 1},
        { 1, 1},
        { 2, 1}
    };
    
    bool input(SDL_Keycode input);
    bool update(uint32_t delta_time);
    friend class renderer;
    friend class board;
};
extern piece falling;
extern const piece tetros[];