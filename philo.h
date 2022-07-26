/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouyer <jbouyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 11:48:53 by jbouyer           #+#    #+#             */
/*   Updated: 2022/07/26 17:50:48 by jbouyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
#include <sys/time.h>

typedef struct s_philosopher
{
	int				ID;
	int				right_fork;
	int				left_fork;
	int				nb_lunch;
	long int		last_lunch;
	struct s_global	*params;
}		t_philosopher;

typedef struct s_global
{
	t_philosopher	philo[250];
	pthread_t		pthrd_philos[250];
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				count_who_is_full;
	long int		time_start;
	int				is_dead;
	pthread_mutex_t	write;
	pthread_mutex_t check_dead;
	pthread_mutex_t	m_global;
	pthread_mutex_t	forks[250];
	pthread_mutex_t	m_philo[250];
}	t_global;

int			ft_atoi(const char *s);
t_global	*init_dinner(char **argv);
int			check_args_digit(char **argv);
void		init_mutex(t_philosopher philo, t_global *params);
void		*init_thread(void *params);
int			food_is_life(t_philosopher *philo);
int			is_dead(t_global *params);
int			is_dead_utils(t_philosopher *philo);
int			food_is_life_reverse(t_philosopher *philo);


/*****************************/
/*        MESSAGE            */
/*****************************/

void		print_fork_right(t_philosopher *philo);
void		print_fork_left(t_philosopher *philo);
void		print_eating(t_philosopher *philo);
char		*print_sleep(void);
char		*print_think(void);
char		*print_died(void);

/*****************************/
/*          TIME             */
/*****************************/

long int	convert_time(long int seconds, long int microseconds);
long int	get_time(void);

#endif