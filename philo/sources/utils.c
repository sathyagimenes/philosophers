/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-cama <sde-cama@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:09:20 by sde-cama          #+#    #+#             */
/*   Updated: 2023/06/18 21:11:41 by sde-cama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_mem(t_data	*data)
{
	int	i;

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

time_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (error_msg("Errorgettimeofday() FAILURE\n", NULL, FALSE));
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
