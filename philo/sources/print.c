/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-cama <sde-cama@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 21:10:31 by sde-cama          #+#    #+#             */
/*   Updated: 2023/06/18 21:11:51 by sde-cama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_msg(t_string str, t_data *data, t_bool make_free)
{
	printf("%s\n", str);
	if (make_free)
		free_mem(data);
	return (1);
}

int	print_msg(t_philo *philo, t_string action)
{
	time_t	time;
	int		philo_num;

	time = get_time() - philo->data->start_time;
	philo_num = philo->id + 1;
	printf("%ld ms Philosopher %d %s\n", time, philo_num, action);
	return (0);
}

int	print_status(t_philo *philo, t_string action)
{
	pthread_mutex_lock(&philo->data->write_lock);
	if (continue_simulation(philo))
		print_msg(philo, action);
	pthread_mutex_unlock(&philo->data->write_lock);
	return (0);
}
