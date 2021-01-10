#include "philo_one.h"

void		ft_random(t_philo *ph, int *i, t_fork **fork)
{
	*i = 0;
	if (ph->n % 2)
		*fork = ph->left_fork;
	else
		*fork = ph->right_fork;
}

int			ft_get_forks(t_philo *ph)
{
	int		i;
	t_fork	*fork;

	ft_random(ph, &i, &fork);
	while (i < 2)
	{
		if (pthread_mutex_lock(fork->mutex))
			return (ERR_MUTEX);
		if (fork->last_philo != ph->n)
		{
			if (pthread_mutex_lock(ph->info->print_mutex))
				return (ERR_MUTEX);
			ft_print_stat(TOOK_FORK, ph);
			if (pthread_mutex_unlock(ph->info->print_mutex))
				return (ERR_MUTEX);
			fork->last_philo = ph->n;
			fork = ph->left_fork;
			if (ph->n % 2)
				fork = ph->right_fork;
			i++;
		}
		else if (pthread_mutex_unlock(fork->mutex))
			return (ERR_MUTEX);
	}
	return (SUCCESS);
}

static int	ft_eat(t_philo *ph)
{
	if (pthread_mutex_lock(ph->info->print_mutex))
		return (ERR_MUTEX);
	ft_print_stat(EAT, ph);
	if (pthread_mutex_unlock(ph->info->print_mutex))
		return (ERR_MUTEX);
	if (pthread_mutex_lock(ph->info->check_mutex))
		return (ERR_MUTEX);
	ph->last_meal = ft_get_time();
	ph->round++;
	if (pthread_mutex_unlock(ph->info->check_mutex))
		return (ERR_MUTEX);
	ft_usleep(ph->info->ms_to_eat * 1000);
	if (pthread_mutex_unlock(ph->left_fork->mutex))
		return (ERR_MUTEX);
	if (pthread_mutex_unlock(ph->right_fork->mutex))
		return (ERR_MUTEX);
	return (SUCCESS);
}

static void	*ft_philo(void *ptr)
{
	t_philo *ph;

	ph = (t_philo*)ptr;
	while (ph->round != ph->info->finish_rounds)
	{
		ft_get_forks(ph);
		ft_eat(ph);
		if (pthread_mutex_lock(ph->info->print_mutex))
			return (0x000);
		ft_print_stat(SLEEP, ph);
		if (pthread_mutex_unlock(ph->info->print_mutex))
			return (0x000);
		ft_usleep(ph->info->ms_to_sleep * 1000);
		if (pthread_mutex_lock(ph->info->print_mutex))
			return (0x000);
		ft_print_stat(THINK, ph);
		if (pthread_mutex_unlock(ph->info->print_mutex))
			return (0x000);
	}
	return (0x000);
}

int			ft_start_eating(t_core *core, size_t ms_start, size_t num)
{
	int	i;

	i = -1;
	while (++i < num)
		if (pthread_create(&(core->thread[i]), NULL, ft_philo, &(core->ph[i])))
			return (ERR_MUTEX);
	ft_check(core);
	i = -1;
	while (++i < num)
		if (pthread_detach(core->thread[i]))
			return (ERR_MUTEX);
	return (SUCCESS);
}
