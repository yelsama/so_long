/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_gactions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 19:22:21 by ymohamed          #+#    #+#             */
/*   Updated: 2022/10/15 20:26:48 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	playgame(int keycode, t_all_to_rndr *all)
{
	static int	moves;
	static void	*tmp;
	t_pp		newpp;
	t_pp		oldpp;

	tmp = all->entity->player;
	if (all->wind->collects > 0)
	{
		if (go_dir(all, keycode, &newpp, &oldpp))
		{
			ft_printf("number of moves %d\n", ++moves);
			all->entity->player = all->entity->player_a;
			all->entity->player_a = tmp;
		}
	}
	if (keycode == 53)
		sl_exit(all);
	return (1);
}
