/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:35:14 by csilva-m          #+#    #+#             */
/*   Updated: 2024/07/15 17:46:02 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "libft.h"
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum e_bool
{
	FALSE,
	TRUE
}			t_bool;

typedef struct s_core
{
	char	**argv;
	int		nb_of_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		eat_cicles;
}			t_core;

#endif