/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamoulin <mamoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:23:40 by mamoulin          #+#    #+#             */
/*   Updated: 2024/04/12 16:04:15 by mamoulin         ###   ########.fr       */
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

	philo_lst = NULL;
	ft_memset(&data, 0, sizeof(t_data));
	if (control_args(ac, av) == 1)
	{
		write(2, "Error: wrong arguments\n", 23);
		return (1);
	}
	init_philo(av, &data, &philo_lst);
	// for (int i = 0; i < 3; i++)
	// {
	// 	printf("--------- philo n %d has %d tte\n", philo_lst->id, philo_lst->data->tte);
	// 	philo_lst = philo_lst->next;
	// }
	// ft_print_lst(philo_lst, &data);
	printf("the program start at %ld millisec\n", philo_lst->data->start_time);
	init_mutex(philo_lst);
	open_threads(&data, philo_lst);
	
	ft_destroy_mutex(philo_lst);
	free_all(philo_lst, &data);
	return (0);
}