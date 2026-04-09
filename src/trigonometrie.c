#include "../fonction_math.h"

void	f_sin_x(double x_, double a, double b, double h, double k, t_vars *vars)
{
	const double step = 0.1;
	unsigned int *buffer = (unsigned int *)vars->img->addr;
	while (x_ < vars->greed.x_max)
	{
		double y_ = a * sin(b *(x_ - h)) + k;
		
		int x = (int)((x_ - vars->greed.x_min) * vars->scale_w);
		int y = (int)((vars->greed.y_max - y_) * vars->scale_h);

		if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
			buffer[y * WIDTH + x] = 0x00FF0000;
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

		if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
			buffer[y * WIDTH + x] = 0x0000FF00;
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

		if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
			buffer[y * WIDTH + x] = 0x0000FF;
		x_ += step;
	}
}
/**
 * @file	trigonometrie.c
 * 
 * @brief	Fonction pour créer un cercle
 * 
 * 	A partir de r et de l'angle (en radian) thita on peut tracer un cercle trigonometrique.
 * 
 * 	x = r * cos(thita)
 * 	y = r * sin(thita)
 * 
 * 	Pour transformer des coordonnées cartésien (x,y) en coordonnées trigonométrique (r, thita),
 * 	on utilise la formule suivente: r = sqrt((x * x) + (y * y)), 
 * 									thita = atan2(y, x)
 * 
 * @param	r		Rayon du cercle, correspond à x quand thita vaut 0.
 * 
 * @param	thita	Angle entre l'axe des abscices et le rayon r au coordonnées y
 */
void f_cercle(double r, double thita, t_vars* vars)
{
	double step = 0.01;
	unsigned int *buffer = (unsigned int *)vars->img->addr;
	// double r = sqrt((x_ * x_) + (y_ * y_));
	// double thita = atan2(y_, x_);

	while (thita < M_PI * 2)
	{
		// double y_ = (cos(thita) * x_) + (sin(thita) * y_);
		double x1 = r * cos(thita);
		double y1 = r * sin(thita);
		
		int x = (int)((x1 - vars->greed.x_min) * vars->scale_w);
		int y = (int)((vars->greed.y_max - y1) * vars->scale_h);

		if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
			buffer[y * WIDTH + x] = 0x0000FF;
		thita += step;
	}
}

void f_link_cercle(double r, double thita, t_vars* vars)
{
	unsigned int *buffer = (unsigned int *)vars->img->addr;

	double x1 = r * cos(thita);
	double y1 = r * sin(thita);
	
	int x = (int)((x1 - vars->greed.x_min) * vars->scale_w);
	int y = (int)((vars->greed.y_max - y1) * vars->scale_h);

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		buffer[y * WIDTH + x] = 0x0000FF;
}

void f_spirale_archimede(double tour,double a, double b, t_vars* vars)
{
	double step = 0.01;
	unsigned int *buffer = (unsigned int *)vars->img->addr;
	double r = 0;
	double thita = 0;

	while (thita < M_PI * 2 * tour)
	{
		// double y_ = (cos(thita) * x_) + (sin(thita) * y_);
		double x1 = r * cos(thita);
		double y1 = r * sin(thita);
		
		int x = (int)((x1 - vars->greed.x_min) * vars->scale_w);
		int y = (int)((vars->greed.y_max - y1) * vars->scale_h);

		if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
			buffer[y * WIDTH + x] = 0x0000FF;
		thita += step;
		r = a * thita + b;
	}
}

void f_spirale_hyperbolique(double tour,double a, t_vars* vars)
{
	double step = 0.01;
	unsigned int *buffer = (unsigned int *)vars->img->addr;
	double r = 0;
	double thita = 0;

	while (thita < M_PI * 2 * tour)
	{
		// double y_ = (cos(thita) * x_) + (sin(thita) * y_);
		double x1 = r * cos(thita);
		double y1 = r * sin(thita);
		
		int x = (int)((x1 - vars->greed.x_min) * vars->scale_w);
		int y = (int)((vars->greed.y_max - y1) * vars->scale_h);

		if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
			buffer[y * WIDTH + x] = 0x0000FF;
		thita += step;
		r = a / thita;
	}
}

void f_spirale_asymptote(double tour,double a, double b, double c, t_vars* vars)
{
	double step = 0.01;
	unsigned int *buffer = (unsigned int *)vars->img->addr;
	double r = 0;
	double thita = 0;

	while (thita < M_PI * 2 * tour)
	{
		// double y_ = (cos(thita) * x_) + (sin(thita) * y_);
		double x1 = r * cos(thita);
		double y1 = r * sin(thita);
		
		int x = (int)((x1 - vars->greed.x_min) * vars->scale_w);
		int y = (int)((vars->greed.y_max - y1) * vars->scale_h);

		if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
			buffer[y * WIDTH + x] = 0x0000FF;
		thita += step;
		r = a * (thita / (thita + c)) + b;
	}
}

void f_spirale_log(double tour,double a, double b, t_vars* vars)
{
	double step = 0.01;
	unsigned int *buffer = (unsigned int *)vars->img->addr;
	double r = 2;
	double thita = 0;

	while (thita < M_PI * 2 * tour)
	{
		// double y_ = (cos(thita) * x_) + (sin(thita) * y_);
		double x1 = r * cos(thita);
		double y1 = r * sin(thita);
		
		int x = (int)((x1 - vars->greed.x_min) * vars->scale_w);
		int y = (int)((vars->greed.y_max - y1) * vars->scale_h);

		if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
			buffer[y * WIDTH + x] = 0x0000FF;
		thita += step;
		r = a * pow(b, thita);
	}
}
