/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:49:04 by ymohamed          #+#    #+#             */
/*   Updated: 2022/10/10 21:00:47 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "./resources/mlx/mlx.h"
# include "./resources/get_next_line/get_next_line.h"
# include "./resources/ft_libft_printf/ft_libft_printf.h"
# include <fcntl.h>
//# include <stdlib.h>
#include <stdio.h>

# define BLOCK_DIM 64

//Initiate the game to run
typedef struct s_game_ptr
{
	void	*game_ptr;
	void	*window;
	char	*map_name;
	char	*g_wind_name;
}	t_game_ptr;

//Define Hight and Widht of the main window and each block dimentsion
typedef struct s_g_window_sizes
{
	int	main_windx;
	int	main_windy;
	int	block_xy;
}	t_wind_dims;

//Define Map Characteristics to read through G.N.L
typedef struct s_mapread_args
{
	int		fd;
	int		clms;
	int		rws;
	char	*crnt_line;
}	t_mapread_args;




//Set X Y dimetions for xy demand
typedef struct s_dimentions
{
	int	x;
	int	y;
}	t_dimentions;

//Holds values of limts for moves towards x and y
typedef struct s_dim_lop_lim
{
	int	x_lim;
	int	y_lim;
}	t_dim_limits;

//Represents the whole image of the frame
typedef struct s_g_entities_im
{
	void	*wall;
}	t_entities;

int	map_is_valid(char *argv, t_wind_dims *wind, char *vext);
int	initiate_g(t_game_ptr *mygame, t_wind_dims *wind);

#endif