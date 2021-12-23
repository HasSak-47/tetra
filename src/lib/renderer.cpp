#include <renderer.h>
#include <thread>

static vec2i set_unit(vec2i& screen_size){
    return {screen_size.x / 24, screen_size.y / 18};
}

renderer::renderer() : m_win(nullptr, &SDL_DestroyWindow), m_ren(nullptr, &SDL_DestroyRenderer){}

renderer::renderer(const char* name, int width, int height): 
    m_win( SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0), &SDL_DestroyWindow),
    m_ren( SDL_CreateRenderer(m_win.get(), -1, 0), &SDL_DestroyRenderer),
    m_dimention(width, height),
    m_unit(set_unit(m_dimention)),
    m_unit_dimention(24 , 18)
    {
    ended = promise_end.get_future();
}

renderer::~renderer() {}

void renderer::render() {
    std::cout << "render thread: " << std::this_thread::get_id() << '\n';
    {
        std::lock_guard<std::mutex> lock(render_mutex);
        rendering = true;
        this->ended_render.notify_all();
    }
    while(!m_close){
        //in this part it locks the render_mutex and starts rendering the scene
        //since lock_guard only unlocks when unscoped I created this
        uint32_t start = SDL_GetTicks();
        {
            std::lock_guard<std::mutex> lock(render_mutex);
            rendering = true;
            this->ended_render.notify_all();

        }
        //this is the start time of the rendering process

        //we get the inputs
        SDL_PollEvent(&m_event);
        SDL_SetRenderDrawColor(m_ren.get(), 0x1a, 0x1a, 0x1a, 0x88); //set the background color
        SDL_RenderClear(m_ren.get()); //clear the screen

        if(m_event.type == SDL_QUIT) {
            end_game = true; //set that the game ended 
            m_close = true; //set that the window can close

            std::cout << "Closing window\n";
            rendering = false;
            this->ended_render.notify_all();
            break;
        }

        //this renders each of the renderee objects
        for(auto& renderee : renderees){
            renderee->render();
        }

        SDL_RenderPresent(m_ren.get());
        delta_time = SDL_GetTicks() - start;

        {
            std::lock_guard<std::mutex> lock(render_mutex);
            rendering = false;
            this->ended_render.notify_all();
        }

        while(m_event.type != SDL_QUIT && SDL_GetTicks() - start < 16){
            SDL_PollEvent(&m_event);
            if(m_event.type == SDL_QUIT){
                end_game = true; //set that the game ended 
                m_close = true; //set that the window can close
            }
        }
    }


    std::cout << "setting value\n";
    promise_end.set_value(true);

    std::cout << "Closing rendered window\n";
    rendering = false;
    this->ended_render.notify_all();
}

bool renderer::should_close(){
    return m_event.type == SDL_QUIT;
}

SDL_Event renderer::get_event(){
//    SDL_PollEvent(&m_event);
    return this->m_event;
}

vec2i renderer::get_dimentions(){
    return this->m_dimention;
}

vec2i renderer::get_unit_dimentions(){
    return this->m_unit_dimention;
}


vec2i renderer::get_unit(){
    return this->m_unit;
}

SDL_Renderer* renderer::get_renderer(){
    return m_ren.get();
}

void renderer::wait_for_render(){
    std::unique_lock<std::mutex> ren_lock(ren.render_mutex);
    ren.ended_render.wait(ren_lock, []{return !ren.rendering || end_game;});
}