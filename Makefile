# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/08 21:09:49 by mhaile            #+#    #+#              #
#    Updated: 2024/02/08 23:18:56 by mhaile           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 			philo

FILES	= 		main.c src/utils/ft_putstr_fd.c src/utils/ft_atoi_l.c src/utils/ft_bzero.c src/utils/ft_isdigit.c \
				src/philo_utils/init_philos.c
				
# Colors:
GREEN		=	\e[92;5;118m
GRAY		=	\e[33;2;37m
RED         =   \e[91m
RESET		=	\e[0m
CURSIVE		=	\e[33;3m

SRCS_FOLDER = 	src

# SRCS =			$(addprefix $(SRCS_FOLDER)/, $(FILES))
SRCS =			$(FILES)
OBJS =			$(SRCS:.c=.o)


CC = 			cc

CFLAGS =		-Wall -Wextra -Werror -g3
RM =			rm -rf

all: 			$(NAME)

%.o: %.c
				@printf "$(CURSIVE)$(GRAY)	~ Making object file $(notdir $@) from source file $(notdir $<) ... $(RESET)\n"
				@$(CC) $(CFLAGS) -o $@ -c $<

$(NAME):  		$(OBJS)
				@printf "$(CURSIVE)$(GRAY) 	- Compiling $(NAME)... $(RESET)\n"
		 		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
				@printf "$(GREEN)    - Philosophers (./philo) Executable ready.\n$(RESET)"

clean:
				@${RM} ${OBJS} ${OBJS_BONUS}
				@printf "$(CURSIVE)$(GRAY)	- Removing object files ... $(RESET)\n"
				@printf "$(RED)    - Object files removed.$(RESET)\n"

fclean: 		clean
				@${RM} ${NAME}
				@printf "$(CURSIVE)$(GRAY)	- Removing $(NAME)... $(RESET)\n"
				@printf "$(RED)    - Executable & Archives removed.$(RESET)\n"

re: 			fclean all
				@printf "$(CURSIVE)$(GRAY)	- Remaking $(NAME)... $(RESET)\n"
				
rebonus: 		fclean bonus

.PHONY: 		all clean fclean re