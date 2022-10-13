/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_gactions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 19:22:21 by ymohamed          #+#    #+#             */
/*   Updated: 2022/10/13 21:59:09 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	playgame(int keycode, t_wind_dims *wind)
{
	static int	moves;

	(void)wind;
	ft_printf ("number of keboard strikes %d\n", ++moves);
	if (keycode == 53)  // or mouse on x
	{
		//free all what needed to be free
		exit(0);
	}
	return (1);
}
