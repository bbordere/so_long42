/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 18:44:55 by bbordere          #+#    #+#             */
/*   Updated: 2022/03/07 10:59:44 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft.h"

# define UP 1
# define DOWN 2
# define LEFT 3
# define RIGHT 4
# define SPRITE_SIZE 64

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_assets
{
	t_img	*floor;
	t_img	*wall;
	t_img	*collec;
	t_img	*collec2;
	t_img	*collec3;
	t_img	*exit;
}	t_assets;

typedef struct s_map
{
	int		x;
	int		y;
	int		width;
	int		item;
	int		exit;
	int		start;
	int		height;
	char	**map;
	int		fd_map;
}	t_map;

typedef struct s_player
{
	t_img	*img_b;
	t_img	*img_f;
	t_img	*img_r;
	t_img	*img_l;
	int		x;
	int		on_exit;
	int		y;
	int		nb_col;
	int		dir;
	int		move;

}	t_player;

typedef struct s_enemy
{
	t_img	*img_b;
	t_img	*img_f;
	int		dir;
	int		on_wall;
}	t_enemy;

typedef struct s_data
{
	t_assets	*assets;
	t_map		*map;
	t_img		*img;
	t_player	*player;
	t_enemy		*enemy;
	int			sprite_size;
	void		*mlx;
	void		*win;
	int			c_tick;
	int			e_tick;
}	t_data;

int			ft_check_map_char(t_map *map);
void		ft_check_extension(char *file);
void		ft_free_map(char **map);
void		*ft_free_img(t_img	*img, void *mlx);
void		*ft_free_assets(t_assets *assets, void *mlx);
void		*ft_free_enemy(t_enemy *enemy, void *mlx);
void		*ft_free_player(t_player *player, void *mlx);
void		*ft_free(void *ptr);
t_img		*ft_init_img(void *mlx, char *path, int width, int height);
t_assets	*ft_init_assets(void *mlx);
t_player	*ft_init_player(void *mlx);
t_enemy		*ft_init_enemy(void *mlx);
t_data		*ft_init_data(char *path);
t_map		*ft_init_map(char *file);
void		*ft_free_data(t_data *data);
void		ft_paint(t_img *element, t_img *mlx_img, int x, int y);
void		ft_free_map(char **map);

void		ft_destroy_img(t_data *data);
void		ft_free_player_assets(t_data *data);
int			ft_free_mlx(t_data *data);
void		ft_down(t_data *data);
void		ft_print_collec(t_data *data);
void		ft_print_steps(t_data *data);
void		ft_up(t_data *data);
void		ft_left(t_data *data);
void		ft_move(int *comp, int set, t_player *player);
void		ft_paint_up(t_data *data);
void		ft_on_exit(t_data *data);
void		ft_right(t_data *data);
void		ft_error_exit_msg(void *ptr1, void *ptr2, char *msg);
int			ft_key_hook(int keycode, t_data *data);
int			ft_quit(t_data *data);
void		ft_on_exit(t_data *data);
void		ft_render_map(t_data *data);
void		ft_render_player(t_data *data, int x, int y);
void		ft_paint_up(t_data *data);
void		ft_paint_down(t_data *data);
void		ft_paint_left(t_data *data);
void		*ft_free_enemy(t_enemy *enemy, void *mlx);
void		ft_paint_right(t_data *data);
void		ft_check_enemy(t_data *data, int dir);
int			ft_quit_msg(t_data *data, char *msg);
void		ft_do_move_enemy(t_data *data, int x, int y, int dir);
void		ft_anim_enemy(t_data *data, int x, int y);
void		ft_anim_pot(t_data *data, int x, int y);
void		ft_do_anim(t_data *data);
int			ft_animations(t_data *data);
int			ft_key_hook_bonus(int keycode, t_data *data);
int			ft_notify(t_data *data);

#endif
