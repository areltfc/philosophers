##
## EPITECH PROJECT, 2018
## philosphers
## File description:
## philosophers
##

SRCS	=	src/main.c			\
		src/philosophers.c		\
		src/simulator.c			\
		src/philosopher_methods.c

OBJS	=	$(SRCS:.c=.o)

CFLAGS	=	-Wextra -Wall
CFLAGS	+=	-I include/

LDFLAGS	+=	-Llib/ -lriceferee -lpthread

CC	=	gcc

NAME	=	philo

all:		$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(OBJS)

fclean:		clean
	rm -f $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
