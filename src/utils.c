#include "../sinus.h"

int f_close(t_controller* con)
{
	if (con && con->vars)
	{
		if (con->vars->img && con->vars->img->img)
		{
			mlx_destroy_image(con->mlx, con->vars->img->img);
			free(con->vars->img);
		}
		if (con->vars->win)
			mlx_destroy_window(con->mlx, con->vars->win);
		free(con->vars);
	}
	// if (con)
	// {
	// 	if (con->tars->img && con->tars->img->img)
	// 	{
	// 		mlx_destroy_image(con->mlx, con->tars->img->img);
	// 		free(con->tars->img);
	// 	}
	// 	if (con->tars->win)
	// 	{
	// 		mlx_destroy_window(con->mlx, con->tars->win);
	// 		free(con->tars);
	// 	}
	// }
	if (con->mlx)
		mlx_destroy_display(con->mlx);
	free(con->mlx);

	exit(0);
	return(0);
}

int event_key(int key, t_controller* con)
{
	for (int i = 0; i < con->vars->height; i++){
		for (int j = 0; j < con->vars->width; j++){
			my_mlx_pixel_put(con->vars->img, j, i, 0xAAAAAA);
		}
	}

	printf("%d\n", key);
	if (key == 65307)
		f_close(con);
	else if (key == 97)
		f_tan_x(-20, con->vars);
	else if (key == 65362)
		f_asymptote(-10, 0, 1.25, -1, 0.5, con->vars);
	
	for (int i = 0; i < con->vars->height; i++){

		for (int j = 0; j < con->vars->width; j++){

			if (i == (con->vars->height / 2) || j == (con->vars->width / 2))
				my_mlx_pixel_put(con->vars->img, j, i, 0x00000000);
		}
	}
	mlx_put_image_to_window(con->mlx, con->vars->win, con->vars->img->img, 0, 0);
	return(0);
}

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void vars_init(t_vars *vars, t_controller* control)
{
	vars->width = 1200;
	vars->height = 600;
	vars->greed.x_min = -50;
	vars->greed.x_max = 50;
	vars->greed.y_min = -25;
	vars->greed.y_max = 25;
	vars->greed.scale_x = vars->greed.x_max - vars->greed.x_min;
	vars->greed.scale_y = vars->greed.y_max - vars->greed.y_min;
	vars->scale_h = vars->height / vars->greed.scale_y;
	vars->scale_w = vars->width / vars->greed.scale_x;
	vars->win = mlx_new_window(control->mlx, vars->width, vars->height, "test");
	vars->img = malloc(sizeof(t_data));
	vars->img->img = mlx_new_image(control->mlx, vars->width, vars->height);
	vars->img->addr = mlx_get_data_addr(vars->img->img,
									   &(vars->img->bits_per_pixel), &(vars->img->line_length), &(vars->img->endian));

	for (int i = 0; i < vars->height; i++){
		for (int j = 0; j < vars->width; j++){
			my_mlx_pixel_put(vars->img, j, i, 0xAAAAAA);
		}
	}

	for (int i = 0; i < vars->height; i++){

		for (int j = 0; j < vars->width; j++){

			if (i == (vars->height / 2) || j == (vars->width / 2))
				my_mlx_pixel_put(vars->img, j, i, 0x00000000);
		}
	}
}

void f_ax(double x_, int a, t_vars *vars)
{
	double step = 0.01;
	
	while (x_ < vars->greed.x_max)
	{
		double y_ = x_ * a;

		int x = vars->width / 2 + (int)(vars->scale_w * x_);
		int y = vars->height / 2 - (int)(vars->scale_h * y_);

		if (x >= 0 && x < vars->width && y >= 0 && y < vars->height)
			my_mlx_pixel_put(vars->img, x, y, 0xFF0000);
		x_ += step;
	}
}

void f_ax_plus_b(double x_, double a, double b, t_vars *vars)
{
	double step = 0.01;

	while (x_ < vars->greed.x_max)
	{
		double y_ = x_ * a + b;
		
		int x = vars->width / 2 + (int)(vars->scale_w * x_);
		int y = vars->height / 2 - (int)(vars->scale_h * y_);

		if (x >= 0 && x < vars->width && y >= 0 && y < vars->height)
			my_mlx_pixel_put(vars->img, x, y, 0xFF0000);
		x_ += step;
	}
}

void f_ax2(double x_, double a, t_vars *vars)
{
	double step = 0.01;

	while (x_ < vars->greed.x_max)
	{
		double y_ = a * x_ * x_;
		
		int x = vars->width / 2 + (int)(vars->scale_w * x_);
		int y = vars->height / 2 - (int)(vars->scale_h * y_);

		if (x >= 0 && x < vars->width && y >= 0 && y < vars->height)
			my_mlx_pixel_put(vars->img, x, y, 0xFF0000);
		x_ += step;
	}
}

void f_ax2_puls_bx_plus_c(double x_, double a, double b, double c, t_vars* vars)
{
    double step = 0.01;

	while (x_ < vars->greed.x_max)
	{
		double y_ = (a * x_ * x_) + (b * x_) * c;
		
		int x = vars->width / 2 + (int)(vars->scale_w * x_);
		int y = vars->height / 2 - (int)(vars->scale_h * y_);

		if (x >= 0 && x < vars->width && y >= 0 && y < vars->height)
			my_mlx_pixel_put(vars->img, x, y, 0xFF0000);
		x_ += step;
	}
}

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

void f_ellipse(double x_, double y_, double a, double b, t_vars* vars)
{
	double step = 0.01;
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
			my_mlx_pixel_put(vars->img, x, y, 0x0000FF);
		fi += step;
	}
}

void f_exp_base(double x_, double c, t_vars *vars)
{
	double step = 0.01;

	while (x_ < vars->greed.x_max)
	{
		double y_ = pow(c, x_);
		
		int x = vars->width / 2 + (int)(vars->scale_w * x_);
		int y = vars->height / 2 - (int)(vars->scale_h * y_);

		if (x >= 0 && x < vars->width && y >= 0 && y < vars->height)
			my_mlx_pixel_put(vars->img, x, y, 0x0000FF);
		x_ += step;
	}
}

void f_exp_canon_simple(double x_, double a, double b, double c, t_vars *vars)
{
	double step = 0.01;

	while (x_ < vars->greed.x_max)
	{
		double y_ = a * pow(c, x_ * b);
		
		int x = vars->width / 2 + (int)(vars->scale_w * x_);
		int y = vars->height / 2 - (int)(vars->scale_h * y_);

		if (x >= 0 && x < vars->width && y >= 0 && y < vars->height)
			my_mlx_pixel_put(vars->img, x, y, 0x0000FF);
		x_ += step;
	}
}

void f_exp_canon(double x_, double a, double b, double c, double h, double k, t_vars *vars)
{
	double step = 0.01;

	while (x_ < vars->greed.x_max)
	{
		double y_ = (a * pow(c, (x_ - h) * b)) + k;
		
		int x = vars->width / 2 + (int)(vars->scale_w * x_);
		int y = vars->height / 2 - (int)(vars->scale_h * y_);

		if (x >= 0 && x < vars->width && y >= 0 && y < vars->height)
			my_mlx_pixel_put(vars->img, x, y, 0x0000FF);
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

	while (x_ < vars->greed.x_max)
	{
		double y_ = logbase(x_, c);
		
		int x = vars->width / 2 + (int)(vars->scale_w * x_);
		int y = vars->height / 2 - (int)(vars->scale_h * y_);

		if (x >= 0 && x < vars->width && y >= 0 && y < vars->height)
			my_mlx_pixel_put(vars->img, x, y, 0x00FF00);
		x_ += step;
	}
}

void f_diff_ax(double x_, double a, t_vars *vars)
{
	double step = 0.01;
	
	while (x_ < 50)
	{
		double y_ = a * exp(x_ * a);
		
		int x = vars->width / 2 + (int)(vars->scale_w * x_);
		int y = vars->height / 2 - (int)(vars->scale_h * y_);

		if (x >= 0 && x < vars->width && y >= 0 && y < vars->height)
			my_mlx_pixel_put(vars->img, x, y, 0x00FF00);
		x_ += step;
	}
}

void f_asymptote(double x_, double a, double b, double c, double d, t_vars *vars)
{
	double step = 0.01;

	while (x_ < 10)
	{
		double y_ = (a * x_ + b) / (c * x_ + d);
		
		int x = vars->width / 2 + (int)(vars->scale_w * x_);
		int y = vars->height / 2 - (int)(vars->scale_h * y_);

		if (x >= 0 && x < vars->width && y >= 0 && y < vars->height)
			my_mlx_pixel_put(vars->img, x, y, 0x00FF00);
		x_ += step;
	}
}

void f_clothoide(double x_, double y_, double k, t_vars *vars)
{
	double step = 0.01;
	// double r = sqrt((x_ * x_) + (y_ * y_));
	double t = atan2(y_, x_);
	double x1 = x_;
	double y1 = y_;

	while (t < 10)
	{
		x1 = (k *(cos(t) * (-1 * sin(t))) * x1) + x_;
		y1 = (k *(cos(t) * (sin(t))) * y1) + y_;
		
		int x = vars->width / 2 + (int)(vars->scale_w * x_);
		int y = vars->height / 2 - (int)(vars->scale_h * y_);

		if (x >= 0 && x < vars->width && y >= 0 && y < vars->height)
			my_mlx_pixel_put(vars->img, x, y, 0x0000FF);
		t += step;
	}
}

void f_diff_ax_plus_b(double x_, double a, double b, t_vars *vars)
{
	double step = 0.01;
	
	while (x_ < 50)
	{
		double y_ = a * exp(x_ * a) - (b/ a);
		
		int x = vars->width / 2 + (int)(vars->scale_w * x_);
		int y = vars->height / 2 - (int)(vars->scale_h * y_);

		if (x >= 0 && x < vars->width && y >= 0 && y < vars->height)
			my_mlx_pixel_put(vars->img, x, y, 0x00FF00);
		x_ += step;
	}
}

