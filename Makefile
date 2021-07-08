# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmarian <jmarian@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/15 16:53:36 by jmarian           #+#    #+#              #
#    Updated: 2021/07/07 14:26:40 by jmarian          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = 		gcc

FLAG =		 -g -Wall -Wextra -Werror

OBJC =		$(SRCS:.c=.o)

NAME	=	philo
				
SRCS	=	eat.c									\
			philo.c									\
			soft.c									\
			make_argv.c								\
			dead_inside.c							\

RM		=	rm -f

all: 		$(NAME) philo.h

$(NAME):	$(OBJC)
			$(CC) $(FLAG) $(OBJC) -ltermcap -o $(NAME)

%.o:	%.c
			$(CC) -c $(FLAG) $< -o $@

clean:
			$(RM) $(OBJC)

fclean:		clean
			$(RM) $(NAME)
		
re: 		fclean all clean

.PHONY:		all clean fclean re
