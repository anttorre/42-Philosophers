/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:16:33 by anttorre          #+#    #+#             */
/*   Updated: 2024/03/19 16:32:11 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	think(t_data *d)
{
	philo_msg("is thinking", d);
}

void	dream(t_data *d)
{
	philo_msg("is sleeping", d);
	ft_usleep(d->philos[d->i].time_to_sleep);
}
