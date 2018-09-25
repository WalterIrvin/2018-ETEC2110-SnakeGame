/*
Name: Walter Irvin
Class: ETEC2110 Systems Programming
Section: 51
Date: 4/20/18
Assignment: Lab9 Program 2 (Snake Game)
file name: board
*/
#include "lab9.2.hpp"
//static appleimgsurf;
Board::Board(int screen_width, int screen_height, int square_dim)
{
    max_x = screen_width;
    max_y = screen_height;
    square_size = square_dim;
    cols = max_x / square_size;
    rows = max_y / square_size;
}

 void Board::renderBoard(SDL_Renderer * renderer, vector<Segment> snake_bit, Apple apple, SDL_Surface * snakebody, SDL_Surface * snakeright, SDL_Surface *  snakeleft, SDL_Surface *  snakeup, SDL_Surface *  snakedown)
 {
    int i;
    SDL_Rect tmp;
    SDL_Texture* snake_tex;
    SDL_Texture* apple_tex;
    if(apple.edible)
    {
      apple_tex = SDL_CreateTextureFromSurface(renderer, apple.appleimg);
      tmp.x = apple.x;
      tmp.y = apple.y;
      tmp.w = square_size;
      tmp.h = square_size;
      SDL_RenderCopy(renderer, apple_tex, NULL, &tmp);
      SDL_DestroyTexture(apple_tex);
    }

    for(i = 0; i < snake_bit.size(); i++)
    {
        if(i == 0)
        {
            if(snake_bit[0].velx == 0 && snake_bit[0].vely == 1) // pointing down
            {
                snake_tex =  SDL_CreateTextureFromSurface(renderer, snakedown);
            }
            if(snake_bit[0].velx == 0 && snake_bit[0].vely == -1) // pointing up
            {
                snake_tex =  SDL_CreateTextureFromSurface(renderer, snakeup);
            }
            if(snake_bit[0].velx == -1 && snake_bit[0].vely == 0) // pointing left
            {
                snake_tex =  SDL_CreateTextureFromSurface(renderer, snakeleft);
            }
            if(snake_bit[0].velx == 1 && snake_bit[0].vely == 0) // pointing right
            {
                snake_tex =  SDL_CreateTextureFromSurface(renderer, snakeright);
            }

        }
        else
        {
            snake_tex =  SDL_CreateTextureFromSurface(renderer, snakebody);
        }

        tmp.x = snake_bit[i].x;
        tmp.y = snake_bit[i].y;
        tmp.w = square_size;
        tmp.h = square_size;
        SDL_RenderCopy(renderer, snake_tex, NULL, &tmp);
        SDL_DestroyTexture(snake_tex);
    }
 }
