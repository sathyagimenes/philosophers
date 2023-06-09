/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-cama <sde-cama@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:09:20 by sde-cama          #+#    #+#             */
/*   Updated: 2023/06/09 20:16:17 by sde-cama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_mem(t_data	*data)
{
	if (data)
		printf("freeing memory\n");
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
	int		sign;

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
