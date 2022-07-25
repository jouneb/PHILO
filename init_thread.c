/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouyer <jbouyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 16:25:34 by jbouyer           #+#    #+#             */
/*   Updated: 2022/07/25 15:20:45 by jbouyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static int is_philo_max_lunch(t_global *params)
// {
// 	int	i;

// 	i = 0;
// 	while (i <= params->nb_philos)
// 	{
// 		if (params->must_eat != -1)
// 		{
// 			if (params->philo[i].nb_lunch == params->must_eat)
// 			{
// 				pthread_mutex_lock(&params->m_global);
// 				params->count_who_is_full++;
// 				pthread_mutex_unlock(&params->m_global);
// 			}
// 			if (params->count_who_is_full == params->nb_philos)
// 				return (1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }
static void	*is_philo_dead_or_max_lunch(void *parameters)
{
	int			i;

	t_global	*params;
	params = parameters;
	while(1)
	{
		i = 1;
		while(i <= params->nb_philos)
		{
			if ((get_time()- params->philo[i].last_lunch) > params->time_to_die)
			{
				pthread_mutex_lock(&params->m_global);
				params->is_dead = 1;
				pthread_mutex_unlock(&params->m_global);
				pthread_mutex_lock(&params->write);
				printf("\033[35;01m%ld %i %s\033[00m\n",(get_time() - params->time_start), \
						params->philo[i].ID, print_died());
				pthread_mutex_unlock(&params->write);
				return (0);
			}
				else if (params ->must_eat != -1)
			{
				if (params->philo[i].nb_lunch == params->must_eat)
					{	
						pthread_mutex_lock(&params->m_global);
						params->philo[i].nb_lunch++;
						params->count_who_is_full++;
						pthread_mutex_unlock(&params->m_global);
						pthread_mutex_lock(&params->write);
						printf("\033[34;01m%ld %i enough food for me\033[00m\n",(get_time() - params->time_start), \
						params->philo[i].ID);
						pthread_mutex_unlock(&params->write);
						if (params->count_who_is_full == params->nb_philos)
							{
								pthread_mutex_lock(&params->m_global);
								params->is_dead = 2;
								pthread_mutex_unlock(&params->m_global);
								pthread_mutex_lock(&params->write);
								printf("\033[39;01mtout le monde a fini son diner\033[00m\n");
								pthread_mutex_unlock(&params->write);
								return(0);
							}
					}
			}
			i++;
		}
	}
}
static void *routine(void *philo_args)
{
	t_philosopher	*philo;

	philo = philo_args;
	if (philo->ID % 2 == 0)
		usleep(200);
	//  while (philo->params->is_dead == 0)
	while (1)
	{
		if (food_is_life(philo) == 0)
		{
			pthread_mutex_unlock(&philo->params->forks[philo->right_fork]);
			pthread_mutex_unlock(&philo->params->forks[philo->left_fork]);
			pthread_mutex_unlock(&philo->params->write);
			break;
		}
		if (philo->params->is_dead != 0)
			return (0);
		pthread_mutex_lock(&philo->params->write);
		printf("%ld %i %s\n",(get_time() - philo->params->time_start), philo->ID, print_sleep());
		pthread_mutex_unlock(&philo->params->write);
		if (philo->params->is_dead != 0)
			break;
		usleep((philo->params->time_to_sleep)*1000);
		if (philo->params->is_dead != 0)
			return (0);
		pthread_mutex_lock(&philo->params->write);
		printf("%ld %i %s\n",(get_time() - philo->params->time_start), philo->ID, print_think());
		pthread_mutex_unlock(&philo->params->write);
	}
	return(NULL);
}

void	*init_thread(void *parameters)
{
	pthread_t	death_status;
	int			i;
	t_global	*params;

	params = parameters;
	i = 1;
	// while (params->is_dead == 0)
	// {
		while(i <= params->nb_philos)
		{
			// pthread_mutex_lock(&params->m_philo[i]);
			pthread_create(&params->pthrd_philos[i], NULL, routine, &params->philo[i]);
			// pthread_mutex_unlock(&params->m_philo[i]);
			i++;
		}
		i = 1;
		if (pthread_create(&death_status, NULL, is_philo_dead_or_max_lunch, params) == 0)
		{
			pthread_join(death_status, NULL);
			return(0);
			// break;
		}
		pthread_join(death_status, NULL);
		while(i <= params->nb_philos)
		{
			// pthread_mutex_lock(&params->m_philo[i]);
			pthread_join(params->pthrd_philos[i], NULL);
			// pthread_mutex_unlock(&params->m_philo[i]);
			i++;
		}
	// }
	return (0);
}