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

static inline void	background_sinus(double x_, double a, double b, double h, double k, t_vars *vars)
{
	double step = 1;
	unsigned int *buffer = (unsigned int *)vars->img->addr;
    static double def = 0;

	while (x_ < vars->greed.x_max)
	{
		double y_ = a * sin(b * (x_ - (h + def))) + k;
		
		int x = (int)((x_ - vars->greed.x_min) * vars->scale_w);
		int y = (int)((vars->greed.y_max - y_) * vars->scale_h);

		if (x >= 0 && x < vars->width && y >= 0 && y < vars->height)
        {
			buffer[y * vars->width + x] = BLEU;
            if ((x + 1) >= 0 && (x + 1 < vars->width))
			    buffer[y * vars->width + (x + 1)] = BLEU;
            if ((y + 1) >= 0 && (y + 1 < vars->height))
			    buffer[(y + 1) * vars->width + x] = BLEU;
            if ((x + 1) >= 0 && (x + 1 < vars->width && (y + 1) >= 0 && (y + 1) < vars->height))
			    buffer[(y + 1) * vars->width + (x + 1)] = BLEU;
        }
		x_ += step;
	}
    def += 0.005;
    if (def >= x_)
        def = 0;
}

#endif