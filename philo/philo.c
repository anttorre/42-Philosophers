/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:16:00 by anttorre          #+#    #+#             */
/*   Updated: 2024/03/19 15:49:05 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

static	void	init_forks_philos(t_data *data, char **argv)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philos)
		pthread_mutex_init(&data->forks[i], NULL);
	i = -1;
	while (++i < data->num_of_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].eating = 0;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = get_current_time();
		data->philos[i].time_to_die = ft_atol(argv[2]);
		data->philos[i].time_to_eat = ft_atol(argv[3]);
		data->philos[i].time_to_sleep = ft_atol(argv[4]);
		data->philos[i].start_time = get_current_time();
		data->philos[i].l_fork = &data->forks[i];
		if (i == 0)
			data->philos[i].r_fork = &data->forks[data->num_of_philos - 1];
		else
			data->philos[i].r_fork = &data->forks[i - 1];
	}
}

static void	init_program(t_data *data, char **argv, int argc)
{
	int	i;

	data->dead_flag = 0;
	data->num_of_philos = ft_atol(argv[1]);
	data->num_times_to_eat = -1;
	if (argc == 6)
		data->num_times_to_eat = ft_atol(argv[5]);
	pthread_mutex_init(&data->write_lock, NULL);
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
	init_forks_philos(data, argv);
}

int	main(int argc, char **argv)
{
	t_data				data;

	if (!check_args(argv) || argc < 5 || argc > 6)
		return (printf("Invalid Arguments\n"), 1);
	init_program(&data, argv, argc);
	threads(data);
}
