/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouyer <jbouyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:10:14 by jbouyer           #+#    #+#             */
/*   Updated: 2022/07/21 17:52:22 by jbouyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	food_is_life(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->params->forks[philo->right_fork]);
	if (philo->params->is_dead != 0)
			return (0);
	printf("%ld %i has taken a fork right\n",(get_time() - \
			philo->params->time_start), philo->ID);
	pthread_mutex_lock(&philo->params->forks[philo->left_fork]);
	if (philo->params->is_dead != 0)
		return (0);
	printf("%ld %i has taken a fork left\n",(get_time() - \
			philo->params->time_start), philo->ID);
	philo->last_lunch = get_time();
	if (philo->params->is_dead != 0)
			return (0);
	printf("%ld %i Is eating\n",(get_time() - philo->params->time_start), philo->ID);
	usleep((philo->params->time_to_eat)*1000);
	if (philo->params->is_dead != 0)
			return (0);
	philo->nb_lunch++;
	pthread_mutex_unlock(&philo->params->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->params->forks[philo->left_fork]);
	return (1);
}