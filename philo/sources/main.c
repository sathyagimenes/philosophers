/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-cama <sde-cama@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 23:06:33 by sde-cama          #+#    #+#             */
/*   Updated: 2023/06/09 20:14:42 by sde-cama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_args(char **argv)
{
	int i;
	int j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if ((argv[i][j] < 48 || argv[i][j] > 57) && argv[i][j] != ' ')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_data data;
	/*
	number_of_philosophers;
	time_to_die;
	time_to_eat;
	time_to_sleep;
	number_of_times_each_philosopher_must_eat
	*/
	if (argc < 5 || argc > 6)
		return (error_msg("Error: Invalid quantity of arguments", NULL, FALSE));
	if (check_args(argv))
		return (error_msg("Error: Invalid argument. Must be interger", NULL, FALSE));
	if (init(&data, argc, argv))
		return(1);
	// if (!start_routine(data))
	// {
		//init threading
	// }
	free_mem(&data);
	printf("it is working...\n");
	return (0);
}

/*
	threading
	salva start time = get_time
	
*/
