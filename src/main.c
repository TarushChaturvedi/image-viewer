#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>

SDL_Window* window;
SDL_Renderer* renderer;
bool running;

void render(SDL_Texture*, SDL_Rect*);
void handleEvents();

int main(int argc, const char* argv[]) {

  if (argc != 2) {
    fprintf(stderr, "Invalid usage!\n");
    return -1;
  }

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    fprintf(stderr, "SDL_Init() failed, error: %s\n", SDL_GetError());
    return -1;
  }

  if (fopen(argv[1], "r") == NULL) {
    fprintf(stderr, "Failed to open file!\n");
    return -1;
  }

  SDL_Surface* tempSurface = IMG_Load(argv[1]);

  if (tempSurface == NULL) {
    fprintf(stderr, "IMG_Load() failed, error: %s\n", SDL_GetError());
    return -1;
  }

  if(SDL_CreateWindowAndRenderer(tempSurface->w, tempSurface->h, SDL_WINDOW_RESIZABLE | SDL_WINDOW_MOUSE_FOCUS, &window, &renderer) != 0) {
    fprintf(stderr, "SDL_CreateWindowAndRenderer() failed, error: %s\n", SDL_GetError());
    return -1;
  }

  running = true;

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
  SDL_Rect dstRect;
  dstRect.x = 0;
  dstRect.y = 0;
  dstRect.h = tempSurface->h;
  dstRect.w = tempSurface->w;
  SDL_FreeSurface(tempSurface);

  while (running) {
    render(texture, &dstRect);
    handleEvents();
  }

  SDL_Quit();

  return 0;
}

void render(SDL_Texture* texture, SDL_Rect* dstRect) {
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, texture, dstRect, NULL);
  SDL_RenderPresent(renderer);
}

void handleEvents() {
  SDL_Event event;
  SDL_PollEvent(&event);

  switch (event.type) {
    case SDL_QUIT:
      running = false;
      break;
    case SDL_KEYDOWN:
      if (event.key.keysym.scancode == SDL_SCANCODE_Q) {
        running = false;
      }
      break;
    default:
      break;
  }
}
