#include <stdio.h>
#include "philo_one.h"

size_t	ft_new_atoi(char *str, size_t *dst)
{
	size_t		i;

	i = 0;
	while (*str >= 0x030 && *str <= 0x039)
	{
		i = i * 10 + *str - 0x030;
		str++;
	}
	if (*str)
		return (ERR_ARG);
	*dst = i;
	return (SUCCESS);
}

void	*ft_hello(void *ptr)
{
	t_philo *ph;

	ph = (t_philo*)ptr;
	
	return NULL;
}

int		ft_start_eating(t_philo *philo, size_t ms_start, size_t num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pthread_create(&(philo[i].thread), NULL, ft_hello, &(philo[i]));
		pthread_join((philo[i].thread), NULL);
		i++;
	}
	return (SUCCESS);
}

int		ft_parser(int argc, char **argv, t_core *core)
{
	int		i;

	if (argc < 5 || argc > 6)
		return (ERR_ARG);
	i = 0;
	while (i++ < argc)
	{
		if (i == 1 && ft_new_atoi(argv[i], &(core->number)))
			return (ERR_ARG);
		if (i == 2 && ft_new_atoi(argv[i], &(core->ms_to_die)))
			return (ERR_ARG);
		if (i == 3 && ft_new_atoi(argv[i], &(core->ms_to_eat)))
			return (ERR_ARG);
		if (i == 4 && ft_new_atoi(argv[i], &(core->ms_to_sleep)))
			return (ERR_ARG);
		if (argc == 6 && i == 5 && ft_new_atoi(argv[i], &(core->finish_rounds)))
			return (ERR_ARG);
	}
	return (ft_valid(core));
}

int		main(int argc, char **argv)
{
	t_core		*core;
	int			ret;

	if (!(core = (t_core*)malloc(sizeof(t_core))))
		return (ft_print_error(ERR_MALLOC));
	memset(core, 0, sizeof(t_core));
	if ((ret = ft_parser(argc, argv, core)))
		return (ft_print_error(ret));
	if (!(core->philo = (t_philo*)malloc(sizeof(t_philo) * core->number)))
		return (ft_print_error(ERR_MALLOC));
	core->start_ms = ft_get_time();
	int i = 0;
	while (i < core->number)
	{
		core->philo[i].last_meal = (size_t)i;
		i++;
	}
	if (!ft_start_eating(core->philo, core->start_ms, core->number))
		return (ft_print_error(EXIT_FAILURE));

}
