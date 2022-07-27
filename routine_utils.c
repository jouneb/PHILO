/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouyer <jbouyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:10:14 by jbouyer           #+#    #+#             */
/*   Updated: 2022/07/27 18:01:55 by jbouyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead_utils(t_philosopher *philo)
{
	int	last_lunch;

	pthread_mutex_lock(&philo->params->m_global);
	last_lunch = philo->last_lunch;
	pthread_mutex_unlock(&philo->params->m_global);
	return (last_lunch);
}

static int	check_dead(t_philosopher *philo)
{
	if (is_dead(philo->params) != 0)
	{
		pthread_mutex_unlock(&philo->params->forks[philo->right_fork]);
		pthread_mutex_unlock(&philo->params->forks[philo->left_fork]);
		return (0);
	}
	return (1);
}

static int	take_a_fork(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->params->forks[philo->left_fork]);
	if (is_dead(philo->params) != 0)
	{
		pthread_mutex_unlock(&philo->params->forks[philo->left_fork]);
		return (0);
	}
	print_fork_left(philo);
	if (philo->params->nb_philos == 1)
	{
		pthread_mutex_unlock(&philo->params->forks[philo->left_fork]);
		usleep(philo->params->time_to_die);
		return (0);
	}
	pthread_mutex_lock(&philo->params->forks[philo->right_fork]);
	if (is_dead(philo->params) != 0)
	{
		pthread_mutex_unlock(&philo->params->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->params->forks[philo->right_fork]);
		return (0);
	}
	print_fork_right(philo);
	return (1);
}

static int	take_a_fork_right(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->params->forks[philo->right_fork]);
	if (is_dead(philo->params) != 0)
	{
		pthread_mutex_unlock(&philo->params->forks[philo->right_fork]);
		return (0);
	}
	print_fork_right(philo);
	if (philo->params->nb_philos == 1)
	{
		pthread_mutex_unlock(&philo->params->forks[philo->right_fork]);
		usleep(philo->params->time_to_die);
		return (0);
	}
	pthread_mutex_lock(&philo->params->forks[philo->left_fork]);
	if (is_dead(philo->params) != 0)
	{
		pthread_mutex_unlock(&philo->params->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->params->forks[philo->right_fork]);
		return (0);
	}
	print_fork_left(philo);
	return (1);
}

int	food_is_life(t_philosopher *philo)
{
	if (philo->id % 2 == 0)
	{
		if (take_a_fork(philo) == 0)
			return (0);
	}
	else
	{
		if (take_a_fork_right(philo) == 0)
			return (0);
	}
	pthread_mutex_lock(&philo->params->m_global);
	philo->last_lunch = get_time();
	pthread_mutex_unlock(&philo->params->m_global);
	if (check_dead(philo) == 0)
		return (0);
	print_eating(philo);
	usleep(philo->params->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->params->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->params->forks[philo->left_fork]);
	pthread_mutex_lock(&philo->params->m_global);
	philo->nb_lunch++;
	pthread_mutex_unlock(&philo->params->m_global);
	return (1);
}
