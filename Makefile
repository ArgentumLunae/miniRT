# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mteerlin <mteerlin@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/03/16 08:52:20 by mteerlin      #+#    #+#                  #
#    Updated: 2021/04/13 09:50:18 by mteerlin      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	= minirt.out

SRC_DIR = src/

SRC		= sortoutmaths.c \
			get_next_line.c \
			get_next_line_utils.c \
			rt_parse_scene.c \
			obj_camera.c \
			obj_cylinder.c \
			obj_light.c obj_plane.c \
			obj_sphere.c \
			obj_square.c \
			obj_triangle.c \
			rt_util_structs.c \
			rt_free_scene.c \
			rt_free_utils.c \
			rt_sphere_inter.c \
			rt_light_angle.c \
			vectormaths.c \
			colour_utils.c \
			intersect_plane.c
OBJ		= $(SRC:.c=.o)
HDR		= get_next_line.h \
			minirt.h \
			rtscene.h
LIBFT	= $(LIB_DIR)libft.a

CFLAGS	= -Wall -Wextra -Werror

all: 		$(NAME)

$(NAME):	$(OBJ)
			$(CC) -Lmlx -lmlx -Llibft -lft -framework OpenGL -framework AppKit $(OBJ) -o $(NAME)
#			$(CC) -fsanitize=address -g $(OBJ) -Lmlx_linux -lmlx -Llibft -lft -Imlx -Ilibft -Iget_next_line -L/usr/lib -lXext -lX11 -lm -lz -o $(NAME)

%.o:		%.c $(HDR)
			$(CC) $(CFLAGS) -Imlx -Ilibft -Iget_next_line -c $< -o $@

clean:
			rm -f *.o *.so

fclean:
			$(MAKE) clean
			rm -f $(NAME)

re:
			$(MAKE) fclean
			$(MAKE) all

.PHONY:		all clean fclean re