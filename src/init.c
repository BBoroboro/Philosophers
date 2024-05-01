/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamoulin <mamoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:47:53 by mamoulin          #+#    #+#             */
/*   Updated: 2024/05/01 15:04:09 by mamoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(char **av, t_data *data, t_philo **philo_lst)
{
	init_data(data, av);
	fill_philo_lst(data, philo_lst);
}

void	init_data(t_data *data, char **av)
{
	data->philo_nb = ft_atoi(av[1]);
	data->ttd = ft_atoi(av[2]);
	data->tte = ft_atoi(av[3]);
	data->tts = ft_atoi(av[4]);
	if (av[5])
		data->total_meals = ft_atoi(av[5]);
}

void	ft_fill(t_philo	*prev_philo, t_philo	*new_philo)
{
	prev_philo->next = new_philo;
	prev_philo = prev_philo->next;
}

void	fill_philo_lst(t_data *data, t_philo **first_philo)
{
	int		i;
	t_philo	*prev_philo;
	t_philo	*new_philo;

	i = 0;
	while (++i <= data->philo_nb)
	{
		new_philo = ft_calloc(1, sizeof(t_philo));
		if (!new_philo)
			return (ft_free_lst(*first_philo, data));
		if (i == 1)
		{
			*first_philo = new_philo;
			prev_philo = *first_philo;
		}
		else
		{
			prev_philo->next = new_philo;
			prev_philo = prev_philo->next;
		}
		new_philo->id = i;
		new_philo->data = data;
		if (!new_philo->data)
			return (ft_free_lst(*first_philo, data));
	}
	prev_philo->next = *first_philo;
}

int	init_mutex(t_philo *philo)
{
	int	i;

	i = 0;
	while (++i <= philo->data->philo_nb)
	{
		philo->fork = malloc(sizeof(pthread_mutex_t));
		if (pthread_mutex_init(philo->fork, NULL))
		{
			ft_destroy_mutex(philo);
			return (1);
		}
		philo = philo->next;
	}
	i = 0;
	while (++i <= philo->data->philo_nb)
	{
		philo->meal_lock = malloc(sizeof(pthread_mutex_t));
		if (pthread_mutex_init(philo->meal_lock, NULL))
		{
			ft_destroy_mutex(philo);
			return (1);
		}
		philo = philo->next;
	}
	init_mutex2(philo);
	return (0);
}

int	init_mutex2(t_philo *philo)
{
	philo->data->write_lock = malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(philo->data->write_lock, NULL))
	{
		ft_destroy_mutex(philo);
		return (1);
	}
	philo->data->dead_lock = malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(philo->data->dead_lock, NULL))
	{
		ft_destroy_mutex(philo);
		return (1);
	}
	philo->data->full_lock = malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(philo->data->full_lock, NULL))
	{
		ft_destroy_mutex(philo);
		return (1);
	}
	return (0);
}
