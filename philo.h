/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouyer <jbouyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 11:48:53 by jbouyer           #+#    #+#             */
/*   Updated: 2022/07/27 17:52:20 by jbouyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philosopher
{
	int				id;
	int				right_fork;
	int				left_fork;
	int				nb_lunch;
	long int		last_lunch;
	struct s_global	*params;
}		t_philosopher;

typedef struct s_global
{
	t_philosopher	philo[250];
	pthread_t		pth_philo[250];
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				count_who_is_full;
	long int		time_start;
	int				is_dead;
	pthread_mutex_t	write;
	pthread_mutex_t	check_dead;
	pthread_mutex_t	m_global;
	pthread_mutex_t	forks[250];
}	t_global;

t_global	*init_dinner(char **argv);
void		init_mutex_global(t_global *params);
void		*init_thread(void *params);
int			food_is_life(t_philosopher *philo);
int			is_dead(t_global *params);

/*****************************/
/*        MESSAGES            */
/*****************************/

void		print_fork_right(t_philosopher *philo);
void		print_fork_left(t_philosopher *philo);
void		print_eating(t_philosopher *philo);
void		enough_food(t_philosopher *philo);
void		print_died(t_philosopher *philo);

/*****************************/
/*          TIME             */
/*****************************/

long int	get_time(void);

/*****************************/
/*          UTILS            */
/*****************************/

int			ft_atoi(const char *s);
int			check_args_digit(char **argv);
int			is_dead_utils(t_philosopher *philo);

#endif