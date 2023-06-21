/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-cama <sde-cama@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 09:46:49 by sde-cama          #+#    #+#             */
/*   Updated: 2023/06/21 02:47:07 by sde-cama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_routine(t_philo *philo);
void	think_routine(t_philo *philo, t_bool first_round);
void	eat_routine(t_philo *philo);
void	one_philo_routine(t_philo *philo);

void	*philo_routine(void *philo_data)
{
	t_philo	*philo;

	philo = (t_philo *)philo_data;
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal = philo->data->start_time;
	pthread_mutex_unlock(&philo->meal_time_lock);
	while (get_time() < philo->data->start_time)
		continue ;
	if (philo->data->death_time == 0)
		return (NULL);
	if (philo->data->philo_num == 1)
	{
		one_philo_routine(philo);
		return (NULL);
	}
	if (philo->id % 2)
		think_routine(philo, TRUE);
	while (continue_simulation(philo))
	{
		eat_routine(philo);
		sleep_routine(philo);
		think_routine(philo, FALSE);
	}
	return (NULL);
}

void	sleep_routine(t_philo *philo)
{
	print_status(philo, "is sleeping");
	pthread_mutex_unlock(&philo->data->forks_lock[philo->fork[1]]);
	pthread_mutex_unlock(&philo->data->forks_lock[philo->fork[0]]);
	wait_action(philo, philo->data->sleep_time);
}

void	eat_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks_lock[philo->fork[0]]);
	print_status(philo, "has taken right fork");
	pthread_mutex_lock(&philo->data->forks_lock[philo->fork[1]]);
	print_status(philo, "has taken left fork");
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_time_lock);
	wait_action(philo, philo->data->eat_time);
	if (continue_simulation(philo))
	{
		pthread_mutex_lock(&philo->meal_time_lock);
		philo->times_ate += 1;
		pthread_mutex_unlock(&philo->meal_time_lock);
	}
}

void	think_routine(t_philo *philo, t_bool first_round)
{
	time_t	time_to_think;

	if (first_round)
	{
		pthread_mutex_lock(&philo->meal_time_lock);
		time_to_think = (philo->data->death_time
				- (get_time() - philo->last_meal)) / 2;
		pthread_mutex_unlock(&philo->meal_time_lock);
		wait_action(philo, time_to_think);
	}
	else
		print_status(philo, "is thinking");
}

void	one_philo_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks_lock[philo->fork[0]]);
	print_status(philo, "has taken right fork");
	pthread_mutex_unlock(&philo->data->forks_lock[philo->fork[0]]);
	wait_action(philo, philo->data->death_time);
	print_status(philo, "died");
}
