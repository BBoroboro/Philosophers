/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamoulin <mamoulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:24:08 by mamoulin          #+#    #+#             */
/*   Updated: 2024/05/01 13:52:45 by mamoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
// define

// structs
typedef struct s_data
{
	long	start_time;
	int simulation_over;
	int philo_nb;
	int dead_flag;
	long int death_time;
	int dead_philo_id;
	int	full_flag;
	int ttd;
	int tte;
	int tts;
	int total_meals;
	int finished_eating;
	pthread_t monitor;
	// pthread_mutex_t *last_meal;
	// pthread_mutex_t *finished_meal;
	pthread_mutex_t *full_lock; // lr dead_ock peut faire ca
	pthread_mutex_t *dead_lock;
	pthread_mutex_t	*write_lock;
}	t_data;

typedef struct s_philo
{
	int id;
	long time_of_death;
	long time_lst_meal;
	int meals_eaten;
	pthread_t thread;
	pthread_mutex_t *fork;
	pthread_mutex_t	*meal_lock;
	struct s_philo *next;
	t_data *data;
}	t_philo;

// free_functions.c
void	free_all(t_philo *philo_lst, t_data *data);
void	ft_free_lst(t_philo *head, t_data *data);
void	ft_free_philos_data(t_philo *philo);
// free_functions2.c
void	ft_free_mutex(t_data *data, t_philo *philo);
void	ft_free_mutex2(t_data *data);
void ft_destroy_mutex(t_philo *philo_lst);

//control (parsing)
int	control_args(int ac,char **av);
int	control_args_nb(int ac);
int control_philo_nb(char **av);
//parsing2.c
int control_if_pos(char **av);
int control_args_symb(char **av);
int	control_limits(char **av);

//init.c
void	init_philo(char **av, t_data *data, t_philo **philo_lst);
void	init_data(t_data *data, char **av);
void	fill_philo_lst(t_data *data, t_philo **philo_lst);
int	init_mutex(t_philo *philo_lst);
int	init_mutex2(t_philo *philo_lst);
//void	init_philo_lst(t_data *data);

//routine.c
void	ft_one_philo(t_philo *philo);
void	*routine_philo(void *arg);
void	ft_simulation(t_philo *philo);
int	ft_action(t_philo *philo, long time);
int	ft_action2(t_philo *philo, long time);
//routine2.c
void	ft_launch_death(t_philo *philo);
void	*routine_check(void *arg);
//threads.c
int open_thread_monitor(t_data *data, t_philo *philo);
int	open_threads(t_data *data, t_philo *philo);

//actions.c
void	ft_take_fork(t_philo *philo);
void	ft_take_fork2(t_philo *philo);
void	ft_eating(t_philo *philo);
void	ft_sleeping(t_philo *philo);
void	ft_thinking(t_philo *philo);
void	ft_death(t_philo *philo);
void	ft_all_eaten(t_philo *philo);

//philo_sync.c
void	ft_philo_even_case(t_philo *philo);
void	ft_philo_odd_case(t_philo *philo);

//check.c
int		check_if_over(t_philo *philo);
int		check_if_full(t_philo *philo);
int	check_meal_time(t_philo *philo);

//get_time.c
long ft_get_time_in_ms(void);

//utils.c
void	ft_print_lst(t_philo *philo, t_data *data);
int	ft_lst_size(t_philo **lst);
long	ft_atoi(const char *str);
// void	*ft_memcpy(void *dest, const void *src, size_t n); // do i really use it?
//utils2.c
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);

#endif