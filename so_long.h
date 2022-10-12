/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:49:04 by ymohamed          #+#    #+#             */
/*   Updated: 2022/10/13 00:52:15 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "./resources/mlx/mlx.h"
# include "./resources/get_next_line/get_next_line.h"
# include "./resources/ft_libft_printf/ft_libft_printf.h"
# include <fcntl.h>
#include <stdio.h>

# define BLOCK_DIM 64

//Reprsents all the map characteristics to be changed if needed
typedef enum e_map_elemants
{
	player = 'P',
	collectible = 'C',
	enemy = 'N',
	exit_point = 'E',
	wall = '1',
	ground = '0'
}	t_valid_entities;

//Initiate the game to run
typedef struct s_game_ptr
{
	void	*game_ptr;
	void	*window;
	char	*g_wind_name;
}	t_game_ptr;

//Define Hight and Widht of the main window and each block dimentsion
typedef struct s_g_window_sizes
{
	int		main_windx;
	int		main_windy;
	int		block_xy;
	int		collects;
	int		exit_fond;
	int		plyr_fond;
	char	*valid_elmts;
	char	**two_d_map;
}	t_wind_dims;

//Used in map validation to to load neede elemnts
typedef struct s_stackmap_elmt
{
	char	*all_map;
	char	*line;
	int		fd;
	int		ret;
}	t_stak_map_elmnts;

//Defice image directories for the game elemnts
typedef struct s_directories_for_elements
{
	char	*wall_dir;
	char	*player_dir;
	char	*collec_dir;
	char	*exit_dir;
	char	*enem_dir;
}	t_elmt_dir;

//Represents the whole image of the frame
typedef struct s_g_entities_im
{
	void	*wall;
}	t_entities;

int	map_is_valid(char *argv, t_wind_dims *wind, char *vext);
int	initiate_g(t_game_ptr *mygame, t_wind_dims *wind, t_elmt_dir *dir);

#endif