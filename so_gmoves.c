/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_gmoves.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:08:32 by ymohamed          #+#    #+#             */
/*   Updated: 2022/10/22 09:11:51 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	you_win(t_pp	newpp, t_pp oldpp, t_all_to_rndr *all)
{
	all->wind->two_d_map[oldpp.py][oldpp.px] = ground;
	all->wind->two_d_map[newpp.py][newpp.px] = exit_point;
	ft_printf("You Win the Game\n");
	all->wind->plyr_fond--;
	sl_exit(all, 0);
}

void	game_over(t_all_to_rndr *all)
{
	ft_printf("You lost\nGame Over\n");
	sl_exit(all, 0);
}

static void	moveplayer(t_pp	newpp, t_pp oldpp, t_all_to_rndr *all)
{
	all->wind->two_d_map[oldpp.py][oldpp.px] = ground;
	all->wind->two_d_map[newpp.py][newpp.px] = player;
	all->wind->player_pos.px = newpp.px;
	all->wind->player_pos.py = newpp.py;
}

int	set_move(t_pp newpp, t_pp oldpp, t_all_to_rndr *all)
{
	oldpp = all->wind->player_pos;
	if (newpp.py < 1 || newpp.px < 1)
		return (0);
	if (all->wind->two_d_map[newpp.py][newpp.px] == wall)
		return (0);
	if (all->wind->two_d_map[newpp.py][newpp.px] == ground)
		moveplayer(newpp, oldpp, all);
	if (all->wind->two_d_map[newpp.py][newpp.px] == collectible)
	{
		moveplayer(newpp, oldpp, all);
		all->wind->collects--;
	}
	if (all->wind->two_d_map[newpp.py][newpp.px] == enemy)
	{
		all->wind->two_d_map[oldpp.py][oldpp.px] = ground;
		all->wind->two_d_map[newpp.py][newpp.px] = enemy;
		game_over(all);
	}
	if (all->wind->two_d_map[newpp.py][newpp.px] == exit_point &&
	all->wind->collects > 0)
		moveplayer(newpp, oldpp, all);
	if (all->wind->two_d_map[newpp.py][newpp.px] == exit_point &&
	all->wind->collects < 1)
		you_win(newpp, oldpp, all);
	return (1);
}

int	valid_key(int key, t_pp *newpp, t_pp oldpp)
{
	if (key == 126 || key == 13)
	{
		newpp->px = oldpp.px;
		newpp->py = oldpp.py - 1;
	}
	else if (key == 125 || key == 1)
	{
		newpp->px = oldpp.px;
		newpp->py = oldpp.py + 1;
	}
	else if (key == 124 || key == 2)
	{
		newpp->px = oldpp.px + 1;
		newpp->py = oldpp.py;
	}
	else if (key == 123 || key == 0)
	{
		newpp->px = oldpp.px - 1;
		newpp->py = oldpp.py;
	}
	else
		return (0);
	return (1);
}
