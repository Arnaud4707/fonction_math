#ifndef STRUCT_FONCTION_H
#define STRUCT_FONCTION_H


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
typedef struct s_trigo{
	double	x;
	double	a;
	double	b;
	double	h;
	double	k;
}	t_trigo;

typedef struct s_test{
    int     x0;
    int     x1;
    int     y0;
    int     y1;
}   t_test;

typedef struct s_algebre{
    double  a;
    double  b;
    double  c;
    double  d;
}   t_algebre;




#endif