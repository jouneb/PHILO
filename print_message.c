/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouyer <jbouyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 16:25:44 by jbouyer           #+#    #+#             */
/*   Updated: 2022/07/27 17:22:09 by jbouyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_fork_right(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->params->write);
	printf("%ld %i has taken a fork right\n", (get_time() - \
			philo->params->time_start), philo->id);
	pthread_mutex_unlock(&philo->params->write);
}

void	print_fork_left(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->params->write);
	printf("%ld %i has taken a fork left\n", (get_time() - \
			philo->params->time_start), philo->id);
	pthread_mutex_unlock(&philo->params->write);
}

void	print_eating(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->params->write);
	printf("\033[32;01m%ld %i Is eating\033[00m\n", (get_time() - \
			philo->params->time_start), philo->id);
	pthread_mutex_unlock(&philo->params->write);
}

void	print_died(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->params->write);
	printf("\033[35;01m%ld %i died\033[00m\n", (get_time() - \
			philo->params->time_start), philo->id);
	pthread_mutex_unlock(&philo->params->write);
}
