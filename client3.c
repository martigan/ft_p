/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaspail <mgaspail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/16 07:10:11 by mgaspail          #+#    #+#             */
/*   Updated: 2014/05/16 07:30:53 by mgaspail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	ft_help(void)
{
	char	*str;

	str = "HELP\nListe des commandes\nls : list files from current dir\n";
	str = ft_strjoin(str, "pwd : show current path on server\n");
	str = ft_strjoin(str, "cd <dir> : get in <dir>\nmkdir <dir> : ");
	str = ft_strjoin(str, "create a directory in current path\n");
	str = ft_strjoin(str, "get <file> : download <file> from server\n");
	str = ft_strjoin(str, "put <file> : upload <file> to server in ");
	str = ft_strjoin(str, "current path\nSUCCESS\n");
	ft_putstr(str);
}

void	ft_send(int fd, int sock, char *buf, int r)
{
	write(fd, buf, r);
	send(sock, "S", 1, 0);
}

void	ft_get2(int sock, int r)
{
	char	buf[30];

	r = recv(sock, buf, 20, 0);
	if (buf[0] == '1')
		ft_putendl("ERROR : read error.");
	else if (buf[0] == '2')
		ft_putendl("ERROR : transfer error.");
	else
		ft_putendl("SUCCESS");
}

void	ft_get(char *cmd, int sock)
{
	int		fd;
	int		r;
	char	buf[1024];

	r = recv(sock, buf, 1023, 0);
	if (buf[0] == 'S')
	{
		if ((fd = open(cmd + 4, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR |
				S_IWUSR)) != -1)
		{
			send(sock, "S", 1, 0);
			while ((r = recv(sock, buf, 1023, 0)) == 1023)
				ft_send(fd, sock, buf, r);
			if (r > 0)
				ft_send(fd, sock, buf, r);
			if (r < 0)
				send(sock, "E2", 2, 0);
			close(fd);
		}
		else
			send(sock, "E1", 2, 0);
		ft_get2(sock, r);
	}
	else
		ft_putendl("ERROR : cannot open file on server.");
}

void	ft_cd(int sock, char *buf)
{
	char	c;

	send(sock, buf, ft_strlen(buf), 0);
	recv(sock, &c, 1, 0);
	if (c == '1')
		ft_putendl("ERROR : malloc error.");
	else if (c == '2')
		ft_putendl("ERROR : not a directory.");
	else
		ft_putendl("SUCCESS");
}
