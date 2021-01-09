#include "philo_one.h"

void	ft_clear(t_core *core)
{
	int	i;

	i = -1;
	while (++i < core->number)
	{
		pthread_mutex_destroy(core->forks->mutex);
		free(core->forks[i].mutex);
	}
	free(core->info->print_mutex);
	free(core->forks);
	free(core->thread);
	free(core);
}

int		main(int argc, char **argv)
{
	t_core		*core;
	int			ret;

	if (argc < 5 || argc > 6)
		return (ft_print_error(ERR_ARG));
	if (!(core = (t_core*)malloc(sizeof(t_core))))
		return (ft_print_error(ERR_MALLOC));
	memset(core, 0, sizeof(t_core));
	if ((ret = ft_parser(argc, argv, core)))
		return (ft_print_error(ret));
	if (argc == 5)
		core->info->finish_rounds = -1;
	if ((ret = ft_init(core)))
		return (ft_print_error(ret));
	core->info->start_ms = ft_get_time();
	if (ft_start_eating(core, core->info->start_ms, core->number))
		return (ft_print_error(EXIT_FAILURE));
	ft_clear(core);
}
