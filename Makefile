# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/16 20:31:26 by bbordere          #+#    #+#              #
#    Updated: 2022/02/23 14:51:46 by bbordere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

# CFLAGS = -Wall -Werror -Wextra

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

fclean : clean
	rm -f $(NAME)

re: fclean all

re_bonus: fclean bonus

.PHONY: all clean fclean re bonus re_bonus