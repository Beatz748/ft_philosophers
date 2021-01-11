/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshantel <kshantel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:30:36 by kshantel          #+#    #+#             */
/*   Updated: 2021/01/11 18:24:32 by kshantel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	ft_check_time(t_philo *ph)
{
	if (ft_get_time() - ph->last_meal > ph->info->ms_to_die)
	{
		if (sem_wait(ph->info->print) < 0)
			ft_print_error(ERR_SEM);
		ft_print_stat(DEATH, ph);
		exit(1);
	}
}

int		ft_usleep(size_t time, t_philo *ph)
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
		ft_check_time(ph);
		if (((new.tv_sec - start.tv_sec) * 1000000 +
		new.tv_usec - start.tv_usec) > (long)time)
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
