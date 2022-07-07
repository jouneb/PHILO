/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouyer <jbouyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:23:06 by jbouyer           #+#    #+#             */
/*   Updated: 2022/07/07 17:21:35 by jbouyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutex(t_philosopher philo, t_global *params)
{
	pthread_mutex_init(&params->forks[philo.right_fork], NULL);
	pthread_mutex_init(&params->forks[philo.left_fork], NULL);
	// pthread_create(&params->forks[philo.right_fork], NULL, eat, &params);
	// pthread_create(&params->forks[philo.left_fork], NULL, eat, &params);
	// pthread_join(&params->forks[philo.right_fork], NULL);
	// pthread_join(&params->forks[philo.left_fork], NULL);
}