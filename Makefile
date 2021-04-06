# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mteerlin <mteerlin@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/03/16 08:52:20 by mteerlin      #+#    #+#                  #
#    Updated: 2021/04/06 19:51:12 by mteerlin      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	= minirt.out
SRC		= playwithmaths.c \
			get_next_line.c \
			get_next_line_utils.c \
			startparce.c \
			freescene.c \
			vectormaths.c
OBJ		= $(SRC:.c=.o)
HDR		= get_next_line.h \
			minirt.h \
			vmaths.h
LIBFT	= $(LIB_DIR)libft.a

CFLAGS	= -Wall -Wextra -Werror

all: 		$(NAME)

$(NAME):	$(OBJ) $(HDR)
			$(CC) -fsanitize=address -g -Lmlx -lmlx -Llibft -lft -framework OpenGL -framework AppKit $(OBJ) -o $(NAME)
#			$(CC) -fsanitize=address -g $(OBJ) -Lmlx_linux -lmlx -Llibft -lft -Imlx -Ilibft -L/usr/lib -lXext -lX11 -lm -lz -o $(NAME)

%.o:		%.c
			$(CC) $(CFLAGS) -Imlx -Ilibft -Ivmaths -Iget_next_line -c $< -o $@

clean:
			rm -f *.o *.so

fclean:
			$(MAKE) clean
			rm -f $(NAME)

re:
			$(MAKE) fclean
			$(MAKE) all

.PHONY:		all clean fclean re