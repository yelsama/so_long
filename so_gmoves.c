/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_gmoves.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:08:32 by ymohamed          #+#    #+#             */
/*   Updated: 2022/10/15 03:57:30 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	moveplayer(t_pp	*newpp, t_pp *oldpp, t_all_to_rndr *all)
{
	all->wind->two_d_map[oldpp->py][oldpp->px] = ground;
	all->wind->two_d_map[newpp->py][newpp->px] = player;
	all->wind->player_pos->px = newpp->px;
	all->wind->player_pos->py = newpp->py;
}

static int	set_move(t_pp *newpp, t_pp *oldpp, t_all_to_rndr *all)
{
	if (newpp->py < 1 || newpp->px < 1)
		return (0);
	if (all->wind->two_d_map[newpp->py][newpp->px] == wall)
		return (0);
	if (all->wind->two_d_map[newpp->py][newpp->px] == ground)
		moveplayer(newpp, oldpp, all);
	if (all->wind->two_d_map[newpp->py][newpp->px] == collectible)
	{
		moveplayer(newpp, oldpp, all);
		all->wind->collects--;
	}
	if (all->wind->two_d_map[newpp->py][newpp->px] == enemy)///////
	{
		all->wind->two_d_map[oldpp->py][oldpp->px] = ground;
		//game_over(wind);
	}
	if (all->wind->two_d_map[newpp->py][newpp->px] == exit_point &&
	all->wind->collects > 0)
		moveplayer(newpp, oldpp, all);
	return (1);
}

int	go_dir(t_all_to_rndr *all, int dir, t_pp *newpp, t_pp *oldpp)
{
	oldpp = all->wind->player_pos;
	if (dir == 126 || dir == 13)
	{
		newpp->px = oldpp->px;
		newpp->py = oldpp->py - 1;
	}
	else if (dir == 125 || dir == 1)
	{
		newpp->px = oldpp->px;
		newpp->py = oldpp->py + 1;
	}
	else if (dir == 124 || dir == 2)
	{
		newpp->px = oldpp->px + 1;
		newpp->py = oldpp->py;
	}
	else if (dir == 123 || dir == 0)
	{
		newpp->px = oldpp->px - 1;
		newpp->py = oldpp->py;
	}
	else
		return (0);
	return (set_move(newpp, oldpp, all));
}
