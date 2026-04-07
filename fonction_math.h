#ifndef FONCTION_MATH_H
#define FONCTION_MATH_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include "mlx/mlx.h"
#include "mlx/mlx_int.h"

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

/**
 * @struct	t_data
 * 
 * @brief	Structure de l'image de la window.
 * 
 * @param	img		Pointeur vers l'image alloué par la mlx.
 * 
 * @param	addr	La chaine de caractères contenant l'emplacement des pixels.
 * 
 * @param	bpp		Le nombre de bits par pixel.
 * 
 * @param	endian	La fin le l'image.
 */
typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}				t_data;

/**
 * @struct	t_greed
 * 
 * @brief	Structure de la grille.
 * 
 * @param	x_min	Valeur du x mininum, la borne inférieur de l'axe des abscisses.
 * 
 * @param	x_max	Valeur du x maximum, la borne superieur de l'axes des abscisses.
 * 
 * @param	y_min	Valeur du y mininum, la borne inférieur de l'axe des ordonnées.
 * 
 * @param	y_max	Valeur du y maximum, la borne superieur de l'axes des ordonnées.
 */
typedef struct s_greed {
	double x_min;
	double x_max;
	double y_min;
	double y_max;
	double scale_x;
	double scale_y;
}	t_greed;

/**
 * @struct	Structure de la fonction sinus.
 * 
 * @brief	Les variables de la fonction.
 * 
 * @param	x	Le point d'inflexion.
 * 
 * @param	a	Ampliture.
 * 
 * @param	b	Période d'oscillation.
 * 
 * @param	h	Déffasage.
 * 
 * @param	k	Axe d'oscillation.
 */
typedef struct s_sin{
	double	x;
	double	a;
	double	b;
	double	h;
	double	k;
}	t_sin;

/**
 * @struct	Structure s_fonction
 * 
 * @brief	Structure qui contient les structures des fonctions.
 * 
 * @param	sin		Structure de la fonction sinus.
 */
typedef	struct s_fonction{
	t_sin	sin;
}	t_fonction;


/**
 * @struct	t_vars
 * 
 * @brief	Structure contenant les information de la window.
 * 
 * @param	win			Pointeur vers la window alloé par la mlx.
 * 
 * @param	img			Pointeur vers la structure t_data.
 * 
 * @param	height		La hauteur de la fenêtre.
 * 
 * @param	wight		La largeur de la fenêtre.
 * 
 * @param	scale_h		Le rapport entre la hauteur fenêtre et celle de la grille.
 * 
 * @param	scale_w		Le rapport entre la largeur fenêtre et celle de la grille.
 * 
 * @param	greed		Structure t_greed.
 * 
 * @param	id_fonction	La fonction à affiche.
 * 
 * @param	nb_fonction	Nombre de fonction affichable.
 * 
 * @param	fonction	Structure qui contient toutes les structures des fonctions.
 */
typedef struct s_vars t_vars;
struct s_vars{
	
	void*				win;
	t_data*				img;
	int					height;
	int 				width;
	double 				scale_h;
	double 				scale_w;
	t_greed 			greed;
	int					id_fonction;
	int					nb_fonction;
	t_fonction			fonction;
	struct	s_col_name*	col;
};

/**
 * @struct	t_controller
 * 
 * @brief	Structure de controle du programme.
 * 
 * @param	mlx		Pointeur alloué par la mlx, connexion entre le programme et X11.
 * 
 * @param	vars	Structure t_vars pour une 1ère fenêtre.
 * 
 * @param	tars	Structure t_vars pour une 2ère fenêtre.
 */
typedef struct s_controller{
	void* mlx;
	t_vars* vars;
	t_vars* tars;
}	t_controller;

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
int		event_key(int key, t_controller* core);

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
void	change_a_in_sin(int key, t_controller* core);
void	move(double dx, double dy, t_vars *vars);

__int64_t		diff_time(struct timeval* st, struct timeval* end);

void    init_function(t_controller* core);
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
void	f_cercle(double x_, double y_, t_vars* vars);
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
 * On obtien le developpement suivent:
 *  y = C * e^ax
 * 	g(0) = n = C * e^a0
 * 	n = C * 1
 * 
 * @param 	x_ 	la valeur de la coordonée x avec laquelle on va commencé
 * à appliquer la fonction obtenue. Elle est incrémenté de 0.01 jusqu'a x < 50.
 * @param	a 	la forme de l'equation differentiel y' = ay
 * @param	c	la solution de g(0).
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

#endif