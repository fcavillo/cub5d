NAME = CUB3D

CC = clang
MLX_DIR = minilibx-linux
MLX = libmlx.a

CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address

HEADER = includes/cub3d.h

SRCS = srcs/check_zeros.c \
		srcs/cub3d.c \
		srcs/draw.c \
		srcs/errors.c \
		srcs/gnl_utils.c \
		srcs/gnl.c \
		srcs/initialize.c \
		srcs/keys.c \
		srcs/parse_map.c \
		srcs/parse_params.c \
		srcs/ray_initialize.c \
		srcs/ray_move.c \
		srcs/ray_utils.c \
		srcs/ray.c \
		srcs/save.c \
		srcs/sprite.c \
		srcs/tools.c \
		srcs/tools2.c


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