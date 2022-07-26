/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouyer <jbouyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 16:25:44 by jbouyer           #+#    #+#             */
/*   Updated: 2022/07/26 17:50:29 by jbouyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_fork_right(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->params->write);
	printf("%ld %i has taken a fork right\n",(get_time() - 
			philo->params->time_start), philo->ID);
	pthread_mutex_unlock(&philo->params->write);
}

void	print_fork_left(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->params->write);
	printf("%ld %i has taken a fork left\n",(get_time() - \
			philo->params->time_start), philo->ID);
	pthread_mutex_unlock(&philo->params->write);
}

void	print_eating(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->params->write);
	printf("\033[32;01m%ld %i Is eating\033[00m\n",(get_time() - philo->params->time_start), philo->ID); //il mange
	pthread_mutex_unlock(&philo->params->write);
}

char	*print_sleep(void)
{
	char *str;

	str = "is sleeping";
	return(str);
}

char	*print_think(void)
{
	char *str;

	str = "is thinking";
	return(str);
}

char	*print_died(void)
{
	char *str;

	str = "died";
	return(str);
}
