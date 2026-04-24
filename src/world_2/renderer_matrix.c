#include "../../include/fonction_math.h"

t_vect cube[8] = {
    {-1,-1,-1,1}, {1,-1,-1,1},
    {1,1,-1,1},  {-1,1,-1,1},
    {-1,-1,1,1}, {1,-1,1,1},
    {1,1,1,1},   {-1,1,1,1}
};

int render_loop_matrice(void* core_)
{

    struct timeval 	start_tv;
    struct timeval 	end_tv;
	int color[6] = {
	0x00FF0000,
	0x00FF0000,
	0x0000FF00,
	0x0000FF00,
	0x000000FF,
	0x000000FF
};

	(void)color;
	gettimeofday(&start_tv, NULL);
	t_controller* core = (t_controller*)(core_);
	int size = WIDTH * HEIGHT;
    fill_background(core->vars->img, NOIR);
	for (int i = 0; i < size; i++){
    	((float*)core->vars->matrice.zbuffer)[i] = INFINITY;}

	display_cube_triangles(core, cube, color);
	// display_fdf(core);
	gettimeofday(&end_tv, NULL);
	int t = diff_time(&start_tv, &end_tv);
	__int16_t fps = 1000000 / t;
	printf("time of prosses: %d\n", t);
	char buff[20];
	if (t < 20000)
	{
		fps = 1000000 / 20000;
		t = 20000 - t;
	}
	mlx_put_image_to_window(core->mlx, core->vars->win, core->vars->img->img, 0, 0);
	sprintf(buff, "FPS: %d", fps);
	mlx_string_put(core->mlx, core->vars->win, 0, 40, 0x00FFFF00, buff);
	if (core->vars->matrice.mode == 1)
	{
		sprintf(buff, "Isometric Mode");
		mlx_string_put(core->mlx, core->vars->win, 0, 20, 0x00FFFF00, buff);
	}
	else
	{
		sprintf(buff, "3D Mode");
		mlx_string_put(core->mlx, core->vars->win, 0, 20, 0x00FFFF00, buff);
	}
	if (t < 20000)
		usleep(t);
	return (0);
}
