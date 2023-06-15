NAME = philo
INCLUDES_PATH = ./includes
CC = cc
CFLAGS = -pthread -Wall -Werror -Wextra -g3

SRCS = ./sources/main.c				\
		./sources/utils.c				\
		./sources/init.c				\
		./sources/routines.c				\
		./sources/controller.c				\


OBJS    = $(SRCS:%.c=%.o)

all:    $(NAME)

$(NAME):	$(OBJS)
				$(CC) $(CFLAGS) $(OBJS) -o $@

%.o:		%.c
				$(CC) $(CFLAGS) -I $(INCLUDES_PATH) -o $@ -c $<

run:	$(NAME)
			./$(NAME) 4 410 200 200

valg:	$(NAME)
			valgrind -s --leak-check=full --track-origins=yes --log-file=valg.log ./$(NAME) 4 410 200 200 10

t-valg:	$(NAME)
			valgrind --tool=helgrind --tool=drd --log-file=t-valg.log ./$(NAME) 4 410 200 200 10

clean:
				rm -f $(OBJS)

fclean:		clean
				rm -f $(NAME)

re:			fclean all