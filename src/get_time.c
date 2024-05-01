/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamoulin <mamoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:46:35 by mamoulin          #+#    #+#             */
/*   Updated: 2024/04/26 15:00:35 by mamoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_get_time_in_ms(void)
{
	struct timeval	time_struct;
	long			seconds;
	long			microseconds;
	long			time_ms;

	gettimeofday(&time_struct, NULL);
	seconds = time_struct.tv_sec;
	microseconds = time_struct.tv_usec;
	time_ms = (seconds * 1000) + (microseconds / 1000);
	return (time_ms);
}
