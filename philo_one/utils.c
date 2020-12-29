#include "philo_one.h"

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

void	ft_error_msg(char *err)
{
	write(2, err, ft_strlen(err));
}

int		ft_print_error(int num)
{
	if (num == ERR_TIME)
		ft_error_msg("\033[0;35man error has occured - timeofday\033[0m\n");
	if (num == ERR_ARG)
		ft_error_msg("\033[0;35man error has occured - bad arguments\033[0m\n");
	return (num);
}

size_t	get_time(void)
{
	static struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (ft_print_error(ERR_TIME));
	return ((size_t)time.tv_sec * 1000 + (size_t)time.tv_usec / 1000);
}
