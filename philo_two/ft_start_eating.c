/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_eating.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshantel <kshantel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:28:08 by kshantel          #+#    #+#             */
/*   Updated: 2021/01/13 13:28:10 by kshantel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int			ft_get_forks(t_philo *ph)
{
	if (sem_wait(ph->info->helper))
		return (ERR_SEM);
	if (sem_wait(ph->info->forks) < 0)
		return (ERR_SEM);
	ft_print_stat(TOOK_FORK, ph);
	if (sem_wait(ph->info->forks) < 0)
		return (ERR_SEM);
	ft_print_stat(TOOK_FORK, ph);
	if (sem_post(ph->info->helper))
		return (ERR_SEM);
	return (SUCCESS);
}

static int	ft_eat(t_philo *ph)
{
	ft_print_stat(EAT, ph);
	ph->last_meal = ft_get_time();
	ph->round++;
	ft_usleep(ph->info->ms_to_eat * 1000);
	if (sem_post(ph->info->forks) < 0)
		return (ERR_SEM);
	if (sem_post(ph->info->forks) < 0)
		return (ERR_SEM);
	return (SUCCESS);
}

static void	*ft_philo(void *ptr)
{
	t_philo *ph;

	ph = (t_philo*)ptr;
	while (ph->round != (int)ph->info->finish_rounds)
	{
		ft_get_forks(ph);
		ft_eat(ph);
		ft_print_stat(SLEEP, ph);
		ft_usleep(ph->info->ms_to_sleep * 1000);
		ft_print_stat(THINK, ph);
	}
	return (0x000);
}

int			ft_start_eating(t_core *core, size_t num)
{
	int	i;

	i = -1;
	while (++i < (int)num)
		if (pthread_create(&(core->thread[i]), NULL, ft_philo, &(core->ph[i])))
			return (ERR_SEM);
	ft_check(core);
	i = -1;
	while (++i < (int)num)
		if (pthread_detach(core->thread[i]))
			return (ERR_SEM);
	return (SUCCESS);
}
