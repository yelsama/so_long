/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:36:36 by ymohamed          #+#    #+#             */
/*   Updated: 2022/10/19 08:51:29 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	assign_dirs_windname_elemnts(t_game_ptr *mygame,
t_wind_dims *wind, t_elmt_dir *dir)
{
	mygame->g_wind_name = "so_long";
	wind->valid_elmts = "01CEPN\n";
	dir->wall_dir = "./images/wall_2.xpm";
	dir->ground_dir = "./images/bg_1.xpm";
	dir->collec1_dir = "./images/collectable_1.xpm";
	dir->collec2_dir = "./images/collectable_2.xpm";
	dir->player_dir = "./images/playera_1.xpm";
	dir->player_dir_a = "./images/playera_2.xpm";
	dir->exit_dir = "./images/exit_1.xpm";
	dir->enem_dir1 = "./images/en1.xpm";
	dir->enem_dir2 = "./images/en2.xpm";
	dir->enem_dir3 = "./images/en3.xpm";
}

int	main(int argc, char *argv[])
{
	t_game_ptr		mygame;
	t_wind_dims		wind;
	t_elmt_dir		dir;
	t_all_to_rndr	all;

	assign_dirs_windname_elemnts(&mygame, &wind, &dir);
	if (argc < 2)
		ft_printf("Error\nNo map has been chosen, prog exiting");
	if (argc < 2)
		return (0);
	wind.enemies = 0;
	if (!map_is_valid(argv[1], &wind, ".ber"))
		return (0);
	if (!all_paths_valid(&wind))
		return (0);
	initiate_g(&mygame, &wind, &dir, &all);
	while (--wind.main_windy)
		free(wind.two_d_map[wind.main_windy]);
	free(wind.two_d_map[0]);
	free(wind.two_d_map);
	return (0);
}
