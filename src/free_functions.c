/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamoulin <mamoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:50:45 by mamoulin          #+#    #+#             */
/*   Updated: 2024/04/17 16:30:42 by mamoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_philo *philo_lst, t_data *data)
{
	ft_free_mutex(data, philo_lst);
	ft_free_lst(philo_lst, data);
}

void	ft_free_lst(t_philo *head, t_data *data)
{
	int	i;
	t_philo	*tmp;
	t_philo *philo;

	if (!head)
		return ;
	philo = head;
	i = 1;
	while (i <= data->philo_nb && philo)
	{
		tmp = philo->next;
		free(philo);
		philo = tmp;
		i++;
	}
}

void	ft_free_philos_data(t_philo *philo)
{
	int	i;
	int j;

	i = 0;
	j = philo->data->philo_nb;
	while (i < j)
	{
		printf("%d\n", i);
		free(philo->data);
		philo = philo->next;
		i++;
	}
}

void	ft_free_mutex(t_data *data, t_philo *philo)
{
	int	i;
	t_philo *temp;

	i = 1;
	while(i <= data->philo_nb && philo)
	{
		temp = philo;
		philo = philo->next;
		if (temp->fork)
		{
			pthread_mutex_destroy(temp->fork);
			free(temp->fork);
		}
		i++;
	}
	i = 1;
	while(i <= data->philo_nb && philo)
	{
		temp = philo;
		philo = philo->next;
		if (temp->meal_lock)
		{
			pthread_mutex_destroy(temp->meal_lock);
			free(temp->meal_lock);
		}
		i++;
	}
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

void ft_destroy_mutex(t_philo *philo_lst)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(philo_lst->data->write_lock);
	while(i < philo_lst->data->philo_nb)
	{
		pthread_mutex_destroy(philo_lst->meal_lock);
		philo_lst = philo_lst->next;
		i++;
	}
	i = 0;
	while(i < philo_lst->data->philo_nb)
	{
		pthread_mutex_destroy(philo_lst->fork);
		philo_lst = philo_lst->next;
		i++;
	}
}

// void ft_destroy_mutex(t_philo *philo)
// {
//     while (philo)
// 	{
//         if (philo->fork) 
// 		{
//            // pthread_mutex_destroy(philo->fork);
//             //free(philo->fork);
//         }
//         philo = philo->next;
//     }

//     // Clean up meal lock
//     if (philo && philo->data->meal_lock) {
//         //pthread_mutex_destroy(philo->data->meal_lock);
//         //free(philo->data->meal_lock);
//     }

//     // Clean up write lock
//     if (philo && philo->data->write_lock) {
//         //pthread_mutex_destroy(philo->data->write_lock);
//         //free(philo->data->write_lock);
//     }
// }