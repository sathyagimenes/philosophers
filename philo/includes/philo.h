/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-cama <sde-cama@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 23:07:49 by sde-cama          #+#    #+#             */
/*   Updated: 2023/06/18 20:49:12 by sde-cama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>		// printf
# include <stdlib.h>	// malloc, free
# include <unistd.h>	// write, usleep
# include <pthread.h>	// pthread functions
# include <sys/time.h>	// gettimeofday

# define TRUE 1
# define FALSE 0

typedef int				t_bool;
typedef char			*t_string;
typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	t_data			*data;
	pthread_t		thread;
	time_t			last_meal;
	int				times_ate;
	int				fork[2];
	pthread_mutex_t	meal_time_lock;
}	t_philo;

typedef struct s_data
{
	pthread_t		controller;
	t_bool			end_simulation;
	int				philo_num;
	int				meals_num;
	int				death_time;
	time_t			eat_time;
	time_t			sleep_time;
	time_t			start_time;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	controll_lock;
	pthread_mutex_t	*forks_lock;
	t_philo			**philos;
}	t_data;

int		error_msg(t_string str, t_data *data, t_bool make_free);
int		init(t_data *data, int argc, char **argv);
int		ft_atoi(const char *nptr);
void	free_mem(t_data	*data);
int		print_status(t_philo *philo, t_string action);
void	*philo_routine(void *philo_data);
void	*controller_routine(void *philo_data);
time_t	get_time(void);
int		print_msg(t_philo *philo, t_string action);
t_bool	continue_simulation(t_philo *philo);
void	wait_action(t_philo *philo, time_t time_to_wait);

#endif
