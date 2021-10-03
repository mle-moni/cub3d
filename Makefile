# used this as inspiration to make it work on linux
# https://github.com/iciamyplant/Cub3d-Linux/

SRC =	bonus/main.c \
		bonus/parsing.c \
		bonus/utils.c \
		gnl/get_next_line.c \
		gnl/get_next_line_utils.c \
		bonus/get_params.c \
		bonus/config.c \
		bonus/parse_map.c \
		bonus/split.c \
		bonus/utils2.c \
		bonus/draw.c \
		bonus/game/hooks.c \
		bonus/game/move.c \
		bonus/game/raycast.c \
		bonus/game/dda.c \
		save/bmp.c \
		bonus/game/display_sprites.c \
		bonus/init.c \
		bonus/game/fps.c \
		bonus/game/hud.c \
		bonus/game/bonus_move.c \
		bonus/game/shift_color.c \
		bonus/game/koopa.c \
		bonus/game/laiktu.c \
		bonus/game/change_map.c \
		bonus/game/konami.c

NAME = Cub3D

MLX_DIR = minilibx-linux
MLX = libmlx.a 
CC = clang

# diff entre .a et .dylib
# .a = lib static, les fonctions utilisees sont directement ecrite dans le binaire
# .dylib = lib dynamique, les fonctions doivent etre chargees au momnent ou on lance le binaire

CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address

OBJ_DIR = obj
SRC_DIR = .
INC_DIR = inc

OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
DPD = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.d))

.c.o:
	${CC} ${CFLAGS} -c$< -o ${<:.c=.o}

# -C faire make comme si on etait dana le dossier
# -j multisreder / ameliore la vitesse de compliation
# Pas de regle opti car makefile mlx pas compatible
all:
	@$(MAKE) -j $(NAME)

# permet de pouvoir comparer la derniere modification de la dep par rapport a la regle
# -L donner le nom du dossier / -l donner le nom le la lib
# loader path = ecrit le chemin de la mlx dans le binaire pour pouvoir la retrouver au moment ou on lance le binaire
$(NAME): $(OBJ)
		${CC} $(CFLAGS) -o $(NAME) $(OBJ) -L $(MLX_DIR) -lmlx -lm -lbsd -lX11 -lXext
		@echo $(NAME) : Created !

# si le .c est plus recent que le .o on rentre dans la regle
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | .gitignore
		@mkdir -p $(OBJ_DIR)
		${CC} $(CFLAGS) -I $(INC_DIR) -I $(MLX_DIR) -c $< -o $@

.gitignore:
		@echo $(NAME) > .gitignore

clean:
	@rm -f $(OBJ_DIR)/**/*.o $(OBJ_DIR)/*.o 
	@echo "obj deleted"

fclean:	clean
	@rm -rf $(NAME)
	@echo "[$(NAME)]: deleted"

re: fclean all

.PHONY: all, clean, fclean, re

# Utilise les .d (et ignore s'ils n'existe pas)
-include $(DPD)