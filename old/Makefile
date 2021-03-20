NAME = CUB3D

CC = clang
MLX_DIR = minilibx-linux
MLX = libmlx.a

CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address

HEADER = srcs/cub3d.h

SRCS = srcs/cub3d.c \
		srcs/init.c \
		srcs/tools.c \
		srcs/tools2.c \
		srcs/save.c \
		srcs/get_next_line.c \
		srcs/get_next_line_utils.c \
		srcs/error.c \
		srcs/parsing_params.c \
		srcs/parse_map.c \
		srcs/check_map_zero.c \
		test.c \
		srcs/raycasting_init.c \
		srcs/raycating.c \
		srcs/keys.c \
		srcs/raycasting_utils.c \
		srcs/draw.c \
		srcs/raycasting_moving.c \
		srcs/sprites.c

OBJ = $(SRCS:.c=.o)
CFLAGS+=-I $(MLX_DIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(MLX_DIR)/$(MLX) -lm -lbsd -lX11 -lXext
	@echo $(NAME) : created.


all : $(NAME)

clean :
	rm -rf $(SRCS_O) 
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)
	rm -rf a.out

re : fclean all

.PHONY: all clean fclean re