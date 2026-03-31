#ifndef SINUS_H
#define SINUS_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "../mlx/mlx.h"

#define _USE_MATH_DEFINES
#include <math.h>

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_greed {
	int x_min;
	int x_max;
	int y_min;
	int y_max;
	double scale_x;
	double scale_y;
}	t_greed;

typedef struct s_vars {
	void* win;
	t_data* img;
	int height;
	int width;
	double scale_h;
	double scale_w;
	t_greed greed;
}	t_vars;

typedef struct s_controller{
	void* mlx;
	t_vars* vars;
	t_vars* tars;
}	t_controller;

int		f_close(t_controller *cont);
int		event_key(int key, t_controller* con);

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void 	vars_init(t_vars *vars, t_controller* control);
void 	f_ax(double x, int a, t_vars* vars);
void	f_ax_plus_b(double x_, double a, double b, t_vars* vars);
void	f_sin_x(double x_, t_vars*vars, t_controller* con);
void	f_cos_x(double x_, t_vars *vars);
void	f_tan_x(double x_, t_vars *vars);
void	f_cercle(double x_, double y_, t_vars* vars);
void	f_link_cercle(double x_, double y_, t_vars* vars);
void	f_spirale_archimede(double tour, double a_, double b, t_vars* vars);
void 	f_spirale_log(double tour,double a, double b, t_vars* vars);
void	f_ellipse(double x_, double y_, double a, double b, t_vars* vars);
void	f_spirale_hyperbolique(double tour,double a, t_vars* vars);
void	f_ax2(double x_, double a, t_vars* vars);
void 	f_ax2_puls_bx_plus_c(double x_, double a, double b, double c, t_vars* vars);
void	f_exp_base(double x_, double c, t_vars *vars);
void	f_exp_canon_simple(double x_, double a, double b, double c, t_vars *vars);
void	f_exp_canon(double x_, double a, double b, double c, double h, double k, t_vars *vars);
void	f_log_base(double x_, double c, t_vars *vars);
void	f_asymptote(double x_, double a, double b, double c, double d, t_vars *vars);
void	f_spirale_asymptote(double tour,double a, double b, double c, t_vars* vars);
void	f_diff_ax(double x_, t_vars *vars);
void	f_clothoide(double x_, double y_, double k, t_vars *vars);

#endif