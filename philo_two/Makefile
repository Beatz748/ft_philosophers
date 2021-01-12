SRCS			=	ft_init.c ft_parser.c ft_start_eating.c main.c utils.c ft_messages.c ft_time.c ft_main_check.c

INCS				=	philo_two.h

OBJS			=	$(SRCS:.c=.o)

CC				=	clang -Wall -Werror -Wextra

RM				=	rm -rf

NAME			= philo_two

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CC) -o $(NAME) ${OBJS} ${INCLIB}
				@echo "Done"

clean:
					@echo "cleaning"
					$(RM) $(OBJS)

fclean:			clean
					$(RM) $(NAME)

re:				fclean $(NAME)
