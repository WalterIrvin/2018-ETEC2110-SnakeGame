/*
Name: Walter Irvin
Class: ETEC2110 Systems Programming
Section: 51
Date: 4/20/18
Assignment: Lab9 Program 2 (Snake Game)
file name: header
*/
using namespace std;
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
class Segment
{
    public:
    int x, y, size, velx, vely;
    Segment(int a, int b, int c, int d, int e);
};
class Apple
{
    public:
    int x, y, screen_width, screen_height;
    int size, edible;
    SDL_Surface * appleimg;
    Apple(int max_x, int max_y, int s, SDL_Surface * applesurf);
    SDL_Surface* imgsurf;
    int hit_detect(vector<Segment> snake_bit);
    void reset(vector<Segment> snake_bit);
};
class Board
{
    public:
    SDL_Surface* imgsurf;
    int max_x;
    int max_y;
    int square_size;
    int cols;
    int rows;
    Board(int screen_width, int screen_height, int square_dim);
    void renderBoard(SDL_Renderer * renderer, vector<Segment> snake_bit, Apple apple, SDL_Surface * snakebody, SDL_Surface * snakeright, SDL_Surface *  snakeleft, SDL_Surface *  snakeup, SDL_Surface *  snakedown);
};

class Snake
{
    public:
    int length;
    int alive;
    vector<Segment> snake_bits;
    Snake(int s);
    void slither(int dx, int dy);
    void intersect(int max_x, int max_y);
    void append();
};

