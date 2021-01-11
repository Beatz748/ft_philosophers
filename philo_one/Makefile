SRCS			=	ft_init.c ft_parser.c ft_start_eating.c main.c utils.c ft_messages.c ft_time.c ft_main_check.c

INCS				=	philo_one.h

OBJS			=	$(SRCS:.c=.o)

CC				=	gcc -g -Wall -Wextra -Werror

RM				=	rm -rf

NAME			= philo_one

all:			$(NAME)

$(NAME):		$(OBJS)
				@echo "\033[1;32m"
				$(CC)  -o $(NAME) ${OBJS} ${INCLIB}
				@echo "\033[1;35mDone"

clean:
					@echo "\033[1;33mcleaning"
					$(RM) $(OBJS)

fclean:			clean
					$(RM) $(NAME)

re:				fclean $(NAME)
