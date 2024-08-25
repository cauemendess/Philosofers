/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:38:35 by csilva-m          #+#    #+#             */
/*   Updated: 2024/08/25 18:26:01 by csilva-m         ###   ########.fr       */
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
	printf("%zu %d %s\n", get_ms(), id, str);
	pthread_mutex_unlock(&get_core()->print);
}

void	eat(t_philo *philo)
{
	int	n_of_philos;
	int	left_fork;
	int	right_fork;

	n_of_philos = get_core()->nb_of_philos;
	left_fork = philo->id - 1;
	right_fork = (philo->id % n_of_philos);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo[left_fork].fork);
		pthread_mutex_lock(&philo[right_fork].fork);
	}
	else
	{
		pthread_mutex_lock(&philo[right_fork].fork);
		pthread_mutex_lock(&philo[left_fork].fork);
	}
	print_action("has taken a fork", philo->id);
	print_action("has taken a fork", philo->id);
	print_action("is eating", philo->id);
	
	usleep(get_core()->time_to_eat * 1000);
	pthread_mutex_unlock(&philo[left_fork].fork);
	pthread_mutex_unlock(&philo[right_fork].fork);
}

void	chill(t_philo *philo)
{
	print_action("is sleeping", philo->id);
	usleep(get_core()->time_to_sleep * 1000);
	print_action("is thinking", philo->id);
	usleep(1000);
}

t_bool verify_die(t_philo *philo)
{
	return get_bool(get_core()->alguemmorreu)
}

void monitor()
{
	int i;

	i = 0;
	while (i < philo_number)
	{
		if (
			// atual morreu
		)
		{
			get_core()->alguemmorreu = true;
		}
	}
}

void	*routine(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	while (1)
	{
		if(verify_die(philo))
			break;
		eat(philo);
		chill(philo);
	}
	return (NULL);
}
void	inicialize_philos(void)
{
	int		i;
	int		n_of_philos;
	t_philo	*philos;

	philos = get_core()->philos;
	get_core()->day = get_time();
	pthread_mutex_init(&get_core()->print, NULL);
	i = 0;
	n_of_philos = get_core()->nb_of_philos;
	while (i < n_of_philos)
	{
		pthread_mutex_init(&philos[i].fork, NULL);
		i++;
	}
	i = 0;
	while (i < n_of_philos)
	{
		philos[i].id = i + 1;
		pthread_create(&philos[i].philo, NULL, &routine, &philos[i]);
		i++;
	}
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
		pthread_mutex_destroy(&philos[i].fork);
		printf("BYE\n");
		i++;
	}
}

int	main(int argc, char **argv)
{
	//if (!validate_args(argc, argv))
	//	return (1);
	(void)argc;
	(void)argv;
	//pthread_mutex_init(&mutex, NULL);
	save_data(argv);
	inicialize_philos();
	destroy_philos();
	return (0);
}
