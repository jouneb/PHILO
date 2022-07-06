/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dinner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouyer <jbouyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 16:08:02 by jbouyer           #+#    #+#             */
/*   Updated: 2022/07/06 17:27:31 by jbouyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_global	*init_dinner(char **argv)
{
	t_global	*params;

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
	// init_philo(&params);
	return (params);
}
// time_start = gettimeofday;
