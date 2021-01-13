/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshantel <kshantel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:30:39 by kshantel          #+#    #+#             */
/*   Updated: 2021/01/13 13:03:05 by kshantel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	ft_clear(t_core *core)
{
	int	i;

	i = -1;
	free(core->ph);
	sem_unlink(SEM_TABLE);
	sem_unlink(SEM_HELP);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_READ);
	free(core->info->thread);
	free(core->info);
	free(core);
}

int		main(int argc, char **argv)
{
	t_core		*core;
	int			ret;

	if (argc < 5 || argc > 6)
		return (ft_print_error(ERR_ARG));
	if (!(core = (t_core*)malloc(sizeof(t_core))))
		return (ft_print_error(ERR_MALLOC));
	memset(core, 0, sizeof(t_core));
	if ((ret = ft_parser(argc, argv, core)))
		return (ft_print_error(ret));
	if (argc == 5)
		core->info->finish_rounds = -1;
	if ((ret = ft_init(core)))
		return (ft_print_error(ret));
	core->info->start_ms = ft_get_time();
	if (ft_start_eating(core, core->number))
		return (ft_print_error(EXIT_FAILURE));
	ft_clear(core);
}
