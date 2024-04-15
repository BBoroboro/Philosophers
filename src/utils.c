/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamoulin <mamoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:25:51 by mamoulin          #+#    #+#             */
/*   Updated: 2024/04/15 11:22:23 by mamoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_lst(t_philo *philo_lst, t_data *data)
{
	t_philo *philo;
	int i;

	if (!philo_lst)
		return ;
	philo = philo_lst;
	i = 1;
	while (i <= data->philo_nb)
	{
		printf("--- philo n.%d ---\n", philo->id);
		printf("data ttd = %d", philo->data->tte);
		printf("-----------------\n\n");
		philo = philo->next;
		i++;
	}
}

int	ft_lst_size(t_philo **philo_lst)
{
	size_t	i;
	t_philo *philo;

	if (!philo_lst)
		return (0);
	philo = *philo_lst;
	i = 0;
	while (philo)
	{
		philo = philo->next;
		i++;
	}
	return (i);
}

long	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		result = (result * 10) + (str[i] - 48);
		i++;
	}
	return (sign * result);
}

void	*ft_memset(void *s, int c, size_t n)
{
	char	*str;

	str = s;
	while (n)
	{
		*str = (unsigned char)c;
		str++;
		n--;
	}
	return (s);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*dest;

	if (nmemb && size > (size_t) - 1 / nmemb)
		return (NULL);
	dest = (void *)malloc(nmemb * size);
	if (!dest)
		return (NULL);
	ft_bzero(dest, nmemb * size);
	return (dest);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*dst;

	if (!dest && !src)
		return (NULL);
	dst = (char *)dest;
	i = 0;
	while (i < n)
	{
		*dst = (*(char *)src);
		dst++;
		src++;
		i++;
	}
	return (dest);
}
