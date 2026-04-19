#ifndef FONCTION_MATH_H
#define FONCTION_MATH_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include "../mlx/mlx.h"
#include "color.h"
#include "struct_fonction.h"
#include "matrice.h"
#include "matrice_fonction.h"
#include "background.h"
#include "grilles.h"
#include "object.h"
#include "game_of_life.h"

#define _USE_MATH_DEFINES
#include <math.h>

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

// --------------------------------------------------------------

/**
 * @file	utils.c
 * 
 * @brief	Fonction qui close une window.
 * 
 * @param	core	Structure de controle.
 */
int		f_close(t_controller *core);

/**
 * @file	events.c
 * 
 * @brief	Fonction de gestion d'évènements après l'appuie d'une touche.
 * 
 * @param	key		La touche appuiée.
 * 
 * @param	core	Structure de controle.
 */
int		event_key_fonction(int key, t_controller* core);

int		event_key_matrice(int key, t_controller* core);

/**
 * @file	renderer.c
 * 
 * @brief	Fonction de gestion de l'affichage.
 * 
 * @param	core	Structure de controle.
 */
int		render_loop(void* core_);

/** */
void	zoom(int a, t_controller* core);
void	arrow(int key, t_controller* core);
void	change_param_trigo(int key, t_controller* core);
void	change_param_algebre(int key, t_controller* core);
void	move(double dx, double dy, t_vars *vars);

unsigned	long	diff_time(struct timeval* st, struct timeval* end);

void    init_function_math(t_controller* core);
void 	vars_init(t_vars *vars, t_controller* control);
void	f_ax_plus_b(double x_, double a, double b, t_vars* vars);

/**
 * @file	trigonimetrie.c
 * 
 * @brief	Fonction sinus f(x) = a sin(b(x - h)) + k
 * 
 * @param	x	Le point sur l'axe d'oscillation où commence la fonction sinus.
 * 
 * @param	k	L'axe d'oscillation sur lequel va s'effectuer la fonction sinus.
 * 
 *		 	On le trouve avec la formule suivente: k = (max + min) / 2 ou k = y.
 * 
 * @param	a	L'amplitude de la fonction, est la distance entre l'axe d'oscillation et
 * le maximum ou le minimum.
 * 
 * 			Il s'obtient avec la formule suivente: a = (maximum - minimum) / 2.
 * 
 * @param	b	La periode d'oscillation de la fonction. p = 2PI / b
 * 
 * @param	h	Le déphasage correspond au déplacement horizontal de la
 *  fonction sinus transformée par rapport à la fonction sinus de base.
 * 
 * @param	vars	Le pointeur vers la structure de la fenêtre.
 */
void	f_sin_x(double x_, double a, double b, double h, double k, t_vars *vars);

void	f_cos_x(double x_, double a, double b, double h, double k, t_vars *vars);
void	f_tan_x(double x_, double a, double b, double h, double k, t_vars *vars);


/**
 * @file	trigonometrie.c
 * 
 * @brief	Fonction pour créer un cercle
 * 
 * 	A savoir, le sinus correspon à l'axe des ordonnées, le cosinus à l'axe des abscices.
 * 
 * 	Formule générale d'une transformation d'un point (x,y) par un un angle thita:
 * 
 * 	x' = (cos(thita) * x) - (sin(thita) * y)
 * 
 * 	y' = (sin(thita) * y) + (cos(thita) * x)
 * 
 * 	A partir de r et de l'angle (en radian) thita on peut tracer un cercle trigonometrique.
 * 
 * 	x = r * cos(thita)
 * 
 * 	y = r * sin(thita)
 * 
 * 	Pour transformer des coordonnées cartésien (x,y) en coordonnées trigonométrique (r, thita),
 * 	on utilise la formule suivente: r = sqrt((x * x) + (y * y)), 
 * 									thita = tan(y, x)
 * 
 * @param	r		Rayon du cercle, correspond à x quand thita vaut 0.
 * 
 * @param	thita	Angle entre l'axe des abscices et le rayon r au coordonnées y
 */
void	f_cercle(double r, double thita, t_vars* vars);
void	f_link_cercle(double x_, double y_, t_vars* vars);
void	f_spirale_archimede(double tour, double a_, double b, t_vars* vars);
void 	f_spirale_log(double tour,double a, double b, t_vars* vars);
void	f_ellipse(double x_, double y_, double a, double b, t_vars* vars);
void	f_spirale_hyperbolique(double tour,double a, t_vars* vars);
void 	f_ax2_puls_bx_plus_c(double x_, double a, double b, double c, t_vars* vars);
void	f_a_power_x(double x_, double a, t_vars *vars);
void	f_exp_canon_simple(double x_, double a, double b, double c, t_vars *vars);
void	f_exp_canon(double x_, double a, double b, double c, double h, double k, t_vars *vars);

void	f_log_base(double x_, double c, t_vars *vars);
void	f_asymptote(double x_, double a, double b, double c, double d, t_vars *vars);
void	f_spirale_asymptote(double tour,double a, double b, double c, t_vars* vars);


/**
 * @file  	utils.c
 * 
 * @brief 	Fonction differentiel y'= ay => g(x) = C * e^ax
 *
 * En partant de g(0) = n, g = y' et n = ay.
 * Sachant que e^x est la seul solution de y' = y.
 * Sachant que la dérivée de (e^u)' est u' * e^u.
 * e étant le nombre d'euler.
 * On obtien le developpement suivent:
 *  y = C * e^ax
 * 	g(0) = n = C * e^a0
 * 	n = C * 1
 * 
 * @param 	x_ 	la valeur de la coordonée x avec laquelle on va commencé
 * à appliquer la fonction obtenue. Elle est incrémenté de 0.01 jusqu'a x < 50.
 * @param	a 	la forme de l'equation differentiel y' = ay
 * @param	c	la solution de g(0). On l'appel aussi condition initial.
 * 
 * @author Arnaud Mugisha <amugisha6@gmail.com>
 * 
 * @version 1.0
 * 
 * @date 2026
 */
void	f_diff_ax(double x_, double a, double c, t_vars *vars);
void	f_clothoide(double x_, double y_, double k, t_vars *vars);
void	f_diff_ax_plus_b(double x_, double a, double b, double c, t_vars *vars);

void    grille_point(t_controller* core);
void    animation_sinus(double x_, double a, double b, double h, double k, t_vars *vars);
void    animation_sinus_concentrique(double a, double r, double thita, t_vars *vars);

static inline	void	affiche_param(t_controller* core)
{
	char buff[70];

	sprintf(buff, "         Diminuer/Augmenter les parametres.");
	mlx_string_put(core->mlx, core->vars->win, 0, 50, 0x00000000, buff);

	if (core->vars->id_fonction == 1)
	{
		sprintf(buff, "    Fonction: ax + b");
		mlx_string_put(core->mlx, core->vars->win, 0, 70, 0x00000000, buff);
		sprintf(buff, "a: %f     Touche A - / E +",core->vars->fonction.al.a);
		mlx_string_put(core->mlx, core->vars->win, 0, 100, 0x00000000, buff);
		sprintf(buff, "b: %f     Touche Q - / D +",core->vars->fonction.al.b);
		mlx_string_put(core->mlx, core->vars->win, 0, 120, 0x00000000, buff);
	}
	else if (core->vars->id_fonction == 2)
	{
		sprintf(buff, "    Fonction: ax2 + bx + c");
		mlx_string_put(core->mlx, core->vars->win, 0, 70, 0x00000000, buff);
		sprintf(buff, "a: %f     Touche A - / E +",core->vars->fonction.al.a);
		mlx_string_put(core->mlx, core->vars->win, 0, 100, 0x00000000, buff);
		sprintf(buff, "b: %f     Touche Q - / D +",core->vars->fonction.al.b);
		mlx_string_put(core->mlx, core->vars->win, 0, 120, 0x00000000, buff);
		sprintf(buff, "c: %f     Touche W - / C +",core->vars->fonction.al.c);
		mlx_string_put(core->mlx, core->vars->win, 0, 140, 0x00000000, buff);
	}
	else if (core->vars->id_fonction == 3)
	{
		sprintf(buff, "    Fonction: a^x");
		mlx_string_put(core->mlx, core->vars->win, 0, 70, 0x00000000, buff);
		sprintf(buff, "a: %f     Touche A - / E +",core->vars->fonction.al.a);
		mlx_string_put(core->mlx, core->vars->win, 0, 100, 0x00000000, buff);
	}
	else if (core->vars->id_fonction == 4)
	{
		sprintf(buff, "    Fonction: y' = ay => g(x) = C * e^ax");
		mlx_string_put(core->mlx, core->vars->win, 0, 70, 0x00000000, buff);
		sprintf(buff, "a: %f     Touche A - / E +",core->vars->fonction.al.a);
		mlx_string_put(core->mlx, core->vars->win, 0, 100, 0x00000000, buff);
		sprintf(buff, "c: %f     Touche W - / C +",core->vars->fonction.al.c);
		mlx_string_put(core->mlx, core->vars->win, 0, 140, 0x00000000, buff);
	}
	else if (core->vars->id_fonction == 5)
	{
		sprintf(buff, "    Fonction: y' = ay + b => g(x) = C * e^ax + b/a");
		mlx_string_put(core->mlx, core->vars->win, 0, 70, 0x00000000, buff);
		sprintf(buff, "a: %f     Touche A - / E +",core->vars->fonction.al.a);
		mlx_string_put(core->mlx, core->vars->win, 0, 100, 0x00000000, buff);
		sprintf(buff, "b: %f     Touche Q - / D +",core->vars->fonction.al.b);
		mlx_string_put(core->mlx, core->vars->win, 0, 120, 0x00000000, buff);
		sprintf(buff, "c: %f     Touche W - / C +",core->vars->fonction.al.c);
		mlx_string_put(core->mlx, core->vars->win, 0, 140, 0x00000000, buff);
	}
	else if (core->vars->id_fonction == 6)
	{
		sprintf(buff, "    Fonction cercle: x = r * cos(thita)");
		mlx_string_put(core->mlx, core->vars->win, 0, 70, 0x00000000, buff);
		sprintf(buff, "r: %f     Touche A - / E +",core->vars->fonction.trigo.a);
		mlx_string_put(core->mlx, core->vars->win, 0, 100, 0x00000000, buff);
		sprintf(buff, "thita: %f     Touche Q - / D +",core->vars->fonction.trigo.b);
		mlx_string_put(core->mlx, core->vars->win, 0, 120, 0x00000000, buff);
	}
	else if (core->vars->id_fonction == 7)
	{
		sprintf(buff, "    Fonction spirale d'archimède: r = a * thita + b");
		mlx_string_put(core->mlx, core->vars->win, 0, 70, 0x00000000, buff);
		sprintf(buff, "a: %f     Touche A - / E +",core->vars->fonction.trigo.a);
		mlx_string_put(core->mlx, core->vars->win, 0, 100, 0x00000000, buff);
		sprintf(buff, "b: %f     Touche Q - / D +",core->vars->fonction.trigo.b);
		mlx_string_put(core->mlx, core->vars->win, 0, 120, 0x00000000, buff);
	}
	else if (core->vars->id_fonction == 8)
	{
		sprintf(buff, "    Fonction spirale hyperbolique: r = a / thita");
		mlx_string_put(core->mlx, core->vars->win, 0, 70, 0x00000000, buff);
		sprintf(buff, "a: %f     Touche A - / E +",core->vars->fonction.trigo.a);
		mlx_string_put(core->mlx, core->vars->win, 0, 100, 0x00000000, buff);
	}
	else if (core->vars->id_fonction == 9)
	{
		sprintf(buff, "    Fonction spirale asymptotique: r = a * (t / (t + c)) + b");
		mlx_string_put(core->mlx, core->vars->win, 0, 70, 0x00000000, buff);
		sprintf(buff, "a: %f     Touche A - / E +",core->vars->fonction.trigo.a);
		mlx_string_put(core->mlx, core->vars->win, 0, 100, 0x00000000, buff);
		sprintf(buff, "b: %f     Touche Q - / D +",core->vars->fonction.trigo.b);
		mlx_string_put(core->mlx, core->vars->win, 0, 120, 0x00000000, buff);
		sprintf(buff, "c: %f     Touche W - / C +",core->vars->fonction.trigo.h);
		mlx_string_put(core->mlx, core->vars->win, 0, 140, 0x00000000, buff);
	}
	else if (core->vars->id_fonction == 10)
	{
		sprintf(buff, "    Fonction spirale logarithmique: r = a * b^thita");
		mlx_string_put(core->mlx, core->vars->win, 0, 70, 0x00000000, buff);
		sprintf(buff, "a: %f     Touche A - / E +",core->vars->fonction.trigo.a);
		mlx_string_put(core->mlx, core->vars->win, 0, 100, 0x00000000, buff);
		sprintf(buff, "b: %f     Touche Q - / D +",core->vars->fonction.trigo.b);
		mlx_string_put(core->mlx, core->vars->win, 0, 120, 0x00000000, buff);
	}
	else if (core->vars->id_fonction == 11)
	{
		sprintf(buff, "    Fonction sinus canonique: y = a * sin( b *(x - h)) + k");
		mlx_string_put(core->mlx, core->vars->win, 0, 70, 0x00000000, buff);
		sprintf(buff, "a: %f     Touche A - / E +",core->vars->fonction.trigo.a);
		mlx_string_put(core->mlx, core->vars->win, 0, 100, 0x00000000, buff);
		sprintf(buff, "b: %f     Touche Q - / D +",core->vars->fonction.trigo.b);
		mlx_string_put(core->mlx, core->vars->win, 0, 120, 0x00000000, buff);
		sprintf(buff, "h: %f     Touche W - / C +",core->vars->fonction.trigo.h);
		mlx_string_put(core->mlx, core->vars->win, 0, 140, 0x00000000, buff);
		sprintf(buff, "k: %f     Touche Z - / S +",core->vars->fonction.trigo.k);
		mlx_string_put(core->mlx, core->vars->win, 0, 160, 0x00000000, buff);
	}
	else if (core->vars->id_fonction == 12)
	{
		sprintf(buff, "    Fonction cosinus canonique: y = a * cos( b *(x - h)) + k");
		mlx_string_put(core->mlx, core->vars->win, 0, 70, 0x00000000, buff);
		sprintf(buff, "a: %f     Touche A - / E +",core->vars->fonction.trigo.a);
		mlx_string_put(core->mlx, core->vars->win, 0, 100, 0x00000000, buff);
		sprintf(buff, "b: %f     Touche Q - / D +",core->vars->fonction.trigo.b);
		mlx_string_put(core->mlx, core->vars->win, 0, 120, 0x00000000, buff);
		sprintf(buff, "h: %f     Touche W - / C +",core->vars->fonction.trigo.h);
		mlx_string_put(core->mlx, core->vars->win, 0, 140, 0x00000000, buff);
		sprintf(buff, "k: %f     Touche Z - / S +",core->vars->fonction.trigo.k);
		mlx_string_put(core->mlx, core->vars->win, 0, 160, 0x00000000, buff);
	}
	else if (core->vars->id_fonction == 13)
	{
		sprintf(buff, "    Fonction tangente canonique: y = a * tan( b *(x - h)) + k");
		mlx_string_put(core->mlx, core->vars->win, 0, 70, 0x00000000, buff);
		sprintf(buff, "a: %f     Touche A - / E +",core->vars->fonction.trigo.a);
		mlx_string_put(core->mlx, core->vars->win, 0, 100, 0x00000000, buff);
		sprintf(buff, "b: %f     Touche Q - / D +",core->vars->fonction.trigo.b);
		mlx_string_put(core->mlx, core->vars->win, 0, 120, 0x00000000, buff);
		sprintf(buff, "h: %f     Touche W - / C +",core->vars->fonction.trigo.h);
		mlx_string_put(core->mlx, core->vars->win, 0, 140, 0x00000000, buff);
		sprintf(buff, "k: %f     Touche Z - / S +",core->vars->fonction.trigo.k);
		mlx_string_put(core->mlx, core->vars->win, 0, 160, 0x00000000, buff);
	}
	else if (core->vars->id_fonction == 14)
	{
		sprintf(buff, "    Fonction animation sinus: y = a * tan( b *(x - h)) + k");
		mlx_string_put(core->mlx, core->vars->win, 0, 70, 0x00000000, buff);
		sprintf(buff, "a: %f     Touche A - / E +",core->vars->fonction.trigo.a);
		mlx_string_put(core->mlx, core->vars->win, 0, 100, 0x00000000, buff);
		sprintf(buff, "b: %f     Touche Q - / D +",core->vars->fonction.trigo.b);
		mlx_string_put(core->mlx, core->vars->win, 0, 120, 0x00000000, buff);
		sprintf(buff, "h: %f     Touche W - / C +",core->vars->fonction.trigo.h);
		mlx_string_put(core->mlx, core->vars->win, 0, 140, 0x00000000, buff);
		sprintf(buff, "k: %f     Touche Z - / S +",core->vars->fonction.trigo.k);
		mlx_string_put(core->mlx, core->vars->win, 0, 160, 0x00000000, buff);
	}
	else if (core->vars->id_fonction == 15)
	{
		sprintf(buff, "    Fonction sinus concentrique: x = (r+dr) * cos(thita)");
		mlx_string_put(core->mlx, core->vars->win, 0, 70, 0x00000000, buff);
		sprintf(buff, "r: %f     Touche A - / E +",core->vars->fonction.trigo.a);
		mlx_string_put(core->mlx, core->vars->win, 0, 100, 0x00000000, buff);
		sprintf(buff, "thita: %f     Touche Q - / D +",core->vars->fonction.trigo.b);
		mlx_string_put(core->mlx, core->vars->win, 0, 120, 0x00000000, buff);
	}
}

// #define TAB void(*tab_f[1])(double x_, double y_, t_vars *vars) = {f_cercle}

#endif