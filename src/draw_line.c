#include "../fonction_math.h"

void    drawLine(int x0, int y0, int x1, int y1, int c, t_controller* core)
{
    unsigned int* buff = (unsigned int*)(core->vars->img->addr);
    int dx = x1 - x0;
    int dy = y1 - y0;
    int incX = SGN(dx);
    int incY = SGN(dy);
    dx = ABS(dx);
    dy = ABS(dy);

    if (dy == 0)
    {
        // horizontal line
        for (int x = x0; x != x1 + incX; x += incX)
            buff[y0 * WIDTH + x] = c;
    }
    else if (dx == 0)
    {
        // vertical line
        for (int y = y0; y != y1 + incY; y += incY)
            buff[y * WIDTH + x0] = c;
    }
    else if (dx >= dy)
    {
        // more horizontal than vertical
        int slope = 2 * dy;
        int error = -dx;
        int errorInc = -2 * dx;
        int y = y0;

        for (int x = x0; x != x1 + incX; x += incX)
        {
            buff[y * WIDTH + x] = c;
            error += slope;

            if (error >= 0)
            {
                y += incY;
                error += errorInc;
            }
        }
    }
    else
    {
        // more vertical than horizontal
        int slope = 2 * dx;
        int error = -dy;
        int errorInc = -2 * dy;
        int x = x0;

        for (int y = y0; y != y1 + incY; y += incY)
        {
            buff[y * WIDTH + x] = c;
            error += slope;

            if (error >= 0)
            {
                x += incX;
                error += errorInc;
            }
        }
    }
}