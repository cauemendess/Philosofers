/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:23:46 by csilva-m          #+#    #+#             */
/*   Updated: 2024/09/12 16:42:06 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_joker(void)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		pthread_mutex_init(&get_core()->joker[i], NULL);
		i++;
	}
}

void	inicialize_philos(void)
{
	int		i;
	int		n_of_philos;
	t_philo	*philos;

	n_of_philos = get_core()->nb_of_philos;
	philos = get_core()->philos;
	pthread_mutex_init(&get_core()->print, NULL);
	init_joker();
	i = 0;
	while (i < n_of_philos)
	{
		pthread_mutex_init(&philos[i].fork, NULL);
		i++;
	}
	i = 0;
	get_core()->day = get_time();
	while (i < n_of_philos)
	{
		philos[i].id = i + 1;
		philos[i].last_meal = get_time();
		pthread_create(&philos[i].philo, NULL, &routine, &philos[i]);
		i++;
	}
	while (!monitor(get_core()))
		;
}
