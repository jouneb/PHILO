/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouyer <jbouyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 16:25:34 by jbouyer           #+#    #+#             */
/*   Updated: 2022/07/08 12:41:28 by jbouyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


static int	is_philo_dead_or_max_lunch(t_philosopher *philo)
{
	if ((get_time()-philo->last_lunch) > philo->params->time_to_die)
		{
			printf("%ld %i %s\n",(get_time() - philo->params->time_start), \
					philo->ID, print_died());
			// free_struct;
			return(0);
		}
	if (philo->params->must_eat == -1)
		return(1);
	else 
	{
		if (philo->nb_lunch == philo->params->must_eat)
			{
				// free_struct;
				return(0);
			}
	}
	return (1);
}
static void *routine(void *philo_args)
{
	t_philosopher	*philo;

	philo = philo_args;
	if (philo->ID % 2 == 0)
		usleep(100);
	while (is_philo_dead_or_max_lunch(philo) != 0)
	{
		pthread_mutex_lock(&philo->params->forks[philo->right_fork]);
		printf("%ld %i  %sright\n",(get_time() - philo->params->time_start), philo->ID, print_fork());
		pthread_mutex_lock(&philo->params->forks[philo->left_fork]);
		printf("%ld %i  %sleft\n",(get_time() - philo->params->time_start), philo->ID, print_fork());
		philo->last_lunch = (get_time() - philo->params->time_start);
		printf("%ld %i %s\n",(get_time() - philo->params->time_start), philo->ID, print_eating());
		usleep((philo->params->time_to_eat)*1000);
		printf("last lunch time == %ld\n", philo->last_lunch);
		philo->nb_lunch++;
		pthread_mutex_unlock(&philo->params->forks[philo->right_fork]);
		pthread_mutex_unlock(&philo->params->forks[philo->left_fork]);
		printf("%ld %i %s\n",(get_time() - philo->params->time_start), philo->ID, print_sleep());
		usleep((philo->params->time_to_sleep)*1000);
		printf("%ld %i %s\n",(get_time() - philo->params->time_start), philo->ID, print_think());
	}
	return(NULL);
}

void	init_thread(t_global *params)
{
	pthread_t	philos;
	int			i;

	i = 1;
	while(i <= params->nb_philos)
	{
		pthread_create(&philos, NULL, routine, &params->philo[i]);
		i++;
	}
	i = 1;
	while(i <= params->nb_philos)
	{
		pthread_join(philos, NULL);
		i++;
	}
}