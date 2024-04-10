/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamoulin <mamoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 13:24:21 by mamoulin          #+#    #+#             */
/*   Updated: 2024/04/10 18:12:56 by mamoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine_philo(void *arg)
{	
	t_philo *philo;
	pthread_mutex_t print;

	philo = (t_philo *)arg;
	int i;
	i = 0;
	pthread_mutex_init(&print, NULL);
	while (i < 6)//while(philo->data->dead_flag == 0)
	{
		pthread_mutex_lock(&print);
		printf("Test from thread\n");
		pthread_mutex_unlock(&print);
		sleep(3);
		i++;
	}
	pthread_mutex_destroy(&print);
	printf("Ending thread\n");
	return (NULL);
}

// int	open_thread_monitor(t_data *data)
// {}

int	open_threads(t_data *data, t_philo *philo)
{
	int i;
	pthread_mutex_t mutex;

	pthread_mutex_init(&mutex, NULL);
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
	pthread_mutex_destroy(&mutex);
	return (0);
}