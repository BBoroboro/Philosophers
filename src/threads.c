/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamoulin <mamoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 13:24:21 by mamoulin          #+#    #+#             */
/*   Updated: 2024/05/01 17:31:42 by mamoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	open_thread_monitor(t_data *data, t_philo *philo)
{
	if (pthread_create(&data->monitor, NULL, &routine_check, philo))
	{
		perror("Failed to create thread\n");
		return (1);
	}
	if (pthread_join(data->monitor, NULL) != 0)
		return (1);
	return (0);
}

int	open_threads(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	data->start_time = ft_get_time_in_ms();
	//  lock start 1
	while (++i <= data->philo_nb)
	{
		philo->time_lst_meal = data->start_time;
		if (pthread_create(&philo->thread, NULL, &routine_philo, philo) != 0)
		{
			perror("Failed to create thread\n");
			return (1);
		}
		philo = philo->next;
	}
	// unlock start 3
	if (data->philo_nb > 1)
		open_thread_monitor(data, philo);
	i = 0;
	while (++i <= data->philo_nb)
	{
		if (pthread_join(philo->thread, NULL) != 0)
			return (1);
		philo = philo->next;
	}
	return (0);
}
