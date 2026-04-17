#ifndef GRILLES_H
#define GRILLES_H

#include "struct_fonction.h"

static inline void    grille_orthonorme(t_controller* core)
{
	unsigned int *buffer = (unsigned int *)core->vars->img->addr;

	for (int i = floor(core->vars->greed.x_min); i <= ceil(core->vars->greed.x_max); i++){
		int x = (i - core->vars->greed.x_min) * core->vars->scale_w;
		
		int color = 0X00CCCCCC;
		if (x >= 0 && x < WIDTH)
		{
			if (i == 0)
			{
				color = 0X00000000;
				for (int y = 0; y < HEIGHT; y++){
					buffer[y * WIDTH + x-1] = color;
					buffer[y * WIDTH + x+1] = color;
				}
			}
			else if (i % 5 == 0)
				color = 0X00A0A0A0;
			for (int y = 0; y < HEIGHT; y++)
				buffer[y * WIDTH + x] = color;
		}
	}
	for (int i = floor(core->vars->greed.y_min); i <= ceil(core->vars->greed.y_max); i++){
		int y = (core->vars->greed.y_max - i) * core->vars->scale_h;
		
		if (y >= 0 && y < HEIGHT)
		{
			int color = 0x00CCCCCC;
			if (i == 0)
			{
				color = 0X00000000;
				for (int x = 0; x < WIDTH; x++){
					buffer[(y + 1) * WIDTH + x] = color;
					buffer[(y - 1) * WIDTH + x] = color;
				}
			}
			else if (i % 5 == 0)
				color = 0X00A0A0A0;
			for (int x = 0; x < WIDTH ; x++)
				buffer[y * WIDTH + x] = color;
		}
	}
}

static inline void projection_isometrique(int x, int y, int *sx, int *sy, int cx, int cy, float scale)
{
    *sx = cx + (x - y) * scale;
    *sy = cy + (x + y) * scale / 2;
}

static inline void grille_isometrique(t_controller* core, int color)
{
    int center_x = WIDTH / 2;
    int center_y = HEIGHT / 2;
    float scale = core->vars->scale_w;

    for (int x = core->vars->greed.x_min; x <= core->vars->greed.x_max; x++)
    {
        for (int y = core->vars->greed.y_min; y <= core->vars->greed.y_max; y++)
        {
            int sx ,sy, sx2, sy2, sx3, sy3;

			projection_isometrique(x, y, &sx, &sy, center_x, center_y, scale);
			projection_isometrique(x + 1, y, &sx2, &sy2, center_x, center_y, scale);
			projection_isometrique(x, y + 1, &sx3, &sy3, center_x, center_y, scale);
            if (sx2 >= 0 && sx2 < WIDTH && sy2 >= 0 && sy2 < HEIGHT)
                drawLine(sx, sy, sx2, sy2, color, core);
			if (sx3 >= 0 && sx3 < WIDTH && sy3 >= 0 && sy3 < HEIGHT)
				drawLine(sx, sy, sx3, sy3, color, core);
        }
    }
}

#endif