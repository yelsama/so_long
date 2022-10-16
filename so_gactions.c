/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_gactions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 19:22:21 by ymohamed          #+#    #+#             */
/*   Updated: 2022/10/17 02:13:28 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	playgame(int keycode, t_all_to_rndr *all)
{
	static int	moves;
	void		*tmp;
	t_pp		newpp;
	t_pp		oldpp;

	tmp = all->entity->player;
	if (valid_key(keycode, &newpp, &oldpp, all) && all->wind->plyr_fond)
	{
		if (set_move(&newpp, &oldpp, all) && all->wind->plyr_fond)
			ft_printf("number of moves %d\n", ++moves);
		all->entity->player = all->entity->player_a;
		all->entity->player_a = tmp;
	}
	if (all->wind->collects < 1)
		all->wind->two_d_map[all->wind->exit_pos->py][all->wind->exit_pos->px]
			= exit_point;
	if (keycode == 53)
		sl_exit(all);
	return (1);
}
