/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_gactions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 19:22:21 by ymohamed          #+#    #+#             */
/*   Updated: 2022/10/15 04:14:26 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	playgame(int keycode, t_all_to_rndr *all)
{
	static int	moves;
	t_pp		newpp;
	t_pp		oldpp;

	if (go_dir(all, keycode, &newpp, &oldpp))
		ft_printf("number of moves %d\n", ++moves);
	if (keycode == 53)  // or mouse on x
	{
		//free all what needed to be free
		exit(0);
	}
	return (1);
}
