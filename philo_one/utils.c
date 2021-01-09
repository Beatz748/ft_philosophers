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

static int	ft_num_buf(size_t num, char *buf)
{
	int		i;
	size_t	copy;
	size_t	length;

	i = 0;
	copy = num;
	if (num == 0)
	{
		i = 1;
		buf[0] = 0x030;
	}
	while (copy)
	{
		copy /= 10;
		i++;
	}
	length = i--;
	while (num)
	{
		buf[i--] = (num % 10) + 0x030;
		num /= 10;
	}
	return (length);
}

int		ft_print_stat(size_t num, t_philo *ph)
{
	int		length;
	char	msg[50];

	length = ft_num_buf(ft_get_time() - ph->info->start_ms, msg);
	length += ft_strcpy(&msg[length], "ms ");
	length += ft_num_buf(ph->n, &msg[length]);
	if (num == DEATH)
		length += ft_strcpy(&msg[length], " died\n");
	if (num == TOOK_FORK)
		length += ft_strcpy(&msg[length], " has taken a fork\n");
	if (num == SLEEP)
		length += ft_strcpy(&msg[length], " is sleeping\n");
	if (num == EAT)
		length += ft_strcpy(&msg[length], " is eating\n");
	if (num == THINK)
		length += ft_strcpy(&msg[length], " is thinking\n");
	if (write(1, msg, length) != length)
		return (ERR_WRITE);
	return (length);
}

int		ft_print_error(int num)
{
	int		len;
	char	msg[60];

	len = ft_strcpy(&msg[0], "\033[0;35m");
	if (num == ERR_TIME)
		len += ft_strcpy(&msg[len], "an error has occured - timeofday");
	if (num == ERR_ARG)
		len += ft_strcpy(&msg[len], "an error has occured - bad arguments");
	if (num == ERR_MALLOC)
		len += ft_strcpy(&msg[len], "an error has occured, malloc refused");
	if (num == ERR_MUTEX)
		len += ft_strcpy(&msg[len], "an error has occured, mutex refused");
	len += ft_strcpy(&msg[len], "\033[0m\n");
	if (write(2, msg, len) != len)
		return (ERR_WRITE);
	return (num);
}

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
