/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamoulin <mamoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 13:09:35 by mamoulin          #+#    #+#             */
/*   Updated: 2024/04/29 10:26:38 by mamoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_if_full(t_philo *philo)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < philo->data->philo_nb)
	{
		pthread_mutex_lock(philo->meal_lock);
		if (philo->meals_eaten >= philo->data->total_meals)
			count++;
		pthread_mutex_unlock(philo->meal_lock);
		philo = philo->next;
		i++;
	}
	if (count == philo->data->philo_nb)
		return (1);
	return (0);
}

int	check_if_over(t_philo *philo)
{
	pthread_mutex_lock(philo->data->dead_lock);
	if (philo->data->dead_flag == 1)
	{
		pthread_mutex_unlock(philo->data->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->data->dead_lock);
	pthread_mutex_lock(philo->data->full_lock);
	if (philo->data->full_flag == 1)
	{
		pthread_mutex_unlock(philo->data->full_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->data->full_lock);
	return (0);
}

int	check_meal_time(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(philo->meal_lock);
	if (ft_get_time_in_ms() - philo->time_lst_meal > data->ttd)
	{
		pthread_mutex_unlock(philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

// int		check_if_over(t_philo *philo)
// {
// 	int res;

// 	res = 0;
// 	pthread_mutex_lock(philo->data->dead_lock);
// 	if (philo->data->dead_flag == 1)
// 		res = 1;
// 	pthread_mutex_unlock(philo->data->dead_lock);
// 	pthread_mutex_lock(philo->data->full_lock);
// 	if (philo->data->full_flag == 1)
// 		res = 1;
// 	pthread_mutex_unlock(philo->data->full_lock);
// 	return (res);
// }
