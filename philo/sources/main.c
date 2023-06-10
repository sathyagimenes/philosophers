/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-cama <sde-cama@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 23:06:33 by sde-cama          #+#    #+#             */
/*   Updated: 2023/06/10 00:56:25 by sde-cama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_args(char **argv);
static int	start_simulation(t_data *data);
void		*routine(void *philo);

int main(int argc, char **argv)
{
	t_data *data;
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
	data = malloc(sizeof(t_data) * 1);
	if (init(data, argc, argv))
		return(1);
	if (start_simulation(data))
		return (1);
	free_mem(data);
	return (0);
}

static int check_args(char **argv)
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

time_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

static int start_simulation(t_data *data)
{
	int i;

	i = 0;
	data->start_time = get_time();
	while (i < data->philo_num)
	{
		pthread_create(&data->philos[i]->thread, NULL, &routine, data->philos[i]);
		print_msg(data->start_time, data->philos[i]->id, "is working1");
		i++;
	}
	return (0);
}

void	*routine(void *philo_data)
{
	t_philo	*philo;

	philo = (t_philo *)philo_data;
	pthread_mutex_lock(&philo->data->write_lock);
	print_msg(philo->data->start_time, philo->id, "is working");
	pthread_mutex_unlock(&philo->data->write_lock);
	return (NULL);
}
