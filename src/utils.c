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


void vars_init(t_vars *vars, t_controller* control)
{
	vars->width = 1200;
	vars->height = 600;
	vars->greed.x_min = -50;
	vars->greed.x_max = 50;
	vars->greed.y_min = -25;
	vars->greed.y_max = 25;
	vars->f = 1;
	vars->greed.scale_x = vars->greed.x_max - vars->greed.x_min;
	vars->greed.scale_y = vars->greed.y_max - vars->greed.y_min;
	vars->scale_h = vars->height / vars->greed.scale_y;
	vars->scale_w = vars->width / vars->greed.scale_x;
	vars->win = mlx_new_window(control->mlx, vars->width, vars->height, "test");
	vars->img = malloc(sizeof(t_data));
	vars->img->img = mlx_new_image(control->mlx, vars->width, vars->height);
	vars->img->addr = mlx_get_data_addr(vars->img->img,
									   &(vars->img->bits_per_pixel), &(vars->img->line_length), &(vars->img->endian));
}
