/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:01:43 by csilva-m          #+#    #+#             */
/*   Updated: 2024/09/12 17:02:31 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_core	*get_core(void)
{
	static t_core	core;

	return (&core);
}

void	print_action(char *str, int id)
{
	pthread_mutex_lock(&get_core()->print);
	if (!verify_die())
		printf("%llu %d %s\n", get_time() - get_core()->day, id, str);
	pthread_mutex_unlock(&get_core()->print);
}

size_t	set_last_meal(void)
{
	size_t	last_meal;

	pthread_mutex_lock(&get_core()->joker[LAST_MEAL]);
	last_meal = get_time();
	pthread_mutex_unlock(&get_core()->joker[LAST_MEAL]);
	return (last_meal);
}

int	get_eat_count(t_philo *philo)
{
	int	eat_count;

	pthread_mutex_lock(&get_core()->joker[EAT_COUNT]);
	eat_count = philo->eat_count;
	pthread_mutex_unlock(&get_core()->joker[EAT_COUNT]);
	return (eat_count);
}
