# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mamoulin <mamoulin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/23 16:03:47 by mamoulin          #+#    #+#              #
#    Updated: 2024/04/30 18:09:01 by mamoulin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC1 = ./src/main.c \
		./src/parsing.c \
		./src/parsing2.c \
		./src/init.c \
		./src/free_functions.c \
		./src/free_functions2.c \
		./src/threads.c \
		./src/routine.c \
		./src/routine2.c \
		./src/get_time.c \
		./src/actions.c \
		./src/actions2.c \
		./src/philo_sync.c \
		./src/utils.c \
		./src/utils2.c \
		./src/check.c \

SRC2 =	

SRC_BONUS = 
			

OBJ1 = ${SRC1:.c=.o}
OBJ2 = ${SRC2:.c=.o}
OBJ_BONUS = ${SRC_BONUS:.c=.o}

NAME = philo
BONUS = 
HEADER = philo.h
CC = cc -pthread
CFLAGS = -Wall -Werror -Wextra -g3
CPPFLAGS = -I./include
RM = rm -f
INCLUDES = -I/usr/include

all:		${NAME}

.c.o:
	${CC} ${CFLAGS} ${CPPFLAGS} -c $< -o ${<:.c=.o} $(INCLUDES)

${NAME}:	${OBJ1} ${OBJ2}
		$(CC) $(CFLAGS) $(CPPFLAGS) -o $(NAME) $(OBJ1) ${OBJ2}

# ${BONUS}:	${OBJ2} ${OBJ_BONUS}
# 		make -C ./libft
# 		$(CC) $(CFLAGS) $(CPPFLAGS) -L$(LIBFT) -o $(BONUS) $(OBJ_BONUS) $(OBJ2) -lft

# bonus:		${BONUS}

clean:
		${RM} ${OBJ1} ${OBJ2} ${OBJ_BONUS} 



fclean:		clean
			${RM} ${NAME} ${BONUS}

re:		fclean all

.PHONY: all clean fclean re