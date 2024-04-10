/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamoulin <mamoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:47:53 by mamoulin          #+#    #+#             */
/*   Updated: 2024/04/10 17:28:01 by mamoulin         ###   ########.fr       */
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
		data->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
}


void	fill_philo_lst(t_data *data, t_philo **first_philo)
{
	int i;
	t_philo *prev_philo;
	t_philo *new_philo;

	i = 1;
	while(i <= data->philo_nb)
	{
		new_philo = ft_calloc(1, sizeof(t_philo));
		if(!new_philo)
		{
			ft_free_lst(*first_philo, data);
			return ;
		}
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
		// prev_philo = prev_philo->next;
		i++;
	}
	prev_philo->next = *first_philo;
}


// void	init_philo_lst(t_data *data)
// {
// 	data->philo_lst = malloc(sizeof(t_philo *));
// 	// protect malloc
// }

int	init_mutex(t_data *data, t_philo *philo)
{
	int	i;

	i = 1;
	while(i <= data->philo_nb)
	{
		philo->fork = malloc(sizeof(pthread_mutex_t)); 
		if (pthread_mutex_init(philo->fork, NULL))
		{
			//need a cleanup function for mutex here
			return (1);
		}
		philo = philo->next;
		i++;
	}
	data->meal_lock = malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(data->meal_lock, NULL))
	{
		//need a cleanup function for mutex here
		return (1);
	}
	data->write_lock = malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(data->write_lock, NULL))
	{
		//need a cleanup function for mutex here
		return (1);
	}
	return (0);
}
