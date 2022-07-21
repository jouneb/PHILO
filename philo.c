/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouyer <jbouyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:04:12 by jbouyer           #+#    #+#             */
/*   Updated: 2022/07/21 16:33:39 by jbouyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"

int	main(int argc, char **argv)
{
	t_global	*params;
	pthread_t	simu;

	if ((argc < 5) || (argc > 6) || (check_args_digit(argv) == 1))
		return (printf("Arguments incorrects"));
	params = init_dinner(argv);
	while (params->is_dead == 0)
	{
		pthread_create(&simu, NULL, init_thread, params);
		pthread_join(simu, NULL);
	}
	return (0);
}
