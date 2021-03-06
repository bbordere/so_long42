# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/16 20:31:26 by bbordere          #+#    #+#              #
#    Updated: 2022/06/10 13:15:40 by bbordere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

INCLUDES = includes/

CFLAGS = -Wall -Werror -Wextra -I $(INCLUDES) -g3

NAME = so_long

BONUS = so_long_bonus

FILES = src/main.c src/paint_move.c src/map_checker.c src/cleaning.c \
		 src/init.c src/map.c src/paint.c src/exiting.c src/move.c src/hook.c \
		 src/render.c src/error.c

FILES_BONUS = bonus/main_bonus.c bonus/map_checker_bonus.c src/map.c src/paint.c \
			bonus/init.c  bonus/cleaning.c bonus/move.c src/paint_move.c \
			src/hook.c bonus/move_enemy.c bonus/print_infos.c bonus/render.c \
			bonus/animations.c bonus/exiting.c bonus/hook_bonus.c src/error.c

SRCS = $(FILES)

SRCS_BONUS= $(FILES_BONUS)

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

$(NAME): $(OBJS)
	@$(MAKE) -s all -C minilibx-linux
	@ printf '\033[0;33mCompiling Libft\033[0m\n'
	@$(MAKE) -s all -C libft
	@printf '\033[0;32mLibft compiled sucessfully !\033[0m\n'
	@printf '\033[0;33mCompiling so_long\033[0m\n'
	@$(CC) $(CFLAGS) $(OBJS) libft/libft.a minilibx-linux/libmlx.a -lXext -lX11 -o $(NAME)
	@printf '\033[0;32mso_long compiled sucessfully ! Have fun x)\033[0m\n'

all: $(NAME)

clean:
	@rm -f ${OBJS}
	@rm -f ${OBJS_BONUS}
	@$(MAKE) -s clean -C minilibx-linux
	@$(MAKE) -s clean -C libft
	@printf '\033[0;32mclean done\033[0m\n'

fclean : clean
	@rm -f $(NAME)
	@rm -f $(BONUS)
	@$(MAKE) -s fclean -C libft
	@printf '\033[0;32mfclean done\033[0m\n'

bonus: $(OBJS_BONUS)
	@$(MAKE) -s all -C minilibx-linux
	@ printf '\033[0;33mCompiling Libft\033[0m\n'
	@$(MAKE) -s all -C libft
	@printf '\033[0;32mLibft compiled sucessfully !\033[0m\n'
	@printf '\033[0;33mCompiling so_long\033[0m\n'
	@$(CC) $(CFLAGS) $(OBJS_BONUS) libft/libft.a minilibx-linux/libmlx.a -lXext -lX11 -o $(BONUS)
	@printf '\033[0;32mso_long compiled sucessfully ! Have fun x)\033[0m\n'

re: fclean all

re_bonus: fclean bonus

.PHONY: all clean fclean re bonus re_bonus

.SILENT: ${OBJS_BONUS} ${OBJS}
