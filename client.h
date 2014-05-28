/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaspail <mgaspail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/14 11:15:28 by mgaspail          #+#    #+#             */
/*   Updated: 2014/05/16 07:37:02 by mgaspail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <sys/socket.h>
# include <netdb.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <fcntl.h>

void	ft_pwd(int sock, char *name);
void	ft_ls(int sock, char *name);
void	ft_mkdir(int sock, char *name);
void	ft_put2(int sock, int r, int fd);
void	ft_put(int sock, char *name);
void	ft_get2(int sock, int r);
void	ft_get(char *cmd, int sock);
void	ft_cd(int sock, char *buf);
void	ft_send(int fd, int sock, char *buf, int r);
void	ft_send2(int sock, char *buf);
void	ft_help(void);

#endif
