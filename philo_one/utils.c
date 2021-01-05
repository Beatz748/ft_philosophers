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
		return (ERR_ARG);
	return (SUCCESS);
}

void	ft_error_msg(char *err)
{
	if (write(2, err, ft_strlen(err)) != ft_strlen(err))
		exit(EXIT_FAILURE);
}

static	int ft_num_buf(size_t num, char *buf)
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
		length += ft_strcpy(&msg[length], " is eating now\n");
	write(1, msg, length);
	return (length);
}

int		ft_print_error(int num)
{
	int		length;
	char	msg[60];

	length = ft_strcpy(&msg[0], "\033[0;35m");
	if (num == ERR_TIME)
		length += ft_strcpy(&msg[length], "an error has occured - timeofday");
	if (num == ERR_ARG)
		length += ft_strcpy(&msg[length], "an error has occured - bad arguments");
	if (num == ERR_MALLOC)
		length += ft_strcpy(&msg[length], "an error has occured, malloc refused");
	if (num == ERR_MUTEX)
		length += ft_strcpy(&msg[length], "an error has occured, mutex refused");
	length += ft_strcpy(&msg[length], "\033[0m\n");
	write(1, msg, length);
	return (num);
}
void	ft_usleep(size_t time)
{
	struct timeval	start;
	struct timeval	new;

	gettimeofday(&start, NULL);
	while (42)
	{
		usleep(42);
		gettimeofday(&new, NULL);
		if (((new.tv_sec - start.tv_sec) * 1000000 + new.tv_usec - start.tv_usec) > time)
			break ;
	}
}

size_t	ft_get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (ft_print_error(ERR_TIME));
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
