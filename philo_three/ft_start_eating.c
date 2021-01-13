/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_eating.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshantel <kshantel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:28:08 by kshantel          #+#    #+#             */
/*   Updated: 2021/01/13 13:31:31 by kshantel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int			ft_get_forks(t_philo *ph)
{
	if (sem_wait(ph->info->helper))
		return (ERR_SEM);
	if (sem_wait(ph->info->forks) < 0)
		return (ERR_SEM);
	if (sem_wait(ph->info->print) < 0)
		return (ERR_SEM);
	ft_print_stat(TOOK_FORK, ph);
	if (sem_post(ph->info->print) < 0)
		return (ERR_SEM);
	if (sem_wait(ph->info->forks) < 0)
		return (ERR_SEM);
	ft_print_stat(TOOK_FORK, ph);
	if (sem_post(ph->info->helper))
		return (ERR_SEM);
	return (SUCCESS);
}

static int	ft_eat(t_philo *ph)
{
	if (sem_wait(ph->info->print) < 0)
		return (ERR_SEM);
	ft_print_stat(EAT, ph);
	ph->last_meal = ft_get_time();
	ph->round++;
	if (sem_post(ph->info->print) < 0)
		return (ERR_SEM);
	ft_usleep(ph->info->ms_to_eat * 1000);
	if (sem_post(ph->info->forks) < 0)
		return (ERR_SEM);
	if (sem_post(ph->info->forks) < 0)
		return (ERR_SEM);
	return (SUCCESS);
}

static void	*ft_death(void *ptr)
{
	t_philo *ph;

	ph = (t_philo*)ptr;
	while (1)
	{
		usleep(100);
		if (ft_get_time() - ph->last_meal >= ph->info->ms_to_die)
		{
			if (sem_wait(ph->info->print) < 0)
				return (0x000);
			ft_print_stat(DEATH, ph);
			exit(1);
		}
	}
}

static void	*ft_philo(void *ptr)
{
	t_philo *ph;

	ph = (t_philo*)ptr;
	if (pthread_create(ph->info->thread, NULL, ft_death, ph))
		return (0x000);
	while (ph->round != (int)ph->info->finish_rounds)
	{
		ft_get_forks(ph);
		ft_eat(ph);
		if (sem_wait(ph->info->print) < 0)
			return (0x000);
		ft_print_stat(SLEEP, ph);
		if (sem_post(ph->info->print) < 0)
			return (0x000);
		ft_usleep(ph->info->ms_to_sleep * 1000);
		if (sem_wait(ph->info->print) < 0)
			return (0x000);
		ft_print_stat(THINK, ph);
		if (sem_post(ph->info->print) < 0)
			return (0x000);
	}
	if (pthread_detach(*ph->info->thread))
		return (0x000);
	exit(1);
	return (0x000);
}

int			ft_start_eating(t_core *core, size_t num)
{
	int		i;
	pid_t	pid;

	i = -1;
	while (++i < (int)num)
	{
		if ((pid = fork()) == 0)
			ft_philo(&(core->ph[i]));
		else if (pid < 0)
			return (ERR_FORK);
		core->ph[i].pid = pid;
	}
	ft_check(core);
	i = -1;
	usleep(100000);
	while (++i < (int)num)
		kill(core->ph[i].pid, SIGTERM);
	return (SUCCESS);
}
