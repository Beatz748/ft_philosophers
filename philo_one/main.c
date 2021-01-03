#include "philo_one.h"

int		main(int argc, char **argv)
{
	t_core		*core;
	int			ret;

	if (!(core = (t_core*)malloc(sizeof(t_core))))
		return (ft_print_error(ERR_MALLOC));
	memset(core, 0, sizeof(t_core));
	if ((ret = ft_parser(argc, argv, core)))
		return (ft_print_error(ret));
	if ((ret = ft_init(core)))
		return (ft_print_error(ret));
	core->info->start_ms = ft_get_time();
	// size_t now;
	// usleep(2000);
	// now = ft_get_time() - core->info->start_ms;
			// printf(" \033[41m  IT'S DEBUG !!! === %ld \033[0m \n", now);
	if (!ft_start_eating(core, core->info->start_ms, core->number))
		return (ft_print_error(EXIT_FAILURE));
}
