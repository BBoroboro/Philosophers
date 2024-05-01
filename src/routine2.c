/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamoulin <mamoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 13:24:21 by mamoulin          #+#    #+#             */
/*   Updated: 2024/05/01 17:08:27 by mamoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_launch_death(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(philo->data->dead_lock);
	data->dead_flag = 1;
	philo->data->dead_philo_id = philo->id;
	if (philo->data->death_time == 0)
		philo->data->death_time = ft_get_time_in_ms() - philo->data->start_time;
	pthread_mutex_unlock(philo->data->dead_lock);
	usleep(1000);
	ft_death(philo);
}

void	*routine_check(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (1)
	{
		if (check_meal_time(philo) || data->dead_flag == 1)
		{
			ft_launch_death(philo);
			break ;
		}
		if (check_if_full(philo) && philo->data->total_meals != 0)
		{
			pthread_mutex_lock(philo->data->full_lock);
			data->full_flag = 1;
			pthread_mutex_unlock(philo->data->full_lock);
			break ;
		}
		usleep(1);
		philo = philo->next;
	}
	return (NULL);
}
