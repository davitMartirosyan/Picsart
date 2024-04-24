#ifndef RENDER_H
#define RENDER_H
#include "tty.h"

void scc( int code);
void *scp(void *ptr);
SDL_Surface* surface_from_file(const char *file);
Font font_load_from_file(SDL_Renderer* renderer, const char* file_path);
void render_char(SDL_Renderer *renderer, Font *font, char c, Vec2f pos, float scale);
void render_text_sized(SDL_Renderer *renderer, Font *font, const char *text, size_t text_size, Vec2f pos, Uint32 color, float scale);
void render_text(SDL_Renderer *renderer, Font *font, const char *text, Vec2f pos, Uint32 color, float scale);

#endif