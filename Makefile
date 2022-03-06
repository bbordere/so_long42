# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/16 20:31:26 by bbordere          #+#    #+#              #
#    Updated: 2022/03/06 23:34:35 by bbordere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

INCLUDES = includes/

CFLAGS = -Wall -Werror -Wextra -I $(INCLUDES)

NAME = so_long

FILES = src/test.c map_checker.c src/cleaning.c src/init.c src/map.c src/paint.c src/exiting.c src/move.c

FILES_BONUS = test_bonus.c map_checker.c

SRCS = $(FILES)

SRCS_BONUS= $(FILES_BONUS)

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

$(NAME): $(OBJS)
	# $(CC) $(CFLAGS) $(OBJS) libft/libft.a -lmlx -lXext -lX11 -o $(NAME)
	$(MAKE) -s all -C minilibx-linux
	$(MAKE) -s all -C libft
	$(CC) $(OBJS) libft/libft.a minilibx-linux/libmlx.a -lXext -lX11 -o $(NAME)
all: $(NAME)

clean:
	rm -f ${OBJS}
	$(MAKE) -s clean -C minilibx-linux
	$(MAKE) -s clean -C libft

fclean : clean
	rm -f $(NAME)
	$(MAKE) -s fclean -C libft

bonus: $(OBJS_BONUS)
	$(MAKE) -s all -C minilibx-linux
	$(MAKE) -s all -C libft
	$(CC) $(CFLAGS) $(OBJS_BONUS) libft/libft.a minilibx-linux/libmlx.a -lXext -lX11 -o $(NAME)

re: fclean all

re_bonus: fclean bonus

.PHONY: all clean fclean re bonus re_bonus
