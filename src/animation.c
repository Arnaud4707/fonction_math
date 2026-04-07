#include "../fonction_math.h"

void    animation_sinus(double x_, double a, double b, double h, double k, t_vars *vars)
{
    double step = 0.01;
	unsigned int *buffer = (unsigned int *)vars->img->addr;
    static double  speed = 0;

	while (x_ < speed)
	{
		double y_ = a * sin(b * (x_ - h)) + k;
		// f_link_cercle(x_, y_, con->tars);
		
		int x = (int)((x_ - vars->greed.x_min) * vars->scale_w);
		int y = (int)((vars->greed.y_max - y_) * vars->scale_h);

		if (x >= 0 && x < vars->width && y >= 0 && y < vars->height)
			buffer[y * vars->width + x] = 0x00FF0000;
		x_ += step;
	}
    speed += 0.05;
}