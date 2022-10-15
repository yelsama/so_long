/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_ginitiate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 10:23:30 by ymohamed          #+#    #+#             */
/*   Updated: 2022/10/15 20:25:49 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	set_player_exit_pos(t_wind_dims *wind, t_pp *p, t_pp *e)
{
	p->py = -1;
	while (++p->py < wind->main_windy)
	{
		p->px = -1;
		while (++p->px < wind->main_windx)
			if (wind->two_d_map[p->py][p->px] == player)
				break ;
		if (wind->two_d_map[p->py][p->px] == player)
			break ;
	}
	e->py = -1;
	while (++e->py < wind->main_windy)
	{
		e->px = -1;
		while (++e->px < wind->main_windx)
			if (wind->two_d_map[e->py][e->px] == exit_point)
				break ;
		if (wind->two_d_map[e->py][e->px] == exit_point)
			break ;
	}
	wind->exit_pos = e;
	wind->player_pos = p;
}

static void	img_to_wind(void *entity, t_game_ptr *mygame, int x, int y)
{
	mlx_put_image_to_window(mygame->game_ptr, mygame->window,
		entity, x * BLOCK_DIM, y * BLOCK_DIM);
}

int	load_map(t_all_to_rndr *all)
{
	int	x;
	int	y;

	y = -1;
	while (++y < all->wind->main_windy)
	{
		x = -1;
		while (++x < all->wind->main_windx)
		{
			if (all->wind->two_d_map[y][x] == player)
				img_to_wind(all->entity->player, all->mygame, x, y);
			else if (all->wind->two_d_map[y][x] == wall)
				img_to_wind(all->entity->wall, all->mygame, x, y);
			else if (all->wind->two_d_map[y][x] == collectible)
				img_to_wind(all->entity->collec, all->mygame, x, y);
			else if (all->wind->two_d_map[y][x] == exit_point &&
			all->wind->collects < 1)
				img_to_wind(all->entity->exit, all->mygame, x, y);
			else if (all->wind->two_d_map[y][x] == enemy)
				img_to_wind(all->entity->enemy, all->mygame, x, y);
			else
				img_to_wind(all->entity->ground, all->mygame, x, y);
		}
	}
	return (0);
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
	entity->player_a = mlx_xpm_file_to_image(mygame->game_ptr,
			dir->player_dir_a, &wind->block_xy, &wind->block_xy);
	entity->collec = mlx_xpm_file_to_image(mygame->game_ptr, dir->collec_dir,
			&wind->block_xy, &wind->block_xy);
	entity->exit = mlx_xpm_file_to_image(mygame->game_ptr, dir->exit_dir,
			&wind->block_xy, &wind->block_xy);
	entity->enemy = mlx_xpm_file_to_image(mygame->game_ptr, dir->enem_dir,
			&wind->block_xy, &wind->block_xy);
}

//starts the game main window and set its dimentions
int	initiate_g(t_game_ptr *mygame, t_wind_dims *wind, t_elmt_dir *dir,
t_all_to_rndr *all)
{
	t_entities		entity;
	t_pp			pp;
	t_pp			ep;

	mygame->game_ptr = mlx_init();
	mygame->window = mlx_new_window(mygame->game_ptr,
			wind->main_windx * BLOCK_DIM, wind->main_windy * BLOCK_DIM,
			mygame->g_wind_name);
	set_inital_frame(mygame, wind, dir, &entity);
	set_player_exit_pos(wind, &pp, &ep);
	all->entity = &entity;
	all->mygame = mygame;
	all->wind = wind;
	mlx_hook(mygame->window, 2, 0, playgame, all);
	mlx_hook(mygame->window, 17, 0, sl_exit, all);
	mlx_loop_hook(mygame->game_ptr, load_map, all);
	mlx_loop(mygame->game_ptr);
	return (1);
}
