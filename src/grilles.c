#include "../fonction_math.h"


void    grille_point(t_controller* core)
{
	// unsigned int *buffer = (unsigned int *)core->vars->img->addr;   
    // for (double i = floor(core->vars->greed.x_min); i < ceil(core->vars->greed.x_max); i += 1){
    //     int x = (i - core->vars->greed.x_min) * core->vars->scale_w;
    //     if (x >= 0 && x < core->vars->width)
    //     {
    //         for (int j = floor(core->vars->greed.y_min); j < ceil(core->vars->greed.y_max); j += 1){
    //             int y = (core->vars->greed.y_max - j) * core->vars->scale_h;
    //             if (y >= 0 && y < core->vars->height)
    //                 buffer[y * core->vars->width + x] = 0x00000000;
    //         }
    //     }
    // }

    // for (double j = core->vars->greed.y_min; j < core->vars->greed.y_max; j += 2)
        // f_sin_x(core->vars->greed.x_min, core->vars->fonction.sin.a, core->vars->fonction.sin.b,
            // core->vars->fonction.sin.h, j, core->vars);
    animation_sinus(0, core->vars->fonction.sin.a, core->vars->fonction.sin.b,
        core->vars->fonction.sin.h, 0, core->vars);
}