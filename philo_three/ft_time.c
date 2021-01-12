/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshantel <kshantel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:30:36 by kshantel          #+#    #+#             */
/*   Updated: 2021/01/12 14:21:53 by kshantel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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
