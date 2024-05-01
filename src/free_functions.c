/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamoulin <mamoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:50:45 by mamoulin          #+#    #+#             */
/*   Updated: 2024/04/30 15:52:16 by mamoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_philo *philo_lst, t_data *data)
{
	ft_free_mutex(data, philo_lst);
	ft_free_mutex2(data);
	ft_free_lst(philo_lst, data);
}

void	ft_free_lst(t_philo *head, t_data *data)
{
	int		i;
	t_philo	*tmp;
	t_philo	*philo;

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
	int	j;

	i = 0;
	j = philo->data->philo_nb;
	while (i < j)
	{
		free(philo->data);
		philo = philo->next;
		i++;
	}
}
