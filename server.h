/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaspail <mgaspail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/14 10:10:09 by mgaspail          #+#    #+#             */
/*   Updated: 2014/05/16 07:03:13 by mgaspail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <sys/socket.h>
# include <netdb.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

void	ft_ls(char *pwd, int cs);
void	ft_mkdir(char *cmd, int cs, char *pwd);
void	ft_send(int fd, int cs, char *buf, int r);
void	ft_put(char *cmd, int cs, char *pwd);
void	ft_get2(int cs, int r, int fd);
void	ft_joinfree(char *tmp, char *cd);
char	*cddotdot(char *tmp);
void	ft_cdsend(int ret, int cs);
int		ft_cd2(char *tmp, char *cd);
void	ft_cd(char *cmd, int cs, char **pwd);
int		usage(char *str);
void	ft_get(char *name, int cs, char *pwd);

#endif
