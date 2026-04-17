#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "struct_fonction.h"

static inline	void fill_background(t_data *img, int color)
{
	int pixel_len = HEIGHT * WIDTH;
	int i = 0;
	for (; i < pixel_len - 4; i += 4){
		((int *)img->addr)[i] = color;
		((int *)img->addr)[i + 1] = color;
		((int *)img->addr)[i + 2] = color;
		((int *)img->addr)[i + 3] = color;
	}
	for (; i < pixel_len; i++)
		((int *)img->addr)[i] = color;
    // for (int y = 0; y < height; y++)
    // {
    //     unsigned int *row = (unsigned int *)(img->addr + y * img->line_length);
        
    //     for (int x = 0; x < WIDTH; x++)
    //         row[x] = color;
    // }
}

static inline void	background_sinus(double x_, double a, double b, double h, double k, int c, t_vars *vars)
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
			buffer[y * vars->width + x] = c;
            if ((x + 1) >= 0 && (x + 1 < vars->width))
			    buffer[y * vars->width + (x + 1)] = c;
            if ((y + 1) >= 0 && (y + 1 < vars->height))
			    buffer[(y + 1) * vars->width + x] = c;
            if ((x + 1) >= 0 && (x + 1 < vars->width && (y + 1) >= 0 && (y + 1) < vars->height))
			    buffer[(y + 1) * vars->width + (x + 1)] = c;
        }
		x_ += step;
	}
    def += 0.005;
    if (def >= x_)
        def -= x_;
}

static inline void    background_sinus_concentrique(double a, double r, double thita, int color, t_vars *vars)
{
    double step = 0.05;
	unsigned int *buffer = (unsigned int *)vars->img->addr;
	const double dp = M_PI * 2;
	static double ap = 0;
	static double inc = 0.0025;

	while (thita < dp)
	{
		double x1 = (r + ap) * cos(thita);
		double y1 = (r + ap) * sin(thita);
		
		int x = (int)((x1 - vars->greed.x_min) * vars->scale_w);
		int y = (int)((vars->greed.y_max - y1) * vars->scale_h);

		if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
			buffer[y * WIDTH + x] = color;
		thita += step;
	}
	// if (ap >= a)
	// 	inc = -0.0025;
	// else if (ap <= 0)
	// 	inc = 0.0025;
	if (ap >= a)
		ap -= a;
	ap += inc;
}

// static inline void    background_sinus_concentrique(double a, double r, double thita, t_vars *vars)
// {
//     double step = 0.1;
// 	unsigned int *buffer = (unsigned int *)vars->img->addr;
// 	const double dp = M_PI * 2;
// 	static double ap = 0;
// 	static double inc = 0.025;

// 	while (thita < dp)
// 	{
// 		double x1 = (r + ap) * cos(thita);
// 		double y1 = (r + ap) * sin(thita);
		
// 		int x = (int)((x1 - vars->greed.x_min) * vars->scale_w);
// 		int y = (int)((vars->greed.y_max - y1) * vars->scale_h);

// 		if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
// 			buffer[y * WIDTH + x] = 0x0000FF;
// 		thita += step;
// 	}
// 	if (ap >= a)
// 		inc = -0.025;
// 	else if (ap <= 0)
// 		inc = 0.025;
// 	ap += inc;
// }

#endif