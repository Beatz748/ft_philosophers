#include "philo_one.h"

int			ft_get_fork(t_philo *ph)
{
	int		i;
	t_fork	*fork;

	i = 0;
	ph->last_meal = ft_get_time();
	fork = &(ph->right_fork);
	if (ph->n % 2)
		fork = &(ph->left_fork);
	while (i < 2)
	{
		if (pthread_mutex_lock(fork->mutex))
			return (ERR_MUTEX);
		if (fork->last_philo != ph->n)
		{
			fork->last_philo = ph->n;
			if (++i > 1)
				break ;
				printf("philo %d took fork 1\n", ph->n);
			fork = &(ph->left_fork);
			if (ph->n % 2)
				fork = &(ph->right_fork);
				printf("philo %d took fork 2\n", ph->n);
		}
		else if (pthread_mutex_unlock(fork->mutex))
			return (ERR_MUTEX);
		else
					printf(" \033[41m  IT'S DEBUG !!! === %s \033[0m \n", "lol");
	}
	return (0x000);
}

static void	*ft_hello(void *ptr)
{
	t_philo *ph;

	ph = (t_philo*)ptr;
	while (ph->info.finish_rounds != ph->round)
	{
		if (ft_get_fork(ph))
			break ;
		usleep(ph->info.ms_to_sleep * 1000);
		ph->left_fork.last_philo = ph->n;
		ph->round++;
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
		now = ft_get_time();
		if (now - core->ph[i].last_meal > core->info.ms_to_die)
		{
			printf("%ld ? ", now - core->ph[i].last_meal);
			printf("  %ld\n", core->info.ms_to_die);
			return (ft_print_stat(DEATH, i));
		}
		i++;
		if (i >= core->number)
			i = 0;
	}
	return (0x000);
}

int			ft_start_eating(t_core *core, size_t ms_start, size_t num)
{
	int	i;

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
