/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaspail <mgaspail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/16 07:10:02 by mgaspail          #+#    #+#             */
/*   Updated: 2014/05/16 07:10:06 by mgaspail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	ft_pwd(int sock, char *name)
{
	char				buf[1024];
	int					r;

	send(sock, name, ft_strlen(name), 0);
	r = recv(sock, buf, 1023, 0);
	if (r > 0)
	{
		buf[r] = '\0';
		ft_putendl(buf + 1);
	}
}

void	ft_ls(int sock, char *name)
{
	char				buf[1024];
	int					r;

	send(sock, name, ft_strlen(name), 0);
	while ((r = recv(sock, buf, 1023, 0)) == 1023)
	{
		buf[r] = '\0';
		ft_putstr(buf);
	}
	buf[r] = '\0';
	ft_putstr(buf);
}

void	ft_mkdir(int sock, char *name)
{
	char				buf[30];
	int					r;

	send(sock, name, ft_strlen(name), 0);
	r = recv(sock, buf, 29, 0);
	if ((buf[0] = 'S'))
	{
		ft_putstr("SUCCESS : ");
		ft_putstr(name);
		ft_putendl(" created.");
	}
	else
	{
		ft_putstr("ERROR : fail to create a directory named ");
		ft_putendl(name + 7);
	}
}

void	ft_put2(int sock, int r, int fd)
{
	char	buf[1024];

	while ((r = read(fd, buf, 1023)) == 1023)
	{
		send(sock, buf, r, 0);
		r = recv(sock, buf, 20, 0);
		if (buf[0] == 'E')
			r = -2;
		if (r < 0)
			break ;
	}
	if (r > 0)
	{
		send(sock, buf, r, 0);
		r = recv(sock, buf, 20, 0);
		if (buf[0] == 'S')
			ft_putendl("SUCCESS");
		else
			r = -2;
	}
	else if (r == -1)
		ft_putendl("ERROR : read error.");
	else if (r == -2)
		ft_putendl("ERROR : transfer error.");
}

void	ft_put(int sock, char *name)
{
	int		fd;
	char	buf[1024];
	int		r;

	if ((fd = open(name + 4, O_RDONLY)) == -1)
	{
		ft_putstr("ERROR : cannot open ");
		ft_putendl(name + 4);
		return ;
	}
	send(sock, name, ft_strlen(name), 0);
	r = recv(sock, buf, 20, 0);
	if (buf[0] == 'S')
		ft_put2(sock, r, fd);
	else
		ft_putendl("ERROR : cannot create file on server.");
	close(fd);
}
