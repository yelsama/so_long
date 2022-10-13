/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:36:36 by ymohamed          #+#    #+#             */
/*   Updated: 2022/10/13 21:56:51 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char *argv[])
{
	t_game_ptr	mygame;
	t_wind_dims	wind;
	t_elmt_dir	dir;

	mygame.g_wind_name = "so_long";
	wind.valid_elmts = "01CEPN\n";
	dir.wall_dir = "./images/wall_2.xpm";
	dir.ground_dir = "./images/bg_1.xpm";
	dir.collec_dir = "./images/collectable_1.xpm";
	dir.player_dir = "./images/player_1.xpm";
	dir.exit_dir = "./images/exit_1.xpm";
	dir.enem_dir = "./images/enemy_1.xpm";
	if (argc < 2)
		ft_printf("Error\nNo map has been chosen, prog exiting");
	if (argc < 2)
		return (0);
	if (!map_is_valid(argv[1], &wind, ".ber"))
		return (0);
	//check rout validity
	//
	if (!initiate_g(&mygame, &wind, &dir))
		return (0);
	mlx_loop(mygame.game_ptr);
	return (0);
}
