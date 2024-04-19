/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamoulin <mamoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:31:12 by mamoulin          #+#    #+#             */
/*   Updated: 2024/04/19 10:15:13 by mamoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
//gather all the controls
int	control_args(int ac,char **av)
{
	if (control_args_nb(ac))
		return (1);
	if (control_args_symb(av))
		return (1);
	if (control_if_pos(av))
		return(1);
	if (control_philo_nb(av))
		return (1);
	if (control_limits(av))
		return (1);
	return (0);
}
// control ac is 5 (or 6 with the optional arg)
int	control_args_nb(int ac)
{
	if (ac < 5 || ac > 6)
		return (1);
	return (0);
}

int control_philo_nb(char **av)
{
	if (ft_atoi(av[1]) > 200)
		return (1);
	return (0);
}

int control_if_pos(char **av)
{
	int	i;
	int	j;

	i = 1;
	while(av[i])
	{
		if ((j = ft_atoi(av[i]) <= 0))
			return (1);
		i++;
	}
	return (0);
}

// control **av only contains digits, also control the neg numb
int control_args_symb(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while(av[i][j] != '\0')
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return(0);
}

int	control_limits(char **av)
{
	int i;

	i = 1;
	while(av[i])
	{
		if(ft_atoi(av[i]) > 2147483647)
			return(1);
		i++;
	}
	return (0);
}
