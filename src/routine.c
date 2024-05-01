/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamoulin <mamoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 13:24:21 by mamoulin          #+#    #+#             */
/*   Updated: 2024/05/01 17:31:45 by mamoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->fork);
	pthread_mutex_lock(philo->data->write_lock);
	printf("%ld %d has taken a fork\n", ft_get_time_in_ms()
		- philo->data->start_time, philo->id);
	pthread_mutex_unlock(philo->data->write_lock);
	pthread_mutex_unlock(philo->fork);
	usleep(philo->data->ttd * 1000);
	pthread_mutex_lock(philo->data->write_lock);
	printf("%ld %d died\n", ft_get_time_in_ms() - philo->data->start_time,
		philo->id);
	pthread_mutex_unlock(philo->data->write_lock);
}

void	*routine_philo(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	i = 0;
	// lock mutex start 2
	// unlock mutex start 4
	if (philo->data->philo_nb == 1)
	{
		ft_one_philo(philo);
		return (NULL);
	}
	if (philo->id % 2 != 0)
	{
		ft_thinking(philo);
		usleep(philo->data->tte * 1000);
	}
	while (!check_if_over(philo))
		ft_simulation(philo);
	return (NULL);
}

void	ft_simulation(t_philo *philo)
{
	while (!check_if_over(philo))
	{
		if (philo->data->philo_nb % 2 == 0)
			ft_philo_even_case(philo);
		else
			ft_philo_odd_case(philo);
		ft_eating(philo);
		if (ft_action(philo, philo->data->tte))
			break ;
		pthread_mutex_unlock(philo->fork);
		pthread_mutex_unlock(philo->next->fork);
		ft_sleeping(philo);
		if (ft_action2(philo, philo->data->tts))
			break ;
		ft_thinking(philo);
	}
}

int	ft_action(t_philo *philo, long time)
{
	long	current;

	current = ft_get_time_in_ms();
	while ((long)ft_get_time_in_ms() - current < time && !check_if_over(philo))
	{
		if (ft_get_time_in_ms() - philo->time_lst_meal >= philo->data->ttd)
		{
			pthread_mutex_lock(philo->data->dead_lock);
			philo->data->dead_flag = 1;
			if (philo->data->death_time == 0)
				philo->data->death_time = ft_get_time_in_ms()
					- philo->data->start_time;
			philo->data->dead_philo_id = philo->id;
			pthread_mutex_unlock(philo->data->dead_lock);
			pthread_mutex_unlock(philo->fork);
			pthread_mutex_unlock(philo->next->fork);
			return (1);
		}
		usleep(1);
	}
	return (0);
}

int	ft_action2(t_philo *philo, long time)
{
	long	current;

	current = ft_get_time_in_ms();
	while ((long)ft_get_time_in_ms() - current < time && !check_if_over(philo))
	{
		if (ft_get_time_in_ms() - philo->time_lst_meal >= philo->data->ttd)
		{
			pthread_mutex_lock(philo->data->dead_lock);
			philo->data->dead_flag = 1;
			philo->data->dead_philo_id = philo->id;
			if (philo->data->death_time == 0)
				philo->data->death_time = ft_get_time_in_ms()
					- philo->data->start_time;
			pthread_mutex_unlock(philo->data->dead_lock);
			return (1);
		}
		usleep(1);
	}
	return (0);
}
