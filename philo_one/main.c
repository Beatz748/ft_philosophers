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
		return (1);
	*dst = i;
	return (0);
}

int		ft_valid(t_core *core)
{
	if (core->number > 200 || core->number < 2 || core->ms_to_die < 60
	|| core->ms_to_eat < 60 || core->ms_to_sleep < 60)
		return (ERR_ARG);
	return (0);
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

	core = (t_core*)malloc(sizeof(t_core));
	memset(core, 0, sizeof(t_core));
	if ((ret = ft_parser(argc, argv, core)))
		return (ft_print_error(ret));
	core->philo = (t_philo*)malloc(sizeof(t_philo) * core->number);
	
}
