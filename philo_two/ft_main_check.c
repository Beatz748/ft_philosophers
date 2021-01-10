#include "philo_two.h"

static int	ft_check_status(t_philo *ph)
{
	if (sem_wait(ph->info->read))
		return (ERR_SEM);
	if (ft_get_time() - ph->last_meal > ph->info->ms_to_die)
		ph->death = 1;
	if (sem_post(ph->info->read))
		return (ERR_SEM);
	return (SUCCESS);
}

static int	ft_check_fin(t_core *core)
{
	int	i;

	i = 0;
	if (sem_post(core->info->read))
		return (ERR_SEM);
	while (i != core->number)
	{
		usleep(100);
		if (sem_wait(core->info->read) < 0)
			return (ERR_SEM);
		if (core->ph[i].round == core->info->finish_rounds)
			i++;
		else
			i = 0;
		// if (sem_post(core->info->read))
		// 	return (ERR_SEM);
	}
	return (SUCCESS);
}

int			ft_check(t_core *core)
{
	int		i;
	size_t	now;

	i = 0;
		if (sem_wait(core->info->read) < 0)
			return (ERR_SEM);
	while (1)
	{
		usleep(100);
		ft_check_status(&(core->ph[i]));
		if (core->ph[i].death == 1)
		{
			if (sem_wait(core->info->print))
				return (ERR_SEM);
			ft_print_stat(DEATH, &(core->ph[i]));
			break ;
		}
		if (sem_wait(core->info->read))
			return (ERR_SEM);
		if (core->ph[i].round == core->info->finish_rounds)
			return (ft_check_fin(core));
		// if (sem_post(core->info->read))
		// 	return (ERR_SEM);
		if (++i >= core->number)
			i = 0;
	}
	return (SUCCESS);
}
