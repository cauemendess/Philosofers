/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:35:14 by csilva-m          #+#    #+#             */
/*   Updated: 2024/08/28 17:53:59 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "libft.h"
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum e_bool
{
	FALSE,
	TRUE
}					t_bool;

typedef struct s_philo
{
	pthread_mutex_t	fork;
	pthread_t		philo;
	int				id;
	size_t			last_meal;
}					t_philo;
typedef struct s_core
{
	char			**argv;
	t_philo			philos[200];
	long long		day;
	int				nb_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_cicles;
	pthread_mutex_t print;
	pthread_mutex_t joker;
	t_bool			philo_dies;
}					t_core;

t_core			*get_core(void);
size_t			get_time(void);
size_t			get_ms(void);
t_bool			verify_die(t_philo *philo);


#endif