#include "philo_one.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s || fd < 0)
		return ;
	write(fd, s, ft_strlen(s));
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(-n, fd);
	}
	else if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd(n % 10 + '0', fd);
	}
	else
		ft_putchar_fd(n + '0', fd);
}

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

int		ft_valid(t_core *core)
{
	if (core->number > 200 || core->number < 2 ||
	core->info.ms_to_die < 60
	|| core->info.ms_to_eat < 60 || core->info.ms_to_sleep < 60)
		return (ERR_ARG);
	return (SUCCESS);
}

void	ft_error_msg(char *err)
{
	if (write(2, err, ft_strlen(err)) != ft_strlen(err))
		exit(EXIT_FAILURE);
}

int		ft_print_stat(int num, int i)
{
	if (num == DEATH)
	{
		ft_putstr_fd("philo ", 1);
		ft_putnbr_fd(i, 1);
		ft_putstr_fd(" is dead, call later\n", 1);
	}
	return (num);
}

int		ft_print_error(int num)
{
	if (num == ERR_TIME)
		ft_error_msg("\033[0;35man error has occured - timeofday\033[0m\n");
	if (num == ERR_ARG)
		ft_error_msg("\033[0;35man error has occured - bad arguments\033[0m\n");
	if (num == ERR_MALLOC)
		ft_error_msg("\033[0;35man error has occured, malloc refused\033[0m\n");
	if (num == ERR_MUTEX)
		ft_error_msg("\033[0;35man error has occured, mutex refused\033[0m\n");
	return (num);
}

size_t	ft_get_time(void)
{
	static struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (ft_print_error(ERR_TIME));
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
