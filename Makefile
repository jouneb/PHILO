# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbouyer <jbouyer@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/06 13:13:41 by jbouyer           #+#    #+#              #
#    Updated: 2022/07/26 14:19:13 by jbouyer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

FLAGS = -Wall -Wextra -Werror -lpthread -g3

#------------------------------------#
#               SOURCES              #
#------------------------------------#

SRC	=	philo.c \
		init_dinner.c \
		utils.c \
		print_message.c \
		init_mutex.c \
		init_thread.c \
		routine_utils.c

#------------------------------------#
#               OBJECTS              #
#------------------------------------#

OBJ	=	${SRC:.c=.o}

#------------------------------------#
#               HEADER               #
#------------------------------------#

HEADER	=	philo.h	

#------------------------------------------------------------------------------#
#                                                                              #
#                                   RULES                                      #
#                                                                              #
#------------------------------------------------------------------------------#

all: $(NAME)

$(NAME):$(OBJ)
		gcc -o $(NAME) $(OBJ) $(FLAGS)

%.o : %.c $(HEADER)
		gcc $(FLAGS) -c $< -o $@

clean : 
		rm -rf $(OBJ)

fclean : 
		rm -rf $(NAME) $(OBJ)

re : fclean 
	make all

.PHONY: all clean fclean re