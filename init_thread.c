/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouyer <jbouyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 16:25:34 by jbouyer           #+#    #+#             */
/*   Updated: 2022/07/08 13:33:27 by jbouyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


static int	is_philo_dead_or_max_lunch(t_global *params)
{
	int			i;

	i = 1;
	while(i <= params->nb_philos)
	{
		if ((get_time()- params->philo[i].last_lunch) > params->time_to_die)
		{
			params->is_dead = 1;
			printf("%ld %i %s\n",(get_time() - params->time_start), \
					params->philo[i].ID, print_died());
			// free_struct;
			return(0);
		}
		if (params->must_eat == -1)
			return(1);
		else 
		{
			if (params->philo[i].nb_lunch == params->must_eat)
				{
					params->is_dead = 1;
					// free_struct;
					break;
				}
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
	while (1)
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
	is_philo_dead_or_max_lunch(params);
	// if (params->is_dead == 1)
	// 		return(0);
	i = 1;
	while(i <= params->nb_philos)
	{
		// if (params->is_dead == 1)
		// 	break;
		pthread_join(philos, NULL);
		i++;
	}
}