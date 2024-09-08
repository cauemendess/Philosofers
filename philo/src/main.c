/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:38:35 by csilva-m          #+#    #+#             */
/*   Updated: 2024/09/08 18:50:18 by csilva-m         ###   ########.fr       */
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
	if(!verify_die())
		printf("%llu %d %s\n", get_time() - get_core()->day, id, str);
	pthread_mutex_unlock(&get_core()->print);
}

size_t set_last_meal(void)
{
	size_t last_meal;
	pthread_mutex_lock(&get_core()->joker[LAST_MEAL]);
	last_meal = get_time();
	pthread_mutex_unlock(&get_core()->joker[LAST_MEAL]);
	return(last_meal);
}

void	eat(t_philo *philo)
{
	int	n_of_philos;
	int	left_fork;
	int	right_fork;

	n_of_philos = get_core()->nb_of_philos;
	left_fork = 0;
	if(philo->id == n_of_philos)
		right_fork = -(philo->id - 1);
	else
		right_fork = 1;
	if(get_eat_cicles() != 0 && philo->eat_count == get_eat_cicles())
		return ;
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
	
	pthread_mutex_lock(&get_core()->joker[LAST_MEAL]);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&get_core()->joker[LAST_MEAL]);
	
	print_action("is eating", philo->id);
	usleep(get_core()->time_to_eat * 1000);
	
	philo->eat_count++;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo[left_fork].fork);
		pthread_mutex_unlock(&philo[right_fork].fork);
	}
	else
	{
		pthread_mutex_unlock(&philo[right_fork].fork);
		pthread_mutex_unlock(&philo[left_fork].fork);
	}
}

void	chill(t_philo *philo)
{
	print_action("is sleeping", philo->id);
	usleep(get_core()->time_to_sleep * 1000);
	print_action("is thinking", philo->id);
	//usleep(1000);
}

t_bool monitor(t_core *core)
{
	int i;
	t_philo	*philo;
	size_t meal;

	philo = core->philos;
	i = 0;
	while (i < get_core()->nb_of_philos)
	{
		pthread_mutex_lock(&get_core()->joker[LAST_MEAL]);
		meal = philo->last_meal;
		pthread_mutex_unlock(&get_core()->joker[LAST_MEAL]);
		if ((get_time() - meal) > (get_core()->time_to_die))
		{
			print_action("died", philo[i].id);
			pthread_mutex_lock(&get_core()->joker[PHILO_DIE]);
			get_core()->philo_dies = TRUE;
			pthread_mutex_unlock(&get_core()->joker[PHILO_DIE]);
			return(1);
		}
	}
	return(0);
}

void instakill(void)
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



void	*routine(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;

	if(get_nb_philos() == 1)
		instakill();
	while (!verify_die())
	{
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
	n_of_philos = get_core()->nb_of_philos;
	philos = get_core()->philos;
	pthread_mutex_init(&get_core()->print, NULL);
	i = 0;
	while(i < 10)
	{
		pthread_mutex_init(&get_core()->joker[i], NULL);
		i++;
	}
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
	while(!monitor(get_core()))
		;
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

	while(i < n_of_philos)
	{
		pthread_join(philos[i].philo, NULL);
		i++;
	}
	i = 0;
	while (i < n_of_philos)
	{
		pthread_mutex_destroy(&philos[i].fork);
		printf("BYE\n");
		i++;
	}
	i = 0;
	while(i < 10)
	{
		pthread_mutex_destroy(&get_core()->joker[i]);
		i++;
	}
	//pthread_join(get_core()->monitor, NULL);
}

int	main(int argc, char **argv)
{
	//if (!validate_args(argc, argv))
	//	return (1);
	(void)argc;
	(void)argv;
	//pthread_mutex_init(&mutex, NULL);
	//get_core()->day = get_time();
	get_core()->philo_dies = FALSE;
	save_data(argv);
	inicialize_philos();
	destroy_philos();
	return (0);
}
