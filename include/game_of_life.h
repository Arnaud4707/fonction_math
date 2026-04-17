#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

#include "struct_fonction.h"
#include "color.h"

void	init_map_game_of_life(int nb_caseX, int nb_caseY, int gen, t_controller *core);
void	display_map_game_of_life(t_controller *core);
int		event_mouse_game_of_life(int button, int x, int y, void *core);
int		event_key_game_of_life(int key, t_controller *core);
void	generation_game_of_life(t_game_of_life *gol);
int		render_loop_game_of_life(void *core_);
int		render_loop_game_of_life_generation(void* core_);
int		event_mose_move_gol_pen(int x, int y, void* core_);
#endif