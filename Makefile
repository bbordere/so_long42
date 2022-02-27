# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/16 20:31:26 by bbordere          #+#    #+#              #
#    Updated: 2022/02/27 10:50:15 by bbordere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g3

NAME = so_long

FILES = test.c map_checker.c

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
