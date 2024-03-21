/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:39:18 by anttorre          #+#    #+#             */
/*   Updated: 2024/03/21 14:26:30 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	philosopher_dead(t_philo *philo, size_t time_to_die, t_philo *p)
{
	pthread_mutex_lock(&p->data->meal_lock);
	if (get_current_time() - philo->last_meal >= time_to_die
		&& philo->eating == 0)
		return (pthread_mutex_unlock(&p->data->meal_lock), 1);
	pthread_mutex_unlock(&p->data->meal_lock);
	return (0);
}

int	check_if_dead(t_philo *p)
{
	int	i;

	i = 0;
	while (i < p->data->num_of_philos)
	{
		if (philosopher_dead(&p[i], p[i].time_to_die, p))
		{
			philo_msg("has died", p);
			pthread_mutex_lock(&p->data->dead_lock);
			p->data->dead_flag = 1;
			pthread_mutex_unlock(&p->data->dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_if_all_ate(t_philo *p)
{
	int	i;
	int	philo_finish_eat;

	i = 0;
	philo_finish_eat = 0;
	if (p->data->num_times_to_eat == -1)
		return (0);
	while (i < p->data->num_of_philos)
	{
		pthread_mutex_lock(&p->data->meal_lock);
		if (p[i].meals_eaten >= p->data->num_times_to_eat)
			philo_finish_eat++;
		pthread_mutex_unlock(&p->data->meal_lock);
		i++;
	}
	if (philo_finish_eat == p->data->num_of_philos)
	{
		pthread_mutex_lock(&p->data->dead_lock);
		p->data->dead_flag = 1;
		pthread_mutex_unlock(&p->data->dead_lock);
		return (1);
	}
	return (0);
}

void	*monitoring(void *philo)
{
	t_philo	*p;

	p = philo;
	while (1)
		if (check_if_dead(p) || check_if_all_ate(p))
			break ;
	return (philo);
}
