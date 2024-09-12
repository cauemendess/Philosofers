/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:35:14 by csilva-m          #+#    #+#             */
/*   Updated: 2024/09/12 17:05:13 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

enum
{
	PHILO_DIE,
	START_TIME,
	PHILO_COUNT,
	TIME_TO_DIE,
	TIME_TO_EAT,
	TIME_TO_SLEEP,
	TOTAL_MEALS,
	PHILO_ID,
	EAT_COUNT,
	LAST_MEAL
};

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
	int				eat_count;
	size_t			last_meal;
}					t_philo;
typedef struct s_core
{
	char			**argv;
	t_philo			philos[200];
	long long		day;
	int				nb_of_philos;
	size_t			time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_cicles;
	pthread_mutex_t	print;
	pthread_mutex_t	joker[10];
	pthread_t		monitor;
	t_bool			philo_dies;
	t_bool			all_eat;
}					t_core;

//sett
size_t				set_last_meal(void);

// getters
t_core				*get_core(void);
long				get_time(void);
int					get_eat_cicles(void);
size_t				get_ms(void);
t_bool				verify_die(void);
size_t				get_last_meal(t_philo *philo);
int					get_nb_philos(void);

//util
int					ft_atoi(const char *nptr);
int					ft_isdigit(int c);
void				print_action(char *str, int id);

// algorithm
void				*routine(void *void_philo);
void				inicialize_philos(void);
int					get_eat_count(t_philo *philo);
t_bool				monitor(t_core *core);
void				instakill(void);

t_bool				validate_args(int argc, char **argv);

#endif