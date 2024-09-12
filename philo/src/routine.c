/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:23:43 by csilva-m          #+#    #+#             */
/*   Updated: 2024/09/12 16:24:16 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo, int left_fork, int right_fork)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(&philo[right_fork].fork);
		pthread_mutex_lock(&philo[left_fork].fork);
	}
	else
	{
		pthread_mutex_lock(&philo[left_fork].fork);
		pthread_mutex_lock(&philo[right_fork].fork);
	}
}

void	drop_forks(t_philo *philo, int left_fork, int right_fork)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_unlock(&philo[right_fork].fork);
		pthread_mutex_unlock(&philo[left_fork].fork);
	}
	else
	{
		pthread_mutex_unlock(&philo[left_fork].fork);
		pthread_mutex_unlock(&philo[right_fork].fork);
	}
}

void	eat(t_philo *philo)
{
	int	n_of_philos;
	int	left_fork;
	int	right_fork;

	n_of_philos = get_core()->nb_of_philos;
	left_fork = 0;
	if (philo->id == n_of_philos)
		right_fork = -(philo->id - 1);
	else
		right_fork = 1;
	take_forks(philo, left_fork, right_fork);
	print_action("has taken a fork", philo->id);
	print_action("has taken a fork", philo->id);
	pthread_mutex_lock(&get_core()->joker[LAST_MEAL]);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&get_core()->joker[LAST_MEAL]);
	print_action("is eating", philo->id);
	usleep(get_core()->time_to_eat * 1000);
	pthread_mutex_lock(&get_core()->joker[EAT_COUNT]);
	philo->eat_count++;
	pthread_mutex_unlock(&get_core()->joker[EAT_COUNT]);
	drop_forks(philo, left_fork, right_fork);
}

void	chill(t_philo *philo)
{
	print_action("is sleeping", philo->id);
	usleep(get_core()->time_to_sleep * 1000);
	print_action("is thinking", philo->id);
	usleep(1000);
}

void	*routine(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	if (get_nb_philos() == 1)
		instakill();
	while (!verify_die())
	{
		eat(philo);
		chill(philo);
	}
	return (NULL);
}
