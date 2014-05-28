/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaspail <mgaspail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/16 07:04:57 by mgaspail          #+#    #+#             */
/*   Updated: 2014/05/16 07:04:59 by mgaspail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	ft_joinfree(char *tmp, char *cd)
{
	char	*tmp2;

	tmp2 = tmp;
	tmp = ft_strjoin(tmp2, cd);
	free(tmp2);
	tmp2 = tmp;
	tmp = ft_strjoin(tmp2, "/");
	free(tmp2);
}

char	*cddotdot(char *tmp)
{
	int		len;
	char	*ret;

	len = ft_strlen(tmp) - 2;
	while (tmp[len] && tmp[len] != '/')
		len--;
	if (len > 0)
		ret = ft_strsub(tmp, 0, len + 1);
	else
		ret = tmp;
	return (ret);
}

void	ft_cdsend(int ret, int cs)
{
	if (ret == 1)
		send(cs, "1", 1, 0);
	else if (ret == 2)
		send(cs, "2", 1, 0);
	else
		send(cs, "S", 1, 0);
}

int		ft_cd2(char *tmp, char *cd)
{
	int		ret;
	char	*path;
	DIR		*dir;

	ret = 0;
	if ((path = ft_strjoin(tmp, cd)))
	{
		free(path);
		if ((dir = opendir(path)))
			ft_joinfree(tmp, cd);
		else
			ret = 2;
	}
	else
		ret = 1;
	ft_putendl(tmp);
	return (ret);
}

void	ft_cd(char *cmd, int cs, char **pwd)
{
	char	*tmp;
	char	**cd;
	int		i;
	int		ret;

	ret = 0;
	if (!(tmp = ft_strdup(*pwd)))
		ret = 1;
	if (!(cd = ft_strsplit(cmd, '/')))
		ret = 1;
	i = -1;
	while (ret == 0 && cd[++i])
	{
		if (ft_strcmp(cd[i], "."))
		{
			if (ft_strcmp(cd[i], ".."))
				ret = ft_cd2(tmp, cd[i]);
			else if (ft_strlen(tmp) >= 2)
				tmp = cddotdot(tmp);
		}
	}
	if (ret == 0)
		*pwd = ft_strdup(tmp);
	ft_cdsend(ret, cs);
}
