/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshantel <kshantel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:30:28 by kshantel          #+#    #+#             */
/*   Updated: 2021/01/13 13:04:22 by kshantel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int			ft_check(t_core *core)
{
	int		status;

	if (waitpid(-1, &status, WUNTRACED) < 0)
		return (ERR_FORK);
	core->number = core->number;
	return (SUCCESS);
}
