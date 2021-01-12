/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshantel <kshantel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 18:26:26 by kshantel          #+#    #+#             */
/*   Updated: 2021/01/12 14:40:52 by kshantel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdlib.h>
# include <signal.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <pthread.h>

# define SEM_WRITE "/sem for write"
# define SEM_READ "/sem for read"
# define SEM_HELP "/sem helper"
# define SEM_TABLE "/sem table"
# define SUCCESS 0
# define ERR_TIME -1
# define ERR_ARG -2
# define ERR_MALLOC -3
# define ERR_SEM -4
# define ERR_WRITE -5
# define ERR_FORK -6
# define DEATH 1
# define TOOK_FORK 2
# define SLEEP 3
# define EAT 4
# define THINK 5

typedef struct	s_info
{
	int				status;
	size_t			ms_to_die;
	size_t			ms_to_eat;
	size_t			ms_to_sleep;
	size_t			start_ms;
	size_t			finish_rounds;
	sem_t			*helper;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*read;
	pthread_t		*thread;
}				t_info;

typedef struct	s_philo
{
	int			n;
	pid_t		pid;
	int			death;
	int			round;
	size_t		last_meal;
	t_info		*info;
}				t_philo;

typedef struct	s_core
{
	size_t		number;
	t_info		*info;
	t_philo		*ph;
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
void			ft_check_time(t_philo *ph);
void			ft_free_pth(t_philo *ph);
#endif
