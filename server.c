/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaspail <mgaspail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/14 10:05:40 by mgaspail          #+#    #+#             */
/*   Updated: 2014/05/16 07:04:26 by mgaspail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int		create_server(int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	proto = getprotobyname("tcp");
	if (proto == 0)
		return (-1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(sock, (struct sockaddr *)&sin, sizeof(sin));
	listen(sock, 1);
	return (sock);
}

int		ft_check(char *cmd, char **pwd, int cs)
{
	if (ft_strcmp(cmd, "quit") == 0)
	{
		ft_putstr("client ");
		ft_putnbr(cs);
		ft_putendl(" quits.");
		return (1);
	}
	else if (ft_strcmp(cmd, "ls") == 0)
		ft_ls(*pwd, cs);
	else if (ft_strcmp(cmd, "pwd") == 0)
		send(cs, *pwd, ft_strlen(*pwd), 0);
	else if (ft_strncmp(cmd, "mkdir ", 6) == 0)
		ft_mkdir(cmd + 6, cs, *pwd);
	else if (ft_strncmp(cmd, "put ", 4) == 0)
		ft_put(cmd + 4, cs, *pwd);
	else if (ft_strncmp(cmd, "get ", 4) == 0)
		ft_get(cmd + 4, cs, *pwd);
	else if (ft_strncmp(cmd, "cd ", 3) == 0)
	{
		ft_cd(cmd + 3, cs, pwd);
		ft_putendl(*pwd);
	}
	return (0);
}

void	ft_child(int cs)
{
	int					r;
	char				buf[1024];
	char				*pwd;

	if ((pwd = (char *)malloc(sizeof(char) * 3)))
	{
		pwd = "./";
		ft_putendl("Client connected.");
		send(cs, "Bienvenue, ceci est un FTP.", 27, 0);
		while (1)
		{
			r = recv(cs, buf, 1023, 0);
			if (r > 0)
			{
				buf[r] = '\0';
				if (ft_check(buf, &pwd, cs))
					break ;
				ft_putendl(buf);
			}
		}
	}
	else
		send(cs, "ERROR : malloc failed.", 22, 0);
	close(cs);
}

void	server(int sock)
{
	int					pid;
	int					cs;
	unsigned int		cslen;
	struct sockaddr_in	csin;

	while (1)
	{
		cs = accept(sock, (struct sockaddr *)&csin, &cslen);
		if ((pid = fork()) == 0)
			ft_child(cs);
	}
}

int		main(int argc, char **argv)
{
	int					port;
	int					sock;
	int					cs;

	if (argc != 2)
		return (usage(argv[0]));
	port = ft_atoi(argv[1]);
	sock = create_server(port);
	server(sock);
	close(sock);
	return (0);
}
