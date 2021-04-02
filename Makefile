# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mteerlin <mteerlin@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/03/16 08:52:20 by mteerlin      #+#    #+#                  #
#    Updated: 2021/04/02 15:54:01 by mteerlin      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	= minirt.out
SRC		= minirt.c \
			get_next_line.c \
			get_next_line_utils.c \
			startparce.c \
			freescene.c
OBJ		= $(SRC:.c=.o)
HDR		= get_next_line.h \
			minirt.h
LIBFT	= $(LIB_DIR)libft.a

CFLAGS	= -Wall -Wextra -Werror

all: 		$(NAME)

$(NAME):	$(OBJ) $(HDR)
#			$(CC) -Lmlx_linux -lmlx -Llibft -lft -framework OpenGL -framework AppKit $(OBJ) -o $(NAME)
			$(CC) -fsanitize=address -g $(OBJ) -Lmlx_linux -lmlx -Llibft -lft -Imlx -Ilibft -L/usr/lib -lXext -lX11 -lm -lz -o $(NAME)

%.o:		%.c
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