#ifndef STRUCT_FONCTION_H
#define STRUCT_FONCTION_H

#include "math.h"

#define WIDTH 1200
#define HEIGHT 600
#define MENU 200
#define ABS(_x) ((_x) >= 0 ? (_x) : -(_x))
#define SGN(_x) ((_x) < 0 ? -1 : ((_x) > 0 ? 1 : 0))

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
typedef struct s_trigo
{
	double x;
	double a;
	double b;
	double h;
	double k;
} t_trigo;

typedef struct s_test
{
	int x0;
	int x1;
	int y0;
	int y1;
} t_test;

typedef struct s_algebre
{
	double a;
	double b;
	double c;
	double d;
} t_algebre;

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
typedef struct s_data
{
	void *img;
	char *addr;
	int bpp;
	int line_length;
	int endian;
} t_data;

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
typedef struct s_greed
{
	double x_min;
	double x_max;
	double y_min;
	double y_max;
	double scale_x;
	double scale_y;
} t_greed;

typedef struct s_scale
{
	double scaleXY;
	double	scaleZ;
}	t_scale;

typedef struct vect
{
	double x;
	double y;
	double z;
	double w;
}	t_vect;

typedef	struct s_screen_point
{
	int x;
	int y;
}	t_screen_point;

typedef struct s_mat
{
	double	mat[4][4];
}	t_mat;

typedef struct s_camera
{
	t_vect position;
	double yaw;
	double pitch;
} t_camera;

typedef	struct s_angles
{
	double	angleX;
	double	angleY;
	double	angleZ;
}	t_angles;

typedef	struct s_matrice
{
	t_mat		mat_scale;
	t_mat		mat_rotateZ;
	t_mat		mat_rotateY;
	t_mat		mat_rotateX;
	t_mat		mat_translation;
	t_mat		mat_world;
	t_mat		mat_view;
	t_mat		mat_projection;
	int 		offsetX;
	int			offsetY;
	int			mode;
	int			zbuffer[HEIGHT][WIDTH];
	t_scale 	scale;
	t_camera	cam;
	t_angles	angles;
}	t_matrice;

/**
 * @struct	Structure s_fonction
 *
 * @brief	Structure qui contient les structures des fonctions.
 *
 * @param	sin		Structure de la fonction sinus.
 */
typedef struct s_fonction
{
	t_trigo trigo;
	t_algebre al;
	t_test test;
} t_fonction;

typedef	struct	s_maps	t_maps;
struct	s_maps
{
	char *line;
	t_maps *next;
};

typedef struct s_game_of_life
{
	char**	map;
	int**	buff_color;
	int		tail_cell;
	int		gen;
	int		pen;
	int		start;
	int		height;
	int		width;
}	t_game_of_life;


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
 * @param	world		Le projet afficher, 1. Graph; 2. Moteur 3D; 3. Game Of Life
 *
 * @param	gol			La structure de automate cellulaire Game Of Life.
 * 
 * @param	greed		Structure t_greed.
 *
 * @param	id_fonction	La fonction à affiche.
 *
 * @param	nb_fonction	Nombre de fonction affichable.
 *
 * @param	fonction	Structure qui contient toutes les structures des fonctions.
 * 
 * @param	matrice		Structure qui contient quelques variable utile au calcule de matrice.
 */
typedef struct s_vars t_vars;
struct s_vars
{

	void			*win;
	t_data			*img;
	int				height;
	int 			width;
	double			scale_h;
	double			scale_w;
	int				world;
	t_game_of_life	gol;
	t_greed			greed;
	int 			id_fonction;
	int 			nb_fonction;
	t_fonction		fonction;
	t_matrice		matrice;
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
typedef struct s_controller
{
	void *mlx;
	t_vars *vars;
	t_vars *tars;
} t_controller;

static inline void drawLine(int x0, int y0, int x1, int y1, int c, t_controller *core)
{
	if (x0 < 0 || x0 >= WIDTH || y0 < 0 || y0 >= HEIGHT || x1 < 0 || x1 >= WIDTH || y1 < 0 || y1 >= HEIGHT)
		return;
	unsigned int *buff = (unsigned int *)(core->vars->img->addr);
	int dx = x1 - x0;
	int dy = y1 - y0;
	int incX = SGN(dx);
	int incY = SGN(dy);
	dx = ABS(dx);
	dy = ABS(dy);

	if (dy == 0)
	{
		for (int x = x0; x != x1 + incX; x += incX)
			buff[y0 * WIDTH + x] = c;
	}
	else if (dx == 0)
	{
		for (int y = y0; y != y1 + incY; y += incY)
			buff[y * WIDTH + x0] = c;
	}
	else if (dx >= dy)
	{
		int slope = 2 * dy;
		int error = -dx;
		int errorInc = -2 * dx;
		int y = y0;

		for (int x = x0; x != x1 + incX; x += incX)
		{
			buff[y * WIDTH + x] = c;
			error += slope;

			if (error >= 0)
			{
				y += incY;
				error += errorInc;
			}
		}
	}
	else
	{
		int slope = 2 * dx;
		int error = -dy;
		int errorInc = -2 * dy;
		int x = x0;

		for (int y = y0; y != y1 + incY; y += incY)
		{
			buff[y * WIDTH + x] = c;
			error += slope;

			if (error >= 0)
			{
				x += incX;
				error += errorInc;
			}
		}
	}
}

#endif