# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alcierra <alcierra@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/04 00:00:00 by alcierra          #+#    #+#              #
#    Updated: 2021/04/04 00:00:00 by alcierra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    =   philo
HEADER  =   philo.h

FLDR_S  =   srcs/
FLDR_O  =   objs/

SRCS    =	ft_atoi.c               ft_strlcpy.c           ft_strlen.c         \
            ft_usleep.c                                                        \
            parse.c                 philo_func.c           philo_monitor.c     \
            philosophers_init.c     philosophers_start.c   philosophers_join.c \
            philosophers_destroy.c  philosophers_print.c   utils.c				\
            philo_action.c


OBJS    =   ${SRCS:.c=.o}

SRCS_WD =   $(addprefix ${FLDR_S},${SRCS})
OBJS_WD =   $(addprefix ${FLDR_O},${OBJS})

FLAGS   =   -Wall -Wextra -Werror


all: $(FLDR_O) $(NAME)

$(FLDR_O):
		mkdir $(FLDR_O)

$(NAME): ${FLDR_O}main.o ${OBJS_WD} ${HEADER}
		${CC} ${FLAGS} $(OBJS_WD) ${FLDR_O}main.o -o $(NAME)

clean:
		rm -rf ${FLDR_O}main.o ${OBJS_WD} ${OBJS_B_WD}

fclean:
		rm -rf ${FLDR_O}main.o ${OBJS_WD} ${OBJS_B_WD} ${NAME} ${NAME_B}

${FLDR_O}%.o : ${FLDR_S}%.c ${HEADER}
		${CC} ${FLAGS} -c $< -o $@

${FLDR_O}%.o : %.c ${HEADER}
		${CC} ${FLAGS} -c $< -o $@

re: fclean all

.PHONY: all clean fclean re
