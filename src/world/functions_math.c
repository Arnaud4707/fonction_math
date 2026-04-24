#include "../../include/fonction_math.h"

void f_ax_plus_b(double x_, double a, double b, t_vars *vars)
{
	double step = 0.01;
	unsigned int* buffer = (unsigned int*)vars->img->addr;

	while (x_ < vars->greed.x_max)
	{
		double y_ = x_ * a + b;
		
		int x = (int)((x_ - vars->greed.x_min) * vars->scale_w);
		int y = (int)((vars->greed.y_max - y_) * vars->scale_h);

		if (x >= 0 && x < vars->width && y >= 0 && y < vars->height)
			buffer[y * vars->width + x] = 0x00FF0000;
		x_ += step;
	}
}

void f_ax2_puls_bx_plus_c(double x_, double a, double b, double c, t_vars* vars)
{
    double step = 0.01;
	unsigned int* buffer = (unsigned int*)vars->img->addr;

	while (x_ < vars->greed.x_max)
	{
		double y_ = (a * x_ * x_) + (b * x_) * c;
		
		int x = (int)((x_ - vars->greed.x_min) * vars->scale_w);
		int y = (int)((vars->greed.y_max - y_) * vars->scale_h);

		if (x >= 0 && x < vars->width && y >= 0 && y < vars->height)
			buffer[y * vars->width + x] = 0x00FF0000;
		x_ += step;
	}
}

void f_ellipse(double x_, double y_, double a, double b, t_vars* vars)
{
	double step = 0.01;
	unsigned int* buffer = (unsigned int*)vars->img->addr;
	double r = sqrt((x_ * x_) + (y_ * y_));
	double fi = atan2(y_, x_);

	while (fi < M_PI * 2)
	{
		// double y_ = (cos(fi) * x_) + (sin(fi) * y_);
		double x1 = r * a * cos(fi);
		double y1 = r * b * sin(fi);
		
		int x = vars->width / 2 + (int)(vars->scale_w * x1);
		int y = vars->height / 2 - (int)(vars->scale_h * y1);

		if (x >= 0 && x < vars->width && y >= 0 && y < vars->height)
			buffer[y * vars->width + x] = 0x000000FF;
		fi += step;
	}
}

void f_a_power_x(double x_, double a, t_vars *vars)
{
	double step = 0.01;
	unsigned int* buffer = (unsigned int*)vars->img->addr;

	while (x_ < vars->greed.x_max)
	{
		double y_ = pow(a, x_);
		
		int x = (int)((x_ - vars->greed.x_min) * vars->scale_w);
		int y = (int)((vars->greed.y_max - y_) * vars->scale_h);

		if (x >= 0 && x < vars->width && y >= 0 && y < vars->height)
			buffer[y * vars->width + x] = 0x000000FF;
		x_ += step;
	}
}

void f_exp_canon_simple(double x_, double a, double b, double c, t_vars *vars)
{
	double step = 0.01;
	unsigned int* buffer = (unsigned int*)vars->img->addr;

	while (x_ < vars->greed.x_max)
	{
		double y_ = a * pow(c, x_ * b);
		
		int x = (int)((x_ - vars->greed.x_min) * vars->scale_w);
		int y = (int)((vars->greed.y_max - y_) * vars->scale_h);

		if (x >= 0 && x < vars->width && y >= 0 && y < vars->height)
			buffer[y * vars->width + x] = 0x000000FF;
		x_ += step;
	}
}

void f_exp_canon(double x_, double a, double b, double c, double h, double k, t_vars *vars)
{
	double step = 0.01;
	unsigned int* buffer = (unsigned int*)vars->img->addr;

	while (x_ < vars->greed.x_max)
	{
		double y_ = (a * pow(c, (x_ - h) * b)) + k;
		
		int x = (int)((x_ - vars->greed.x_min) * vars->scale_w);
		int y = (int)((vars->greed.y_max - y_) * vars->scale_h);

		if (x >= 0 && x < vars->width && y >= 0 && y < vars->height)
			buffer[y * vars->width + x] = 0x000000FF;
		x_ += step;
	}
}

double logbase(double a, double base)
{
   return log(a) / log(base);
}

void f_log_base(double x_, double c, t_vars *vars)
{
	double step = 0.01;
	unsigned int* buffer = (unsigned int*)vars->img->addr;

	while (x_ < vars->greed.x_max)
	{
		double y_ = logbase(x_, c);
		
		int x = (int)((x_ - vars->greed.x_min) * vars->scale_w);
		int y = (int)((vars->greed.y_max - y_) * vars->scale_h);

		if (x >= 0 && x < vars->width && y >= 0 && y < vars->height)
			buffer[y * vars->width + x] = 0x0000FF00;
		x_ += step;
	}
}

void f_diff_ax(double x_, double a, double c, t_vars *vars)
{
	double step = 0.01;
	unsigned int* buffer = (unsigned int*)vars->img->addr;
	
	while (x_ < vars->greed.x_max)
	{
		double y_ = c * exp(x_ * a);
		
		int x = (int)((x_ - vars->greed.x_min) * vars->scale_w);
		int y = (int)((vars->greed.y_max - y_) * vars->scale_h);

		if (x >= 0 && x < vars->width && y >= 0 && y < vars->height)
			buffer[y * vars->width + x] = 0x0000FF00;
		x_ += step;
	}
}

void f_asymptote(double x_, double a, double b, double c, double d, t_vars *vars)
{
	double step = 0.01;
	unsigned int* buffer = (unsigned int*)vars->img->addr;

	while (x_ < 10)
	{
		double y_ = (a * x_ + b) / (c * x_ + d);
		
		int x = (int)((x_ - vars->greed.x_min) * vars->scale_w);
		int y = (int)((vars->greed.y_max - y_) * vars->scale_h);

		if (x >= 0 && x < vars->width && y >= 0 && y < vars->height)
			buffer[y * vars->width + x] = 0x0000FF00;
		x_ += step;
	}
}

void f_diff_ax_plus_b(double x_, double a, double b, double c, t_vars *vars)
{
	double step = 0.01;
	unsigned int* buffer = (unsigned int*)vars->img->addr;
	
	while (x_ < vars->greed.x_max)
	{
		double y_ = c * exp(x_ * a) - (b/ a);
		
		int x = (int)((x_ - vars->greed.x_min) * vars->scale_w);
		int y = (int)((vars->greed.y_max - y_) * vars->scale_h);

		if (x >= 0 && x < vars->width && y >= 0 && y < vars->height)
			buffer[y * vars->width + x] = 0x0000FF00;
		x_ += step;
	}
}


void	f_courbe_besiers_2(double ax, double ay, double bx, double by, t_vars *vars)
{
	unsigned int* buffer = (unsigned int*)vars->img->addr;
	double t = 0;

	while (t < 1.0)
	{
		double x_ = (1 - t) * ax  + (bx * t);
		double y_ = (1 - t) * ay  + (by * t);
		
		int x = (int)((x_ - vars->greed.x_min) * vars->scale_w);
		int y = (int)((vars->greed.y_max - y_) * vars->scale_h);

		if (x >= 0 && x < vars->width && y >= 0 && y < vars->height)
			buffer[y * vars->width + x] = 0x00FF0000;
		t += 0.001;
	}
}

void	f_courbe_besiers_3(double ax, double ay, double bx, double by, double cx, double cy, t_vars *vars)
{
	unsigned int* buffer = (unsigned int*)vars->img->addr;
	double t = 0;

	while (t < 1.0)
	{
		double x_ = ((1 - t) * (1 - t)) * ax  + (2 * t *(1 - t) * bx) + (cx * t * t);
		double y_ = ((1 - t) * (1 - t)) * ay  + (2 * t *(1 - t) * by) + (cy * t * t);
		
		int x = (int)((x_ - vars->greed.x_min) * vars->scale_w);
		int y = (int)((vars->greed.y_max - y_) * vars->scale_h);

		if (x >= 0 && x < vars->width && y >= 0 && y < vars->height)
			buffer[y * vars->width + x] = 0x00FF0000;
		t += 0.0001;
	}

	int x = (int)((bx - vars->greed.x_min) * vars->scale_w);
	int y = (int)((vars->greed.y_max - by) * vars->scale_h);
	for (int j = - 1; j <= 1; j++){
		for (int i = -1; i <= 1; i++){
		if (x + i >= 0 && x + i < vars->width && y + j >= 0 && y + j < vars->height)
			buffer[(y + j) * vars->width + x + i] = 0x000000FF;
		}
	}

}
