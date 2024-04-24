#include "tty.h"
#define STB_IMAGE_IMPLEMENTATION
#include "./stb_image.h"
void scc( int code)
{
    if (code < 0)
    {
        fprintf(stderr, "SDL eroor: %s\n", SDL_GetError());
        exit(1);
    }
}

void *scp(void *ptr)
{
    if (ptr == NULL)
    {
        fprintf(stderr, "SDL error: %s\n", SDL_GetError());
        exit(1);
    }
    return (ptr);
}

SDL_Surface* surface_from_file(const char *file)
{
    int w, h, n;;
    unsigned char *pixels = stbi_load(file, &w, &h, &n, STBI_rgb_alpha);
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        const Uint32 rmask = 0xff000000;
        const Uint32 gmask = 0x00ff0000;
        const Uint32 bmask = 0x0000ff00;
        const Uint32 amask = 0x000000ff;
    #else
        const Uint32 rmask = 0x000000ff;
        const Uint32 gmask = 0x0000ff00;
        const Uint32 bmask = 0x00ff0000;
        const Uint32 amask = 0xff000000;
    #endif

     const int depth = 32, pitch = 4*w;
    return (scp(SDL_CreateRGBSurfaceFrom((void *)pixels, w, h, depth, pitch, rmask, gmask, bmask, amask)));
}

Font font_load_from_file(SDL_Renderer* renderer, const char* file_path)
{
    Font font = {0};
    SDL_Surface *font_surface = surface_from_file(file_path);
    font.spritesheet = scp(SDL_CreateTextureFromSurface(renderer, font_surface));
    SDL_FreeSurface(font_surface);
    for(size_t ascii = ASCII_DISPLAY_LOW; ascii <= ASCII_DISPLAY_HIGH; ++ascii)
    {
        const size_t index = ascii - ASCII_DISPLAY_LOW;
        const size_t col = index % FONT_COLS;
        const size_t row = index / FONT_COLS;

        font.glyph_table[index] = (SDL_Rect){
            .x = col * FONT_CHAR_WIDTH,
            .y = row * FONT_CHAR_HEIGHT,
            .w = FONT_CHAR_WIDTH,
            .h = FONT_CHAR_HEIGHT,
        };
    }
    return (font);
}

void render_char(SDL_Renderer *renderer, Font *font, char c, Vec2f pos, float scale)
{
    const SDL_Rect dst = {
        .x = (int)floorf(pos.x),
        .y = (int)floorf(pos.y),
        .w = (int)floorf(FONT_CHAR_WIDTH * scale),
        .h = (int)floorf(FONT_CHAR_HEIGHT * scale),
    };
    assert(c >= ASCII_DISPLAY_LOW);
    assert(c <=  ASCII_DISPLAY_HIGH);
    const size_t index = c - ASCII_DISPLAY_LOW;
    scc(SDL_RenderCopy(renderer, font->spritesheet, &font->glyph_table[index], &dst));
}



void render_text_sized(SDL_Renderer *renderer, Font *font, const char *text, size_t text_size, Vec2f pos, Uint32 color, float scale)
{
    size_t n = strlen(text);
    scc(SDL_SetTextureColorMod(
        font->spritesheet,
        (color >> (8 * 0)) & 0xff,
        (color >> (8 * 1)) & 0xff,
        (color >> (8 * 2)) & 0xff)); 
    scc(SDL_SetTextureAlphaMod(font->spritesheet, (color >> (8 * 3)) & 0xff));

    Vec2f pen = pos;
    for(size_t i = 0; i < text_size; ++i)
    {
        render_char(renderer, font, text[i], pen, scale);
        pen.x += FONT_CHAR_WIDTH * scale;
    }
}

void render_text(SDL_Renderer *renderer, Font *font, const char *text, Vec2f pos, Uint32 color, float scale)
{
    render_text_sized(renderer, font, text, strlen(text), pos, color, scale);
}
