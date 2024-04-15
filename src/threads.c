/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamoulin <mamoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 13:24:21 by mamoulin          #+#    #+#             */
/*   Updated: 2024/04/15 18:59:42 by mamoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine_philo(void *arg) // exemple
{	
	t_philo *philo;

	philo = (t_philo *)arg;
	int i;
	i = 0;
	if (philo->data->philo_nb == 1)
	{
		// here need a function to make him die and free all
	}
	if (philo->id % 2 == 0)
	{
		usleep(philo->data->tts * 1000); // see the sleep time
	}
	ft_simulation(philo);
	return (NULL);
}

void	ft_simulation(t_philo *philo)
{
	//philo->data->start_time = ft_get_time_in_ms(); // already initialized in the init functions
	
	while(philo->meals_eaten < philo->data->total_meals) // another condition if meals eaten isnt in the parameters
	{
		//printf("--------- %d meals to eat\n", philo->data->total_meals);
		
		pthread_mutex_lock(philo->fork);
		printf("%ld Philo n %d has taken a fork\n", ft_get_time_in_ms() - philo->data->start_time, philo->id);
		pthread_mutex_lock(philo->next->fork);
		printf("%ld Philo n %d has taken a 2nd fork\n", ft_get_time_in_ms() - philo->data->start_time, philo->id); // erase 2nd
		
		printf("%ld Philo n %d is eating\n", ft_get_time_in_ms() - philo->data->start_time, philo->id);
		philo->time_lst_meal = ft_get_time_in_ms();
		
		if (ft_action(philo, philo->data->tte))
			break ;

		
		pthread_mutex_unlock(philo->fork);
		pthread_mutex_unlock(philo->next->fork);
		
		printf("%ld Philo n %d finished eating\n", ft_get_time_in_ms() - philo->data->start_time, philo->id);

		philo->meals_eaten++;
		
		// if (philo->time_lst_meal - end_meal < 0) // maybe put that somewhere else
		// {
		// 	philo->time_of_death = ft_get_time_in_ms();
		// 	printf("%ld Philo n %d is dead\n", philo->time_of_death, philo->id);
		// 	exit(EXIT_SUCCESS);
		// }
		printf("%ld Philo n %d is sleeping\n", ft_get_time_in_ms() - philo->data->start_time, philo->id);
		
		if (ft_action(philo, philo->data->tts))
		{
			break ;
		}
		printf("%ld Philo n %d is thinking\n", ft_get_time_in_ms() - philo->data->start_time, philo->id);
		
	}
}

int	ft_action(t_philo *philo, long time)
{
	long current;

	current = ft_get_time_in_ms();

	while((long)ft_get_time_in_ms() - current < time)
	{
		// pthread_mutex_lock(philo->data->meal_lock);
		if (ft_get_time_in_ms() - philo->time_lst_meal >= philo->data->ttd)
		{
			philo->data->dead_flag = 1;
			philo->data->dead_philo_id = philo->id;
			// pthread_mutex_unlock(philo->data->meal_lock);
			pthread_mutex_unlock(philo->fork);
			pthread_mutex_unlock(philo->next->fork);
			return (1);
		}
		// if (philo->data->dead_flag)
		// {
		// 	// pthread_mutex_unlock(philo->data->meal_lock);
		// 	pthread_mutex_unlock(philo->fork);
		// 	pthread_mutex_unlock(philo->next->fork);
		// 	return (1);
		// }
		// pthread_mutex_unlock(philo->data->meal_lock);
	}
	return (0);
}

// void	*routine_check(void *arg)
// {
	
// }

// int	open_thread_monitor(t_data *data, t_philo *philo)
// {
// 	pthread_t monitor;
	
// 	if(pthread_create(monitor, NULL, &routine_check, philo));
// 	{
// 	perror("Failed to create thread\n");
// 	return (1);
// 	}
// 	while(philo)
// 	{
		
// 	}
// 	if (pthread_join(philo->thread, NULL) != 0)
// 		return (1);
// }


int	open_threads(t_data *data, t_philo *philo)
{
	int i;

	i = 1;
	data->start_time = ft_get_time_in_ms();
	while (i <= data->philo_nb)
	{
		if (pthread_create(&philo->thread, NULL, &routine_philo, philo) != 0)
		{
			perror("Failed to create thread\n");
			return (1);
		}
		printf("thread number %d has started\n", i);
		philo = philo->next;
		i++;
	}
	i = 1;
	while (i <= data->philo_nb)
	{
		if (pthread_join(philo->thread, NULL) != 0)
				return (1);
		printf("thread number %d has finished execution\n", i);
		philo = philo->next;
		i++;
	}
	if (data->dead_flag == 1) // faire le dead thing ici plutot que dans la routine
	{
		printf("%ld Philo n %d died\n", ft_get_time_in_ms() - data->start_time, philo->data->dead_philo_id);
	}
	return (0);
}