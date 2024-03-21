/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 16:11:51 by anttorre          #+#    #+#             */
/*   Updated: 2024/03/21 13:19:49 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <time.h>
# include <sys/time.h>
# define PHIL_MAX 200

typedef struct s_data
{
	int				i;
	int				dead_flag;
	int				num_of_philos;
	int				num_times_to_eat;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	forks[PHIL_MAX];
}					t_data;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	t_data			*data;
}					t_philo;

/*---- PHILO_UTILS.C ----*/
long long int	ft_atol(const char *str);
int				ft_usleep(size_t milliseconds);
size_t			get_current_time(void);
int				check_args(char **argv);
void			destroy_mutex(t_philo *p);

/*---- THREADS.C ----*/
void			philo_msg(char *s, t_philo *p);
int				start_threads(t_philo *p);

void			eating(t_philo *p);
void			dreaming(t_philo *p);
void			thinking(t_philo *p);
void			*monitoring(void *philo);

#endif