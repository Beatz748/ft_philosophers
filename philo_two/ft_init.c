#include "philo_two.h"

static int		ft_init_forks(t_philo *ph, int num, t_core *core)
{
	int		i;

	i = -1;
	sem_unlink(SEM_HELP);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_TABLE);
	sem_unlink(SEM_READ);
	if ((core->info->forks = sem_open(SEM_TABLE, O_CREAT | S_IRWXU, 0644, num)) == SEM_FAILED)
		return (ERR_SEM);
	if ((core->info->helper = sem_open(SEM_HELP, O_CREAT | S_IRWXU, 0644, 1)) == SEM_FAILED)
		return (ERR_SEM);
	i = -1;
	while (++i < num)
	{
		ph[i].death = 0;
		ph[i].info = core->info;
		ph[i].last_meal = ft_get_time() - ph->info->start_ms;
		ph[i].n = i + 1;
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
	if (!(core->info->print = (sem_t*)malloc(sizeof(sem_t))))
		return (ERR_MALLOC);
	if (!(core->info->read = (sem_t*)malloc(sizeof(sem_t))))
		return (ERR_MALLOC);
	if ((core->info->read =  sem_open(SEM_READ, O_CREAT | S_IRWXU, 0644, 1)) == SEM_FAILED)
		return (ERR_SEM);
	if ((core->info->print =  sem_open(SEM_WRITE, O_CREAT | S_IRWXU, 0644, 1)) == SEM_FAILED)
		return (ERR_SEM);
	return (SUCCESS);
}
