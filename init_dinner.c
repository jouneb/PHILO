/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dinner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouyer <jbouyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 16:08:02 by jbouyer           #+#    #+#             */
/*   Updated: 2022/07/07 17:53:22 by jbouyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

long int	convert_time(long int seconds, long int microseconds)
{
	long int	current_time;

	seconds = seconds * 1000;
	microseconds = microseconds / 1000;
	current_time = seconds + microseconds;
	return (current_time);
}

long int	get_time(void)
{
	struct		timeval	current_time;
	long int	converted_time;

	gettimeofday(&current_time, NULL);
	converted_time = convert_time(current_time.tv_sec, current_time.tv_usec);
	return (converted_time);
}

t_philosopher	init_philo(t_global *params, int i)
{
	t_philosopher	philo;

	philo.nb_lunch = 0;
	philo.ID = i;
	philo.right_fork = i;
	philo.params = params;
	if (i == params->nb_philos)
		philo.left_fork = 1;
	else
		philo.left_fork = i + 1;
	printf("quel philo ? %i\n", philo.ID);
	printf("right fork ? %i\n", philo.right_fork);
	printf("left fork ? %i\n", philo.left_fork);
	return (philo);
}

t_global	*init_dinner(char **argv)
{
	t_global	*params;
	int			i;

	i = 1;
	params = malloc(sizeof(*params));
	if (params == NULL)
		return (NULL);
	params->nb_philos = ft_atoi(argv[1]);
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->time_to_sleep = ft_atoi(argv[4]);
	printf("nb philo = %i\n", params->nb_philos);
	printf("time to die =%i\n", params->time_to_die);
	printf("time to eat = %i\n", params->time_to_eat);
	printf("time_to_sleep = %i\n", params->time_to_sleep);
	if (argv[5])
		params->must_eat = ft_atoi(argv[5]);
	else
		params->must_eat = -1;
	printf("nb must_eat = %i\n",params->must_eat);
	params->time_start = get_time();
	printf("time start = %ld\n", params->time_start);
	while(i <= params->nb_philos)
	{
		params->philo[i] = init_philo(params, i);
		init_mutex(params->philo[i], params);
		i++;
	}
	// i = 1;
	init_thread(params->philo);
	// while(i <= params->nb_philos)
	// {
	// 	// params->philo[i] = init_philo(params, i);
	// 	// init_mutex(params->philo[i], params);
	// 	init_thread(params->philo[i]);
	// 	i++;
	// }
	// while(i <= params->nb_philos)
	// {
	// 	pthread_join(philo, NULL);

	// }
	
	return (params);
}
