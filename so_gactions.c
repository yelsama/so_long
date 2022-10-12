/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_gactions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 10:23:30 by ymohamed          #+#    #+#             */
/*   Updated: 2022/10/13 00:56:33 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	load_to_map(t_game_ptr *mygame, t_entities *entity, t_wind_dims *wind)
{
	int	x;
	int	y;

	x = -1;
	y = -1;
	while (++y < wind->main_windy)
	{
		while (++x < wind->main_windx)
		{
			if (wind->two_d_map[y][x] == '1')
				mlx_put_image_to_window(mygame->game_ptr, mygame->window,
					entity->wall, x * BLOCK_DIM, y * BLOCK_DIM);
		}
		x = -1;
	}
	return (1);
}

static int	set_inital_frame(t_game_ptr *mygame, t_wind_dims *wind,
								t_elmt_dir *dir)
{
	t_entities		entity;

	entity.wall = mlx_xpm_file_to_image(mygame->game_ptr, dir->wall_dir,
			&wind->block_xy, &wind->block_xy);
	if (!load_to_map(mygame, &entity, wind))
		return (0);
	return (1);
}

//starts the game main window and set its dimentions
int	initiate_g(t_game_ptr *mygame, t_wind_dims *wind, t_elmt_dir *dir)
{
	mygame->game_ptr = mlx_init();
	mygame->window = mlx_new_window(mygame->game_ptr,
			wind->main_windx * BLOCK_DIM, wind->main_windy * BLOCK_DIM,
			mygame->g_wind_name);
	if (!set_inital_frame(mygame, wind, dir))
		return (0);
	// mlx_key_hook(mygame->window, am_func, NULL);
	return (1);
}
