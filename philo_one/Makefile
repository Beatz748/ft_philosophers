SRCS			=	ft_init.c ft_parser.c ft_start_eating.c main.c utils.c

INCS				=	philo_one.h

OBJS			=	$(SRCS:.c=.o)

CC				=	gcc

RM				=	rm -rf

NAME			= philo_one

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CC)  -o $(NAME) ${OBJS} ${INCLIB}
				@echo "Done"
