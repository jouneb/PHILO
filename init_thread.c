/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouyer <jbouyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 16:25:34 by jbouyer           #+#    #+#             */
/*   Updated: 2022/07/07 17:56:05 by jbouyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void *routine(void *philo_args)
{
	t_philosopher	*philo;

	philo = philo_args;
	if (philo->ID % 2 == 0)
		usleep(100);
	pthread_mutex_lock(&philo->params->forks[philo->right_fork]);
	printf("%i %s\n",philo->ID, print_fork());
	pthread_mutex_lock(&philo->params->forks[philo->left_fork]);
	printf("%i %s\n",philo->ID, print_fork());
	usleep(philo->params->time_to_eat);
	printf("%i %s\n",philo->ID, print_eating());
	philo->nb_lunch++;
	pthread_mutex_unlock(&philo->params->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->params->forks[philo->left_fork]);
	return(NULL);

}

void	init_thread(t_philosopher *philo)
{
	pthread_t	philos;
	int			i;

	i = 1;
	while(i <= philo->params->nb_philos)
	{
		pthread_create(&philos, NULL, routine, philo->params->philo);
		i++;
	}
	i = 1;
	while(i <= philo->params->nb_philos)
	{
		pthread_join(philos, NULL);
		i++;
	}
	// pthread_join(philo, NULL);
}