#include "../../include/game_of_life.h"
#include <stdio.h>

void	display_map_game_of_life(t_controller *core)
{
	unsigned int* buff = (unsigned int*)(core->vars->img->addr);
	int j = 0;
	
	while (j < core->vars->gol.height){
		int i = 0;
		while (i < core->vars->gol.width){
			int r, g, b;
			r = (core->vars->gol.buff_color[j][i] >> 16) & 0xFF;
			g = (core->vars->gol.buff_color[j][i] >> 8) & 0xFF;
			b = core->vars->gol.buff_color[j][i] & 0xFF;
			
			if (core->vars->gol.map[j][i] == 'A')
				core->vars->gol.buff_color[j][i] = BLANC;
			else{
				if (core->vars->gol.map[j][i] != 0 && core->vars->gol.start != 0){
					core->vars->gol.buff_color[j][i] = ((r - 25) << 16) | ((g - 25) << 8) | ((b - 25));
					core->vars->gol.map[j][i] += -1;
				}
			}
			int departY = j * core->vars->gol.tail_cell;
			int arriveeY = departY + core->vars->gol.tail_cell;
			for (int y = departY; y < arriveeY; y++){
				int departX = i * core->vars->gol.tail_cell;
				int arriveeX = departX + core->vars->gol.tail_cell;
				for (int x = departX; x < arriveeX; x++){
					buff[y * core->vars->width + x] = core->vars->gol.buff_color[j][i];
				}
			}
			i++;
		}
		j++;
	}
}

void	generation_game_of_life(t_game_of_life* gol)
{
	int v = 0;

	char tab[gol->height][gol->width];

	for (int y = 0; y < gol->height; y++){
		for (int x = 0; x < gol->width; x++){
			v = 0;
			for (int dy = -1; dy <= 1; dy++) {
				for (int dx = -1; dx <= 1; dx++) {
					if (dx == 0 && dy == 0)
						continue;
					int nx = (x + dx + gol->width) % gol->width;
					int ny = (y + dy + gol->height) % gol->height;
					if (gol->map[ny][nx] == 'A')
						v++;
				}
			}
			if (gol->map[y][x] == 'A'){
				if (v != 2 && v != 3)
				{
					int r, g, b;
					r = (gol->buff_color[y][x] >> 16) & 0xFF;
					g = (gol->buff_color[y][x] >> 8) & 0xFF;
					b = gol->buff_color[y][x] & 0xFF;
					tab[y][x] = 3;
					gol->buff_color[y][x] = ((r - 180) << 16) | ((g - 180) << 8) | ((b - 180));
				}
				else
					tab[y][x] = 'A';
			}
			else
			{
				if (v == 3)
					tab[y][x] = 'A';
				else
					tab[y][x] = gol->map[y][x];
			}
		}
	}
	for (int j = 0; j < gol->height; j++){
		for (int i = 0; i < gol->width; i++){
			gol->map[j][i] = tab[j][i];
		}
	}
}