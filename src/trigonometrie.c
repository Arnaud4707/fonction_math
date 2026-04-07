#include "../fonction_math.h"

void	f_sin_x(double x_, double a, double b, double h, double k, t_vars *vars)
{
	double step = 0.01;
	unsigned int *buffer = (unsigned int *)vars->img->addr;

	while (x_ < vars->greed.x_max)
	{
		double y_ = a * sin(b * (x_ - h)) + k;
		// f_link_cercle(x_, y_, con->tars);
		
		int x = (int)((x_ - vars->greed.x_min) * vars->scale_w);
		int y = (int)((vars->greed.y_max - y_) * vars->scale_h);

		if (x >= 0 && x < vars->width && y >= 0 && y < vars->height)
			buffer[y * vars->width + x] = 0x00FF0000;
		x_ += step;
	}
}

void	f_cos_x(double x_, double a, double b, double h, double k, t_vars *vars)
{
	double step = 0.01;
	unsigned int *buffer = (unsigned int *)vars->img->addr;

	while (x_ < vars->greed.x_max)
	{
		double y_ = a * cos(b * (x_ - h)) + k;
		
		int x = (int)((x_ - vars->greed.x_min) * vars->scale_w);
		int y = (int)((vars->greed.y_max - y_) * vars->scale_h);

		if (x >= 0 && x < vars->width && y >= 0 && y < vars->height)
			buffer[y * vars->width + x] = 0x0000FF00;
		x_ += step;
	}
}


void	f_tan_x(double x_, double a, double b, double h, double k, t_vars *vars)
{
	double step = 0.01;
	unsigned int *buffer = (unsigned int *)vars->img->addr;

	while (x_ < vars->greed.x_max)
	{
		double y_ = a *tan( b *(x_ - h)) + k;
		
		int x = (int)((x_ - vars->greed.x_min) * vars->scale_w);
		int y = (int)((vars->greed.y_max - y_) * vars->scale_h);

		if (x >= 0 && x < vars->width && y >= 0 && y < vars->height)
			buffer[y * vars->width + x] = 0x0000FF;
		x_ += step;
	}
}

void f_cercle(double x_, double y_, t_vars* vars)
{
	double step = 0.01;
	unsigned int *buffer = (unsigned int *)vars->img->addr;
	double r = sqrt((x_ * x_) + (y_ * y_));
	double fi = atan2(y_, x_);

	while (fi < M_PI * 2)
	{
		// double y_ = (cos(fi) * x_) + (sin(fi) * y_);
		double x1 = r * cos(fi);
		double y1 = r * sin(fi);
		
		int x = (int)((x1 - vars->greed.x_min) * vars->scale_w);
		int y = (int)((vars->greed.y_max - y1) * vars->scale_h);

		if (x >= 0 && x < vars->width && y >= 0 && y < vars->height)
			buffer[y * vars->width + x] = 0x0000FF;
		fi += step;
	}
}

void f_link_cercle(double x_, double y_, t_vars* vars)
{
	double r = 4;
	unsigned int *buffer = (unsigned int *)vars->img->addr;
	double fi = y_;
	(void)x_;

	double x1 = r * cos(fi);
	double y1 = r * sin(fi);
	
	int x = (int)((x1 - vars->greed.x_min) * vars->scale_w);
	int y = (int)((vars->greed.y_max - y1) * vars->scale_h);

	if (x >= 0 && x < vars->width && y >= 0 && y < vars->height)
		buffer[y * vars->width + x] = 0x0000FF;
}

void f_spirale_archimede(double tour,double a, double b, t_vars* vars)
{
	double step = 0.01;
	unsigned int *buffer = (unsigned int *)vars->img->addr;
	double r = 0;
	double fi = 0;

	while (fi < M_PI * 2 * tour)
	{
		// double y_ = (cos(fi) * x_) + (sin(fi) * y_);
		double x1 = r * cos(fi);
		double y1 = r * sin(fi);
		
		int x = (int)((x1 - vars->greed.x_min) * vars->scale_w);
		int y = (int)((vars->greed.y_max - y1) * vars->scale_h);

		if (x >= 0 && x < vars->width && y >= 0 && y < vars->height)
			buffer[y * vars->width + x] = 0x0000FF;
		fi += step;
		r = a * fi + b;
	}
}

void f_spirale_hyperbolique(double tour,double a, t_vars* vars)
{
	double step = 0.01;
	unsigned int *buffer = (unsigned int *)vars->img->addr;
	double r = 0;
	double fi = 0;

	while (fi < M_PI * 2 * tour)
	{
		// double y_ = (cos(fi) * x_) + (sin(fi) * y_);
		double x1 = r * cos(fi);
		double y1 = r * sin(fi);
		
		int x = (int)((x1 - vars->greed.x_min) * vars->scale_w);
		int y = (int)((vars->greed.y_max - y1) * vars->scale_h);

		if (x >= 0 && x < vars->width && y >= 0 && y < vars->height)
			buffer[y * vars->width + x] = 0x0000FF;
		fi += step;
		r = a / fi;
	}
}

void f_spirale_asymptote(double tour,double a, double b, double c, t_vars* vars)
{
	double step = 0.01;
	unsigned int *buffer = (unsigned int *)vars->img->addr;
	double r = 0;
	double fi = 0;

	while (fi < M_PI * 2 * tour)
	{
		// double y_ = (cos(fi) * x_) + (sin(fi) * y_);
		double x1 = r * cos(fi);
		double y1 = r * sin(fi);
		
		int x = (int)((x1 - vars->greed.x_min) * vars->scale_w);
		int y = (int)((vars->greed.y_max - y1) * vars->scale_h);

		if (x >= 0 && x < vars->width && y >= 0 && y < vars->height)
			buffer[y * vars->width + x] = 0x0000FF;
		fi += step;
		r = a * (fi / (fi + c)) + b;
	}
}

void f_spirale_log(double tour,double a, double b, t_vars* vars)
{
	double step = 0.01;
	unsigned int *buffer = (unsigned int *)vars->img->addr;
	double r = 2;
	double fi = 0;

	while (fi < M_PI * 2 * tour)
	{
		// double y_ = (cos(fi) * x_) + (sin(fi) * y_);
		double x1 = r * cos(fi);
		double y1 = r * sin(fi);
		
		int x = (int)((x1 - vars->greed.x_min) * vars->scale_w);
		int y = (int)((vars->greed.y_max - y1) * vars->scale_h);

		if (x >= 0 && x < vars->width && y >= 0 && y < vars->height)
			buffer[y * vars->width + x] = 0x0000FF;
		fi += step;
		r = a * pow(b, fi);
	}
}
