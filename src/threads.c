/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamoulin <mamoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 13:24:21 by mamoulin          #+#    #+#             */
/*   Updated: 2024/04/19 11:39:22 by mamoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->fork);
	pthread_mutex_lock(philo->data->write_lock);
	printf("%ld %d has taken a fork\n", ft_get_time_in_ms() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(philo->data->write_lock);
	pthread_mutex_unlock(philo->fork);
	usleep(philo->data->ttd * 1000);
	
	pthread_mutex_lock(philo->data->write_lock);
	printf("%ld %d died\n", ft_get_time_in_ms() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(philo->data->write_lock);
}

void	*routine_philo(void *arg)
{	
	t_philo *philo;

	philo = (t_philo *)arg;
	int i;
	i = 0;
	if (philo->data->philo_nb == 1)
	{
		ft_one_philo(philo);
		return (NULL);
	}
	if (philo->id % 2 != 0)
	{
		ft_thinking(philo);
		usleep(philo->data->tts * 1000); // plutot tte que tts
	}
	while(philo->data->dead_flag == 0 && philo->data->full_flag == 0)
	{
		ft_simulation(philo);
	}
	return (NULL);
}

void	ft_simulation(t_philo *philo)
{	
	//while(philo->data->total_meals == 0 || philo->meals_eaten < philo->data->total_meals) // another condition if meals eaten isnt in the parameters
	while(philo->data->dead_flag == 0 && philo->data->full_flag == 0)
	{
		if (philo->data->philo_nb % 2 == 0)
			ft_philo_even_case(philo);
		else
			ft_philo_odd_case(philo);
		// if (philo->id %2 == 0)
		// {
		// 	ft_take_fork(philo);		
		// 	ft_take_fork2(philo);
		// }
		// else
		// {
		// 	ft_take_fork2(philo);		
		// 	ft_take_fork(philo);		
		// }
		// ft_eating(philo);

		if (ft_action(philo, philo->data->tte))
			break ;
		
		pthread_mutex_unlock(philo->fork);
		pthread_mutex_unlock(philo->next->fork);
		
		ft_sleeping(philo);
		
		if (ft_action(philo, philo->data->tts))
			break ;
			
		ft_thinking(philo);
	}
	philo->data->simulation_over = 1; // wait, i dont need that anymore
}

int	ft_action(t_philo *philo, long time)
{
	long current;

	current = ft_get_time_in_ms();
	while((long)ft_get_time_in_ms() - current < time)
	{
		if (ft_get_time_in_ms() - philo->time_lst_meal >= philo->data->ttd && !philo->data->dead_flag)
		{
			philo->data->dead_flag = 1;
			philo->data->dead_philo_id = philo->id;
			pthread_mutex_unlock(philo->fork);
			pthread_mutex_unlock(philo->next->fork);
			return (1);
		}
		else if (philo->data->dead_flag) // voir version sans 2nd if et 2e condition du 1er if 
		{
			pthread_mutex_unlock(philo->fork);
			pthread_mutex_unlock(philo->next->fork);
			return (1);
		}
		else if (philo->data->full_flag) // revoir ca car c est inutile la 
		{
			pthread_mutex_unlock(philo->fork);
			pthread_mutex_unlock(philo->next->fork);
			return (1);		
		}
		usleep(100);
	}
	return (0);
}

void	*routine_check(void *arg)
{
	t_philo *philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	int i;
	i = 0;
	while(1) //!data->dead_flag && !data->full_flag)
	{
		if (ft_get_time_in_ms() - philo->time_lst_meal > data->ttd)
		{
			pthread_mutex_lock(philo->data->dead_lock);
			data->dead_flag = 1;
			philo->data->dead_philo_id = philo->id;
			pthread_mutex_unlock(philo->data->dead_lock);
			usleep(2000);
			ft_death(philo);
			break ;
		}
		if(philo->meals_eaten == philo->data->total_meals && philo->data->total_meals != 0)
			i++;
		if (i == philo->data->philo_nb)
		{
			pthread_mutex_lock(philo->data->full_lock);
			data->full_flag = 1;
			pthread_mutex_unlock(philo->data->full_lock);
			ft_all_eaten(philo);
			break ;
		}
		philo = philo->next;
	}
	return (NULL);
}

int	open_threads(t_data *data, t_philo *philo)
{
	int i;

	i = 1;
	data->start_time = ft_get_time_in_ms();
	while (i <= data->philo_nb)
	{
		philo->time_lst_meal = data->start_time;
		if (pthread_create(&philo->thread, NULL, &routine_philo, philo) != 0)
		{
			perror("Failed to create thread\n");
			return (1);
		}
		philo = philo->next;
		i++;
	}
	if (data->philo_nb > 1)
	{
		if (pthread_create(&data->monitor, NULL, &routine_check, philo))
		{
			perror("Failed to create thread\n");
			return (1);
		}
	}
	i = 1;
	while (i <= data->philo_nb)
	{
		if (pthread_join(philo->thread, NULL) != 0)
				return (1);
		philo = philo->next;
		i++;
	}
	if (data->philo_nb > 1)
		if (pthread_join(data->monitor, NULL) != 0)
			return (1);
	return (0);
}

// int join_threads(t_data *data, t_philo *philo)
// {
// 	int	i;
	
// 	i = 1;
// 	while (i <= data->philo_nb)
// 	{
// 		if (pthread_join(philo->thread, NULL) != 0)
// 				return (1);
// 		philo = philo->next;
// 		i++;
// 	}	
// 	return (0);
// }