#include "philo_two.h"

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

int			ft_print_stat(size_t num, t_philo *ph)
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

int			ft_print_error(int num)
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
	if (num == EXIT_FAILURE)
		len += ft_strcpy(&msg[len], "ERROR");
	len += ft_strcpy(&msg[len], "\033[0m\n");
	if (write(2, msg, len) != len)
		return (ERR_WRITE);
	return (num);
}
