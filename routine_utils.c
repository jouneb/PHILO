/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouyer <jbouyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:10:14 by jbouyer           #+#    #+#             */
/*   Updated: 2022/07/25 15:29:49 by jbouyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	food_is_life(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->params->forks[philo->right_fork]);
	if (philo->params->is_dead != 0)
			return (0);
	pthread_mutex_lock(&philo->params->write);
	printf("%ld %i has taken a fork right\n",(get_time() - \
			philo->params->time_start), philo->ID);
	pthread_mutex_unlock(&philo->params->write);
	pthread_mutex_lock(&philo->params->forks[philo->left_fork]);
	if (philo->params->is_dead != 0)
		return (0);
	pthread_mutex_lock(&philo->params->write);
	printf("%ld %i has taken a fork left\n",(get_time() - \
			philo->params->time_start), philo->ID);
	pthread_mutex_unlock(&philo->params->write);
	philo->last_lunch = get_time();
	if (philo->params->is_dead != 0)
			return (0);
	pthread_mutex_lock(&philo->params->write);
	printf("\033[32;01m%ld %i Is eating\033[00m\n",(get_time() - philo->params->time_start), philo->ID);
	pthread_mutex_unlock(&philo->params->write);
	usleep((philo->params->time_to_eat)*1000);
	pthread_mutex_unlock(&philo->params->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->params->forks[philo->left_fork]);
	if (philo->params->is_dead != 0)
			return (0);
	pthread_mutex_lock(&philo->params->m_global);
	philo->nb_lunch++;
	pthread_mutex_unlock(&philo->params->m_global);
	return (1);
}