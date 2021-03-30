# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mteerlin <mteerlin@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/03/16 08:52:20 by mteerlin      #+#    #+#                  #
#    Updated: 2021/03/30 16:32:25 by mteerlin      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	= minirt.out
SRC		= playwithmaths.c \
			get_next_line.c \
			get_next_line_utils.c \
		startparce.c
OBJ		= $(SRC:.c=.o)
HDR		= get_next_line.h \
			minirt.h

CFLAGS	= -Wall -Wextra -Werror

all: 		$(NAME)

$(NAME):	$(OBJ)
				$(CC) -fsanitize=address -g -Lmlx -lmlx -Llibft -lft -framework OpenGL -framework AppKit $(OBJ) -o $(NAME)

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