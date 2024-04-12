/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamoulin <mamoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 13:24:21 by mamoulin          #+#    #+#             */
/*   Updated: 2024/04/12 17:37:05 by mamoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine_philo(void *arg) // exemple
{	
	t_philo *philo;

	philo = (t_philo *)arg;
	int i;
	i = 0;
	// while (i < philo->data->total_meals)//while(philo->data->dead_flag == 0)
	// {
	pthread_mutex_lock(philo->fork);
	pthread_mutex_lock(philo->next->fork);
	philo->time_lst_meal = ft_get_time_in_ms();
	printf("%ld Philo n %d is eating\n", philo->time_lst_meal, philo->id);
	pthread_mutex_unlock(philo->fork);
	pthread_mutex_unlock(philo->next->fork);
	sleep(philo->data->tte);
	long end_meal = ft_get_time_in_ms();
	printf("%ld Philo n %d finished eating\n", end_meal, philo->id);
	if (philo->time_lst_meal - end_meal < 0)
	{
		philo->time_of_death = ft_get_time_in_ms();
		printf("%ld Philo n %d is dead\n", philo->time_of_death, philo->id);
		exit(EXIT_SUCCESS);
	}
		// i++;
	// }

	// printf("Ending thread\n");
	return (NULL);
}

// void	*routine_check(void *arg)
// {
	
// }

// int	open_thread_monitor(t_data *data, t_philo *philo)
// {
// 	pthread_t monitor;
	
// 	if(pthread_create(monitor, NULL, &routine_check, philo));
// 	{
// 	perror("Failed to create thread\n");
// 	return (1);
// 	}
// 	while(philo)
// 	{
		
// 	}
// 	if (pthread_join(philo->thread, NULL) != 0)
// 		return (1);
// }


int	open_threads(t_data *data, t_philo *philo)
{
	int i;

	i = 1;
	while (i <= data->philo_nb)
	{
		if (pthread_create(&philo->thread, NULL, &routine_philo, philo) != 0) // &th[i] is the same as th + i and routine is the function/action you want to implement
		{
			perror("Failed to create thread\n");
			return (1);
		}
		printf("thread number %d has started\n", i);
		philo = philo->next;
		i++;
	}
	i = 1;
	while (i <= data->philo_nb)
	{
		if (pthread_join(philo->thread, NULL) != 0)
				return (1);
		printf("thread number %d has finished execution\n", i);
		philo = philo->next;
		i++;
	}
	return (0);
}