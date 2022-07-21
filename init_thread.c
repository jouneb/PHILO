/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouyer <jbouyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 16:25:34 by jbouyer           #+#    #+#             */
/*   Updated: 2022/07/21 18:00:48 by jbouyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


static void	*is_philo_dead_or_max_lunch(void *parameters)
{
	int			i;

	t_global	*params;
	params = parameters;
	while(1)
	{
		i = 1;
		while(i <= params->nb_philos)
		{
			if ((get_time()- params->philo[i].last_lunch) > params->time_to_die)
			{
				params->is_dead = 1;
				printf("la diff c'est :%li\n", get_time()- params->philo[i].last_lunch);
				printf("\033[35;01m%ld %i %s\033[00m\n",(get_time() - params->time_start), \
						params->philo[i].ID, print_died());
				return (0);
			}
				else if (params ->must_eat != -1)
			{
				if (params->philo[i].nb_lunch == params->must_eat)
					{	
						params->is_dead = 2;
						params->count_who_is_full++;
						printf("\033[34;01m%ld %i enough food for me\033[00m\n",(get_time() - params->time_start), \
						params->philo[i].ID);
						return (0);
					}
				if (params->count_who_is_full == params->nb_philos)
					{
						printf("\033[39;01mtout le monde a fini son diner\033[00m\n");
						return(0);
					}
			}
		}
	}
}
static void *routine(void *philo_args)
{
	t_philosopher	*philo;

	philo = philo_args;
	if (philo->ID % 2 == 0)
		usleep(100);
	while (philo->params->is_dead == 0)
	{
		if (food_is_life(philo) == 0)
		{
		// pthread_mutex_lock(&philo->params->forks[philo->right_fork]);
		// if (philo->params->is_dead != 0)
		// 	break;
		// printf("%ld %i  %sright\n",(get_time() - philo->params->time_start), philo->ID, print_fork());
		// pthread_mutex_lock(&philo->params->forks[philo->left_fork]);
		// printf("%ld %i  %sleft\n",(get_time() - philo->params->time_start), philo->ID, print_fork());
		// philo->last_lunch = get_time();
		// 	if (philo->params->is_dead != 0)
		// 	break;
		// printf("%ld %i %s\n",(get_time() - philo->params->time_start), philo->ID, print_eating());
		// usleep((philo->params->time_to_eat)*1000);
		// printf("last lunch time == %ld\n", philo->last_lunch);
			// if (philo->params->is_dead != 0)
			// break;
		// philo->nb_lunch++;
			pthread_mutex_unlock(&philo->params->forks[philo->right_fork]);
			pthread_mutex_unlock(&philo->params->forks[philo->left_fork]);
			break;
		}
		printf("%ld %i %s\n",(get_time() - philo->params->time_start), philo->ID, print_sleep());
			if (philo->params->is_dead != 0)
			break;
		usleep((philo->params->time_to_sleep)*1000);
		printf("%ld %i %s\n",(get_time() - philo->params->time_start), philo->ID, print_think());
	}
	return(NULL);
}

void	*init_thread(void *parameters)
{
	pthread_t	philos[250];
	pthread_t	death_status;
	int			i;
	t_global	*params;

	params = parameters;
	i = 1;
	// pthread_create(&death_status, NULL, is_philo_dead_or_max_lunch, params);
	// pthread_join(death_status, NULL);
	while (params->is_dead == 0)
	{
		while(i <= params->nb_philos)
		{
			pthread_create(&philos[i], NULL, routine, &params->philo[i]);
			i++;
		}
		i = 1;
	// if (params->is_dead == 2)
	// 	{
	// 		printf("a assez mange");
	// 		return (2);
	// 	}
	// 	if (params->is_dead == 1)
	// 	{
	// 		printf("un philo est mort");
	// 		return (1);
	// 	}
		if (pthread_create(&death_status, NULL, is_philo_dead_or_max_lunch, params) == 0)
		{
			pthread_join(death_status, NULL);
			break;
		}
		pthread_join(death_status, NULL);
		while(i <= params->nb_philos)
		{
			pthread_join(philos[i], NULL);
			// if (params->is_dead == 2)
			// {
			// 	printf("a assez mange");
			// 	return (2);
			// }
			// if (params->is_dead == 1)
			// {
			// 	printf("un philo est mort");
			// 	return (1);
			// }
			i++;
		}
		// if (params->is_dead == 2)
		// 	{
		// 		printf("a assez mange");
		// 		break;
		// 	}
		// if (params->is_dead == 1)
		// {
		// 	printf("un philo est mort");
		// 	break;
		// }
	}
	return (0);
}