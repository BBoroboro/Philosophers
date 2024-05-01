/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamoulin <mamoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:50:45 by mamoulin          #+#    #+#             */
/*   Updated: 2024/04/30 15:52:03 by mamoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free_mutex(t_data *data, t_philo *philo)
{
	int		i;
	t_philo	*temp;

	i = 0;
	while (++i <= data->philo_nb && philo)
	{
		temp = philo;
		philo = philo->next;
		if (temp->fork)
		{
			pthread_mutex_destroy(temp->fork);
			free(temp->fork);
		}
	}
	i = 0;
	while (++i <= data->philo_nb && philo)
	{
		temp = philo;
		philo = philo->next;
		if (temp->meal_lock)
		{
			pthread_mutex_destroy(temp->meal_lock);
			free(temp->meal_lock);
		}
	}
}

void	ft_free_mutex2(t_data *data)
{
	if (data->write_lock)
	{
		pthread_mutex_destroy(data->write_lock);
		free(data->write_lock);
	}
	if (data->dead_lock)
	{
		pthread_mutex_destroy(data->dead_lock);
		free(data->dead_lock);
	}
	if (data->full_lock)
	{
		pthread_mutex_destroy(data->full_lock);
		free(data->full_lock);
	}
}

void	ft_destroy_mutex(t_philo *philo_lst)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(philo_lst->data->write_lock);
	while (i < philo_lst->data->philo_nb)
	{
		pthread_mutex_destroy(philo_lst->meal_lock);
		philo_lst = philo_lst->next;
		i++;
	}
	i = 0;
	while (i < philo_lst->data->philo_nb)
	{
		pthread_mutex_destroy(philo_lst->fork);
		philo_lst = philo_lst->next;
		i++;
	}
}
