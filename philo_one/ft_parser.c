#include "philo_one.h"

static size_t	ft_new_atoi(char *str, size_t *dst)
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

int				ft_parser(int argc, char **argv, t_core *core)
{
	int		i;

	if (argc < 5 || argc > 6)
		return (ERR_ARG);
	i = 0;
	while (i++ < argc)
	{
		if (i == 1 && ft_new_atoi(argv[i], &(core->number)))
			return (ERR_ARG);
		if (i == 2 && ft_new_atoi(argv[i], &(core->info.ms_to_die)))
			return (ERR_ARG);
		if (i == 3 && ft_new_atoi(argv[i], &(core->info.ms_to_eat)))
			return (ERR_ARG);
		if (i == 4 && ft_new_atoi(argv[i], &(core->info.ms_to_sleep)))
			return (ERR_ARG);
		if (argc == 6 && i == 5 && ft_new_atoi(argv[i], &(core->info.finish_rounds)))
			return (ERR_ARG);
	}
	return (ft_valid(core));
}
