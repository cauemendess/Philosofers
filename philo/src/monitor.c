/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:42:15 by csilva-m          #+#    #+#             */
/*   Updated: 2024/09/12 17:01:07 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	verify_philos_meals(void)
{
	int	i;

	i = 0;
	while (i < get_nb_philos())
	{
		if (get_eat_count(&get_core()->philos[i]) < get_eat_cicles())
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	kill_philo(void)
{
	pthread_mutex_lock(&get_core()->joker[PHILO_DIE]);
	get_core()->philo_dies = TRUE;
	pthread_mutex_unlock(&get_core()->joker[PHILO_DIE]);
}

t_bool	monitor(t_core *core)
{
	int		i;
	t_philo	*philo;
	size_t	meal;

	philo = core->philos;
	i = 0;
	while (i < get_core()->nb_of_philos)
	{
		pthread_mutex_lock(&get_core()->joker[LAST_MEAL]);
		meal = philo->last_meal;
		pthread_mutex_unlock(&get_core()->joker[LAST_MEAL]);
		if (get_eat_cicles() != 0 && verify_philos_meals())
		{
			kill_philo();
			return (1);
		}
		else if ((get_time() - meal) > (get_core()->time_to_die))
		{
			print_action("died", philo[i].id);
			kill_philo();
			return (1);
		}
	}
	return (0);
}
