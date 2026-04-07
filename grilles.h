#ifndef GRILLES_H
#define GRILLES_H

#include "fonction_math.h"


static inline	void fill_background(t_data *img, int color, int width, int height)
{
    for (int y = 0; y < height; y++)
    {
        unsigned int *row = (unsigned int *)(img->addr + y * img->line_length);
        
        for (int x = 0; x < width; x++)
            row[x] = color;
    }
}

static inline void    grille_orthonorme(t_controller* core)
{
	unsigned int *buffer = (unsigned int *)core->vars->img->addr;

	for (int i = floor(core->vars->greed.x_min); i <= ceil(core->vars->greed.x_max); i++){
		int x = (i - core->vars->greed.x_min) * core->vars->scale_w;
		
		int color = 0X00CCCCCC;
		if (x >= 0 && x < core->vars->width)
		{
			if (i == 0)
			{
				color = 0X00000000;
				for (int y = 0; y < core->vars->height; y++){
					buffer[y * core->vars->width + x-1] = color;
					buffer[y * core->vars->width + x+1] = color;
				}
			}
			else if (i % 5 == 0)
				color = 0X00A0A0A0;
			for (int y = 0; y < core->vars->height; y++)
				buffer[y * core->vars->width + x] = color;
		}
	}
	for (int i = floor(core->vars->greed.y_min); i <= ceil(core->vars->greed.y_max); i++){
		int y = (core->vars->greed.y_max - i) * core->vars->scale_h;
		
		if (y >= 0 && y < core->vars->height)
		{
			int color = 0x00CCCCCC;
			if (i == 0)
			{
				color = 0X00000000;
				for (int x = 0; x < core->vars->width; x++){
					buffer[(y + 1) * core->vars->width + x] = color;
					buffer[(y - 1) * core->vars->width + x] = color;
				}
			}
			else if (i % 5 == 0)
				color = 0X00A0A0A0;
			for (int x = 0; x < core->vars->width; x++)
				buffer[y * core->vars->width + x] = color;
		}
	}
}

#endif