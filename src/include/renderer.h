#include <SDL.h>
#include <memory>

class renderer{
private:
    std::unique_ptr<SDL_Window, void (*)(SDL_Window*)> m_win;
    std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)> m_ren;
    SDL_Event m_event;

    bool m_close;
    const int m_height, m_width;
protected:
public:
    renderer();
    renderer(const char* name, int width, int height);
    ~renderer();

    renderer(const renderer& other);
    renderer(renderer&& other);

    renderer& operator=(const renderer& other);
    renderer& operator=(renderer&& other);

    void render();
    const bool should_close() const;
};