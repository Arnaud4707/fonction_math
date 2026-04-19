#include "../../include/fonction_math.h"

int 	event_key_game_of_life(int key, t_controller* core)
{
	if (key == 65307)
		f_close(core);
	if (key == 32){
		if (core->vars->gol.start != 0)
		{
			core->vars->gol.start = 0;
			mlx_loop_hook(core->mlx, render_loop_game_of_life, core);
		}
		else
		{
			core->vars->gol.start = core->vars->gol.gen;
			mlx_loop_hook(core->mlx, render_loop_game_of_life_generation, core);
		}
	}
	return(0);
}

int		event_mose_move_gol_pen(int x, int y, void* core_)
{
	t_controller*	core = (t_controller*)(core_);
	int i = x / core->vars->gol.tail_cell;
	int j = y / core->vars->gol.tail_cell;
	if (core->vars->gol.pen == 1){
		core->vars->gol.map[j][i] = 'A';
		core->vars->gol.buff_color[j][i] = BLANC;
	}
	else if (core->vars->gol.pen == -1){
		core->vars->gol.map[j][i] = 0;
		core->vars->gol.buff_color[j][i] = NOIR;
	}
	return (0);
}

int		event_mouse_game_of_life(int button, int x, int y, void* core_)
{
	t_controller* core = (t_controller*)(core_);
	(void)core;(void)x;(void)y;
	if (button == 1)
	{
		if (core->vars->gol.pen != 1)
			core->vars->gol.pen = 1;
		else
			core->vars->gol.pen = 0;
	}
	else if (button == 3)
	{
		if (core->vars->gol.pen != -1)
			core->vars->gol.pen = -1;
		else
			core->vars->gol.pen = 0;
	}
	return (0);
}
