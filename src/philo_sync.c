/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sync.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamoulin <mamoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:31:34 by mamoulin          #+#    #+#             */
/*   Updated: 2024/05/01 17:31:19 by mamoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_philo_even_case(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		ft_take_fork(philo);
		ft_take_fork2(philo);
	}
	else
	{
		ft_take_fork2(philo);
		ft_take_fork(philo);
	}
}

void	ft_philo_odd_case(t_philo *philo)
{
	if (philo->id % 2 != 0 && philo->id != philo->data->philo_nb)
	{
		if (philo->meals_eaten > 0 && philo->data->tte >= philo->data->tts)
			usleep(philo->data->tte * 1000);
		ft_take_fork2(philo);
		ft_take_fork(philo);
	}
	else if (philo->id % 2 == 0)
	{
		if (philo->meals_eaten > 0 && philo->data->tte >= philo->data->tts)
			usleep(philo->data->tte * 1000);
		ft_take_fork(philo);
		ft_take_fork2(philo);
	}
	else if (philo->id == philo->data->philo_nb)
	{
		if (philo->meals_eaten > 0 && philo->data->tte >= philo->data->tts)
			usleep(philo->data->tte * 1000);
		ft_take_fork2(philo);
		ft_take_fork(philo);
	}
}
