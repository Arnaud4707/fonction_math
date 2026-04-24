GREEN  = '\033[0;32m'
RED    = '\033[0;31m'
BRUN   = '\033[0;33m'
WHITE  = '\033[1;37m'
RESET  = '\033[0m'

NAME = boxtool

CC = cc

HEADER= include/fonction_math.h include/color.h include/grilles.h \
		include/matrice.h include/struct_fonction.h include/background.h \
		include/game_of_life.h include/object.h include/matrice_fonction.h

HEADER_MAIN= core.h

CFLAGS = -Wall -Wextra -Werror #-O3 #-march=native -ffast-math

MAIN = main.c

MLX_PATH = mlx/

LIB_MLX = libmlx.a

SRC_PATH = src/

SRC_DIR = utils.c world/trigonometrie_math.c world/renderer_math.c world/functions_math.c \
		world/events_math.c world/init_math.c world/animation_math.c \
		world_2/events_matrix.c world_2/init_matrix.c world_2/matrice_matrix.c \
		world_2/renderer_matrix.c world_2/shader_matrix.c world_2/skybox.c world_2/fdf.c\
		world_3/game_of_life.c world_3/renderer_game_of_life.c \
		world_3/events_game_of_life.c world_3/init_game_of_life.c

SRC = $(addprefix $(SRC_PATH), $(SRC_DIR))

OBJ_PATH = obj/

OBJ = $(addprefix $(OBJ_PATH), $(SRC_DIR:.c=.o))

MLX = $(MLX_PATH)$(LIB_MLX)

MAIN = main.c

OBJ_MAIN = obj/main.o

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(HEADER)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(MLX) $(OBJ) main.c $(HEADER_MAIN)
	$(CC) $(CFLAGS) -c main.c -DWORLD=3 -o $(OBJ_MAIN)
	$(CC) $(CFLAGS) $(OBJ) $(OBJ_MAIN) $(MLX) -lX11 -lXext -lm -o $(NAME) 

all: $(NAME)


$(MLX):
	@echo $(BRUN) "Compiling mlx..."$(RESET)
	@make -sC $(MLX_PATH)
	@echo $(GREEN) "MLX Ready" $(RESET)

world: $(MLX) $(OBJ) main.c $(HEADER_MAIN)
	$(CC) $(CFLAGS) -c main.c -DWORLD=1 -o $(OBJ_MAIN)
	$(CC) $(CFLAGS) $(OBJ) $(OBJ_MAIN) $(MLX) -lX11 -lXext -lm -o $(NAME) 

world_2: $(MLX) $(OBJ) main.c $(HEADER_MAIN)
	$(CC) $(CFLAGS) -c main.c -DWORLD=2 -o $(OBJ_MAIN)
	$(CC) $(CFLAGS) $(OBJ) $(OBJ_MAIN) $(MLX) -lX11 -lXext -lm -o $(NAME) 

world_3: $(MLX) $(OBJ) main.c $(HEADER_MAIN)
	$(CC) $(CFLAGS) -c main.c -DWORLD=3 -o $(OBJ_MAIN)
	$(CC) $(CFLAGS) $(OBJ) $(OBJ_MAIN) $(MLX) -lX11 -lXext -lm -o $(NAME) 

clean:
	@echo $(RED) "Delate main.o" $(RESET)
	rm -rf $(OBJ_PATH)

fclean: clean
	@echo $(RED) "Delate $(NAME)" $(RESET)
	rm -rf $(NAME)
	@echo "Delate mlx" $(RESET)
	@make clean -C $(MLX_PATH)

re: 
	$(MAKE) fclean
	$(MAKE) all 

.PHONY: all clean fclean re