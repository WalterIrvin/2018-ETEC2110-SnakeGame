/*
Name: Walter Irvin
Class: ETEC2110 Systems Programming
Section: 51
Date: 4/20/18
Assignment: Lab9 Program 2 (Snake Game)
file name: snake
*/
#include "lab9.2.hpp"
Segment::Segment(int a, int b, int c, int d, int e)
{
    x=a;
    y=b;
    size=c;
    velx=d;
    vely=e;
}
Snake::Snake(int s)
{
    int i;
    length = 1;
    alive = 1;
    for(i = 0; i < length; i++)
    {
        Segment temp((length * s) - (i * s),0,s,1,0);
        snake_bits.push_back(temp);
    }


}
void Snake::slither(int dx, int dy)
{
    /*
    This function will move the snake via placing all later squares at the old positions of the earlier ones
    only the head of the snake has free will to move to a new spot, all other squares must move to old spots.
    snakes cannot move in diagonals, so either dx or dy is guarenteed to be 1 or 0 or -1, but not both.
    */
    int i;
    vector<Segment> backup_bits = snake_bits;
    for(i = 0; i < snake_bits.size(); i++)
    {
        if(i == 0)
        {
            snake_bits[i].x += snake_bits[i].velx * snake_bits[i].size;
            snake_bits[i].y += snake_bits[i].vely * snake_bits[i].size;
            snake_bits[i].velx = dx;
            snake_bits[i].vely = dy;
        }
        if(i != 0)
        {
            snake_bits[i].x = backup_bits[i-1].x;
            snake_bits[i].y = backup_bits[i-1].y;
            snake_bits[i].velx = backup_bits[i-1].velx;
            snake_bits[i].vely = backup_bits[i-1].vely;
        }
    }
}
void Snake::append()
{
    int x, y, size, dx, dy, last;
    last = snake_bits.size() - 1;
    dx = snake_bits[last].velx;
    dy = snake_bits[last].vely;
    size = snake_bits[last].size;
    x = snake_bits[last].x - (dx * size);
    y = snake_bits[last].y - (dy * size);
    Segment temp(x,y,size,dx,dy);
    snake_bits.push_back(temp);
    length += 1;
}
void Snake::intersect(int max_x, int max_y)
{
    int i, j;
    for(i = 0; i < snake_bits.size(); i++)
    {
        for(j = 0; j < snake_bits.size(); j++)
        {
            if(snake_bits[j].x < 0 || snake_bits[j].y < 0)// checks if  is out of bounds
            {
                alive = 0;
                return;
            }
            if(snake_bits[j].x >= max_x|| snake_bits[j].y >= max_y)
            {
                alive = 0;
                return;
            }
            if((i != j) && (snake_bits[i].x == snake_bits[j].x))
            {
                if(snake_bits[i].y == snake_bits[j].y)
                {
                    alive = 0;
                    return;
                }
            }
        }
    }
}
