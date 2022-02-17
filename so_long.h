/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 18:44:55 by bbordere          #+#    #+#             */
/*   Updated: 2022/02/17 15:48:09 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "minilibx-linux/mlx.h"
// # include <mlx.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft/libft.h"

typedef struct s_assets
{
    void    *floor;
    void    *wall;
    void    *collec;
}	t_assets;

typedef	struct s_game
{
	int		width;
	int		height;
	int		sprite_size;
	void	*mlx;
	void	*win;
}	t_game;

typedef struct s_map
{
	int	x;
	int	y;
	int	fd_map;
}	t_map;


#endif