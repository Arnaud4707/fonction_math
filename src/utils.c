#include "../fonction_math.h"

int f_close(t_controller* core)
{
	if (core && core->vars)
	{
		if (core->vars->img && core->vars->img->img)
		{
			mlx_destroy_image(core->mlx, core->vars->img->img);
			free(core->vars->img);
		}
		if (core->vars->win)
			mlx_destroy_window(core->mlx, core->vars->win);
		free(core->vars);
	}
	// if (con)
	// {
	// 	if (core->tars->img && core->tars->img->img)
	// 	{
	// 		mlx_destroy_image(core->mlx, core->tars->img->img);
	// 		free(core->tars->img);
	// 	}
	// 	if (core->tars->win)
	// 	{
	// 		mlx_destroy_window(core->mlx, core->tars->win);
	// 		free(core->tars);
	// 	}
	// }
	if (core->mlx)
		mlx_destroy_display(core->mlx);
	free(core->mlx);

	exit(0);
	return(0);
}

__int64_t		diff_time(struct timeval* st, struct timeval* end)
{
    return(((end->tv_sec - st->tv_sec) * 1000000 + (end->tv_usec - st->tv_usec)));
}
