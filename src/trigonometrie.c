#include "../sinus.h"


void f_sin_x(double x_, t_vars *vars, t_controller* con)
{
	double step = 0.01;

	while (x_ < vars->greed.x_max)
	{
		double y_ = 4.0 *(sin((x_ + (M_PI / 2) * 2)));
		f_link_cercle(x_, y_, con->tars);
		
		int x = vars->width / 2 + (int)(vars->scale_w * x_);
		int y = vars->height / 2 - (int)(vars->scale_h * y_);

		if (x >= 0 && x < vars->width && y >= 0 && y < vars->height)
			my_mlx_pixel_put(vars->img, x, y, 0xFF0000);
		x_ += step;
	}
}

void f_cos_x(double x_, t_vars *vars)
{
	double step = 0.01;

	while (x_ < vars->greed.x_max)
	{
		double y_ = 4.0 *(cos((x_ + (M_PI / 2) * 2)));
		
		int x = vars->width / 2 + (int)(vars->scale_w * x_);
		int y = vars->height / 2 - (int)(vars->scale_h * y_);

		if (x >= 0 && x < vars->width && y >= 0 && y < vars->height)
			my_mlx_pixel_put(vars->img, x, y, 0x0000FF);
		x_ += step;
	}
}


void f_tan_x(double x_, t_vars *vars)
{
	double step = 0.01;

	while (x_ < vars->greed.x_max)
	{
		double y_ = 4.0 *(tan((x_ + (M_PI / 2) * 2)));
		
		int x = vars->width / 2 + (int)(vars->scale_w * x_);
		int y = vars->height / 2 - (int)(vars->scale_h * y_);

		if (x >= 0 && x < vars->width && y >= 0 && y < vars->height)
			my_mlx_pixel_put(vars->img, x, y, 0x0000FF);
		x_ += step;
	}
}

void f_cercle(double x_, double y_, t_vars* vars)
{
	double step = 0.01;
	double r = sqrt((x_ * x_) + (y_ * y_));
	double fi = atan2(y_, x_);

	while (fi < M_PI * 2)
	{
		// double y_ = (cos(fi) * x_) + (sin(fi) * y_);
		double x1 = r * cos(fi);
		double y1 = r * sin(fi);
		
		int x = vars->width / 2 + (int)(vars->scale_w * x1);
		int y = vars->height / 2 - (int)(vars->scale_h * y1);

		if (x >= 0 && x < vars->width && y >= 0 && y < vars->height)
			my_mlx_pixel_put(vars->img, x, y, 0x0000FF);
		fi += step;
	}
}

void f_link_cercle(double x_, double y_, t_vars* vars)
{
	double r = 4;
	double fi = y_;
	(void)x_;

	double x1 = r * cos(fi);
	double y1 = r * sin(fi);
	
	int x = vars->width / 2 + (int)(vars->scale_w * x1);
	int y = vars->height / 2 - (int)(vars->scale_h * y1);

	if (x >= 0 && x < vars->width && y >= 0 && y < vars->height)
		my_mlx_pixel_put(vars->img, x, y, 0x0000FF);
}

void f_spirale_archimede(double tour,double a, double b, t_vars* vars)
{
	double step = 0.01;
	double r = 0;
	double fi = 0;

	while (fi < M_PI * 2 * tour)
	{
		// double y_ = (cos(fi) * x_) + (sin(fi) * y_);
		double x1 = r * cos(fi);
		double y1 = r * sin(fi);
		
		int x = vars->width / 2 + (int)(vars->scale_w * x1);
		int y = vars->height / 2 - (int)(vars->scale_h * y1);

		if (x >= 0 && x < vars->width && y >= 0 && y < vars->height)
			my_mlx_pixel_put(vars->img, x, y, 0x0000FF);
		fi += step;
		r = a * fi + b;
	}
}

void f_spirale_hyperbolique(double tour,double a, t_vars* vars)
{
	double step = 0.01;
	double r = 0;
	double fi = 0;

	while (fi < M_PI * 2 * tour)
	{
		// double y_ = (cos(fi) * x_) + (sin(fi) * y_);
		double x1 = r * cos(fi);
		double y1 = r * sin(fi);
		
		int x = vars->width / 2 + (int)(vars->scale_w * x1);
		int y = vars->height / 2 - (int)(vars->scale_h * y1);

		if (x >= 0 && x < vars->width && y >= 0 && y < vars->height)
			my_mlx_pixel_put(vars->img, x, y, 0x0000FF);
		fi += step;
		r = a / fi;
	}
}

void f_spirale_asymptote(double tour,double a, double b, double c, t_vars* vars)
{
	double step = 0.01;
	double r = 0;
	double fi = 0;

	while (fi < M_PI * 2 * tour)
	{
		// double y_ = (cos(fi) * x_) + (sin(fi) * y_);
		double x1 = r * cos(fi);
		double y1 = r * sin(fi);
		
		int x = vars->width / 2 + (int)(vars->scale_w * x1);
		int y = vars->height / 2 - (int)(vars->scale_h * y1);

		if (x >= 0 && x < vars->width && y >= 0 && y < vars->height)
			my_mlx_pixel_put(vars->img, x, y, 0x0000FF);
		fi += step;
		r = a * (fi / (fi + c)) + b;
	}
}

void f_spirale_log(double tour,double a, double b, t_vars* vars)
{
	double step = 0.01;
	double r = 2;
	double fi = 0;

	while (fi < M_PI * 2 * tour)
	{
		// double y_ = (cos(fi) * x_) + (sin(fi) * y_);
		double x1 = r * cos(fi);
		double y1 = r * sin(fi);
		
		int x = vars->width / 2 + (int)(vars->scale_w * x1);
		int y = vars->height / 2 - (int)(vars->scale_h * y1);

		if (x >= 0 && x < vars->width && y >= 0 && y < vars->height)
			my_mlx_pixel_put(vars->img, x, y, 0x0000FF);
		fi += step;
		r = a * pow(b, fi);
	}
}
