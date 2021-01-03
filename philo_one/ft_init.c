#include "philo_one.h"

static int		ft_init_forks(t_philo *ph, int num, t_core *core)
{
	int		i;
	t_fork	*fork;

	i = -1;
	if (!(core->forks = (t_fork*)malloc(sizeof(t_fork) * num)))
		return (ERR_MALLOC);
	memset(core->forks, 0, sizeof(t_fork) * num);
	while (++i < num)
	{
		core->forks[i].last_philo = -1;
		core->forks[i].mutex = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
		if (pthread_mutex_init(core->forks[i].mutex, NULL))
			return (ERR_MUTEX);
	}
	i = -1;
	while (++i < num)
	{
		ph[i].info = core->info;
		ph[i].last_meal = ft_get_time() - ph->info->start_ms;
		ph[i].n = i;
		ph[i].left_fork = &(core->forks[i]);
		ph[i].right_fork = &(core->forks[(i + 1) % num]);
	}
			// printf(" \033[41m  IT'S DEBUG !!! === %ld \033[0m \n", ft_get_time() - core->info->start_ms);
	return (SUCCESS);
}

int				ft_init(t_core *core)
{
	int	ret;

	if (!(core->ph = (t_philo*)malloc(sizeof(t_philo) * core->number)))
		return (ERR_MALLOC);
	if (!(core->thread = (pthread_t*)malloc(sizeof(pthread_t) * core->number)))
		return (ERR_MALLOC);
	if ((ret = ft_init_forks((core->ph), core->number, core)))
		return (ret);
	return (SUCCESS);
}
