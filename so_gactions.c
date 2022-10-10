/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_gactions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 10:23:30 by ymohamed          #+#    #+#             */
/*   Updated: 2022/10/10 20:56:29 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	load_to_map(t_game_ptr *mygame, t_entities *entity, t_dimentions axes, t_dim_limits brd_lmt)
{
	char	*map_line;
	int		fd;

	fd = open(mygame->map_name, O_RDONLY);
	if(fd == -1)
		return (0);
	while (++axes.y < brd_lmt.y_lim)
	{
		map_line = get_next_line(fd);
		if (map_line == NULL)
			break ;
		while (++axes.x < brd_lmt.x_lim)
		{
			if (map_line[axes.x] == '1')
				mlx_put_image_to_window(mygame->game_ptr, mygame->window, entity->wall,  axes.x * BLOCK_DIM, axes.y * BLOCK_DIM);
		}
		free(map_line);
		axes.x = -1;
	}
	close(fd);
	return (1);
}

int	set_inital_frame(t_game_ptr *mygame, t_wind_dims *wind)
{
	t_dimentions	axes;
	t_dim_limits	brd_lmt;
	t_entities		entity;

	axes.x = -1;
	axes.y = -1;
	brd_lmt.x_lim = wind->main_windx / BLOCK_DIM;
	brd_lmt.y_lim = wind->main_windy / BLOCK_DIM;
	entity.wall = mlx_xpm_file_to_image(mygame->game_ptr, "./images/wall_3.xpm", &wind->block_xy, &wind->block_xy);
	if (!load_to_map(mygame, &entity, axes, brd_lmt))
		return (0);
	return (1);
}
//starts the game main window and set its dimentions
int	initiate_g(t_game_ptr *mygame, t_wind_dims *wind)
{
	mygame->game_ptr = mlx_init();
	mygame->window = mlx_new_window(mygame->game_ptr, wind->main_windx, wind->main_windy, mygame->g_wind_name);
	if (!set_inital_frame(mygame, wind))
		return (0);
	// mlx_key_hook(mygame->window, am_func, NULL);
	return (1);
}
