/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:38:35 by csilva-m          #+#    #+#             */
/*   Updated: 2024/07/30 18:10:40 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


typedef struct s_philo
{
	pthread_mutex_t *left;
	pthread_mutex_t *right;
	pthread_t philo;
	int *death;
	int	id;
}		t_philo;

long long day;

pthread_mutex_t mutex;

t_core	*get_core(void)
{
	static t_core	core;

	return (&core);
}


t_bool	is_all_digits(const char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\0')
		return (FALSE);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

t_bool	validate_args(int argc, char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!is_all_digits(argv[i]))
		{
			printf("Error: Need to be digits\n");
			return (FALSE);
		}
		i++;
	}
	if (argc > 6 || argc < 5)
	{
		printf("Error: Wrong number of arguments\n");
		return (FALSE);
	}
	else if (ft_atoi(argv[1]) > 200)
	{
		printf("Error: Limit of philosofers is 200\n");
		return (FALSE);
	}
	return (TRUE);
}


void eat(t_philo *philo)
{
	
	printf("%lli %d has taken a fork\n", get_ms(), philo->id);
	printf("%lli %d has taken a fork\n", get_ms(), philo->id);
	printf("%lli %d is eating\n", get_ms(), philo->id);
	
}

void *routine(void *void_philo)
{
	t_philo *philo;
	philo = (t_philo *)void_philo;

	while(1)
	{
		eat(philo);
		//sleepy();
		//think();
	}
	//for(int i = 0; i<2; i++)
	//{
	//	pthread_mutex_lock(&mutex);
	//	printf("%d\n", philho->id);
	//	pthread_mutex_unlock(&mutex);
	//}
	return(NULL);
}
void	inicialize_philos(void)
{
	int i = 0;
	int n_of_philos = 200;
	t_philo philos[200];
	while(i < n_of_philos)
	{
		pthread_create(&philos[i].philo, NULL, routine, &philos[i]);
		philos[i].id = i + 1;
		i++;
	}
	i = 0;
	while(i < n_of_philos)
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
	day = get_time();
	pthread_mutex_init(&mutex, NULL);
	inicialize_philos();
}
