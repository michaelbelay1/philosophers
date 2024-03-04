# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/08 21:09:49 by mhaile            #+#    #+#              #
#    Updated: 2024/03/04 15:49:46 by mhaile           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= 		philo

SRCS	= 		main.c src/utils.c src/parsing.c  \
				src/init_philos.c src/routine.c \
				src/actions.c src/monitoring.c \

OBJS 	=		$(SRCS:.c=.o)

CC 		= 		cc 

CFLAGS	=		-Wall -Wextra -Werror -g3 
# CFLAGS	=		-Wall -Wextra -Werror -g3 -pthread 
RM		=		rm -rf

all: 			$(NAME)

%.o: %.c
# @printf "$(CURSIVE)$(GRAY)	~ Making object file $(notdir $@) from source file $(notdir $<) ... $(RESET)\n"
				@$(CC) $(CFLAGS) -o $@ -c $<

$(NAME):  		$(OBJS)
# @printf "$(CURSIVE)$(GRAY) 	- Compiling $(NAME)... $(RESET)\n"
		 		$(CC) $(CFLAGS) $^ -o $(NAME)
# @printf "$(GREEN)    - Philosophers (./philo) Executable ready.\n$(RESET)"

clean:
				@${RM} ${OBJS}
# @printf "$(CURSIVE)$(GRAY)	- Removing object files ... $(RESET)\n"
# @printf "$(RED)    - Object files removed.$(RESET)\n"

fclean: 		clean
				@${RM} ${NAME}
# @printf "$(CURSIVE)$(GRAY)	- Removing $(NAME)... $(RESET)\n"
# @printf "$(RED)    - Executable removed.$(RESET)\n"

re: 			fclean all
# @printf "$(CURSIVE)$(GRAY)	- Remaking $(NAME)... $(RESET)\n"
				
push: 			fclean
				git add .
				git commit -m "Updated on $(shell date +'%Y-%m-%d %H:%M:%S') by $(USER)"
				git push 

.PHONY: 		all clean fclean re

# Colors:
GREEN	=	\e[92;5;118m
GRAY	=	\e[33;2;37m
RED     =   \e[91m
RESET	=	\e[0m
CURSIVE	=	\e[33;3m