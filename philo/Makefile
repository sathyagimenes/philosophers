NAME = philo
INCLUDES_PATH = ./includes
CC = cc
CFLAGS = -pthread -Wall -Werror -Wextra -g3

SRCS = ./sources/main.c				\
		./sources/utils.c			\
		./sources/init.c			\
		./sources/routines.c		\
		./sources/routine_utils.c	\
		./sources/controller.c		\
		./sources/print.c			\


OBJS    = $(SRCS:%.c=%.o)

all:    $(NAME)

$(NAME):	$(OBJS)
				$(CC) $(CFLAGS) $(OBJS) -o $@

%.o:		%.c
				$(CC) $(CFLAGS) -I $(INCLUDES_PATH) -o $@ -c $<

run:	$(NAME)
			./$(NAME) 4 410 200 200 3

valg:	$(NAME)
			valgrind -s --leak-check=full --log-file=valg.log ./$(NAME) 3 600 100 100 3

t-valg:	$(NAME)
			valgrind --tool=helgrind --tool=drd --log-file=t-valg.log ./$(NAME) 5 500 100 100 3

clean:
				rm -f $(OBJS)

fclean:		clean
				rm -f $(NAME)

re:			fclean all