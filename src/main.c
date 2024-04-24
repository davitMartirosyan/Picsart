#include "tty.h"
#include "render.h"
char buffer[BUFFER_CAPACITY];
size_t buffer_cursor = 0;
size_t buffer_size = 0;

int main( void )
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = scp(SDL_CreateWindow("Picsart", 0, 0, 800, 500, SDL_WINDOW_RESIZABLE));
    SDL_Renderer *renderer = scp(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED));

    Font font = font_load_from_file(renderer, "./fonts/charmap-oldschool_white.png");
    SDL_Surface *font_surface = surface_from_file("./fonts/charmap-oldschool_white.png");
    SDL_Texture *font_texture = SDL_CreateTextureFromSurface(renderer, font_surface);

    bool quit = false;
    while (!quit)
    {
        SDL_Event event = {0};
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                {
                    quit = true;
                }break;
                case SDL_KEYDOWN: {
                        switch(event.key.keysym.sym){
                            case SDLK_BACKSPACE: {
                                if (buffer_size > 0){
                                    buffer_size -= 1;
                                }
                            }
                        }
                }break;
                case SDL_TEXTINPUT:
                {
                    size_t text_size = strlen(event.text.text);
                    const size_t free_space = BUFFER_CAPACITY - buffer_size;
                    if (text_size > free_space){
                        text_size = free_space;
                    }
                    memcpy(buffer + buffer_size, event.text.text, text_size);
                    buffer_size += text_size;
                }break;
            }
        }
        scc(SDL_SetRenderDrawColor(renderer, 0,0,0,0));
        scc(SDL_RenderClear(renderer));

        render_text_sized(renderer, &font, buffer, buffer_size, vec2f(0.0, 0.0), 0xFFFFFFFF, 2.0f);
        SDL_RenderPresent(renderer);
    }
    SDL_Quit(); 
    return (0);
}