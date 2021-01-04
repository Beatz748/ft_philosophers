#include "philo_one.h"

pthread_mutex_t *fork1;
pthread_mutex_t *fork2;

int			ft_get_forks(t_philo *ph)
{
	int		i;
	t_fork	*fork;

	i = 0;
	// fork = ph->right_fork;
	// if (ph->n % 2)
		fork = ph->left_fork;
	while (i < 2)
	{
		if (pthread_mutex_lock(fork->mutex))
			return (ERR_MUTEX);
		if (fork->last_philo != ph->n)
		{
			// printf("philo %d took fork\n", ph->n);
			fork->last_philo = ph->n;
			if (++i > 1)
				break ;
			// fork = ph->left_fork;
			// if (ph->n % 2)
				fork = ph->right_fork;
		}
		else if (pthread_mutex_unlock(fork->mutex))
			return (ERR_MUTEX);
	}
	return (0x000);
}

void		ft_print(t_philo *ph)
{

}

static void	*ft_hello(void *ptr)
{
	t_philo *ph;

	ph = (t_philo*)ptr;
	while (1)
	{
		// ft_get_forks(ph);
		pthread_mutex_lock(ph->left_fork->mutex);
		// usleep(100);
		pthread_mutex_lock(ph->right_fork->mutex);
		pthread_mutex_lock(ph->info->print_mutex);
		ft_print_stat(TOOK_FORK, ph);
		pthread_mutex_unlock(ph->info->print_mutex);
		ph->last_meal = ft_get_time();
		usleep(ph->info->ms_to_eat * 1000);
		pthread_mutex_unlock(ph->left_fork->mutex);
		pthread_mutex_unlock(ph->right_fork->mutex);
		pthread_mutex_lock(ph->info->print_mutex);
		ft_print_stat(SLEEP, ph);
		pthread_mutex_unlock(ph->info->print_mutex);
		usleep(ph->info->ms_to_sleep * 1000);
				printf(" \033[41m  IT'S DEBUG !!! === %s \033[0m \n", "lol");
	}
	return (0x000);
}

int			ft_check(t_core *core)
{
	int		i;
	size_t	now;

	i = 0;
	while (1)
	{
		usleep(100);
		// if (ft_get_time() - core->ph[i].last_meal > core->info->ms_to_die)
		// 	return (ft_print_stat(DEATH, &(core->ph[i])));
		i++;
		if (i >= core->number)
			i = 0;
	}
	return (0x000);
}

int			ft_start_eating(t_core *core, size_t ms_start, size_t num)
{
	int	i;
	fork1 = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	fork2 = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(fork1, NULL);
	pthread_mutex_init(fork2, NULL);
	i = 0;
	while (i < num)
	{
		pthread_create(&(core->thread[i]), NULL, ft_hello, &(core->ph[i]));
		i++;
	}
		ft_check(core);
		exit(0);
	i = 0;
	while (i < num)
	{
		pthread_join((core->thread[i]), NULL);
		i++;
	}
	return (SUCCESS);
}
