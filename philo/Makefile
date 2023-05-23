NAME = philo
INCLUDES_PATH = ./includes
CC = cc
CFLAGS = -pthread -Wall -Werror -Wextra -g3

SRCS = ./sources/main.c				\


OBJS    = $(SRCS:%.c=%.o)

all:    $(NAME)

$(NAME):	$(OBJS)
				$(CC) $(CFLAGS) $(OBJS) -o $@

%.o:		%.c
				$(CC) $(CFLAGS) -I $(INCLUDES_PATH) -o $@ -c $<

valg:	$(NAME)
			valgrind -s --leak-check=full --show-leak-kinds=all \
			--track-origins=yes --trace-children=yes --log-file=valg.log ./$(NAME)

clean:
				rm -f $(OBJS)

fclean:		clean
				rm -f $(NAME)

re:			fclean all