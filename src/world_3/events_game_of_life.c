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
			core->vars->gol.start = 1;
			mlx_loop_hook(core->mlx, render_loop_game_of_life_generation, core);
		}
	}
	else if (key == 'p')
	{
		if ((core->vars->gol.fps - 10000) >= 20000)
			core->vars->gol.fps -= 10000;
	}
	else if (key == 'm')
	{
		if ((core->vars->gol.fps + 10000) <= 250000)
			core->vars->gol.fps += 10000;
	}
	else if (key == 'a')
	{
		if (core->vars->gol.size_pen < 3)
			core->vars->gol.size_pen += 1;
	}
	else if (key == 'z')
	{
		if (core->vars->gol.size_pen > 1)
			core->vars->gol.size_pen -= 1;
	}
	return(0);
}

int		event_mose_move_gol_pen(int x, int y, void* core_)
{
	t_controller*	core = (t_controller*)(core_);
	x = x / core->vars->gol.tail_cell;
	y = y / core->vars->gol.tail_cell;


	if (core->vars->gol.pen == 1){
		core->vars->gol.map[y][x] = 'A';
		core->vars->gol.buff_color[y][x] = BLANC;
		if (core->vars->gol.size_pen >= 2){
			if (x + 1 < core->vars->gol.width){
				core->vars->gol.map[y][x + 1] = 'A';
				core->vars->gol.buff_color[y][x + 1] = BLANC;
			}
			if ((y + 1) < core->vars->gol.height){
				core->vars->gol.map[y + 1][x] = 'A';
				core->vars->gol.buff_color[y + 1][x] = BLANC;
			}
			if ((x + 1) < core->vars->gol.width && (y + 1) < core->vars->gol.height){
				core->vars->gol.map[y + 1][x + 1] = 'A';
				core->vars->gol.buff_color[y + 1][x + 1] = BLANC;
			}
		}
		if (core->vars->gol.size_pen == 3){
			if (x + 1 < core->vars->gol.width && y - 1 >= 0){
				core->vars->gol.map[y - 1][x + 1] = 'A';
				core->vars->gol.buff_color[y - 1][x + 1] = BLANC;
			}
			if ((y - 1) >= 0){
				core->vars->gol.map[y - 1][x] = 'A';
				core->vars->gol.buff_color[y - 1][x] = BLANC;
			}
			if ((x - 1) >= 0 && (y - 1) >= 0){
				core->vars->gol.map[y - 1][x - 1] = 'A';
				core->vars->gol.buff_color[y - 1][x - 1] = BLANC;
			}
			if ((x - 1) >= 0){
				core->vars->gol.map[y][x - 1] = 'A';
				core->vars->gol.buff_color[y][x - 1] = BLANC;
			}
			if ((y + 1) < core->vars->gol.height && x - 1 >= 0){
				core->vars->gol.map[y + 1][x - 1] = 'A';
				core->vars->gol.buff_color[y + 1][x - 1] = BLANC;
			}
		}
	}
	else if (core->vars->gol.pen == -1){
		core->vars->gol.map[y][x] = 0;
		core->vars->gol.buff_color[y][x] = NOIR;
		if (core->vars->gol.size_pen >= 2){
			if (x + 1 < core->vars->gol.width){
				core->vars->gol.map[y][x + 1] = 0;
				core->vars->gol.buff_color[y][x + 1] = NOIR;
			}
			if ((y + 1) < core->vars->gol.height){
				core->vars->gol.map[y + 1][x] = 0;
				core->vars->gol.buff_color[y + 1][x] = NOIR;
			}
			if ((x + 1) < core->vars->gol.width && (y + 1) < core->vars->gol.height){
				core->vars->gol.map[y + 1][x + 1] = 0;
				core->vars->gol.buff_color[y + 1][x + 1] = NOIR;
			}
		}
		if (core->vars->gol.size_pen == 3){
			if (x + 1 < core->vars->gol.width && y - 1 >= 0){
				core->vars->gol.map[y - 1][x + 1] = 0;
				core->vars->gol.buff_color[y - 1][x + 1] = NOIR;
			}
			if ((y - 1) >= 0){
				core->vars->gol.map[y - 1][x] = 0;
				core->vars->gol.buff_color[y - 1][x] = NOIR;
			}
			if ((x - 1) >= 0 && (y - 1) >= 0){
				core->vars->gol.map[y - 1][x - 1] = 0;
				core->vars->gol.buff_color[y - 1][x - 1] = NOIR;
			}
			if ((x - 1) >= 0){
				core->vars->gol.map[y][x - 1] = 0;
				core->vars->gol.buff_color[y][x - 1] = NOIR;
			}
			if ((y + 1) < core->vars->gol.height && x - 1 >= 0){
				core->vars->gol.map[y + 1][x - 1] = 0;
				core->vars->gol.buff_color[y + 1][x - 1] = NOIR;
			}
		}
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
