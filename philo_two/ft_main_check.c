/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshantel <kshantel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:30:28 by kshantel          #+#    #+#             */
/*   Updated: 2021/01/13 13:23:52 by kshantel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static int	ft_check_status(t_philo *ph)
{
	if (ft_get_time() - ph->last_meal >= ph->info->ms_to_die)
		ph->death = 1;
	return (SUCCESS);
}

static int	ft_check_fin(t_core *core)
{
	int	i;

	i = 0;
	while (i != (int)core->number)
	{
		usleep(100);
		if (core->ph[i].round == (int)core->info->finish_rounds)
			i++;
		else
			i = 0;
	}
	return (SUCCESS);
}

int			ft_check(t_core *core)
{
	int		i;

	i = 0;
	while (1)
	{
		usleep(100);
		ft_check_status(&(core->ph[i]));
		if (core->ph[i].death == 1)
		{
			ft_print_stat(DEATH, &(core->ph[i]));
			break ;
		}
		if (core->ph[i].round == (int)core->info->finish_rounds)
			return (ft_check_fin(core));
		if (++i >= (int)core->number)
			i = 0;
	}
	return (SUCCESS);
}
