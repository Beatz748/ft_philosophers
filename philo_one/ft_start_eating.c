#include "philo_one.h"

int			ft_check_status(t_philo *ph)
{
	if (ft_get_time() - ph->last_meal > ph->info->ms_to_die)
		ph->death = 1;
	return (SUCCESS);
}

int			ft_get_forks(t_philo *ph)
{
	int		i;
	t_fork	*fork;

	i = 0;
	ft_check_status(ph);
	fork = ph->right_fork;
	if (ph->n % 2)
		fork = ph->left_fork;
	while (i < 2)
	{
		if (pthread_mutex_lock(fork->mutex))
			return (ERR_MUTEX);
		if (fork->last_philo != ph->n)
		{
			fork->last_philo = ph->n;
			if (++i > 1)
				break ;
			fork = ph->left_fork;
			if (ph->n % 2)
				fork = ph->right_fork;
		}
		else if (pthread_mutex_unlock(fork->mutex))
			return (ERR_MUTEX);
	}
	return (0x000);
}

static void	*ft_hello(void *ptr)
{
	t_philo *ph;

	ph = (t_philo*)ptr;
	while (ph->round != ph->info->finish_rounds)
	{
		ft_get_forks(ph);
		pthread_mutex_lock(ph->info->print_mutex);
		ft_print_stat(TOOK_FORK, ph);
		pthread_mutex_unlock(ph->info->print_mutex);
		ph->last_meal = ft_get_time();
		ft_usleep(ph->info->ms_to_eat * 1000);
		pthread_mutex_unlock(ph->left_fork->mutex);
		pthread_mutex_unlock(ph->right_fork->mutex);
		pthread_mutex_lock(ph->info->print_mutex);
		ft_print_stat(SLEEP, ph);
		pthread_mutex_unlock(ph->info->print_mutex);
		ft_usleep(ph->info->ms_to_sleep * 1000);
		ph->round++;
	}
	return (0x000);
}

int			ft_check_fin(t_core *core)
{
	int	i;

	i = 0;
	while (i != core->number)
	{
		usleep(100);
		if (core->ph[i].round == core->info->finish_rounds)
			i++;
		else
			i = 0;
	}
	return (SUCCESS);
}

int			ft_check(t_core *core)
{
	int		i;
	size_t	now;

	i = 0;
	while (1)
	{
		usleep(100);
		if (core->ph[i].death == 1)
		{
			pthread_mutex_lock(core->info->print_mutex);
			ft_print_stat(DEATH, &(core->ph[i]));
			break ;
		}
		if (core->ph[i].round == core->info->finish_rounds)
			return (ft_check_fin(core));
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
		// exit(0);
	i = 0;
	while (i < num)
	{
		pthread_detach((core->thread[i]));
		i++;
	}
	return (SUCCESS);
}
