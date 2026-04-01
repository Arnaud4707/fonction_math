#include "../sinus.h"

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
	else if (key == 65362)
		con->vars->f++;
	else if (key == 65364)
		con->vars->f--;
	else if (key == 65451)
		zoom(1, con);
	else if (key == 65453)
		zoom(-1, con);

	if (con->vars->f > 4)
		con->vars->f = 1;
	else if (con->vars->f < 1)
		con->vars->f = 4;

	return(0);
}

void zoom(int a, t_controller* core)
{
	if (a == 1)
	{
		core->vars->greed.y_max *= 1.1;
		core->vars->greed.y_min *= 1.1;
		core->vars->greed.x_max *= 1.1;
		core->vars->greed.x_min *= 1.1;
		core->vars->scale_w *= 1.1;
		core->vars->scale_h *= 1.1;
	}
	else
	{
		core->vars->greed.y_max *= 0.9;
		core->vars->greed.y_min *= 0.9;
		core->vars->greed.x_max *= 0.9;
		core->vars->greed.x_min *= 0.9;
		core->vars->scale_w *= 0.9;
		core->vars->scale_h *= 0.9;
	}
}
