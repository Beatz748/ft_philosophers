#include "philo_one.h"

int		ft_usleep(size_t time)
{
	struct timeval	start;
	struct timeval	new;

	if (gettimeofday(&start, NULL) == -1)
		return (ft_print_error(ERR_TIME));
	while (42)
	{
		usleep(42);
		if (gettimeofday(&new, NULL))
			return (ft_print_error(ERR_TIME));
		if (((new.tv_sec - start.tv_sec) * 1000000 +
		new.tv_usec - start.tv_usec) > time)
			break ;
	}
	return (SUCCESS);
}

size_t	ft_get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (ft_print_error(ERR_TIME));
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
