/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamoulin <mamoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 13:24:21 by mamoulin          #+#    #+#             */
/*   Updated: 2024/04/26 12:24:32 by mamoulin         ###   ########.fr       */
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

int		check_if_over(t_philo *philo)
{
	pthread_mutex_lock(philo->data->dead_lock);
	if (philo->data->dead_flag == 1)
	{
		//ft_death(philo);
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
		usleep(philo->data->tte * 1000); // * 1000); // plutot tte que tts
	}

	while(!check_if_over(philo))
		ft_simulation(philo);
	return (NULL);
}

void	ft_simulation(t_philo *philo)
{	
	//while(philo->data->total_meals == 0 || philo->meals_eaten < philo->data->total_meals) // another condition if meals eaten isnt in the parameters
	//while(philo->data->dead_flag == 0 && philo->data->full_flag == 0)
	while(!check_if_over(philo))
	{
		if (philo->data->philo_nb % 2 == 0) // voir parce que j ai pas mal d erreur sur les meal depuis ca
			ft_philo_even_case(philo);
		else
			ft_philo_odd_case(philo);
		ft_eating(philo);

		if (ft_action(philo, philo->data->tte))
			break ;
		
		pthread_mutex_unlock(philo->fork);
		pthread_mutex_unlock(philo->next->fork);
		
		ft_sleeping(philo);
		
		if (ft_action(philo, philo->data->tts))
			break ;
			
		ft_thinking(philo);
	}
	//philo->data->simulation_over = 1; // wait, i dont need that anymore
}

int	ft_action(t_philo *philo, long time)
{
	long current;

	current = ft_get_time_in_ms();
	while((long)ft_get_time_in_ms() - current < time && philo->data->dead_flag == 0)
	{
		//pthread_mutex_lock(philo->data->dead_lock);
		//pthread_mutex_lock(philo->data->last_meal);
		if (ft_get_time_in_ms() - philo->time_lst_meal >= philo->data->ttd) // && !philo->data->dead_flag)
		{
			pthread_mutex_lock(philo->data->dead_lock);
			philo->data->dead_flag = 1;
			philo->data->dead_philo_id = philo->id;
			//ft_death(philo);
			pthread_mutex_unlock(philo->fork);
			pthread_mutex_unlock(philo->next->fork);
			//pthread_mutex_unlock(philo->data->last_meal);
			pthread_mutex_unlock(philo->data->dead_lock);
			return (1);
		}
		usleep(100);
	}
	return (0);
}
int		check_if_full(t_philo *philo)
{
	int i;
	int count;
	
	i = 0;
	count = 0;
	while(i < philo->data->philo_nb)
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
	return(0);
}

void	*routine_check(void *arg)
{
	t_philo *philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while(1) //!data->dead_flag && !data->full_flag)
	{
		if (ft_get_time_in_ms() - philo->time_lst_meal > data->ttd)
		{
			pthread_mutex_lock(philo->data->dead_lock);
			data->dead_flag = 1;
			philo->data->dead_philo_id = philo->id;
			pthread_mutex_unlock(philo->data->dead_lock);
			usleep(5000);
			ft_death(philo);
			break ;
		}
		if (check_if_full(philo) && philo->data->total_meals != 0)
		{
			pthread_mutex_lock(philo->data->full_lock);
			data->full_flag = 1;
			ft_all_eaten(philo);
			pthread_mutex_unlock(philo->data->full_lock);
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
