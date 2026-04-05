#include "../fonction_math.h"

int event_key(int key, t_controller* core)
{
	for (int i = 0; i < core->vars->height; i++){
		for (int j = 0; j < core->vars->width; j++){
			my_mlx_pixel_put(core->vars->img, j, i, 0xAAAAAA);
		}
	}

	printf("%d\n", key);
	if (key == 65307)
		f_close(core);
	else if (key == 116)
		core->vars->id_fonction++;
	else if (key == 121)
		core->vars->id_fonction--;
	else if (key == 112) //65451
		zoom(1, core);
	else if (key == 109)
		zoom(-1, core);

	if (key >= 65361 && key <= 65364)
		arrow(key, core);

	if ((key == 113 || key == 100 || key == 97 || key == 101 || key == 119
		|| key == 99 || key == 122 || key == 115) && core->vars->id_fonction == 7)
		change_a_in_sin(key, core);

	if (core->vars->id_fonction > core->vars->nb_fonction)
		core->vars->id_fonction = 1;
	else if (core->vars->id_fonction < 1)
		core->vars->id_fonction = core->vars->nb_fonction;

	return(0);
}

void	change_a_in_sin(int key, t_controller* core)
{
	double	step = 0.25;
	if (key == 97)
		core->vars->fonction.sin.a -= step;
	else if (key == 101)
		core->vars->fonction.sin.a += step;
	else if (key == 113)
		core->vars->fonction.sin.b -= step;
	else if (key == 100)
		core->vars->fonction.sin.b += step;
	else if (key == 119)
		core->vars->fonction.sin.h -= step;
	else if (key == 99)
		core->vars->fonction.sin.h += step;
	else if (key == 122)
	{
		core->vars->fonction.sin.k -= step;
		printf("ici\n");
	}
	else if (key == 115)
		core->vars->fonction.sin.k += step;
}

void zoom(int a, t_controller* core)
{
	double cx = (core->vars->greed.x_min + core->vars->greed.x_max) / 2;
	double cy = (core->vars->greed.y_min + core->vars->greed.y_max) / 2;

	double factor = (a == -1) ? 1.1 : 0.9;
	
	core->vars->greed.x_min = cx + (core->vars->greed.x_min - cx) * factor;
	core->vars->greed.x_max = cx + (core->vars->greed.x_max - cx) * factor;

	core->vars->greed.y_min = cy + (core->vars->greed.y_min - cy) * factor;
	core->vars->greed.y_max = cy + (core->vars->greed.y_max - cy) * factor;
	
	core->vars->greed.scale_x = core->vars->greed.x_max - core->vars->greed.x_min;
	core->vars->greed.scale_y = core->vars->greed.y_max - core->vars->greed.y_min;
	double scale = fmin(core->vars->width / core->vars->greed.scale_x,
		 core->vars->height / core->vars->greed.scale_y);
	core->vars->scale_w = scale;
	core->vars->scale_h = scale;
}

void	arrow(int key, t_controller* core)
{
	double step_x = (core->vars->greed.x_max - core->vars->greed.x_min) * 0.05;
	double step_y = (core->vars->greed.y_max - core->vars->greed.y_min) * 0.05;

	if (key == 65361)
		move(-step_x, 0, core->vars);
	else if (key == 65363)
		move(step_x, 0, core->vars);
	else if (key == 65362)
		move(0, step_y, core->vars);
	else if (key == 65364)
		move(0, -step_y, core->vars);
}

void	move(double dx, double dy, t_vars *vars)
{
    vars->greed.x_min += dx;
    vars->greed.x_max += dx;
    vars->greed.y_min += dy;
    vars->greed.y_max += dy;
}
