/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshantel <kshantel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:30:28 by kshantel          #+#    #+#             */
/*   Updated: 2021/01/12 14:08:19 by kshantel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int			ft_check(t_core *core)
{
	int		i;
	int		status;
	int		lol;

	i = 0;
	lol = 0;
	status = 0;
	while (!status && lol < (int)core->number)
	{
		if (waitpid(-1, &status, 0) < 0)
			return (ERR_FORK);
		lol++;
	}
	return (SUCCESS);
}
