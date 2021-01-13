/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshantel <kshantel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:31:30 by kshantel          #+#    #+#             */
/*   Updated: 2021/01/13 14:46:00 by kshantel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>

# define SUCCESS 0
# define ERR_TIME 9
# define ERR_ARG -2
# define ERR_MALLOC -3
# define ERR_MUTEX -4
# define ERR_WRITE -5
# define DEATH 1
# define TOOK_FORK 2
# define SLEEP 3
# define EAT 4
# define THINK 5

typedef struct	s_fork
{
	int				last_philo;
	pthread_mutex_t	*mutex;
}				t_fork;

typedef struct	s_info
{
	int				status;
	size_t			ms_to_die;
	size_t			ms_to_eat;
	size_t			ms_to_sleep;
	size_t			start_ms;
	size_t			finish_rounds;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*check_mutex;
}				t_info;

typedef struct	s_philo
{
	int			n;
	int			death;
	int			round;
	size_t		last_meal;
	t_fork		*left_fork;
	t_fork		*right_fork;
	t_info		*info;
}				t_philo;

typedef struct	s_core
{
	size_t		number;
	pthread_t	*thread;
	t_info		*info;
	t_philo		*ph;
	t_fork		*forks;
}				t_core;

size_t			ft_get_time(void);
int				ft_init(t_core *core);
int				ft_print_stat(size_t num, t_philo *ph);
int				ft_parser(int argc, char **argv, t_core *core);
int				ft_start_eating(t_core *core, size_t num);
int				ft_strcpy(char *dst, const char *src);
int				ft_valid(t_core *core);
int				ft_print_error(int num);
int				ft_usleep(size_t time);
int				ft_mini_clear(t_core *core, int err);
int				ft_check(t_core *core);

#endif
