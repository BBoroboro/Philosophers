/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamoulin <mamoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:50:04 by mamoulin          #+#    #+#             */
/*   Updated: 2024/04/30 15:15:47 by mamoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->fork);
	if (check_if_over(philo))
		return ;
	pthread_mutex_lock(philo->data->write_lock);
	printf("%ld %d has taken a fork\n", ft_get_time_in_ms()
		- philo->data->start_time, philo->id);
	pthread_mutex_unlock(philo->data->write_lock);
}

void	ft_take_fork2(t_philo *philo)
{
	pthread_mutex_lock(philo->next->fork);
	if (check_if_over(philo))
		return ;
	pthread_mutex_lock(philo->data->write_lock);
	printf("%ld %d has taken a fork\n", ft_get_time_in_ms()
		- philo->data->start_time, philo->id);
	pthread_mutex_unlock(philo->data->write_lock);
}

void	ft_eating(t_philo *philo)
{
	if (check_if_over(philo))
		return ;
	pthread_mutex_lock(philo->meal_lock);
	pthread_mutex_lock(philo->data->write_lock);
	printf("%ld %d is eating\n", ft_get_time_in_ms() - philo->data->start_time,
		philo->id);
	pthread_mutex_unlock(philo->data->write_lock);
	philo->meals_eaten++;
	philo->time_lst_meal = ft_get_time_in_ms();
	pthread_mutex_unlock(philo->meal_lock);
}
