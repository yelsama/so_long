/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_validmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 22:44:08 by ymohamed          #+#    #+#             */
/*   Updated: 2022/10/17 15:58:11 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	cells_validation(char *almp, int *cnt, int *rcnt, t_wind_dims *wind)
{
	int	ret;

	ret = 1;
	wind->exit_fond = 0;
	wind->plyr_fond = 0;
	while (almp[++(*cnt)] != '\0')
	{
		(*rcnt)++;
		if (almp[*cnt] == '\n')
		{
			if (*rcnt != wind->main_windx +1 || almp[*cnt - 1] != wall
				|| almp[*cnt + 1] != wall)
				ret = 0;
			*rcnt = 0;
		}
		if (!ft_strchr(wind->valid_elmts, almp[*cnt]))
			ret = 0;
		if (almp[*cnt] == exit_point)
			wind->exit_fond++;
		if (almp[*cnt] == collectible)
			wind->collects++;
		if (almp[*cnt] == player)
			wind->plyr_fond++;
	}
	return (ret * wind->exit_fond * wind->collects * wind->plyr_fond);
}

static int	fill_valid_map(char *almp, t_wind_dims *wind)
{
	int	cnt;
	int	rcnt;
	int	ret;

	cnt = -1;
	rcnt = 0;
	ret = 1;
	wind->collects = 0;
	while (almp[++cnt] != '\n')
		if (almp[cnt] != wall)
			ret = 0;
	if (cnt != wind->main_windx || almp[cnt + 1] != wall)
		ret = 0;
	ret *= cells_validation(almp, &cnt, &rcnt, wind);
	if (rcnt != wind->main_windx)
		return (0);
	while (--rcnt)
		if (almp[--cnt] != wall)
			ret = 0;
	if (ret)
		wind->two_d_map = ft_split(almp, '\n');
	if (ret)
		wind->temp_two_d_map = ft_split(almp, '\n');
	return (ret);
}

static int	valid_proccess(char *map_direc, t_wind_dims *wind)
{
	t_stak_map_elmnts	mymap;

	mymap.ret = 0;
	mymap.all_map = 0;
	mymap.fd = open(map_direc, O_RDONLY);
	if (mymap.fd == -1)
		return (0);
	mymap.line = get_next_line(mymap.fd);
	if (mymap.line == NULL)
		return (0);
	wind->main_windx = ft_strlen(mymap.line) - 1;
	wind->main_windy = 0;
	while (mymap.line != NULL)
	{
		mymap.all_map = gnl_strjoin(mymap.all_map, mymap.line);
		free(mymap.line);
		mymap.line = get_next_line(mymap.fd);
		wind->main_windy++;
	}
	if (wind->main_windx)
		mymap.ret = fill_valid_map(mymap.all_map, wind);
	free(mymap.all_map);
	close(mymap.fd);
	return (mymap.ret);
}

static int	valid_extension(char *name, char *vext)
{
	char	*name_ext;

	name_ext = ft_strrchr(name, '.');
	if (!ft_strncmp(vext, name_ext, 4))
		return (1);
	ft_printf("Error\nInvalid map extention. Exiting");
	return (0);
}

int	map_is_valid(char *argv, t_wind_dims *wind, char *vext)
{
	if (!valid_extension(argv, vext))
		return (0);
	if (!valid_proccess(argv, wind) || wind->exit_fond + wind->plyr_fond > 2)
	{
		ft_printf("Error\ncan't read or invalid map");
		return (0);
	}
	wind->block_xy = BLOCK_DIM;
	return (1);
}
