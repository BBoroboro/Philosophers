/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamoulin <mamoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:31:12 by mamoulin          #+#    #+#             */
/*   Updated: 2024/04/29 10:14:46 by mamoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	control_args(int ac, char **av)
{
	if (control_args_nb(ac))
		return (1);
	if (control_args_symb(av))
		return (1);
	if (control_if_pos(av))
		return (1);
	if (control_philo_nb(av))
		return (1);
	if (control_limits(av))
		return (1);
	return (0);
}

int	control_args_nb(int ac)
{
	if (ac < 5 || ac > 6)
		return (1);
	return (0);
}

int	control_philo_nb(char **av)
{
	if (ft_atoi(av[1]) > 200)
		return (1);
	return (0);
}
