/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-cama <sde-cama@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 12:39:15 by sde-cama          #+#    #+#             */
/*   Updated: 2023/06/12 23:10:01 by sde-cama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_philosophers(t_data *data);

void	*controller_routine(void *data_struc)
{
	t_data	*data;

	data = (t_data *)data_struc;
	while (get_time() < data->start_time)
		continue ;
	while (!data->end_simulation)
	{
		check_philosophers(data);
		usleep(1000);
	}
	return (NULL);
}

void	check_philosophers(t_data *data)
{
	int	i;
	time_t	time;
	t_bool	died;
	t_bool	satisfied;

	died = FALSE;
	satisfied = TRUE;
	i = 0;
	while (i < data->philo_num)
	{
		time = get_time();
		pthread_mutex_lock(&data->philos[i]->meal_time_lock);//checar se precisa desse lock
		if (time - data->philos[i]->last_meal >= data->death_time)
		{
			died = TRUE;
			pthread_mutex_unlock(&data->philos[i]->meal_time_lock);
			break ;
		}
		if (data->meals_num != -1 && data->philos[i]->times_ate < data->meals_num)
			satisfied = FALSE;
		pthread_mutex_unlock(&data->philos[i]->meal_time_lock);
		i++;
	}
	if (died || satisfied)
	{
		pthread_mutex_lock(&data->controll_lock);
		data->end_simulation = TRUE;
		pthread_mutex_unlock(&data->controll_lock);
	}
}
