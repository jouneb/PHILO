/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dinner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouyer <jbouyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 16:08:02 by jbouyer           #+#    #+#             */
/*   Updated: 2022/07/27 17:50:28 by jbouyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

static long int	convert_time(long int seconds, long int microseconds)
{
	long int	current_time;

	seconds = seconds * 1000;
	microseconds = microseconds / 1000;
	current_time = seconds + microseconds;
	return (current_time);
}

long int	get_time(void)
{
	long int		converted_time;
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	converted_time = convert_time(current_time.tv_sec, current_time.tv_usec);
	return (converted_time);
}

static t_philosopher	init_philo(t_global *params, int i)
{
	t_philosopher	philo;

	philo.nb_lunch = 0;
	philo.id = i;
	philo.right_fork = i;
	philo.params = params;
	philo.last_lunch = params->time_start;
	if (i == params->nb_philos)
		philo.left_fork = 1;
	else
		philo.left_fork = i + 1;
	return (philo);
}

static void	fill_params(t_global *params, char **argv)
{
	params->nb_philos = ft_atoi(argv[1]);
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->time_to_sleep = ft_atoi(argv[4]);
	params->is_dead = 0;
}

t_global	*init_dinner(char **argv)
{
	t_global	*params;
	int			i;

	i = 1;
	params = malloc(sizeof(*params));
	if (!params || params == NULL)
		return (0);
	fill_params(params, argv);
	if (argv[5])
		params->must_eat = ft_atoi(argv[5]);
	else
		params->must_eat = -1;
	params->time_start = get_time();
	while (i <= params->nb_philos)
	{
		params->philo[i] = init_philo(params, i);
		pthread_mutex_init(&params->forks[params->philo[i].id], NULL);
		i++;
	}
	init_mutex_global(params);
	return (params);
}
