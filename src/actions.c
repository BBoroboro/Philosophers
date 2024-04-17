/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamoulin <mamoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:50:04 by mamoulin          #+#    #+#             */
/*   Updated: 2024/04/17 17:55:47 by mamoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->fork);
	pthread_mutex_lock(philo->data->write_lock);
	printf("%ld %d has taken a fork\n", ft_get_time_in_ms() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(philo->data->write_lock);
}

void	ft_take_fork2(t_philo *philo)
{
	pthread_mutex_lock(philo->next->fork);
	pthread_mutex_lock(philo->data->write_lock);
	printf("%ld %d has taken a fork\n", ft_get_time_in_ms() - philo->data->start_time, philo->id); // erase 2nd
	pthread_mutex_unlock(philo->data->write_lock);
}

void	ft_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_lock);
	printf("%ld %d is eating\n", ft_get_time_in_ms() - philo->data->start_time, philo->id);
	philo->meals_eaten++; // JA m a dit de le mettre la
	pthread_mutex_unlock(philo->meal_lock);
	philo->time_lst_meal = ft_get_time_in_ms();
}

void	ft_sleeping(t_philo *philo)
{
	pthread_mutex_lock(philo->data->write_lock);
	printf("%ld %d is sleeping\n", ft_get_time_in_ms() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(philo->data->write_lock);
}

void	ft_thinking(t_philo *philo)
{
	pthread_mutex_lock(philo->data->write_lock);
	printf("%ld %d is thinking\n", ft_get_time_in_ms() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(philo->data->write_lock);	
}

void	ft_death(t_philo *philo)
{
	pthread_mutex_lock(philo->data->write_lock);
	// if (philo->data->simulation_over == 1)
	// {
	printf("%ld %d died\n", ft_get_time_in_ms() - philo->data->start_time, philo->data->dead_philo_id);
	// }
	pthread_mutex_unlock(philo->data->write_lock);
}

void	ft_all_eaten(t_philo *philo)
{
	pthread_mutex_lock(philo->data->write_lock);
	// if (philo->data->simulation_over == 1)
	// {
	printf("les philos ont mange!");
	// }
	pthread_mutex_unlock(philo->data->write_lock);
}