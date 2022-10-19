/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_enemy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 02:14:59 by ymohamed          #+#    #+#             */
/*   Updated: 2022/10/19 20:14:10 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	set_inital_enemyframe(t_game_ptr *mygame, t_wind_dims *wind,
								t_elmt_dir *dir, t_entities *entity)
{
	entity->enemy = malloc(sizeof(void *));
	entity->enemy1 = mlx_xpm_file_to_image(mygame->game_ptr, dir->enem_dir1,
			&wind->block_xy, &wind->block_xy);
	entity->enemy2 = mlx_xpm_file_to_image(mygame->game_ptr, dir->enem_dir2,
			&wind->block_xy, &wind->block_xy);
	entity->enemy3 = mlx_xpm_file_to_image(mygame->game_ptr, dir->enem_dir3,
			&wind->block_xy, &wind->block_xy);
	if (!entity->enemy || !entity->enemy1 || !entity->enemy2 || !entity->enemy3)
		return (0);
	entity->temp_enemy = entity->enemy;
	return (1);
}

int	enemy_actions(t_all_to_rndr *all)
{
	static int	compare_mv;
	static int	slower;

	slower++;
	if (slower % 15 != 0)
		return (0);
	if (compare_mv == 0)
	{
		all->entity->enemy = all->entity->enemy1;
		compare_mv++;
	}
	else if (compare_mv == 1)
	{
		all->entity->enemy = all->entity->enemy2;
		compare_mv++;
	}
	else if (compare_mv > 1)
	{
		all->entity->enemy = all->entity->enemy3;
		compare_mv = 0;
	}
	//add Enemy patrol here
	return (0);
}
