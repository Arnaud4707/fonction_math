#include "../../include/fonction_math.h"

void	init_function_math(t_controller *core)
{
	core->vars->greed.x_min = -50;
	core->vars->greed.x_max = 50;
	core->vars->greed.y_min = -25;
	core->vars->greed.y_max = 25;
	core->vars->id_fonction = 16;
	core->vars->nb_fonction = 16;
	core->vars->greed.scale_x = core->vars->greed.x_max - core->vars->greed.x_min;
	core->vars->greed.scale_y = core->vars->greed.y_max - core->vars->greed.y_min;
	core->vars->scale_h = core->vars->height / core->vars->greed.scale_y;
	core->vars->scale_w = core->vars->width / core->vars->greed.scale_x;
	core->vars->fonction.trigo.x = 0;
	core->vars->fonction.trigo.a = 4;
	core->vars->fonction.trigo.b = 0;
	core->vars->fonction.trigo.h = 0;
	core->vars->fonction.trigo.k = 0;
	core->vars->fonction.al.a = 1;
	core->vars->fonction.al.b = 1.3;
	core->vars->fonction.al.c = 1;
	core->vars->fonction.al.d = 1;
	core->vars->fonction.besier.ax = 0;
	core->vars->fonction.besier.ay = 0;
	core->vars->fonction.besier.bx = 20;
	core->vars->fonction.besier.by = 20;
	core->vars->fonction.besier.cx = 5;
	core->vars->fonction.besier.cy = 0;

}