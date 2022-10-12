/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:36:36 by ymohamed          #+#    #+#             */
/*   Updated: 2022/10/13 00:53:40 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char *argv[])
{
	t_game_ptr	mygame;
	t_wind_dims	wind;
	t_elmt_dir	dir;

	mygame.g_wind_name = "so_long";
	wind.valid_elmts = "01CEP\n";
	dir.wall_dir = "./images/wall_3.xpm";
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
