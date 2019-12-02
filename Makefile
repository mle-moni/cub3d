SRCS1    = mandatory/main.c mandatory/parsing.c mandatory/utils.c gnl/get_next_line.c gnl/get_next_line_utils.c mandatory/get_params.c mandatory/config.c mandatory/parse_map.c mandatory/split.c mandatory/utils2.c
SRCS2    = mandatory/draw.c mandatory/game/hooks.c mandatory/game/move.c mandatory/game/raycast.c mandatory/game/dda.c save/bmp.c mandatory/game/display_sprites.c mandatory/init.c
BSRCS1   = bonus/main.c bonus/parsing.c bonus/utils.c gnl/get_next_line.c gnl/get_next_line_utils.c bonus/get_params.c bonus/config.c bonus/parse_map.c bonus/split.c bonus/utils2.c
BSRCS2   = bonus/draw.c bonus/game/hooks.c bonus/game/move.c bonus/game/raycast.c bonus/game/dda.c save/bmp.c bonus/game/display_sprites.c bonus/init.c
BSRCS3   = bonus/game/fps.c bonus/game/hud.c bonus/game/bonus_move.c bonus/game/shift_color.c bonus/game/koopa.c bonus/game/laiktu.c bonus/game/change_map.c bonus/game/konami.c
OBJS    = ${SRCS1:.c=.o} ${SRCS2:.c=.o}
B_OBJS    = ${BSRCS1:.c=.o} ${BSRCS2:.c=.o} ${BSRCS3:.c=.o}
NAME    = Cub3D
BNAME    = Cub3D_BONUS
RM      = rm -f
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror
L_FLAGS	= -lmlx -framework OpenGL -framework AppKit
.c.o:
			${CC} ${CFLAGS} -I. -c $< -o ${<:.c=.o}
${NAME}:    ${OBJS}
			${CC} ${CFLAGS} -g3 -fsanitize=address ${L_FLAGS} -o ${NAME} ${OBJS}
bonus:    	${B_OBJS}
			${CC} ${CFLAGS} -g3 -fsanitize=address ${L_FLAGS} -o ${BNAME} ${B_OBJS}
all:        ${NAME}
clean:
			${RM} ${OBJS} ${B_OBJS}
debug:		${OBJS}
			${CC} ${CFLAGS} -g ${L_FLAGS} -o a.out ${OBJS}
fclean:     clean
			${RM} ${NAME} a.out ${BNAME}
re:         fclean all
.PHONY:     all clean fclean re bonus