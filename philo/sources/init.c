/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-cama <sde-cama@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:00:32 by sde-cama          #+#    #+#             */
/*   Updated: 2023/06/14 19:26:44 by sde-cama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int		init_data(t_data *data, int argc, char **argv);
static int		init_philos(t_data *data);
// static int		assign_forks(t_data *data);
static t_bool	init_mutex(t_data *data);

int	init(t_data *data, int argc, char **argv)
{
	if (!data)
		return(error_msg("Error: Could not allocate memory.3", NULL, FALSE));
	if (init_data(data, argc, argv))
		return (1);
	if (init_philos(data))
		return (1);
	if (init_mutex(data))
		return (1);
	return (0);
}

static int	init_data(t_data *data, int argc, char **argv)
{
	data->philo_num = ft_atoi(argv[1]);
	data->death_time = ft_atoi(argv[2]);
	data->eat_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
		data->meals_num = ft_atoi(argv[5]);
	else
		data->meals_num = -1;
	if (data->philo_num <= 0 || data->philo_num > 200 || data->death_time < 0
		|| data->eat_time < 0 || data->sleep_time < 0)
		return (error_msg("Error: Invalid argument value", NULL, FALSE));
	data->dead = FALSE;//verificar se vai usar
	data->end_simulation = FALSE;
	return (0);
}

static void	assign_forks(t_philo *philo)
{
	philo->fork[0] = philo->id;
	philo->fork[1] = (philo->id + 1) % philo->data->philo_num;
	if (philo->id % 2)
	{
		philo->fork[0] = (philo->id + 1) % philo->data->philo_num;
		philo->fork[1] = philo->id;
	}
}

static int init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->philo_num);
	if (!data->philos)
		return (error_msg("Error: Could not allocate memory.1", NULL, FALSE));
	i = 0;
	while (i < data->philo_num)
	{
		data->philos[i] = malloc(sizeof(t_philo) * 1);
		if (!data->philos[i])
		{
			perror("Error: Could not allocate memory.2");
			return (error_msg("Error: Could not allocate memory.2", NULL, FALSE));//rever se precisa dar free
		}
		if (pthread_mutex_init(&data->philos[i]->meal_time_lock, 0) != 0)
		{
			perror("Error: Could not allocate memory.2");
			return (error_msg("Error: Could not create mutex.", NULL, FALSE));
		}
		data->philos[i]->data = data;
		data->philos[i]->id = i;
		data->philos[i]->times_ate = 0;
		assign_forks(data->philos[i]);
		i++;
	}
	// if (assign_forks(data))
	// 	return (1);
	return (0);
}

// static int assign_forks(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	data->forks_lock = malloc(sizeof(pthread_mutex_t) * data->philo_num);
// 	if (!data->forks_lock)
// 		return (error_msg("Error: Could not allocate memory.5", data, FALSE));//precisa apagar mem?
// 	if (pthread_mutex_init(&data->forks_lock[i], 0) != 0)
// 	{
// 		perror("error");
// 		return (error_msg("Error: Could not create mutex.", data, TRUE));
// 	}
// 	data->philos[0]->left_fork = &data->forks_lock[0];
// 	data->philos[0]->right_fork = &data->forks_lock[data->philo_num - 1];
// 	while (++i < data->philo_num)
// 	{
// 		if (pthread_mutex_init(&data->forks_lock[i], NULL) != 0)
// 			return (error_msg("Error: Could not create mutex.", data, TRUE));
// 		data->philos[i]->left_fork = &data->forks_lock[i];
// 		data->philos[i]->right_fork = &data->forks_lock[i - 1];
// 	}
// 	return (0);
// }
static pthread_mutex_t	*init_forks(t_data *self)
{
	pthread_mutex_t	*forks;
	int	i;

	forks = malloc(sizeof(pthread_mutex_t) * self->philo_num);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < self->philo_num)
	{
		if (pthread_mutex_init(&forks[i], 0) != 0)
			return (NULL);
		i++;
	}
	return (forks);
}

static t_bool	init_mutex(t_data *data)
{
	data->forks_lock = init_forks(data);
	if (pthread_mutex_init(&data->controll_lock, NULL) != 0)
		return (error_msg("Error: Could not create mutex.", data, TRUE));
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
		return (error_msg("Error: Could not create mutex.", data, TRUE));
	return (FALSE);
}
