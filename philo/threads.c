/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:53:15 by anttorre          #+#    #+#             */
/*   Updated: 2024/03/21 13:04:24 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	dead_loop(t_philo *p)
{
	pthread_mutex_lock(&p->data->dead_lock);
	if (p->data->dead_flag == 1)
		return (pthread_mutex_unlock(&p->data->dead_lock), 1);
	pthread_mutex_unlock(&p->data->dead_lock);
	return (0);
}

void	philo_msg(char *s, t_philo *p)
{
	size_t	time;

	pthread_mutex_lock(&p->data->write_lock);
	time = get_current_time() - p->start_time;
	if (!dead_loop(p))
		printf("%zu %d %s\n", time, p->id, s);
	pthread_mutex_unlock(&p->data->write_lock);
}

void	*philo_routine(void *philo)
{
	t_philo	*p;

	p = philo;
	if (p->id % 2 == 0)
		ft_usleep(1);
	while (!dead_loop(p))
	{
		eating(p);
		dreaming(p);
		thinking(p);
	}
	return (philo);
}

int	start_threads(t_philo *p)
{
	pthread_t	monitor;

	if (pthread_create(&monitor, NULL, &monitoring, p) != 0)
		return (printf("Error creating thread monitor\n"), destroy_mutex(p), 0);
	p->data->i = -1;
	while (++p->data->i < p->data->num_of_philos)
		if (pthread_create(&p[p->data->i].thread, NULL,
				&philo_routine, &p[p->data->i]) != 0)
			return (printf("Error creating threads\n"), destroy_mutex(p), 0);
	p->data->i = -1;
	while (++p->data->i < p->data->num_of_philos)
		if (pthread_join(p[p->data->i].thread, NULL) != 0)
			return (printf("Error joining threads\n"), destroy_mutex(p), 0);
	p->data->i = 0;
	if (pthread_join(monitor, NULL) != 0)
		return (printf("Error joining thread monitor\n"), destroy_mutex(p), 0);
	return (1);
}
