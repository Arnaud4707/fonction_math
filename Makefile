GREEN  = '\033[0;32m'
RED    = '\033[0;31m'
BRUN   = '\033[0;33m'
WHITE  = '\033[1;37m'
RESET  = '\033[0m'

NAME = graph

CC = cc

HEADER= include/fonction_math.h include/color.h include/grilles.h \
		include/matrice.h include/struct_fonction.h include/background.h \
		include/game_of_life.h include/object.h include/matrice_fonction.h

CFLAGS = -Wall -Wextra -Werror -I./ #-O3 #-march=native -ffast-math

MAIN = main.c

MLX_PATH = mlx/

LIB_MLX = libmlx.a

SRC_PATH = src/

SRC_DIR = utils.c trigonometrie.c renderer.c functions.c \
		events.c init.c grilles.c animation.c matrice.c \
		game_of_life.c

SRC = $(addprefix $(SRC_PATH), $(SRC_DIR))

OBJ_PATH = obj/

OBJ = $(addprefix $(OBJ_PATH), $(SRC_DIR:.c=.o))

MLX = $(MLX_PATH)$(LIB_MLX)

MAIN = main.c

OBJ_MAIN = obj/main.o

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(HEADER)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(MLX) $(OBJ) $(OBJ_MAIN) 
	$(CC) $(CFLAGS) $(OBJ) $(OBJ_MAIN) $(MLX) -lX11 -lXext -lm -o $(NAME) 

all: $(NAME)

$(OBJ_MAIN): main.c  $(HEADER)
	$(CC) $(CFLAGS) -c main.c -o $(OBJ_MAIN)

$(MLX):
	@echo $(BRUN) "Compiling mlx..."$(RESET)
	@make -sC $(MLX_PATH)
	@echo $(GREEN) "MLX Ready" $(RESET)

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