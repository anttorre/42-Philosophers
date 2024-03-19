/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:53:15 by anttorre          #+#    #+#             */
/*   Updated: 2024/03/19 16:28:19 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	philo_msg(char *s, t_data *d)
{
	size_t	time;

	pthread_mutex_lock(&d->write_lock);
	time = get_current_time() - d->philos[d->i].start_time;
	if (!dead_loop(d->philos[d->i]))
		printf("%zu %d %s\n", time, d->philos[d->i].id, s);
	pthread_mutex_unlock(&d->write_lock);
}

int	start_threads(t_data *d)
{
	d->i = -1;
	while (++d->i < d->num_of_philos)
		if (pthread_create(d->philos[d->i].thread, NULL, &philo_routine, d) != 0)
			return (printf("Error creating threads\n"), 0);
	d->i = -1;
	while (++d->i < d->num_of_philos)
		if (pthread_join(d->philos[d->i].thread, NULL) != 0)
			return (printf("Error joining threads\n"), 0);
}
