/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamoulin <mamoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:50:04 by mamoulin          #+#    #+#             */
/*   Updated: 2024/04/30 15:59:09 by mamoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleeping(t_philo *philo)
{
	if (check_if_over(philo))
		return ;
	pthread_mutex_lock(philo->data->write_lock);
	printf("%ld %d is sleeping\n", ft_get_time_in_ms()
		- philo->data->start_time, philo->id);
	pthread_mutex_unlock(philo->data->write_lock);
}

void	ft_thinking(t_philo *philo)
{
	if (check_if_over(philo))
		return ;
	pthread_mutex_lock(philo->data->write_lock);
	printf("%ld %d is thinking\n", ft_get_time_in_ms()
		- philo->data->start_time, philo->id);
	pthread_mutex_unlock(philo->data->write_lock);
}

void	ft_death(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(philo->data->full_lock);
	if (philo->data->full_flag == 1)
	{
		pthread_mutex_unlock(philo->data->full_lock);
		return ;
	}
	pthread_mutex_unlock(philo->data->full_lock);
	pthread_mutex_lock(philo->data->write_lock);
	pthread_mutex_lock(philo->data->dead_lock);
	printf("%ld %d died\n", philo->data->death_time,
		philo->data->dead_philo_id);
	pthread_mutex_unlock(philo->data->dead_lock);
	pthread_mutex_unlock(philo->data->write_lock);
}
