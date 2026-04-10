#include "../fonction_math.h"

void    animation_sinus(double x_, double a, double b, double h, double k, t_vars *vars)
{
    const double step = 0.01;
	static double	speed = 0;
	unsigned int *buffer = (unsigned int *)vars->img->addr;
	// double p = x_ + (2 * M_PI / b); // attention divison par 0.
	double thita = b * (x_ - h);
	double dp = 2* M_PI;
	

	while (thita < speed)
	{
		double y_ = a * sin(thita) + k;
		f_link_cercle(a, thita, vars);
		
		int x = (int)((x_ - vars->greed.x_min) * vars->scale_w);
		int y = (int)((vars->greed.y_max - y_) * vars->scale_h);

		if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
			buffer[y * WIDTH + x] = 0x00FF0000;
		x_ += step;
		thita = b * (x_ - h);
	}
	speed += 0.02;
	if (speed >= dp)
		speed = 0;
}

void    animation_sinus_concentrique(double a, double r, double thita, t_vars *vars)
{
    double step = 0.01;
	unsigned int *buffer = (unsigned int *)vars->img->addr;
	const double dp = M_PI * 2;
	static double ap = 0;
	static double inc = 0.025;

	while (thita < dp)
	{
		double x1 = (r + ap) * cos(thita);
		double y1 = (r + ap) * sin(thita);
		
		int x = (int)((x1 - vars->greed.x_min) * vars->scale_w);
		int y = (int)((vars->greed.y_max - y1) * vars->scale_h);

		if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
			buffer[y * WIDTH + x] = 0x0000FF;
		thita += step;
	}
	if (ap >= a)
		inc = -0.025;
	else if (ap <= 0)
		inc = 0.025;
	ap += inc;
}