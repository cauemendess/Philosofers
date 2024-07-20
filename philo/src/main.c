/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:38:35 by csilva-m          #+#    #+#             */
/*   Updated: 2024/07/20 15:16:54 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


t_core	*get_core(void)
{
	static t_core	core;

	return (&core);
}

t_bool is_all_digits(const char *str)
{
    int i = 0;
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
	int i = 1;
	while(argv[i])
	{
		if(!is_all_digits(argv[i]))
		{
			printf("Error: Need to be digits\n");
			return(FALSE);
		}
		i++;
	}
	if(argc > 6 || argc < 5)
	{
		printf("Error: Wrong number of arguments\n");
		return(FALSE);
	}
	else if(ft_atoi(argv[1]) > 200)
	{
		printf("Error: Limit of philosofers is 200\n");
		return(FALSE);
	}
	return(TRUE);
}


int	main(int argc, char **argv)
{
	if (!validate_args(argc, argv))
		return (1);
	save_data();
}
