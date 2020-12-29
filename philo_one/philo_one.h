#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>

# define SUCCESS 0
# define ERR_TIME -1
# define ERR_ARG -2
# define ERR_MALLOC -3

typedef struct	s_philo
{
	size_t	last_meal;
	pthread_t thread;
}				t_philo;

typedef struct	s_core
{
	size_t		number;
	size_t		ms_to_die;
	size_t		ms_to_eat;
	size_t		ms_to_sleep;
	size_t		start_ms;
	size_t		finish_rounds;
	t_philo		*philo;
}				t_core;

size_t	ft_strlen(char *str);
size_t	ft_get_time();
int		ft_valid(t_core *core);
int		ft_print_error(int num);

#endif
