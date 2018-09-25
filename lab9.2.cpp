/*
Name: Walter Irvin
Class: ETEC2110 Systems Programming
Section: 51
Date: 4/20/18
Assignment: Lab9 Program 2 (Snake Game)
file name: main
*/
#include "lab9.2.hpp"
int done = 0;
int main(int argc, char *argv[])
{
    srand(time(NULL));
    int size = 50;
    int p_pressed = 0;
    int eaten = 0;
    int dx, dy;
    dx = 1;
    dy = 0;
    int a_pressed, s_pressed, d_pressed, w_pressed;
    int paused = 0;
    int SCREEN_WIDTH = 700;
    int SCREEN_HEIGHT = 700;
    SDL_Renderer * renderer = NULL;
    SDL_Window* window = NULL;
    time_t stime = clock();
    time_t dtime;
    //Initialize SDL
    if(TTF_Init()==-1) {
            printf("TTF_Init: %s\n", TTF_GetError());
            exit(2);
        }
        TTF_Font *font;
        font = TTF_OpenFont("font.ttf", 16);
        if(!font) {
            printf("TTF_OpenFont: %s\n", TTF_GetError());
            // handle error
        }
    if( SDL_Init(SDL_INIT_VIDEO) < 0 )
    {
        printf( "SDL not initialized. SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
        //Initialize window

        window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        SDL_Color color = {255,255,255};
        SDL_Surface *text_surface;
        //SDL_Surface* screenSurface = SDL_GetWindowSurface(window);
        renderer = SDL_CreateRenderer(window, 0, 0);
        if(renderer == NULL)
        {
            printf( "SDL_Error: %s\n", SDL_GetError() );
            return 1;
        }

        if( window == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }
        else
        {
            SDL_Surface * snakesurf = SDL_LoadBMP("snake.bmp");
            SDL_Surface * snakeright = SDL_LoadBMP("snakeright.bmp");
            SDL_Surface * snakeleft = SDL_LoadBMP("snakeleft.bmp");
            SDL_Surface * snakeup = SDL_LoadBMP("snakeup.bmp");
            SDL_Surface * snakedown = SDL_LoadBMP("snakedown.bmp");
            SDL_Surface * applesurf = SDL_LoadBMP("apple.bmp");
            Board mainboard(SCREEN_WIDTH, SCREEN_HEIGHT, 50);
            Snake snake(50);
            Apple apple(SCREEN_WIDTH, SCREEN_HEIGHT, 50, applesurf);
            while(!done)
            {

                SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255);
                if(size < 0)
                {
                    size = 0; // bug checking
                }
                SDL_Event event;
                //Event handling
                const Uint8 *state = SDL_GetKeyboardState(NULL);
                if(state[SDL_SCANCODE_ESCAPE])
                {
                    done = 1;
                }
                if(state[SDL_SCANCODE_W] && w_pressed == 0)
                {
                    w_pressed = 1;
                    dx = 0;
                    dy = -1;
                }
                if(!state[SDL_SCANCODE_W])
                {
                    w_pressed = 0;
                }
                if(state[SDL_SCANCODE_S]&& s_pressed == 0)
                {
                    s_pressed = 1;
                    dx = 0;
                    dy = 1;
                }
                if(!state[SDL_SCANCODE_S])
                {
                    s_pressed = 0;
                }
                if(state[SDL_SCANCODE_A] && a_pressed == 0)
                {
                    a_pressed = 1;
                    dx = -1;
                    dy = 0;
                }
                if(!state[SDL_SCANCODE_A])
                {
                    a_pressed = 0;
                }
                if(state[SDL_SCANCODE_D] && d_pressed == 0)
                {
                    d_pressed = 1;
                    dx = 1;
                    dy = 0;
                }
                if(!state[SDL_SCANCODE_D])
                {
                    d_pressed = 0;
                }
                if(state[SDL_SCANCODE_P] && !p_pressed)
                {
                    p_pressed = 1;
                    paused  = 1 - paused;
                }
                if(!state[SDL_SCANCODE_P])
                {
                    p_pressed = 0;
                }
                while(SDL_PollEvent(&event))
                {
                    switch(event.type)
                    {
                    case SDL_QUIT:
                        done = 1;
                    }
                }
                dtime = clock();
                // DRAW SECTION
                if(!paused)
                {
                   SDL_RenderClear(renderer);
                   mainboard.renderBoard(renderer, snake.snake_bits, apple,snakesurf , snakeright, snakeleft, snakeup, snakedown);
                }

                if(snake.alive == 0)
                {
                    paused = 1;
                    char text[5000];
                    sprintf(text, "Game Over, Score is: %d", snake.length);
                    text_surface = TTF_RenderText_Solid(font, text, color);
                    SDL_Texture* surf_txt =  SDL_CreateTextureFromSurface(renderer, text_surface);
                    SDL_Rect tmp;
                    tmp.x = 0;
                    tmp.y = 0;
                    tmp.w = text_surface->w;
                    tmp.h = text_surface->h;
                    //SDL_RenderFillRect(surf_txt, &tmp);
                    SDL_RenderCopy(renderer, surf_txt, NULL, &tmp);
                    SDL_FreeSurface(text_surface);

                    SDL_RenderPresent(renderer);
                }


                eaten = apple.hit_detect(snake.snake_bits);
                if(eaten)
                {
                    eaten = 0;
                    snake.append();
                    apple.reset(snake.snake_bits);
                }
                //TODO
                if(!paused && (dtime - stime) > 350)
                {
                    //TODO
                    snake.slither(dx, dy);
                    snake.intersect(SCREEN_WIDTH, SCREEN_HEIGHT);

                    stime = clock();
                    dtime = clock();
                }
                if(paused  && (dtime - stime) > 1)
                {
                    stime = clock();
                    dtime = clock();
                }
                SDL_RenderPresent(renderer);
            }
        }
    }
    //Destroy window
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow( window );
    //Quit SDL subsystems
    SDL_Quit();
    return 0;
}

