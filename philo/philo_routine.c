/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:16:33 by anttorre          #+#    #+#             */
/*   Updated: 2024/03/25 16:57:11 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	thinking(t_philo *p)
{
	philo_msg("is thinking", p);
}

void	dreaming(t_philo *p)
{
	philo_msg("is sleeping", p);
	ft_usleep(p->time_to_sleep);
}

void	eating(t_philo *p)
{
	pthread_mutex_lock(p->r_fork);
	philo_msg("has taken a fork", p);
	if (p->data->num_of_philos == 1)
	{
		ft_usleep(p->time_to_die);
		pthread_mutex_unlock(p->r_fork);
		return ;
	}
	pthread_mutex_lock(p->l_fork);
	philo_msg("has taken a fork", p);
	philo_msg("is eating", p);
	pthread_mutex_lock(&p->data->meal_lock);
	p->last_meal = get_current_time();
	p->meals_eaten++;
	pthread_mutex_unlock(&p->data->meal_lock);
	ft_usleep(p->time_to_eat);
	pthread_mutex_unlock(p->r_fork);
	pthread_mutex_unlock(p->l_fork);
}
