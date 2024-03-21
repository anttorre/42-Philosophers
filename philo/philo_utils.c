/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 12:04:40 by anttorre          #+#    #+#             */
/*   Updated: 2024/03/21 12:52:53 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

long long int	ft_atol(const char *str)
{
	long long int	num;
	unsigned int	i;
	long long int	sign;

	num = 0;
	i = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num * sign);
}

int	check_args(char **arg)
{
	int	i;
	int	j;

	i = 0;
	while (arg[++i])
	{
		j = -1;
		while (arg[i][++j])
			if (arg[i][j] < '0' || arg[i][j] > '9')
				return (0);
	}
	i = 0;
	while (arg[++i])
	{
		if (i == 5)
		{
			if (ft_atol(arg[i]) < 0)
				return (0);
		}
		else
			if (ft_atol(arg[i]) <= 0 || (i == 1 && ft_atol(arg[i]) > PHIL_MAX))
				return (0);
	}
	return (1);
}

void	destroy_mutex(t_philo *p)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&p->data->write_lock);
	pthread_mutex_destroy(&p->data->meal_lock);
	pthread_mutex_destroy(&p->data->dead_lock);
	while (++i < p->data->num_of_philos)
		pthread_mutex_destroy(&p->data->forks[i]);
}
