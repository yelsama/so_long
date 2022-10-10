/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 20:44:09 by ymohamed          #+#    #+#             */
/*   Updated: 2022/10/10 08:41:23 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_left(char *onboard)
{
	char	*left;
	int		i;
	int		c;

	i = 0;
	c = 0;
	while (onboard[i] != '\0' && onboard[i] != '\n')
		i++;
	if (onboard[i] == '\0')
	{
		free(onboard);
		return (NULL);
	}
	left = gnl_calloc((gnl_strlen(onboard) - i + 1), sizeof(char));
	if (!left)
		return (NULL);
	i++;
	while (onboard[i])
		left[c++] = onboard[i++];
	free(onboard);
	return (left);
}

char	*get_aline(char *onboard)
{	
	char	*line;
	int		i;

	i = 0;
	if (!onboard[0])
		return (NULL);
	while (onboard[i] != '\n' && onboard[i] != '\0')
		i++;
	i++;
	line = gnl_calloc((i + 1), sizeof(char));
	if (!line)
		return (NULL);
	line = gnl_strcpy(line, onboard);
	return (line);
}

char	*get_read_new_with_old(int fd, char *onboard)
{
	char		*block;
	int			redchar;

	block = gnl_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!block)
		return (NULL);
	redchar = (int)BUFFER_SIZE;
	while (redchar != 0 && !gnl_strchr(block, '\n'))
	{
		redchar = read(fd, block, BUFFER_SIZE);
		if (block[0] == '\0')
			break ;
		block[redchar] = '\0';
		onboard = gnl_strjoin(onboard, block);
	}
	if (redchar == -1)
	{
		if (onboard)
			free(onboard);
		free(block);
		return (NULL);
	}
	free(block);
	return (onboard);
}

char	*get_next_line(int fd)
{
	static char	*onboard;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	onboard = get_read_new_with_old(fd, onboard);
	if (!onboard)
		return (NULL);
	line = get_aline(onboard);
	onboard = get_left(onboard);
	return (line);
}
