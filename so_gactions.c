/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_gactions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 19:22:21 by ymohamed          #+#    #+#             */
/*   Updated: 2022/10/21 02:54:20 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	free_enemies(t_all_to_rndr *all)
{
	free (all->entity->temp_enemy);
	mlx_destroy_image(all->mygame->game_ptr, all->entity->enemy1);
	mlx_destroy_image(all->mygame->game_ptr, all->entity->enemy2);
	mlx_destroy_image(all->mygame->game_ptr, all->entity->enemy3);
	enmy_lst_clear(&all->wind->e_list);
}

int	sl_exit(t_all_to_rndr *all, int out)
{
	if (!out)
	{
		mlx_destroy_image(all->mygame->game_ptr, all->entity->temp_coll);
		mlx_destroy_image(all->mygame->game_ptr, all->entity->collec1);
		mlx_destroy_image(all->mygame->game_ptr, all->entity->collec2);
		mlx_destroy_image(all->mygame->game_ptr, all->entity->exit);
		mlx_destroy_image(all->mygame->game_ptr, all->entity->ground);
		mlx_destroy_image(all->mygame->game_ptr, all->entity->player);
		mlx_destroy_image(all->mygame->game_ptr, all->entity->player_a);
		mlx_destroy_image(all->mygame->game_ptr, all->entity->wall);
		if (all->wind->enemies)
			free_enemies(all);
		mlx_clear_window(all->mygame->game_ptr, all->mygame->window);
		mlx_destroy_window(all->mygame->game_ptr, all->mygame->window);
	}
	while (--all->wind->main_windy)
		free(all->wind->two_d_map[all->wind->main_windy]);
	free(all->wind->two_d_map[0]);
	free(all->wind->two_d_map);
	return (exit(out), 1);
}

int	move_coin(t_all_to_rndr *all)
{
	static int	compare_mv;
	static int	slower;

	slower++;
	if (slower % 30 != 0)
		return (0);
	if (compare_mv == 0)
	{
		all->entity->collec = all->entity->collec1;
		compare_mv++;
	}
	else if (compare_mv == 1)
	{
		all->entity->collec = all->entity->collec2;
		compare_mv = 0;
	}
	if (slower == 30000000)
		slower = 0;
	return (0);
}

int	playgame(int keycode, t_all_to_rndr *all)
{
	static int	moves;
	void		*tmp;
	t_pp		newpp;
	t_pp		oldpp;

	oldpp = all->wind->player_pos;
	tmp = all->entity->player;
	ft_bzero(&newpp, sizeof(t_pp));
	if (valid_key(keycode, &newpp, oldpp) && all->wind->plyr_fond)
	{
		if (set_move(newpp, all->wind->player_pos, all) && all->wind->plyr_fond)
			ft_printf("number of moves %d\n", ++moves);
		all->entity->player = all->entity->player_a;
		all->entity->player_a = tmp;
	}
	if (all->wind->collects < 1)
		all->wind->two_d_map[all->wind->exit_pos.py][all->wind->exit_pos.px]
			= exit_point;
	all->wind->pmoves = moves;
	all->pmoves = moves;
	if (keycode == 53)
		sl_exit(all, 0);
	return (1);
}
