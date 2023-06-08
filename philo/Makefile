NAME = philo
INCLUDES_PATH = ./includes
CC = cc
CFLAGS = -pthread -Wall -Werror -Wextra -g3

SRCS = ./sources/main.c				\
		./sources/utils.c				\


OBJS    = $(SRCS:%.c=%.o)

all:    $(NAME)

$(NAME):	$(OBJS)
				$(CC) $(CFLAGS) $(OBJS) -o $@

%.o:		%.c
				$(CC) $(CFLAGS) -I $(INCLUDES_PATH) -o $@ -c $<

run:	$(NAME)
			./$(NAME) 3 410 200 200

valg:	$(NAME)
			valgrind -s --tool=helgrind --tool=drd --log-file=valg.log ./$(NAME)

clean:
				rm -f $(OBJS)

fclean:		clean
				rm -f $(NAME)

re:			fclean all