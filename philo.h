/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouyer <jbouyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 11:48:53 by jbouyer           #+#    #+#             */
/*   Updated: 2022/07/07 17:52:34 by jbouyer          ###   ########.fr       */
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
	struct s_global	*params;
}		t_philosopher;

typedef struct s_global
{
	t_philosopher	philo[250];
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	long int		time_start;
	// pthread_mutex_t	global;
	pthread_mutex_t	forks[250];
}	t_global;

int			ft_atoi(const char *s);
t_global	*init_dinner(char **argv);
int			check_args_digit(char **argv);
void		init_mutex(t_philosopher philo, t_global *params);
void		init_thread(t_philosopher *philo);

/*****************************/
/*        MESSAGE            */
/*****************************/

char		*print_fork(void);
char		*print_eating(void);
void		print_sleep(void);
void		print_think(void);
void		print_died(void);

/*****************************/
/*          TIME             */
/*****************************/

long int	convert_time(long int seconds, long int microseconds);
long int	get_time(void);

#endif
