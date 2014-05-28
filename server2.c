/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaspail <mgaspail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/16 07:04:48 by mgaspail          #+#    #+#             */
/*   Updated: 2014/05/16 07:04:52 by mgaspail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	ft_ls(char *pwd, int cs)
{
	DIR				*dir;
	struct dirent	*read;
	char			*ls;
	char			*tmp;

	if (!(ls = (char *)malloc(sizeof(char) * 1)))
		return ;
	ls[0] = '\0';
	if ((dir = opendir(pwd)))
	{
		while ((read = readdir(dir)))
		{
			if (read->d_name[0] == '.')
				continue ;
			tmp = ls;
			ls = ft_strjoin(tmp, read->d_name);
			free(tmp);
			tmp = ls;
			ls = ft_strjoin(tmp, "\n");
			free(tmp);
		}
		ls = ft_strjoin(ls, "SUCCESS\n");
		closedir(dir);
		send(cs, ls, ft_strlen(ls), 0);
	}
}

void	ft_mkdir(char *cmd, int cs, char *pwd)
{
	int		r;
	char	*path;

	path = ft_strjoin(pwd, cmd);
	r = mkdir(path, 777);
	if (r)
		send(cs, "ERROR", 5, 0);
	else
		send(cs, "SUCCESS", 6, 0);
}

void	ft_send(int fd, int cs, char *buf, int r)
{
	write(fd, buf, r);
	send(cs, "S", 1, 0);
}

void	ft_put(char *cmd, int cs, char *pwd)
{
	int		fd;
	char	*path;
	int		r;
	char	buf[1024];

	path = ft_strjoin(pwd, cmd);
	if ((fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR))
		!= -1)
	{
		send(cs, "S", 1, 0);
		while ((r = recv(cs, buf, 1023, 0)) == 1023)
			ft_send(fd, cs, buf, r);
		if (r > 0)
			ft_send(fd, cs, buf, r);
		if (r < 0)
			send(cs, "E2", 2, 0);
		close(fd);
	}
	else
		send(cs, "E1", 2, 0);
}
