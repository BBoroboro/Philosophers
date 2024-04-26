/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamoulin <mamoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:50:04 by mamoulin          #+#    #+#             */
/*   Updated: 2024/04/25 16:22:34 by mamoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->data->dead_lock);
	if (philo->data->dead_flag == 1)
	{
		pthread_mutex_unlock(philo->data->dead_lock);
		return ;
	}
	pthread_mutex_unlock(philo->data->dead_lock);

	pthread_mutex_lock(philo->data->full_lock);
	if (philo->data->full_flag == 1)
	{
		pthread_mutex_unlock(philo->data->full_lock);
		return ;
	}
	pthread_mutex_unlock(philo->data->full_lock);



	pthread_mutex_lock(philo->fork);
	pthread_mutex_lock(philo->data->write_lock);
	printf("%ld %d has taken a fork\n", ft_get_time_in_ms() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(philo->data->write_lock);
}

void	ft_take_fork2(t_philo *philo)
{
	pthread_mutex_lock(philo->data->dead_lock);
	if (philo->data->dead_flag == 1)
	{
		pthread_mutex_unlock(philo->data->dead_lock);
		return ;
	}
	pthread_mutex_unlock(philo->data->dead_lock);
	
	pthread_mutex_lock(philo->data->full_lock);
	if (philo->data->full_flag == 1)
	{
		pthread_mutex_unlock(philo->data->full_lock);
		return ;
	}
	pthread_mutex_unlock(philo->data->full_lock);
	
	pthread_mutex_lock(philo->next->fork);
	pthread_mutex_lock(philo->data->write_lock);
	printf("%ld %d has taken a fork\n", ft_get_time_in_ms() - philo->data->start_time, philo->id); // erase 2nd
	pthread_mutex_unlock(philo->data->write_lock);
}

void	ft_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->data->dead_lock);
	if (philo->data->dead_flag == 1)
	{
		pthread_mutex_unlock(philo->data->dead_lock);
		return ;
	}
	pthread_mutex_unlock(philo->data->dead_lock);

	pthread_mutex_lock(philo->data->full_lock);
	if (philo->data->full_flag == 1)
	{
		pthread_mutex_unlock(philo->data->full_lock);
		return ;
	}
	pthread_mutex_unlock(philo->data->full_lock);
	
	pthread_mutex_lock(philo->meal_lock);
	pthread_mutex_lock(philo->data->write_lock);
	printf("%ld %d is eating\n", ft_get_time_in_ms() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(philo->data->write_lock);
	philo->meals_eaten++;
	philo->time_lst_meal = ft_get_time_in_ms();
	pthread_mutex_unlock(philo->meal_lock);
}

void	ft_sleeping(t_philo *philo)
{
	pthread_mutex_lock(philo->data->dead_lock);
	if (philo->data->dead_flag == 1)
	{
		pthread_mutex_unlock(philo->data->dead_lock);
		return ;
	}
	pthread_mutex_unlock(philo->data->dead_lock);

	pthread_mutex_lock(philo->data->full_lock);
	if (philo->data->full_flag == 1)
	{
		pthread_mutex_unlock(philo->data->full_lock);
		return ;
	}
	pthread_mutex_unlock(philo->data->full_lock);


	pthread_mutex_lock(philo->data->write_lock);
	printf("%ld %d is sleeping\n", ft_get_time_in_ms() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(philo->data->write_lock);
}

void	ft_thinking(t_philo *philo)
{
	pthread_mutex_lock(philo->data->dead_lock);
	if (philo->data->dead_flag == 1)
	{
		pthread_mutex_unlock(philo->data->dead_lock);
		return ;
	}
	pthread_mutex_unlock(philo->data->dead_lock);

	pthread_mutex_lock(philo->data->full_lock);
	if (philo->data->full_flag == 1)
	{
		pthread_mutex_unlock(philo->data->full_lock);
		return ;
	}
	pthread_mutex_unlock(philo->data->full_lock);
	
	pthread_mutex_lock(philo->data->write_lock);
	printf("%ld %d is thinking\n", ft_get_time_in_ms() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(philo->data->write_lock);	
}

void	ft_death(t_philo *philo)
{

	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(philo->data->full_lock);
	if (philo->data->full_flag == 1)
	{
		//ft_death(philo);
		pthread_mutex_unlock(philo->data->full_lock);
		return ;
	}
	pthread_mutex_unlock(philo->data->full_lock);
	
	pthread_mutex_lock(philo->data->write_lock);

	printf("%ld %d died\n", ft_get_time_in_ms() - philo->data->start_time, philo->data->dead_philo_id);
	pthread_mutex_unlock(philo->data->write_lock);
	
// 	if (data->philo_nb > 1)
// 		if (pthread_join(data->monitor, NULL) != 0)
// 			return ;
	
// 	free_all(philo, data);
// 	exit(EXIT_SUCCESS);
}

void	ft_all_eaten(t_philo *philo)
{
	
	pthread_mutex_lock(philo->data->write_lock);
	printf("les philos ont mange!\n");
	pthread_mutex_unlock(philo->data->write_lock);
}