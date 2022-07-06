/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouyer <jbouyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 11:48:53 by jbouyer           #+#    #+#             */
/*   Updated: 2022/07/06 17:24:33 by jbouyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>

typedef struct s_philosopher
{
	int	right_fork;
	int	left_fork;
	int	nb_lunch;
}		t_philosopher;

typedef struct s_global
{
	t_philosopher	philosophers[200];
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				time_start;
	pthread_mutex_t	forks[200];
}	t_global;

int			ft_atoi(const char *s);
t_global	*init_dinner(char **argv);
int			check_args_digit(char **argv);

/*****************************/
/*        MESSAGE            */
/*****************************/

void		print_fork(void);
void		print_eating(void);
void		print_sleep(void);
void		print_think(void);
void		print_died(void);

#endif
