/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshantel <kshantel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:30:32 by kshantel          #+#    #+#             */
/*   Updated: 2021/01/11 16:15:49 by kshantel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static size_t	ft_new_atoi(char *str, size_t *dst)
{
	size_t		i;

	i = 0;
	while (*str >= 0x030 && *str <= 0x039)
	{
		i = i * 10 + *str - 0x030;
		str++;
	}
	if (*str)
		return (ERR_ARG);
	*dst = i;
	return (SUCCESS);
}

int				ft_mini_clear(t_core *core, int err)
{
	free(core->info);
	free(core);
	return (err);
}

int				ft_parser(int argc, char **argv, t_core *core)
{
	int		i;

	i = 0;
	if (!(core->info = (t_info*)malloc(sizeof(t_info))))
		return (ERR_MALLOC);
	while (i++ < argc)
	{
		if (i == 1 && ft_new_atoi(argv[i], &core->number))
			return (ft_mini_clear(core, ERR_ARG));
		if (i == 2 && ft_new_atoi(argv[i], &(core->info->ms_to_die)))
			return (ft_mini_clear(core, ERR_ARG));
		if (i == 3 && ft_new_atoi(argv[i], &(core->info->ms_to_eat)))
			return (ft_mini_clear(core, ERR_ARG));
		if (i == 4 && ft_new_atoi(argv[i], &(core->info->ms_to_sleep)))
			return (ft_mini_clear(core, ERR_ARG));
		if (argc == 6 && i == 5 &&
		ft_new_atoi(argv[i], &(core->info->finish_rounds)))
			return (ft_mini_clear(core, ERR_ARG));
	}
	return (ft_valid(core));
}
