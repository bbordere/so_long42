# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/16 20:31:26 by bbordere          #+#    #+#              #
#    Updated: 2022/02/16 20:35:43 by bbordere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

NAME = so_long

FILES = test.c

SRCS = $(FILES)

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(OBJS) libft/libft.a -lmlx -lXext -lX11 -o $(NAME)

all: $(NAME)

clean:
	rm -f ${OBJS}

fclean : clean
	rm -f $(NAME)

re: fclean all

re_bonus: fclean bonus

.PHONY: all clean fclean re bonus re_bonus