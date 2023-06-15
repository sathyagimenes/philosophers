/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-cama <sde-cama@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:09:20 by sde-cama          #+#    #+#             */
/*   Updated: 2023/06/14 20:47:19 by sde-cama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_mem(t_data	*data)
{
	int i;

	i = 0;
	if (data->philos[i])
	{
		while (i < data->philo_num)
			free(data->philos[i++]);
		free(data->philos);
	}
	if (data->forks_lock)
		free(data->forks_lock);
	free(data);
}

int	error_msg(t_string str, t_data *data, t_bool make_free)
{
	printf("%s\n", str);
	if (make_free)
		free_mem(data);
	return (1);
}

int	ft_atoi(const char *nptr)
{
	int	num;
	int	sign;

	num = 0;
	sign = 1;
	while ((*nptr <= 13 && *nptr >= 9) || *nptr == 32)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign *= -1;
		nptr++;
	}
	while (*nptr <= '9' && *nptr >= '0')
	{
		num = (num * 10) + (*nptr - 48);
		nptr++;
	}
	return (num * sign);
}

int	print_msg(t_philo *philo, t_string action)
{
	time_t	time;
	int philo_num;

	time = get_time() - philo->data->start_time;
	philo_num = philo->id;
	printf("%ld ms Philosopher %d %s\n", time, philo_num, action);
	return (0);
}

int	print_status(t_philo *philo, t_string action)
{
	pthread_mutex_lock(&philo->data->write_lock);
	print_msg(philo, action);
	pthread_mutex_unlock(&philo->data->write_lock);
	return (0);
}

time_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (error_msg("Errorgettimeofday() FAILURE\n", NULL, FALSE));
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
