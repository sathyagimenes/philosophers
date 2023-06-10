/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-cama <sde-cama@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 23:07:49 by sde-cama          #+#    #+#             */
/*   Updated: 2023/06/10 00:51:25 by sde-cama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>		// printf
# include <stdlib.h>	// malloc, free
# include <string.h>	// memset
# include <unistd.h>	// write, usleep
# include <pthread.h>	// pthread functions
# include <sys/time.h>	// gettimeofday

# define TRUE 1
# define FALSE 0
typedef int			t_bool;
typedef char		*t_string;
typedef struct s_data	t_data;
typedef struct s_philo
{
	int	id;
	t_data			*data;
	pthread_t		thread;
	time_t			last_meal;
	unsigned int	times_ate;
	pthread_mutex_t	meal_time_lock;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
}	t_philo;
typedef struct s_data
{
	pthread_t		*tid;
	t_bool			dead;//ver se vai usar
	t_bool			end_simulation;
	int				philo_num;
	int				meals_num;
	time_t			death_time;
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
int		print_msg(time_t time, int philo, t_string action);

#endif
