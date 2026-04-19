#include "../../include/fonction_math.h"

int	render_loop_game_of_life(void* core_)
{

    struct timeval start_tv;
    struct timeval end_tv;

	gettimeofday(&start_tv, NULL);
	t_controller* core = (t_controller*)(core_);

	display_map_game_of_life(core);

	gettimeofday(&end_tv, NULL);
	int t = diff_time(&start_tv, &end_tv);
	__int16_t fps = 1000000 / t;
	char buff[20];
	if (t < 20000)
	{
		fps = 1000000 / 20000;
		t = 20000 - t;
	}
	mlx_put_image_to_window(core->mlx, core->vars->win, core->vars->img->img, 0, 0);
	sprintf(buff, "FPS: %d", fps);
	mlx_string_put(core->mlx, core->vars->win, 0, 20, 0x00FFFFFF, buff);
	sprintf(buff, "Generation: %d", core->vars->gol.gen);
	mlx_string_put(core->mlx, core->vars->win, 0, 40, 0x00FFFFFF, buff);
	if (t < 20000)
		usleep(t);
	return (0);
}

int	render_loop_game_of_life_generation(void* core_)
{

    struct timeval start_tv;
    struct timeval end_tv;

	gettimeofday(&start_tv, NULL);
	t_controller* core = (t_controller*)(core_);

	generation_game_of_life(&(core->vars->gol));
	display_map_game_of_life(core);
	if (core->vars->gol.start == 0)
		mlx_loop_hook(core->mlx, render_loop_game_of_life, core);

	gettimeofday(&end_tv, NULL);
	int t = diff_time(&start_tv, &end_tv);
	t = core->vars->gol.fps - t;
	int fps = 0;
	if (t < 0)
		fps = 1000000 / t;
	else	
		fps = 1000000 / core->vars->gol.fps;
	char buff[20];
	sprintf(buff, "Generation: %d", core->vars->gol.gen);
	mlx_put_image_to_window(core->mlx, core->vars->win, core->vars->img->img, 0, 0);
	mlx_string_put(core->mlx, core->vars->win, 0, 40, 0x00FFFFFF, buff);
	sprintf(buff, "FPS: %d", fps);
	mlx_string_put(core->mlx, core->vars->win, 0, 20, 0x00FFFFFF, buff);
	if (t >= 0 && t < core->vars->gol.fps)
		usleep(t);
	core->vars->gol.gen += 1;
	return (0);
}