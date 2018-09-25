/*
Name: Walter Irvin
Class: ETEC2110 Systems Programming
Section: 51
Date: 4/20/18
Assignment: Lab9 Program 2 (Snake Game)
file name: apple
*/
#include "lab9.2.hpp"
Apple::Apple(int max_x, int max_y, int s, SDL_Surface * applesurf)
{
    appleimg = applesurf;
    screen_width = max_x;
    screen_height = max_y;
    size = s;
    x = (rand() % screen_width) / s;
    y = (rand() % screen_height) / s;
    x = x * size;
    y = y * size;
    edible = 1; // controls if apple is available to render/ eat.
}
int Apple::hit_detect(vector<Segment> snake_bit)
{
    int i;
    for(i = 0; i < snake_bit.size(); i++)
    {
        if(((snake_bit[i].x == x) && (snake_bit[i].y == y)) && (edible == 1))
        {
            printf("nom\n");
            edible = 0;
            return 1;
        }
    }
    return 0;
}
void Apple::reset(vector<Segment> snake_bit)
{
    int done = 0;
    int i = 0;
    int max_recursion = 10000;
    while(!done || (i < max_recursion))
    {
        x = (rand() % screen_width) / size;
        y = (rand() % screen_height) / size;
        x = x * size;
        y = y * size;
        for(i = 0; i < snake_bit.size(); i++)
        {
            if(!((snake_bit[i].x == x) && (snake_bit[i].y == y)))
            {
                edible = 1;
                return;
            }
        }
        i++;
    }
}
