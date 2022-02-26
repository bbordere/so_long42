# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/16 20:31:26 by bbordere          #+#    #+#              #
#    Updated: 2022/02/25 20:16:48 by bbordere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Werror -Wextra

NAME = so_long

FILES = test.c map_checker.c

SRCS = $(FILES)

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	# $(CC) $(CFLAGS) $(OBJS) libft/libft.a -lmlx -lXext -lX11 -o $(NAME)
	$(MAKE) -s all -C libft
	$(CC) $(OBJS) libft/libft.a minilibx-linux/libmlx.a -lXext -lX11 -o $(NAME)
all: $(NAME)

clean:
	rm -f ${OBJS}
	$(MAKE) -s clean -C libft

fclean : clean
	rm -f $(NAME)
	$(MAKE) -s fclean -C libft

re: fclean all

re_bonus: fclean bonus

.PHONY: all clean fclean re bonus re_bonus
