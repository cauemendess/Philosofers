/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:38:35 by csilva-m          #+#    #+#             */
/*   Updated: 2024/09/12 17:06:58 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	instakill(void)
{
	t_core	*core;

	core = get_core();
	print_action("has taken a fork", core->philos->id);
	usleep(core->time_to_die * 1000);
	print_action("died", 1);
	pthread_mutex_lock(&core->joker[PHILO_DIE]);
	core->philo_dies = TRUE;
	pthread_mutex_unlock(&core->joker[PHILO_DIE]);
}

void	save_data(char **argv)
{
	t_core	*core;

	core = get_core();
	core->nb_of_philos = ft_atoi(argv[1]);
	core->time_to_die = ft_atoi(argv[2]);
	core->time_to_eat = ft_atoi(argv[3]);
	core->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		core->eat_cicles = ft_atoi(argv[5]);
	else
		core->eat_cicles = 0;
}

void	destroy_philos(void)
{
	int		i;
	int		n_of_philos;
	t_philo	*philos;

	philos = get_core()->philos;
	n_of_philos = get_core()->nb_of_philos;
	i = 0;
	while (i < n_of_philos)
	{
		pthread_join(philos[i].philo, NULL);
		i++;
	}
	i = 0;
	while (i < n_of_philos)
	{
		pthread_mutex_destroy(&philos[i].fork);
		i++;
	}
	i = 0;
	while (i < 10)
	{
		pthread_mutex_destroy(&get_core()->joker[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	if (!validate_args(argc, argv))
		return (1);
	get_core()->philo_dies = FALSE;
	save_data(argv);
	inicialize_philos();
	destroy_philos();
	return (0);
}
