# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/08 21:09:49 by mhaile            #+#    #+#              #
#    Updated: 2024/03/05 17:40:33 by mhaile           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= 		philo

SRCS	= 		main.c src/utils.c src/parsing.c  \
				src/init_philos.c src/routine.c \
				src/actions.c src/monitoring.c \

OBJS 	=		$(SRCS:.c=.o)

CC 		= 		cc 

CFLAGS	=		-Wall -Wextra -Werror -g3 -pthread

RM		=		rm -rf

all: 			$(NAME)

%.o: %.c
				$(CC) $(CFLAGS) -o $@ -c $<

$(NAME):  		$(OBJS)
		 		$(CC) $(CFLAGS) $^ -o $(NAME)

clean:
				${RM} ${OBJS}

fclean: 		clean
				${RM} ${NAME}

re: 			fclean all
				
push: 			fclean
				git add .
				git commit -m "Updated on $(shell date +'%Y-%m-%d %H:%M:%S') by $(USER)"
				git push 

.PHONY: 		all clean fclean re
