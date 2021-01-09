#include "philo_one.h"

static int		ft_init_forks(t_philo *ph, int num, t_core *core)
{
	int		i;

	i = -1;
	if (!(core->forks = (t_fork*)malloc(sizeof(t_fork) * num)))
		return (ERR_MALLOC);
	memset(core->forks, 0, sizeof(t_fork) * num);
	while (++i < num)
	{
		core->forks[i].last_philo = -1;
		core->forks[i].mutex = (pthread_mutex_t*)
		malloc(sizeof(pthread_mutex_t));
		if (pthread_mutex_init(core->forks[i].mutex, NULL))
			return (ERR_MUTEX);
	}
	i = -1;
	while (++i < num)
	{
		ph[i].death = 0;
		ph[i].info = core->info;
		ph[i].last_meal = ft_get_time() - ph->info->start_ms;
		ph[i].n = i + 1;
		ph[i].left_fork = &(core->forks[i]);
		ph[i].right_fork = &(core->forks[(i + 1) % num]);
	}
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
	if (!(core->info->print_mutex = (pthread_mutex_t*)
	malloc(sizeof(pthread_mutex_t))))
		return (ERR_MALLOC);
	if (pthread_mutex_init(core->info->print_mutex, NULL))
		return (ERR_MUTEX);
	return (SUCCESS);
}
