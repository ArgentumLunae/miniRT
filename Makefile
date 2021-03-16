# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mteerlin <mteerlin@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/03/16 08:52:20 by mteerlin      #+#    #+#                  #
#    Updated: 2021/03/16 10:04:12 by mteerlin      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	= minirt
SRC		= testimage.c
OBJ		= $(SRC:.c=.o)
HDR		=

CFLAGS	= -Wall -Wextra -Werror

all: 		$(NAME)

$(NAME):	$(OBJ)
				$(CC) -Lmlx -lmlx -framework OpenGL -framework AppKit $(OBJ) libft/libft.a -o $(NAME)

%.o:		%.c
			$(CC) $(CFLAGS) -Imlx -Ilibft -c $< -o $@

clean:
			rm -f *.o *.so

fclean:
			$(MAKE) clean
			rm -f $(NAME)

re:
			$(MAKE) fclean
			$(MAKE) all

.PHONY:		all clean fclean re