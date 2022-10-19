/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_ginitiate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 10:23:30 by ymohamed          #+#    #+#             */
/*   Updated: 2022/10/19 20:03:28 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	img_to_wind(void *entity, t_game_ptr *mygame, int x, int y)
{
	mlx_put_image_to_window(mygame->game_ptr, mygame->window,
		entity, x * BLOCK_DIM, y * BLOCK_DIM);
}

void	chose_load_entity(t_all_to_rndr *all, t_pp *pnt)
{
	if (all->wind->two_d_map[pnt->py][pnt->px] == player)
		img_to_wind(all->entity->player, all->mygame, pnt->px, pnt->py);
	else if (all->wind->two_d_map[pnt->py][pnt->px] == wall)
		img_to_wind(all->entity->wall, all->mygame, pnt->px, pnt->py);
	else if (all->wind->two_d_map[pnt->py][pnt->px] == collectible)
		img_to_wind(all->entity->collec, all->mygame, pnt->px, pnt->py);
	else if (all->wind->two_d_map[pnt->py][pnt->px] == exit_point &&
	all->wind->collects < 1)
		img_to_wind(all->entity->exit, all->mygame, pnt->px, pnt->py);
	else if (all->wind->two_d_map[pnt->py][pnt->px] == enemy)
		img_to_wind(all->entity->enemy, all->mygame, pnt->px, pnt->py);
	else
		img_to_wind(all->entity->ground, all->mygame, pnt->px, pnt->py);
}

static int	load_map(t_all_to_rndr *all)
{
	t_pp	pnt;

	if (all->wind->enemies)
		enemy_actions(all);
	move_coin(all);
	pnt.py = -1;
	while (++pnt.py < all->wind->main_windy)
	{
		pnt.px = -1;
		while (++pnt.px < all->wind->main_windx)
			chose_load_entity(all, &pnt);
	}
	mlx_string_put(all->mygame->game_ptr, all->mygame->window,
		20, 20, 00250, ft_itoa(all->wind->pmoves));
	return (0);
}

static int	set_inital_frame(t_game_ptr *mygame, t_wind_dims *wind,
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
	entity->collec = mlx_xpm_file_to_image(mygame->game_ptr, dir->collec1_dir,
			&wind->block_xy, &wind->block_xy);
	entity->collec1 = mlx_xpm_file_to_image(mygame->game_ptr, dir->collec1_dir,
			&wind->block_xy, &wind->block_xy);
	entity->collec2 = mlx_xpm_file_to_image(mygame->game_ptr, dir->collec2_dir,
			&wind->block_xy, &wind->block_xy);
	entity->exit = mlx_xpm_file_to_image(mygame->game_ptr, dir->exit_dir,
			&wind->block_xy, &wind->block_xy);
	entity->temp_coll = entity->collec;
	if (!entity->wall || !entity->ground || !entity->player || !entity->player_a
		|| !entity->collec || !entity->collec1 || !entity->collec2
		|| !entity->exit)
		return (0);
	return (1);
}

//starts the game main window and set its dimentions
int	initiate_g(t_game_ptr *mygame, t_wind_dims *wind, t_elmt_dir *dir,
t_all_to_rndr *all)
{
	t_entities		entity;

	mygame->game_ptr = mlx_init();
	mygame->window = mlx_new_window(mygame->game_ptr,
			wind->main_windx * BLOCK_DIM, wind->main_windy * BLOCK_DIM,
			mygame->g_wind_name);
	if (!mygame->game_ptr || !mygame->window)
		return (0);
	if (!set_inital_frame(mygame, wind, dir, &entity))
		sl_exit(all, 1);
	all->entity = &entity;
	all->mygame = mygame;
	all->wind = wind;
	if (wind->enemies && !set_inital_enemyframe(mygame, wind, dir, &entity))
		sl_exit(all, 1);
	mlx_hook(mygame->window, 2, 0, playgame, all);
	mlx_hook(mygame->window, 17, 0, sl_exit, all);
	mlx_loop_hook(mygame->game_ptr, load_map, all);
	mlx_loop(mygame->game_ptr);
	return (1);
}
