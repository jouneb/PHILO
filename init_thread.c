/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouyer <jbouyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 16:25:34 by jbouyer           #+#    #+#             */
/*   Updated: 2022/07/26 16:44:01 by jbouyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_global *params)
{
	int i;

	i = 0;
	pthread_mutex_lock(&params->m_global);
	i = params->is_dead;
	pthread_mutex_unlock(&params->m_global);
	return (i);
}
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
	long int	last_lunch;
	int			time_to_die;

	t_global	*params;
	params = parameters;
	pthread_mutex_lock(&params->m_global);
	time_to_die = params->time_to_die;
	pthread_mutex_unlock(&params->m_global);
	while(1)
	{
		i = 1;
		while(i <= params->nb_philos)
		{
			pthread_mutex_lock(&params->m_global);
			last_lunch = params->philo[i].last_lunch;
			pthread_mutex_unlock(&params->m_global);
			if ((get_time()- last_lunch) > time_to_die)
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
	int				ID;

	philo = philo_args;
	pthread_mutex_lock(&philo->params->m_global);
	ID = philo->ID;
	pthread_mutex_unlock(&philo->params->m_global);
	if (ID % 2 == 0)
		usleep(350);
	while (1)
	{
		if (ID % 2 == 0)
		{
			// usleep(350);
			if (food_is_life_reverse(philo)== 0)
				return (0);
		}
		else if (ID % 2 != 0)
		{
			if (food_is_life(philo)== 0)
			// pthread_mutex_unlock(&philo->params->forks[philo->right_fork]);
			// pthread_mutex_unlock(&philo->params->forks[philo->left_fork]);
			return (0);
			// pthread_mutex_unlock(&philo->params->forks[philo->left_fork]);
			// pthread_mutex_unlock(&philo->params->write);
			// break;
		}
		if (is_dead(philo->params) != 0)
			return (0);
		pthread_mutex_lock(&philo->params->write);
		printf("%ld %i %s\n",(get_time() - philo->params->time_start), philo->ID, print_sleep());
		pthread_mutex_unlock(&philo->params->write);
		if (is_dead(philo->params) != 0)
			// return(0);
			break;
		usleep((philo->params->time_to_sleep)*1000);
		if (is_dead(philo->params) != 0)
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
	int			nbr_philos;
	t_global	*params;

	params = parameters;
	i = 1;
	pthread_mutex_lock(&params->m_global);
	nbr_philos = params->nb_philos;
	pthread_mutex_unlock(&params->m_global);
		while(i <= nbr_philos)
		{
			// pthread_mutex_lock(&params->m_philo[i]);
			pthread_create(&params->pthrd_philos[i], NULL, routine, &params->philo[i]);
			// pthread_mutex_unlock(&params->m_philo[i]);
			i++;
		}
		i = 1;
		pthread_create(&death_status, NULL, is_philo_dead_or_max_lunch, params);
		pthread_join(death_status, NULL);
		while(i <= nbr_philos)
		{
			// pthread_mutex_lock(&params->m_philo[i]);
			pthread_join(params->pthrd_philos[i], NULL);
			// pthread_mutex_unlock(&params->m_philo[i]);
			i++;
		}
	// }
	return (0);
}