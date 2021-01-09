#include "philo_two.h"

size_t	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

int		ft_strcpy(char *dst, const char *src)
{
	size_t x;

	x = 0;
	if (!dst || !src)
		return (0);
	while (src[x])
	{
		dst[x] = src[x];
		x++;
	}
	dst[x] = '\0';
	return (ft_strlen(dst));
}

int		ft_valid(t_core *core)
{
	if (core->number > 200 || core->number < 2 ||
	core->info->ms_to_die < 60
	|| core->info->ms_to_eat < 60 || core->info->ms_to_sleep < 60)
		return (ft_mini_clear(core, ERR_ARG));
	return (SUCCESS);
}
