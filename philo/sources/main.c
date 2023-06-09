/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-cama <sde-cama@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 23:06:33 by sde-cama          #+#    #+#             */
/*   Updated: 2023/06/18 21:25:38 by sde-cama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_args(char **argv);
static int	start_simulation(t_data *data);
void		wait_threads(t_data *data);
void		destroy_mutexes(t_data *data);

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6)
		return (error_msg("Invalid quantity of arguments", NULL, FALSE));
	if (check_args(argv))
		return (error_msg("Invalid argument. Must be interger", NULL, FALSE));
	data = malloc(sizeof(t_data) * 1);
	if (!data)
		return (error_msg("Error: Could not allocate memory.", NULL, FALSE));
	if (init(data, argc, argv))
		return (1);
	if (start_simulation(data))
		return (1);
	wait_threads(data);
	destroy_mutexes(data);
	free_mem(data);
	return (0);
}

static int	check_args(char **argv)
{
	int	i;
	int	j;

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

static int	start_simulation(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time() + 20 * data->philo_num;
	while (i < data->philo_num)
	{
		if (pthread_create(&data->philos[i]->thread, NULL,
				&philo_routine, data->philos[i]))
			return (error_msg("Error: failed to create thread", data, TRUE));
		i++;
	}
	if (data->philo_num > 1)
	{
		if (pthread_create(&data->controller, NULL, &controller_routine, data))
			return (error_msg("Error: failed to create thread", data, TRUE));
	}	
	return (0);
}

void	wait_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		pthread_join(data->philos[i]->thread, NULL);
		i++;
	}
	if (data->philo_num > 1)
		pthread_join(data->controller, NULL);
}

void	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		pthread_mutex_destroy(&data->philos[i]->meal_time_lock);
		pthread_mutex_destroy(&data->forks_lock[i]);
		i++;
	}
	pthread_mutex_destroy(&data->controll_lock);
	pthread_mutex_destroy(&data->write_lock);
}
