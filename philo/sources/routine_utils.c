/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-cama <sde-cama@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 20:47:51 by sde-cama          #+#    #+#             */
/*   Updated: 2023/06/18 20:48:41 by sde-cama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_action(t_philo *philo, time_t time_to_wait)
{
	time_t	stop_time;

	stop_time = get_time() + time_to_wait;
	while (get_time() < stop_time)
	{
		if (!continue_simulation(philo))
			break ;
		usleep(100);
	}
}

t_bool	continue_simulation(t_philo *philo)
{
	t_bool	continue_simulation;

	continue_simulation = TRUE;
	pthread_mutex_lock(&philo->data->controll_lock);
	if (philo->data->end_simulation)
		continue_simulation = FALSE;
	pthread_mutex_unlock(&philo->data->controll_lock);
	return (continue_simulation);
}
