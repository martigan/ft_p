/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaspail <mgaspail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/16 07:05:04 by mgaspail          #+#    #+#             */
/*   Updated: 2014/05/16 07:05:06 by mgaspail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int		usage(char *str)
{
	write(2, "Usage : ", 8);
	write(2, str, ft_strlen(str));
	write(2, " <port>\n", 8);
	return (0);
}

void	ft_get2(int cs, int r, int fd)
{
	char	buf[1024];

	while ((r = read(fd, buf, 1023)) == 1023)
	{
		send(cs, buf, r, 0);
		r = recv(cs, buf, 20, 0);
		if (buf[0] == 'E')
			r = -2;
		if (r < 0)
			break ;
	}
	if (r > 0)
	{
		send(cs, buf, r, 0);
		r = recv(cs, buf, 20, 0);
		if (buf[0] == 'S')
			send(cs, "S", 1, 0);
		else
			send(cs, "2", 1, 0);
	}
	else if (r == -1)
		send(cs, "1", 1, 0);
	else
		send(cs, "S", 1, 0);
}

void	ft_get(char *name, int cs, char *pwd)
{
	int		fd;
	char	buf[1024];
	int		r;
	char	*path;

	path = ft_strjoin(pwd, name);
	if ((fd = open(path, O_RDONLY)) == -1)
	{
		send(cs, "E", 1, 0);
		return ;
	}
	send(cs, "S", 1, 0);
	r = recv(cs, buf, 20, 0);
	if (buf[0] == 'S')
		ft_get2(cs, r, fd);
	else
		ft_putendl("ERROR : cannot create file on server.");
	close(fd);
}
