/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:38:35 by csilva-m          #+#    #+#             */
/*   Updated: 2024/07/15 18:52:39 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


t_core	*get_core(void)
{
	static t_core	core;

	return (&core);
}

int	main(int argc, char **argv)
{
	if (argc > 6 || argc < 5)
	{
		printf("Number of arguments wrong\n");
		return (EXIT_FAILURE);
	}
	validate_args(argv);
}
