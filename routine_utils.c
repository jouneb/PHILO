/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouyer <jbouyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:10:14 by jbouyer           #+#    #+#             */
/*   Updated: 2022/07/26 16:44:57 by jbouyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	food_is_life(t_philosopher *philo)
{
	int	time_to_eat;

	pthread_mutex_lock(&philo->params->forks[philo->right_fork]); //bloque la fourchette
	if (is_dead(philo->params) != 0)
	{
		pthread_mutex_unlock(&philo->params->forks[philo->right_fork]);
		return (0);
	}
	pthread_mutex_lock(&philo->params->write);
	printf("%ld %i has taken a fork right\n",(get_time() - 
			philo->params->time_start), philo->ID);
	pthread_mutex_unlock(&philo->params->write);
	if (philo->params->nb_philos == 1) //faire exception pour le cas ou il n'y a qu'un philo. peut aller que dans les impairs.
	{
		pthread_mutex_unlock(&philo->params->forks[philo->right_fork]);
		usleep(philo->params->time_to_die);
		return(0);
	}
	pthread_mutex_lock(&philo->params->forks[philo->left_fork]); //bloque fourchette gauche
	if (is_dead(philo->params) != 0)
	{
		pthread_mutex_unlock(&philo->params->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->params->forks[philo->right_fork]);
		return (0);
	}
	pthread_mutex_lock(&philo->params->write);
	printf("%ld %i has taken a fork left\n",(get_time() - \
			philo->params->time_start), philo->ID);
	pthread_mutex_unlock(&philo->params->write);
	pthread_mutex_lock(&philo->params->m_global);
	philo->last_lunch = get_time();								//change heure du dernier lunch
	pthread_mutex_unlock(&philo->params->m_global);
	if (is_dead(philo->params) != 0)
	{
		pthread_mutex_unlock(&philo->params->forks[philo->right_fork]);
		pthread_mutex_unlock(&philo->params->forks[philo->left_fork]);
		return (0);
	}
	pthread_mutex_lock(&philo->params->write);
	printf("\033[32;01m%ld %i Is eating\033[00m\n",(get_time() - philo->params->time_start), philo->ID); //il mange
	pthread_mutex_unlock(&philo->params->write);
	//fonction pour le tempsde bouffer//
	pthread_mutex_lock(&philo->params->m_global);
	time_to_eat = philo->params->time_to_eat;
	pthread_mutex_unlock(&philo->params->m_global);
	usleep(time_to_eat*1000);
	// if (usleep(time_to_eat*1000) != 0)
	// {
	// 	pthread_mutex_unlock(&philo->params->forks[philo->right_fork]);
	// 	pthread_mutex_unlock(&philo->params->forks[philo->left_fork]);
	// 	return(0);
	// }
	// if (is_dead(philo->params) != 0)
	// {
	// 	pthread_mutex_unlock(&philo->params->forks[philo->right_fork]);
	// 	pthread_mutex_unlock(&philo->params->forks[philo->left_fork]);
	// 	return (0);
	// }
	pthread_mutex_unlock(&philo->params->forks[philo->right_fork]); //commun aux deux trucs.
	pthread_mutex_unlock(&philo->params->forks[philo->left_fork]);
	pthread_mutex_lock(&philo->params->m_global);
	philo->nb_lunch++;
	pthread_mutex_unlock(&philo->params->m_global);
	return (1);
}

int	food_is_life_reverse(t_philosopher *philo)
{
	int	time_to_eat;

	pthread_mutex_lock(&philo->params->forks[philo->left_fork]);
	if (is_dead(philo->params) != 0)
	{
		pthread_mutex_unlock(&philo->params->forks[philo->left_fork]);
		return (0);
	}
	// pthread_mutex_lock(&philo->params->forks[philo->right_fork]);
	pthread_mutex_lock(&philo->params->write);
	printf("%ld %i has taken a fork left\n",(get_time() - \
			philo->params->time_start), philo->ID);
	pthread_mutex_unlock(&philo->params->write);
	// if (is_dead(philo->params) != 0)
	// {		pthread_mutex_unlock(&philo->params->forks[philo->right_fork]);
	// 	return (0);
	// }
	if (philo->params->nb_philos == 1) //faire exception pour le cas ou il n'y a qu'un philo.
	{
		pthread_mutex_unlock(&philo->params->forks[philo->left_fork]);
		usleep(philo->params->time_to_die);
		return(0);
	}
	pthread_mutex_lock(&philo->params->forks[philo->right_fork]);
	if (is_dead(philo->params) != 0)
	{
		pthread_mutex_unlock(&philo->params->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->params->forks[philo->right_fork]);
		return (0);
	}
	pthread_mutex_lock(&philo->params->write);
	printf("%ld %i has taken a fork right\n",(get_time() - \
			philo->params->time_start), philo->ID);
	pthread_mutex_unlock(&philo->params->write);
	pthread_mutex_lock(&philo->params->m_global);
	philo->last_lunch = get_time();
	pthread_mutex_unlock(&philo->params->m_global);
	if (is_dead(philo->params) != 0)
	{
		pthread_mutex_unlock(&philo->params->forks[philo->right_fork]);
		pthread_mutex_unlock(&philo->params->forks[philo->left_fork]);
		return (0);
	}
	pthread_mutex_lock(&philo->params->write);
	printf("\033[32;01m%ld %i Is eating\033[00m\n",(get_time() - philo->params->time_start), philo->ID);
	pthread_mutex_unlock(&philo->params->write);
	//fonction pour le tempsde bouffer//
	pthread_mutex_lock(&philo->params->m_global);
	time_to_eat = philo->params->time_to_eat;
	pthread_mutex_unlock(&philo->params->m_global);
	usleep(time_to_eat*1000);
	// if (usleep(time_to_eat*1000) != 0)
	// {
	// 	pthread_mutex_unlock(&philo->params->forks[philo->right_fork]);
	// 	pthread_mutex_unlock(&philo->params->forks[philo->left_fork]);
	// 	return(0);
	// }
	// if (is_dead(philo->params) != 0)
	// {
	// 	pthread_mutex_unlock(&philo->params->forks[philo->right_fork]);
	// 	pthread_mutex_unlock(&philo->params->forks[philo->left_fork]);
	// 	return (0);
	// }
	pthread_mutex_unlock(&philo->params->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->params->forks[philo->left_fork]);
	pthread_mutex_lock(&philo->params->m_global);
	philo->nb_lunch++;
	pthread_mutex_unlock(&philo->params->m_global);
	return (1);
}