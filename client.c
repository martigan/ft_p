/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaspail <mgaspail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/14 21:16:29 by mgaspail          #+#    #+#             */
/*   Updated: 2014/05/16 07:41:12 by mgaspail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int		usage(char *str)
{
	write(2, "Usage : ", 8);
	write(2, str, ft_strlen(str));
	write(2, " <machine> <port>\n", 18);
	return (0);
}

int		create_client(int port, char *addr)
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
	sin.sin_addr.s_addr = inet_addr(addr);
	connect(sock, (struct sockaddr *)&sin, sizeof(sin));
	return (sock);
}

void	ft_send2(int sock, char *buf)
{
	if (ft_strncmp(buf, "get ", 4) == 0)
	{
		send(sock, buf, ft_strlen(buf), 0);
		ft_get(buf, sock);
	}
	else if (ft_strncmp(buf, "put ", 4) == 0)
		ft_put(sock, buf);
	else if (ft_strncmp(buf, "cd ", 3) == 0)
		ft_cd(sock, buf);
	else if (ft_strcmp(buf, "help") == 0)
		ft_help();
	else if (ft_strncmp(buf, "mkdir ", 6) == 0)
		ft_mkdir(sock, buf);
	else
	{
		ft_putstr("ERROR : ");
		ft_putstr(buf);
		ft_putendl(" command not found.");
	}
}

void	ft_sending(int sock, char *path)
{
	char	buf[1024];
	int		r;
	char	*prompt;

	prompt = ft_strjoin(path, " $>");
	while (ft_putstr(prompt), 1)
	{
		r = read(0, buf, 1023);
		if (r > 0)
		{
			buf[r - 1] = '\0';
			if (ft_strcmp(buf, "quit") == 0)
			{
				send(sock, buf, r, 0);
				break ;
			}
			else if (ft_strcmp(buf, "pwd") == 0)
				ft_pwd(sock, buf);
			else if (ft_strcmp(buf, "ls") == 0)
				ft_ls(sock, buf);
			else
				ft_send2(sock, &buf[0]);
		}
	}
}

int		main(int argc, char **argv)
{
	int		port;
	int		sock;
	int		r;
	char	buff[1024];
	char	*path;

	if (argc != 3)
		return (usage(argv[0]));
	port = ft_atoi(argv[2]);
	sock = create_client(port, argv[1]);
	r = recv(sock, buff, 1024, 0);
	ft_putendl(buff);
	path = ft_strjoin(argv[1], ":");
	path = ft_strjoin(path, argv[2]);
	ft_sending(sock, path);
	close(sock);
	return (0);
}
