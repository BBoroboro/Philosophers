/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamoulin <mamoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:24:08 by mamoulin          #+#    #+#             */
/*   Updated: 2024/04/10 17:59:30 by mamoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
// define

// structs

// typedef struct s_data	t_data;
/// revoir les struct comme LEON <3 !! seulement une liste chaine et pointe sur les data communes
// typedef struct s_philo
// {
// 	int	index;
// 	int	meals_eaten;
// 	pthread_t thread;
// 	pthread_mutex_t	*fork;
// 	int ttd;
// 	int tte;
// 	int tts;
// 	int dead;
// 	int number_of_times_each_philosopher_must_eat;
// 	struct s_philo *next;
// 	t_data *data;
// }		t_philo;

// typedef struct s_data
// {
// 	int 	philo_nb;
// 	int		dead_flag;
// 	int number_of_times_each_philosopher_must_eat;
// 	t_philo	**philo_lst; 
// 	pthread_mutex_t	*meal_lock;
// 	pthread_mutex_t	*write_lock;
// }		t_data; 

typedef struct s_data
{
	int philo_nb;
	int dead_flag;
	int ttd;
	int tte;
	int tts;
	int number_of_times_each_philosopher_must_eat;
	pthread_mutex_t	*meal_lock;
	pthread_mutex_t	*write_lock;
}	t_data;

typedef struct s_philo
{
	int id;
	int meals_eaten;
	pthread_t thread;
	pthread_mutex_t *fork;
	struct s_philo *next;
	t_data *data;
}	t_philo;

// free functions
void	free_all(t_philo *philo_lst, t_data *data);
void	ft_free_lst(t_philo *head, t_data *data);
void	ft_free_mutex(t_data *data, t_philo *philo);

//control (parsing)
int	control_args(int ac,char **av);
int	control_args_nb(int ac);
int control_args_symb(char **av);
int control_philo_nb(char **av);
int control_if_pos(char **av);

//init.c
void	fill_philo_lst(t_data *data, t_philo **philo_lst);
void	init_data(t_data *data, char **av);
void	init_philo(char **av, t_data *data, t_philo **philo_lst);
void	init_philo_lst(t_data *data);
int	init_mutex(t_data *data, t_philo *philo_lst);

//threads.c
int	open_threads(t_data *data, t_philo *philo);

//utils.c
void	ft_print_lst(t_philo *philo, t_data *data);
int	ft_lst_size(t_philo **lst);
long	ft_atoi(const char *str);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memset(void *s, int c, size_t n);


#endif