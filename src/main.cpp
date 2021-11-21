/*
  Tutorial: Moving square
    [x] Step 1: Reorganising the current code.
    [x] Step 2: Draw a green square at the center of the window.
    [x] Step 3: Move the square using the directional keys.
    [x] Step 4: Avoid the square to going off-screen.
    [x] Step 5: Stop the square.
    [x] Step 6: Increase / Decrease the square's step.
    Step 7: Bounce the square when it hits the borders of the window.
*/
#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

// Colors
namespace Colors {
  const SDL_Color BLACK = { 0, 0, 0, SDL_ALPHA_OPAQUE };
  const SDL_Color GREEN = { 0, 255, 0, SDL_ALPHA_OPAQUE };
}

// Graphics
namespace Graphics
{
  struct Screen
  {
    const int WIDTH = 512;
    const int HEIGHT = 284;

    const int center_x = WIDTH / 2;
    const int center_y = HEIGHT / 2;
  };
};

// Game objects
enum SquareState { IDLE, MOVING_UP, MOVING_DOWN, MOVING_LEFT, MOVING_RIGHT };

struct Square
{
  int HEIGHT;
  int WIDTH;
  int x;
  int y;
  SquareState state;
  int step;
};

// Application
struct App
{
  const int DEFAULT_STEP = 2;

  SDL_Window* window;
  SDL_Renderer* renderer;

  Graphics::Screen screen;

  Square square
  {
    32,
    32,
    screen.center_x,
    screen.center_y,
    IDLE,
    DEFAULT_STEP
  };

} app;

// SDL routines

bool InitSDL()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cout << "SDL_Init failed with error: " << SDL_GetError() << std::endl;
    return false;
  }

  return true;
}

// Graphics routines

void ClearScreen(SDL_Renderer* renderer)
{
  SDL_SetRenderDrawColor(renderer, Colors::BLACK.r, Colors::BLACK.g, Colors::BLACK.b, Colors::BLACK.a);
  SDL_RenderClear(renderer);
}

void DrawSquare(int x, int y)
{
  SDL_Rect rect;
  rect.x = x - (app.square.WIDTH / 2);
  rect.y = y - (app.square.HEIGHT / 2);
  rect.w = app.square.WIDTH;
  rect.h = app.square.HEIGHT;

  // Define the green color on the renderer
  SDL_SetRenderDrawColor(app.renderer, Colors::GREEN.r, Colors::GREEN.g, Colors::GREEN.b, Colors::GREEN.a);
  // Ask the renderer to fill our rect with the green color
  SDL_RenderFillRect(app.renderer, &rect);
}

// Application routines

void ShutdownApplication()
{
  if (app.window != nullptr) {
    SDL_DestroyWindow(app.window);
    app.window = nullptr;
  }

  if (app.renderer != nullptr) {
    SDL_DestroyRenderer(app.renderer);
    app.renderer = nullptr;
  }

  SDL_Quit();
}

bool InitApplication()
{
  if (InitSDL() == false )
  {
    ShutdownApplication();
    return false;
  }

  app.window = SDL_CreateWindow(
    "Moving Square (512x284)",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    app.screen.WIDTH,
    app.screen.HEIGHT,
    SDL_WINDOW_OPENGL
  );

  if (app.window == nullptr) {
    std::cout << "Unable to crete the main window. Erro: " << SDL_GetError() << std::endl;
    ShutdownApplication();
    return false;
  }

  app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_PRESENTVSYNC);

  return true;
}

void SetState(SquareState new_state)
{
  app.square.state = new_state;
}

void IncreaseStep()
{
  app.square.step = app.square.step * app.DEFAULT_STEP;
}

void DecreaseStep()
{
  int new_step = app.square.step / app.DEFAULT_STEP;
  if (new_step > app.DEFAULT_STEP)
  {
    app.square.step = new_step;
  }
  else
  {
    app.square.step = app.DEFAULT_STEP;
  }
}

int main(int argc, char *argv[])
{
  if (InitApplication() == false)
  {
    ShutdownApplication();
    return EXIT_FAILURE;
  }

  // Draw loop
  SDL_Event event;
  bool running = true;

  while(running)
  {
    ClearScreen(app.renderer);

    // Check the square's state
    switch (app.square.state)
    {
      case MOVING_UP:
      {
        int new_y = app.square.y - app.square.step;
        if (new_y > (app.square.HEIGHT / 2))
        {
          app.square.y = app.square.y - app.square.step;
        }
        else
        {
          app.square.y = (app.square.HEIGHT / 2);
          SetState(MOVING_DOWN);
        }

        break;
      }
      case MOVING_DOWN:
      {
        int new_y = app.square.y + app.square.step;
        if (new_y + (app.square.HEIGHT / 2) < app.screen.HEIGHT)
        {
          app.square.y = app.square.y + app.square.step;
        }
        else
        {
          app.square.y = new_y - (new_y + (app.square.HEIGHT / 2) - app.screen.HEIGHT);
          SetState(MOVING_UP);
        }

        break;
      }
      case MOVING_LEFT:
      {
        int new_top_left_x = app.square.x - app.square.step - (app.square.WIDTH / 2);
        if (new_top_left_x > app.square.step)
        {
          app.square.x = app.square.x - app.square.step;
        }
        else
        {
          app.square.x = (app.square.WIDTH / 2);
          SetState(MOVING_RIGHT);
        }

        break;
      }
      case MOVING_RIGHT:
      {
        int new_top_left_x = app.square.x + app.square.step;
        if (new_top_left_x + (app.square.WIDTH / 2) <= app.screen.WIDTH)
        {
          app.square.x = app.square.x + app.square.step;
        }
        else
        {
          SetState(MOVING_LEFT);
        }

        break;
      }
      default:
        break;
    }

    // Check and process I/O events
    if (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
        case SDL_KEYDOWN:
        {
          running = event.key.keysym.scancode != SDL_SCANCODE_ESCAPE;

          if (event.key.keysym.scancode == SDL_SCANCODE_UP)
          {
            SetState(MOVING_UP);
          }

          if (event.key.keysym.scancode == SDL_SCANCODE_DOWN)
          {
            SetState(MOVING_DOWN);
          }

          if (event.key.keysym.scancode == SDL_SCANCODE_LEFT)
          {
            SetState(MOVING_LEFT);
          }

          if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
          {
            SetState(MOVING_RIGHT);
          }

          if (event.key.keysym.scancode == SDL_SCANCODE_S)
          {
            SetState(IDLE);
          }

          if (event.key.keysym.scancode == SDL_SCANCODE_I)
          {
            IncreaseStep();
          }

          if (event.key.keysym.scancode == SDL_SCANCODE_D)
          {
            DecreaseStep();
          }

          break;
        }
        case SDL_QUIT:
        {
          running = false;
          break;
        }
        default:
          break;
      }
    }

    // Draw the new content on the renderer
    DrawSquare(app.square.x, app.square.y);

    // Update the screen with the content rendered in the background
    SDL_RenderPresent(app.renderer);
  }

  ShutdownApplication();
  return EXIT_SUCCESS;
}