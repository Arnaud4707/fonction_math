#include "../../include/fonction_math.h"

t_maps*		init_maps(char *file)
{
	FILE *fd;
	t_maps *map;
	char *line = NULL;
	int read;
	size_t size = 1000;
	int size_line;
	t_maps* head;

	fd = fopen(file, "r");
	if (!fd)
		return(NULL);
	map = malloc(sizeof(t_maps));
	head = map;
	read = getline(&line, &size, fd);
	if (read <= 0)
	{
		dprintf(2, "Error: Can't read file\n");
		return (NULL);
	}
	size_line = read;
	map->line = strdup(line);
	map->next = NULL;
	read = getline(&line, &size, fd);
	while (read == size_line)
	{
		map->next = malloc(sizeof(t_maps));
		map->next->line = strdup(line);
		map->next->next = NULL;
		map = map->next;
		read = getline(&line, &size, fd);
	}
	free(line);
	return (head);
}

void	init_mat_identite(t_mat *mat)
{
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			mat->mat[i][j] = 0;
		}
	}
	for (int i = 0; i < 4; i++){
		mat->mat[i][i] = 1;
	}
}

void	init_param_cam_lookat(t_camera* cam)
{
	cam->position.x = 0;
	cam->position.y = 0;
	cam->position.z = 10;
	cam->position.w = 1;
}

void	init_matrice(t_matrice *matrice)
{
	matrice->mode = 2; // 1: isométrie 2: perspective
	matrice->offsetX = WIDTH / 2;
	matrice->offsetY = HEIGHT / 2;
	matrice->scale.scaleXY = 1;
	matrice->scale.scaleZ = 1;
	//---------
	matrice->angles.angleY = M_PI / 4;
	matrice->angles.angleX = atan(1.0 / sqrt(2));
	matrice->angles.angleZ = 0;
	init_mat_rotate_x(&(matrice->mat_rotateX), matrice->angles.angleX);
	init_mat_rotate_y(&(matrice->mat_rotateY), matrice->angles.angleY);
	init_mat_rotate_z(&(matrice->mat_rotateZ), matrice->angles.angleZ);
	init_mat_scale(&(matrice->mat_scale), matrice->scale.scaleXY, matrice->scale.scaleXY, matrice->scale.scaleZ);
	init_mat_translation(&(matrice->mat_translation), 0, 0, 0);
	build_matrix_world(matrice);
	matrice->cam.pitch = 10 * M_PI / 180.0;
	matrice->cam.yaw = 10 * M_PI / 180.0;
	init_param_cam_lookat(&(matrice->cam));
	if (matrice->mode == 1)
		init_projection_ortho(&(matrice->mat_projection), -10, 10, -10, 10, 0.1, 100);
	else
		init_project_perspective(&(matrice->mat_projection), M_PI / 3, (double)WIDTH / HEIGHT, 1000.0, 0.1);
	build_matrix_view_fps(&(matrice->mat_view), &( matrice->cam));
}
