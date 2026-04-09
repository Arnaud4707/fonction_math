#include "../fonction_math.h"

void vars_init(t_vars *vars, t_controller* core)
{
	vars->width = 1200;
	vars->height = 600;
    // mlx_get_screen_size(core->mlx, &(vars->width), &(vars->height));
	vars->greed.x_min = -50;
	vars->greed.x_max = 50;
	vars->greed.y_min = -25;
	vars->greed.y_max = 25;
	vars->id_fonction = 1;
	vars->nb_fonction = 11;
	vars->greed.scale_x = vars->greed.x_max - vars->greed.x_min;
	vars->greed.scale_y = vars->greed.y_max - vars->greed.y_min;
	vars->scale_h = vars->height / vars->greed.scale_y;
	vars->scale_w = vars->width / vars->greed.scale_x;
	vars->win = mlx_new_window(core->mlx, vars->width, vars->height, "Fonction Mathématique");
	vars->img = malloc(sizeof(t_data));
	vars->img->img = mlx_new_image(core->mlx, vars->width, vars->height);
	vars->img->addr = mlx_get_data_addr(vars->img->img,
		&(vars->img->bpp), &(vars->img->line_length), &(vars->img->endian));
    init_function(core);
}

void    init_function(t_controller* core)
{
    core->vars->fonction.trigo.x = 0;
    core->vars->fonction.trigo.a = 4;
    core->vars->fonction.trigo.b = 0.25;
    core->vars->fonction.trigo.h = 0;
    core->vars->fonction.trigo.k = 0;
	core->vars->fonction.al.a = 1;
	core->vars->fonction.al.b = 1.3;
	core->vars->fonction.al.c = 1;
	core->vars->fonction.al.d = 1;
	core->vars->fonction.test.x0 = 0;
	core->vars->fonction.test.x1 = 100;
	core->vars->fonction.test.y0 = 0;
	core->vars->fonction.test.y1 = 100;
}