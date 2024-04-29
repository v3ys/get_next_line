/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veraslan <veraslan@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:08:04 by veraslan          #+#    #+#             */
/*   Updated: 2024/03/14 15:55:47 by veraslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*nl_control(char *buf)
{
	int		i;
	char	*dest;

	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\0')
		return (NULL);
	dest = ft_substr(buf, i + 1, ft_strlen(buf) - i);
	if (dest == NULL)
		return (NULL);
	if (dest[0] == '\0')
	{
		free(dest);
		dest = NULL;
		return (NULL);
	}
	buf[i + 1] = '\0';
	return (dest);
}

char	*ft_call(int fd, char *buf, char *stash)
{
	int		char_read;
	char	*tmp;

	while (1)
	{
		char_read = read(fd, buf, BUFFER_SIZE);
		if (char_read == -1)
			return (NULL);
		else if (char_read == 0)
			break ;
		buf[char_read] = '\0';
		if (stash == NULL)
			stash = ft_strdup("");
		tmp = stash;
		stash = ft_strjoin(tmp, buf);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[MAX_FD];
	char		*res;
	char		*buf;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	res = ft_call(fd, buf, stash[fd]);
	free(buf);
	buf = NULL;
	if (res == NULL)
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	stash[fd] = nl_control(res);
	return (res);
}
