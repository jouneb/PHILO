/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouyer <jbouyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 16:25:34 by jbouyer           #+#    #+#             */
/*   Updated: 2022/07/27 17:46:26 by jbouyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_global *params)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&params->m_global);
	i = params->is_dead;
	pthread_mutex_unlock(&params->m_global);
	return (i);
}

static int	check_is_food_ok(t_philosopher *philo)
{
	if (philo->params->must_eat == -1)
		return (1);
	else if (philo->nb_lunch == philo->params->must_eat)
	{	
		pthread_mutex_lock(&philo->params->m_global);
		philo->nb_lunch++;
		philo->params->count_who_is_full++;
		pthread_mutex_unlock(&philo->params->m_global);
		pthread_mutex_lock(&philo->params->write);
		printf ("\033[34;01m %ld %i enough food for me\033[00m \n", (get_time() - \
				philo->params->time_start), philo->id);
		pthread_mutex_unlock(&philo->params->write);
		if (philo->params->count_who_is_full == philo->params->nb_philos)
		{
			pthread_mutex_lock(&philo->params->m_global);
			philo->params->is_dead = 2;
			pthread_mutex_unlock(&philo->params->m_global);
			pthread_mutex_lock(&philo->params->write);
			printf("\033[39;01mtout le monde a fini son diner\033[00m\n");
			pthread_mutex_unlock(&philo->params->write);
			return (0);
		}
	}
	return (1);
}

static void	*is_philo_dead_or_max_lunch(void *parameters)
{
	int			i;
	long int	last_lunch;
	t_global	*params;

	params = parameters;
	while (1)
	{
		i = 0;
		while (++i <= params->nb_philos)
		{
			pthread_mutex_lock(&params->m_global);
			last_lunch = params->philo[i].last_lunch;
			pthread_mutex_unlock(&params->m_global);
			if ((get_time() - last_lunch) > params->time_to_die)
			{
				pthread_mutex_lock(&params->m_global);
				params->is_dead = 1;
				pthread_mutex_unlock(&params->m_global);
				print_died(&params->philo[i]);
				return (0);
			}
			if (check_is_food_ok(&params->philo[i]) == 0)
				return (0);
		}
	}
}

static void	*routine(void *philo_args)
{
	t_philosopher	*philo;

	philo = philo_args;
	while (1)
	{
		food_is_life(philo);
		if (is_dead(philo->params) != 0)
			return (0);
		pthread_mutex_lock(&philo->params->write);
		printf("%ld %i is sleeping\n", (get_time() - philo->params->time_start), \
				philo->id);
		pthread_mutex_unlock(&philo->params->write);
		if (is_dead(philo->params) != 0)
			break ;
		usleep((philo->params->time_to_sleep) * 1000);
		if (is_dead(philo->params) != 0)
			return (0);
		pthread_mutex_lock(&philo->params->write);
		printf("%ld %i is thinking\n", (get_time() - philo->params->time_start), \
				philo->id);
		pthread_mutex_unlock(&philo->params->write);
	}
	return (NULL);
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
	while (i <= nbr_philos)
	{
		pthread_create(&params->pth_philo[i], NULL, routine, &params->philo[i]);
		i++;
	}
	i = 1;
	pthread_create(&death_status, NULL, is_philo_dead_or_max_lunch, params);
	pthread_join(death_status, NULL);
	while (i <= nbr_philos)
	{
		pthread_join(params->pth_philo[i], NULL);
		i++;
	}
	return (0);
}
