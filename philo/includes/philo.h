/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-cama <sde-cama@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 23:07:49 by sde-cama          #+#    #+#             */
/*   Updated: 2023/06/08 14:26:58 by sde-cama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>		// printf
# include <stdlib.h>	// malloc, free
# include <string.h>	// memset
# include <unistd.h>	// write, usleep
# include <pthread.h>	// pthread functions
# include <sys/time.h>	// gettimeofday

# define TRUE 1
# define FALSE 0
typedef int		t_bool;
typedef char	*t_string;

typedef struct s_data
{
	pthread_t	*tid;
}	t_data;

int	error_msg(t_string str, t_data *data, t_bool make_free);

#endif
