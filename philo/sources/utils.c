/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-cama <sde-cama@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:09:20 by sde-cama          #+#    #+#             */
/*   Updated: 2023/06/08 14:28:03 by sde-cama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_mem(t_data	*data)
{
	if (data)
		printf("freeing memory");
}

int	error_msg(t_string str, t_data *data, t_bool make_free)
{
	printf("%s\n", str);
	if (make_free)
		free_mem(data);
	return (1);
}
