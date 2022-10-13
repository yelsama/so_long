/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_ginitiate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 10:23:30 by ymohamed          #+#    #+#             */
/*   Updated: 2022/10/13 21:57:45 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	set_player_pos(t_wind_dims *wind, t_pp *p)
{
	p->py = -1;
	while (++p->py < wind->main_windy)
	{
		p->px = -1;
		while (++p->px < wind->main_windx)
		{
			if (wind->two_d_map[p->py][p->px] == player)
				break ;
		}
		if (wind->two_d_map[p->py][p->px] == player)
			break ;
	}
	wind->player_pos = *p;
}

static void	img_to_wind(void *entity, t_game_ptr *mygame, int x, int y)
{
	mlx_put_image_to_window(mygame->game_ptr, mygame->window,
		entity, x * BLOCK_DIM, y * BLOCK_DIM);
}

static void	load_map(t_game_ptr *mygame, t_entities *entity, t_wind_dims *wind)
{
	int	x;
	int	y;

	x = -1;
	y = -1;
	while (++y < wind->main_windy)
	{
		while (++x < wind->main_windx)
		{
			if (wind->two_d_map[y][x] == player)
				img_to_wind(entity->player, mygame, x, y);
			else if (wind->two_d_map[y][x] == wall)
				img_to_wind(entity->wall, mygame, x, y);
			else if (wind->two_d_map[y][x] == collectible)
				img_to_wind(entity->collec, mygame, x, y);
			else if (wind->two_d_map[y][x] == exit_point && wind->collects < 1)
				img_to_wind(entity->exit, mygame, x, y);
			else if (wind->two_d_map[y][x] == enemy)
				img_to_wind(entity->enemy, mygame, x, y);
			else
				img_to_wind(entity->ground, mygame, x, y);
		}
		x = -1;
	}
}

static void	set_inital_frame(t_game_ptr *mygame, t_wind_dims *wind,
								t_elmt_dir *dir, t_entities *entity)
{
	entity->wall = mlx_xpm_file_to_image(mygame->game_ptr, dir->wall_dir,
			&wind->block_xy, &wind->block_xy);
	entity->ground = mlx_xpm_file_to_image(mygame->game_ptr, dir->ground_dir,
			&wind->block_xy, &wind->block_xy);
	entity->player = mlx_xpm_file_to_image(mygame->game_ptr, dir->player_dir,
			&wind->block_xy, &wind->block_xy);
	entity->collec = mlx_xpm_file_to_image(mygame->game_ptr, dir->collec_dir,
			&wind->block_xy, &wind->block_xy);
	entity->exit = mlx_xpm_file_to_image(mygame->game_ptr, dir->exit_dir,
			&wind->block_xy, &wind->block_xy);
	entity->enemy = mlx_xpm_file_to_image(mygame->game_ptr, dir->enem_dir,
			&wind->block_xy, &wind->block_xy);
}

//starts the game main window and set its dimentions
int	initiate_g(t_game_ptr *mygame, t_wind_dims *wind, t_elmt_dir *dir)
{
	t_entities		entity;
	t_pp			pp;

	mygame->game_ptr = mlx_init();
	mygame->window = mlx_new_window(mygame->game_ptr,
			wind->main_windx * BLOCK_DIM, wind->main_windy * BLOCK_DIM,
			mygame->g_wind_name);
	set_inital_frame(mygame, wind, dir, &entity);
	load_map(mygame, &entity, wind);
	set_player_pos(wind, &pp);
	// mlx_key_hook(mygame->window, am_func, NULL);
	mlx_hook(mygame->window, 2, 1, &playgame, wind);
	//  mlx_hook()
	return (1);
}
