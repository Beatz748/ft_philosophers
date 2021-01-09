#include "philo_one.h"

static int	ft_check_status(t_philo *ph)
{
	if (pthread_mutex_lock(ph->info->check_mutex))
		return (ERR_MUTEX);
	if (ft_get_time() - ph->last_meal > ph->info->ms_to_die)
		ph->death = 1;
	if (pthread_mutex_unlock(ph->info->check_mutex))
		return (ERR_MUTEX);
	return (SUCCESS);
}

static int	ft_check_fin(t_core *core)
{
	int	i;

	i = 0;
	if (pthread_mutex_unlock(core->info->check_mutex))
		return (ERR_MUTEX);
	while (i != core->number)
	{
		usleep(100);
		if (pthread_mutex_lock(core->info->check_mutex))
			return (ERR_MUTEX);
		if (core->ph[i].round == core->info->finish_rounds)
			i++;
		else
			i = 0;
		if (pthread_mutex_unlock(core->info->check_mutex))
			return (ERR_MUTEX);
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
		ft_check_status(&(core->ph[i]));
		if (core->ph[i].death == 1)
		{
			if (pthread_mutex_lock(core->info->print_mutex))
				return (ERR_MUTEX);
			ft_print_stat(DEATH, &(core->ph[i]));
			break ;
		}
		if (pthread_mutex_lock(core->info->check_mutex))
			return (ERR_MUTEX);
		if (core->ph[i].round == core->info->finish_rounds)
			return (ft_check_fin(core));
		if (pthread_mutex_unlock(core->info->check_mutex))
			return (ERR_MUTEX);
		// i++;
		if (++i >= core->number)
			i = 0;
	}
	return (SUCCESS);
}
