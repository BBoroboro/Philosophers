/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamoulin <mamoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:23:40 by mamoulin          #+#    #+#             */
/*   Updated: 2024/04/10 18:02:53 by mamoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
usefull links

gives comprehensive explanation and yt vids to better understnd threads etc
https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2

https://www.codequoi.com/threads-mutex-et-programmation-concurrente-en-c/


*/

void	*routine()
{
	printf("Test from thread\n");
	sleep(3);
	printf("Ending thread\n");
	return 0;
}
int	main(int ac, char **av)
{
	t_data data;
	t_philo *philo_lst;

	ft_memset(&data, 0, sizeof(t_data));
	philo_lst = NULL;
	if (control_args(ac, av) == 1)
	{
		write(2, "Error: wrong arguments\n", 23);
		return (1);
	}
	init_philo(av, &data, &philo_lst);
	
	ft_print_lst(philo_lst, &data);
	init_mutex(&data, philo_lst);
	open_threads(&data, philo_lst);
	

	
	free_all(philo_lst, &data);
	return (0);
}