/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamoulin <mamoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:23:40 by mamoulin          #+#    #+#             */
/*   Updated: 2024/04/26 18:30:10 by mamoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philo_lst;

	philo_lst = NULL;
	ft_memset(&data, 0, sizeof(t_data));
	if (control_args(ac, av) == 1)
	{
		write(2, "Error: wrong arguments\n", 23);
		return (1);
	}
	init_philo(av, &data, &philo_lst);
	init_mutex(philo_lst);
	open_threads(&data, philo_lst);
	free_all(philo_lst, &data);
	return (0);
}
