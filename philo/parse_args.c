/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:10:54 by anttorre          #+#    #+#             */
/*   Updated: 2024/03/18 16:10:14 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

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
