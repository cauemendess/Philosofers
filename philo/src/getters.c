/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 17:48:37 by csilva-m          #+#    #+#             */
/*   Updated: 2024/09/12 16:00:24 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	verify_die(void)
{
	t_bool	dies;

	pthread_mutex_lock(&get_core()->joker[PHILO_DIE]);
	dies = get_core()->philo_dies;
	pthread_mutex_unlock(&get_core()->joker[PHILO_DIE]);
	return (get_core()->philo_dies);
}

size_t	get_last_meal(t_philo *philo)
{
	size_t	meal;

	pthread_mutex_lock(&get_core()->joker[LAST_MEAL]);
	meal = philo->last_meal;
	pthread_mutex_unlock(&get_core()->joker[LAST_MEAL]);
	return (meal);
}

size_t	get_time_to_die(void)
{
	size_t	die;

	pthread_mutex_lock(&get_core()->joker[TIME_TO_DIE]);
	die = get_core()->time_to_die;
	pthread_mutex_unlock(&get_core()->joker[TIME_TO_DIE]);
	return (die);
}

int	get_nb_philos(void)
{
	int	nb;

	pthread_mutex_lock(&get_core()->joker[PHILO_COUNT]);
	nb = get_core()->nb_of_philos;
	pthread_mutex_unlock(&get_core()->joker[PHILO_COUNT]);
	return (nb);
}

int	get_eat_cicles(void)
{
	int	eat_cicles;

	pthread_mutex_lock(&get_core()->joker[TOTAL_MEALS]);
	eat_cicles = get_core()->eat_cicles;
	pthread_mutex_unlock(&get_core()->joker[TOTAL_MEALS]);
	return (eat_cicles);
}
