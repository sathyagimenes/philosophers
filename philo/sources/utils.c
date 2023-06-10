/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-cama <sde-cama@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:09:20 by sde-cama          #+#    #+#             */
/*   Updated: 2023/06/10 00:21:19 by sde-cama         ###   ########.fr       */
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

int	print_msg(time_t time, int philo, t_string action)
{
	printf("%ld %d %s\n", time, philo, action);
	return (0);
}
