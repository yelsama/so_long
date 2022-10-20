/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_enmylst_utls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 18:45:29 by ymohamed          #+#    #+#             */
/*   Updated: 2022/10/21 02:53:42 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	enmy_lst_clear(t_enemies **e_lst)
{
	t_enemies	*tmp;

	if (!*e_lst || !e_lst)
		return (0);
	while ((*e_lst)->next_e != NULL)
	{
		tmp = (*e_lst)->next_e;
		free (*e_lst);
		*e_lst = tmp;
	}
	free(*e_lst);
	e_lst = NULL;
	return (0);
}

static int	add_enemy_tolst(t_pp e, t_enemies **e_lst)
{
	t_enemies	*new;
	t_enemies	*tmp;

	new = malloc(sizeof(t_enemies));
	if (!new)
		return (0);
	new->dir = 1;
	new->e_pos = e;
	new->next_e = NULL;
	if (*e_lst == NULL)
		*e_lst = new;
	else
	{
		tmp = *e_lst;
		while (tmp->next_e != NULL)
			tmp = tmp->next_e;
		tmp->next_e = new;
	}
	return (1);
}

int	set_enemieslst(t_wind_dims *wind)
{
	t_enemies	*tmp;
	t_pp		pnt;
	int			ret;

	if (!wind->enemies)
		return (1);
	tmp = NULL;
	ret = 1;
	pnt.py = -1;
	while (++pnt.py < wind->main_windy)
	{
		pnt.px = -1;
		while (++pnt.px < wind->main_windx)
			if (wind->two_d_map[pnt.py][pnt.px] == enemy)
				ret *= add_enemy_tolst(pnt, &tmp);
	}
	wind->e_list = tmp;
	return (ret);
}
