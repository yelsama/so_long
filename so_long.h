/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:49:04 by ymohamed          #+#    #+#             */
/*   Updated: 2022/10/26 10:04:19 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "./resources/mlx/mlx.h"
# include "./resources/get_next_line/get_next_line.h"
# include "./resources/ft_libft_printf/ft_libft_printf.h"
# include <fcntl.h>

# define BLOCK_DIM 64

//Reprsents all the map characteristics to be changed if needed
typedef enum e_map_elements
{
	player = 'P',
	collectible = 'C',
	enemy = 'N',
	exit_point = 'E',
	wall = '1',
	ground = '0'
}	t_valid_entities;

//To represent a map position (x,y)
typedef struct s_point_pos
{
	int	px;
	int	py;
}	t_pp;

//Initiate the game to run
typedef struct s_game_ptr
{
	void	*game_ptr;
	void	*window;
	char	*g_wind_name;
}	t_game_ptr;

// creates a list of enemies
typedef struct s_enimies
{
	t_pp				e_pos;
	int					dir;
	struct s_enimies	*next_e;
}	t_enemies;

//Define Map info like Hight and Widht of the main window and each
//block dimentsion
typedef struct s_g_window_sizes
{
	int			main_windx;
	int			main_windy;
	int			block_xy;
	int			collects;
	int			exit_fond;
	int			plyr_fond;
	int			enemies;
	int			pmoves;
	char		*valid_elmts;
	char		**two_d_map;
	char		**temp_two_d_map;
	t_pp		player_pos;
	t_pp		exit_pos;
	t_enemies	*e_list;
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
	char	*player_dir_a;
	char	*collec1_dir;
	char	*collec2_dir;
	char	*exit_dir;
	char	*enem_dir1;
	char	*enem_dir2;
	char	*enem_dir3;
	char	*ground_dir;
}	t_elmt_dir;

//Represents the whole image of the frame
typedef struct s_g_entities_im
{
	void	*wall;
	void	*ground;
	void	*player;
	void	*player_a;
	void	*collec;
	void	*collec1;
	void	*collec2;
	void	*exit;
	void	*enemy;
	void	*enemy1;
	void	*enemy2;
	void	*enemy3;
	void	*temp_enemy;
	void	*temp_coll;
}	t_entities;

//All elemnts needed to render game map
typedef struct s_all_to_render
{
	t_wind_dims	*wind;
	t_entities	*entity;
	t_game_ptr	*mygame;
	int			pmoves;
}	t_all_to_rndr;

int		map_is_valid(char *argv, t_wind_dims *wind, char *vext);
int		all_paths_valid(t_wind_dims *wind);
int		initiate_g(t_game_ptr *mygame, t_wind_dims *wind,
			t_elmt_dir *dir, t_all_to_rndr *all);
int		playgame(int keycode, t_all_to_rndr *all);
int		valid_key(int key, t_pp *newpp, t_pp oldpp);
int		set_move(t_pp newpp, t_pp oldpp, t_all_to_rndr *all, int *moves);
int		move_coin(t_all_to_rndr *all);
int		enemy_actions(t_all_to_rndr *all);
int		set_inital_enemyframe(t_game_ptr *mygame, t_wind_dims *wind,
			t_elmt_dir *dir, t_entities *entity);
void	chose_load_entity(t_all_to_rndr *all, t_pp *pnt);
int		sl_exit(t_all_to_rndr *all, int out);
int		set_enemieslst(t_wind_dims *wind);
int		enmy_lst_clear(t_enemies **e_lst);
void	game_over(t_all_to_rndr *all);

#endif