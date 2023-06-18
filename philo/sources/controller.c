/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-cama <sde-cama@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 12:39:15 by sde-cama          #+#    #+#             */
/*   Updated: 2023/06/18 14:00:49 by sde-cama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	check_philosophers(t_data *data);

void	*controller_routine(void *data_struc)
{
	t_data	*data;

	data = (t_data *)data_struc;
	while (get_time() < data->start_time)
		continue ;
	// while (TRUE)
	// {
	// 	if (check_philosophers(data))
	// 		return (NULL);
	// 	usleep(1000);
	// }
	while (check_philosophers(data))
		usleep(1000);
	return (NULL);
}

t_bool	check_philosophers(t_data *data)
{
	int		i;
	t_bool	died;
	t_bool	satisfied;

	died = FALSE;
	satisfied = TRUE;
	i = 0;
	while (i < data->philo_num)
	{
		pthread_mutex_lock(&data->philos[i]->meal_time_lock);
		if ((get_time() - data->philos[i]->last_meal) >= data->death_time)
		{
			died = TRUE;
			// pthread_mutex_unlock(&data->philos[i]->meal_time_lock);
			break ;
		}
		if (data->meals_num == -1 || data->philos[i]->times_ate < data->meals_num)
			satisfied = FALSE;
		pthread_mutex_unlock(&data->philos[i]->meal_time_lock);
		i++;
	}
	if (died || satisfied)
	{
		pthread_mutex_lock(&data->controll_lock);
		data->end_simulation = TRUE;
		pthread_mutex_unlock(&data->controll_lock);
		if (died)
		{
			pthread_mutex_lock(&data->write_lock);
			print_msg(data->philos[i], "died");
			pthread_mutex_unlock(&data->write_lock);
			pthread_mutex_unlock(&data->philos[i]->meal_time_lock);
		}
		return (FALSE);
	}
	return (TRUE);
}
