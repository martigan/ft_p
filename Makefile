# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgaspail <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/05/14 21:55:01 by mgaspail          #+#    #+#              #
#    Updated: 2014/05/16 07:16:55 by mgaspail         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC =			gcc

NAME1 =			client
SRC1 =			client.c client2.c client3.c
OBJ1 =			client.o client2.o client3.o

NAME2 =			serveur
SRC2 =			server.c server2.c server3.c server4.c
OBJ2 =			server.o server2.o server3.o server4.o

CFLAG =			-Wall -Wextra -Werror

LIBNAME =		ft
LPATH =			libft
LIB =			$(LPATH)/lib$(LIBNAME).a
LIBINC =		-L$(LPATH) -l$(LIBNAME)
LIBH =			-I$(LPATH)/

RM =			/bin/rm -f

all :			$(NAME1) $(NAME2)

$(NAME1) :		$(LIB) $(OBJ1)
				@echo "\033[32m[$(CC)] \033[0m" | tr -d '\n'
				$(CC) $(CFLAG) $(OBJ1) $(LIBINC) -o $(NAME1)
				@echo "\033[32m[$(CC)] --- " | tr -d '\n'
				@echo "\033[1;35m$(NAME1)\033[0m\033[32m created\033[0m"

$(NAME2) :		$(LIB) $(OBJ2)
				@echo "\033[32m[$(CC)] \033[0m" | tr -d '\n'
				$(CC) $(CFLAG) $(OBJ2) $(LIBINC) -o $(NAME2)
				@echo "\033[32m[$(CC)] --- " | tr -d '\n'
				@echo "\033[1;35m$(NAME2)\033[0m\033[32m created\033[0m"

$(LIB) :
				@$(MAKE) -C $(LPATH)

clean :
				@echo "\033[31m[$(NAME1) $(NAME2) clean] \033[0m" | tr -d '\n'
				$(RM) $(OBJ1)
				$(RM) $(OBJ2)

fclean :		clean
				make -C libft/ fclean
				@echo "\033[31m[$(NAME1) $(NAME2) fclean] \033[0m" | tr -d '\n'
				$(RM) $(NAME1)
				$(RM) $(NAME2)

re :			fclean all

.PHONY :		all clean re fclean
