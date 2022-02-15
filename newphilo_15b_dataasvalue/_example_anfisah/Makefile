NAME = 		philosophers

SRCS = 		srcs/main.c \
			srcs/utils.c \
			srcs/philo_life.c \
			srcs/init_struc_free.c

OBJS = 		${SRCS:.c=.o}

INCLUDES = 	include

HEADER = 	philosophers.h

CC = 		gcc

FLAGS = 	-Wall -Wextra -Werror #-fsanitize=address -g

RM = 		rm -f

%.o:	%.c ${INCLUDES}/${HEADER}
			${CC} ${FLAGS} -c $< -o ${<:.c=.o} -I ${INCLUDES}

all: 		${NAME}

${NAME}:	${OBJS}
			${CC} -fsanitize=thread -g  ${FLAGS} -pthread -o ${NAME} ${OBJS} -I ${INCLUDES}

clean: 		
			${RM} ${OBJS}

fclean: 	clean
			${RM} ${NAME}

re: 		fclean all

.PHONY:		all clean fclean re .c.o