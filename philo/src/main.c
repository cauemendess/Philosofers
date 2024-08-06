/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:38:35 by csilva-m          #+#    #+#             */
/*   Updated: 2024/08/05 22:17:50 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

typedef struct s_philo
{
	pthread_mutex_t	fork;
	pthread_t		philo;
	int				*death;
	int				id;
}					t_philo;

pthread_mutex_t		mutex;

t_core	*get_core(void)
{
	static t_core	core;

	return (&core);
}

void	eat(t_philo *philo)
{
	printf("%lli %d has taken a fork\n", get_ms(), philo->id);
	printf("%lli %d has taken a fork\n", get_ms(), philo->id);
	printf("%lli %d is eating\n", get_ms(), philo->id);
}

void	chill(t_philo *philo)
{
	printf("%lli %d is sleeping\n", get_ms(), philo->id);
	printf("%lli %d is thinking\n", get_ms(), philo->id);
}

void	*routine(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	//while(1)
	//{
	eat(philo);
	chill(philo);
	//}
	//for(int i = 0; i<2; i++)
	//{
	//	pthread_mutex_lock(&mutex);
	//	printf("%d\n", philho->id);
	//	pthread_mutex_unlock(&mutex);
	//}
	return (NULL);
}
void	inicialize_philos(void)
{
	int		i;
	int		n_of_philos;
	t_philo	philos[200];

	i = 0;
	n_of_philos = 200;
	while (i < n_of_philos)
	{
		pthread_create(&philos[i].philo, NULL, routine, &philos[i]);
		philos[i].id = i + 1;
		i++;
	}
	i = 0;
	while (i < n_of_philos)
	{
		pthread_join(philos[i].philo, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	//if (!validate_args(argc, argv))
	//	return (1);
	(void)argc;
	(void)argv;
	get_core()->day = get_time();
	pthread_mutex_init(&mutex, NULL);
	inicialize_philos();
}
