SRCS			=	ft_init.c ft_parser.c ft_start_eating.c main.c utils.c

INCS				=	philo_one.h

OBJS			=	$(SRCS:.c=.o)

CC				=	gcc -g

RM				=	rm -rf

NAME			= philo_one

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CC)  -o $(NAME) ${OBJS} ${INCLIB}
				@echo "\033[1;32mDone"

clean:
					$(RM) $(OBJS)

fclean:			clean
					$(RM) $(NAME)

re:				fclean $(NAME)
