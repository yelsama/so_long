/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_validpath.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 17:21:08 by ymohamed          #+#    #+#             */
/*   Updated: 2022/10/16 23:49:10 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	free_print_message(t_wind_dims *wind)
{
	ft_printf("Error\nMap has one or more invalid path\nExiting");
	free(wind->player_pos);
	free(wind->exit_pos);
}

static void	set_player_exit_pos(t_wind_dims *wind)
{
	wind->player_pos->py = -1;
	while (++wind->player_pos->py < wind->main_windy)
	{
		wind->player_pos->px = -1;
		while (++wind->player_pos->px < wind->main_windx)
			if (wind->two_d_map[wind->player_pos->py]
				[wind->player_pos->px] == player)
				break ;
		if (wind->two_d_map[wind->player_pos->py]
			[wind->player_pos->px] == player)
			break ;
	}
	wind->exit_pos->py = -1;
	while (++wind->exit_pos->py < wind->main_windy)
	{
		wind->exit_pos->px = -1;
		while (++wind->exit_pos->px < wind->main_windx)
			if (wind->two_d_map[wind->exit_pos->py]
				[wind->exit_pos->px] == exit_point)
				break ;
		if (wind->two_d_map[wind->exit_pos->py]
			[wind->exit_pos->px] == exit_point)
			break ;
	}
}

static int	patrol_path(int px, int py, char **map, t_wind_dims *wind)
{
	if (map[py][px] == 'X' || map[py][px] == '1')
		return (0);
	if (map[py][px] == 'C')
		wind->collects--;
	else if (map[py][px] == 'E')
		wind->exit_fond--;
	map[py][px] = 'X';
	if (px + 1 < wind->main_windx)
		patrol_path(px + 1, py, map, wind);
	if (px - 1 > 0)
		patrol_path(px - 1, py, map, wind);
	if (py - 1 > 0)
		patrol_path(px, py - 1, map, wind);
	if (py + 1 < wind->main_windy)
		patrol_path(px, py + 1, map, wind);
	return (0);
}

int	all_paths_valid(t_wind_dims *wind)
{
	int		valid_collect;
	int		valid_exit;
	int		row;

	row = -1;
	wind->player_pos = malloc(sizeof(t_pp *));
	wind->exit_pos = malloc(sizeof(t_pp *));
	if (!wind->player_pos || !wind->exit_pos)
		return (0);
	set_player_exit_pos(wind);
	valid_collect = wind->collects;
	valid_exit = wind->exit_fond;
	patrol_path(wind->player_pos->px, wind->player_pos->py,
		wind->temp_two_d_map, wind);
	while (++row < wind->main_windy)
		free(wind->temp_two_d_map[row]);
	free(wind->temp_two_d_map);
	if (wind->collects > 0 || wind->exit_fond > 0)
	{
		free_print_message(wind);
		return (0);
	}
	wind->collects = valid_collect;
	wind->exit_fond = valid_exit;
	return (1);
}
