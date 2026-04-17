#include "../include/game_of_life.h"
#include <stdio.h>

void	display_map_game_of_life(t_controller *core)
{
	unsigned int* buff = (unsigned int*)(core->vars->img->addr);
	int color = BLANC;
	int j = 0;
	
	while (j < core->vars->gol.height){
		int i = 0;
		while (i < core->vars->gol.width){
			if (core->vars->gol.map[j][i] == 'A')
				color = NOIR;
			else
				color = BLANC;
			int departY = j * core->vars->gol.tail_cell;
			int arriveeY = departY + core->vars->gol.tail_cell;
			for (int y = departY; y < arriveeY; y++){
				int departX = i * core->vars->gol.tail_cell;
				int arriveeX = departX + core->vars->gol.tail_cell;
				for (int x = departX; x < arriveeX; x++){
					buff[y * core->vars->width + x] = color;
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
	int endY = gol->height - 1;
	int endX = gol->width - 1;

	char tab[gol->height][gol->width];

	for (int y = 0; y < gol->height; y++){
		for (int x = 0; x < gol->width; x++){
			if (y == 0 && x == 0){ // h g
				if (gol->map[y][x + 1] == 'A')
					v++;
				if (gol->map[y + 1][x + 1] == 'A')
					v++;
				if (gol->map[y + 1][x] == 'A')
					v++;
				if (gol->map[y][x] == 'A')
				{
					if (v == 2 || v == 3)
						tab[y][x] = 'A';
					else
						tab[y][x] = 'D';
				}
				else
				{
					if (v == 3)
						tab[y][x] = 'A';
					else
						tab[y][x] = 'D';
				}
			}
			else if (y == 0 && x == endX){ // h d
				if (gol->map[0][endX - 1] == 'A')
					v++;
				if (gol->map[1][endX - 1] == 'A')
					v++;
				if (gol->map[1][endX] == 'A')
					v++;
				if (gol->map[y][x] == 'A')
				{
					if (v == 2 || v == 3)
						tab[y][x] = 'A';
					else
						tab[y][x] = 'D';
				}
				else
				{
					if (v == 3)
						tab[y][x] = 'A';
					else
						tab[y][x] = 'D';
				}
			}
			else if (y == 0 && x < endX){ // h h
				
				if (gol->map[y][x - 1] == 'A')
					v++;
				if (gol->map[y][x + 1] == 'A')
					v++;
				if (gol->map[y + 1][x - 1] == 'A')
				v++;
				if (gol->map[y + 1][x] == 'A')
					v++;
				if (gol->map[y + 1][x + 1] == 'A')
					v++;
				if (gol->map[y][x] == 'A')
				{
					if (v == 2 || v == 3)
						tab[y][x] = 'A';
					else
						tab[y][x] = 'D';
				}
				else
				{
					if (v == 3)
						tab[y][x] = 'A';
					else
						tab[y][x] = 'D';
				}
			}
			else if (x == 0 && y < endY) // ligne veticale gauche
			{
				if (gol->map[y - 1][x] == 'A')
					v++;
				if (gol->map[y - 1][x + 1] == 'A')
					v++;
				if (gol->map[y][x + 1] == 'A')
					v++;
				if (gol->map[y + 1][x] == 'A')
					v++;
				if (gol->map[y + 1][x + 1] == 'A')
					v++;
				if (gol->map[y][x] == 'A')
				{
					if (v == 2 || v == 3)
						tab[y][x] = 'A';
					else
						tab[y][x] = 'D';
				}
				else
				{
					if (v == 3)
						tab[y][x] = 'A';
					else
						tab[y][x] = 'D';
				}
			}
			else if (y < endY && x < endX) // global
			{
				if (gol->map[y - 1][x - 1] == 'A')
					v++;
				if (gol->map[y - 1][x] == 'A')
					v++;
				if (gol->map[y - 1][x + 1] == 'A')
					v++;
				if (gol->map[y][x - 1] == 'A')
					v++;
				if (gol->map[y][x + 1] == 'A')
					v++;
				if (gol->map[y + 1][x - 1] == 'A')
					v++;
				if (gol->map[y + 1][x] == 'A')
					v++;
				if (gol->map[y + 1][x + 1] == 'A')
					v++;
				if (gol->map[y][x] == 'A')
				{
					if (v == 2 || v == 3)
						tab[y][x] = 'A';
					else
						tab[y][x] = 'D';
				}
				else
				{
					if (v == 3)
						tab[y][x] = 'A';
					else
						tab[y][x] = 'D';
				}
			}
			else if (x == endX && y < endY) // ligne veticale droit
			{
				if (gol->map[y - 1][x] == 'A')
					v++;
				if (gol->map[y - 1][x - 1] == 'A')
					v++;
				if (gol->map[y][x - 1] == 'A')
					v++;
				if (gol->map[y + 1][x - 1] == 'A')
					v++;
				if (gol->map[y + 1][x] == 'A')
					v++;
				if (gol->map[y][x] == 'A')
				{
					if (v == 2 || v == 3)
						tab[y][x] = 'A';
					else
						tab[y][x] = 'D';
				}
				else
				{
					if (v == 3)
						tab[y][x] = 'A';
					else
						tab[y][x] = 'D';
				}
			}
			else if (x < endX && y == endY) // ligne du bas
			{
				if (gol->map[y][x - 1] == 'A')
					v++;
				if (gol->map[y - 1][x - 1] == 'A')
					v++;
				if (gol->map[y - 1][x] == 'A')
				v++;
				if (gol->map[y - 1][x + 1] == 'A')
					v++;
				if (gol->map[y][x + 1] == 'A')
					v++;
				if (gol->map[y][x] == 'A')
				{
					if (v == 2 || v == 3)
						tab[y][x] = 'A';
					else
						tab[y][x] = 'D';
				}
				else
				{
					if (v == 3)
						tab[y][x] = 'A';
					else
						tab[y][x] = 'D';
				}
			}
			else if (y == endY && x == 0){
				if (gol->map[endY][1] == 'A')
					v++;
				if (gol->map[endY - 1][1] == 'A')
					v++;
				if (gol->map[endY - 1][0] == 'A')
					v++;
				if (gol->map[y][x] == 'A')
				{
					if (v == 2 || v == 3)
						tab[y][x] = 'A';
					else
						tab[y][x] = 'D';
				}
				else
				{
					if (v == 3)
						tab[y][x] = 'A';
					else
						tab[y][x] = 'D';
				}
			}
			else if (y == endY && x == endX){
				if (gol->map[endY][endX - 1] == 'A')
					v++;
				if (gol->map[endY - 1][endX - 1] == 'A')
					v++;
				if (gol->map[endY - 1][endX] == 'A')
					v++;
				if (gol->map[y][x] == 'A')
				{
					if (v == 2 || v == 3)
						tab[y][x] = 'A';
					else
						tab[y][x] = 'D';
				}
				else
				{
					if (v == 3)
						tab[y][x] = 'A';
					else
						tab[y][x] = 'D';
				}
			}
			v = 0;
		}
	}
	for (int j = 0; j < gol->height; j++){
		for (int i = 0; i < gol->width; i++){
			gol->map[j][i] = tab[j][i];
		}
	}
}