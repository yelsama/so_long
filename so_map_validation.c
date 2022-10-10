/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_map_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 22:44:08 by ymohamed          #+#    #+#             */
/*   Updated: 2022/10/10 21:04:46 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

typedef struct s_stackmap_elmt
{
	char	*all_map;
	char	*line;
	int		fd;
}	t_stak_map_elmnts;

static int	wall_valid_elmnts(char *map_direc, t_wind_dims *wind)
{
	t_stak_map_elmnts	mymap;

	mymap.all_map = 0;
	mymap.fd = open(map_direc, O_RDONLY);
	if(mymap.fd == -1)
		return (0);
	mymap.line = get_next_line(mymap.fd);
	wind->main_windx = ft_strlen(mymap.line) - 1;
	wind->main_windy = 0;
	while (mymap.line != NULL)
	{
		mymap.all_map = gnl_strjoin(mymap.all_map, mymap.line);
		free(mymap.line);
		mymap.line = get_next_line(mymap.fd);
		wind->main_windy++;
	}
	puts(mymap.all_map);   /////////
	//if valid fill as tow D or free everything and return error
	free(mymap.all_map);	////////
	return (1);
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
	if (!wall_valid_elmnts(argv, wind))
	{
		ft_printf("Error\ncan't read map");
		return (0);
	}
	ft_printf("this number of rows %d\n", wind->main_windy);
	ft_printf("this number of coloms %d\n", wind->main_windx);
	wind->main_windx *= BLOCK_DIM;
	wind->main_windy *= BLOCK_DIM;
	wind->block_xy = BLOCK_DIM;
	return (1);
}