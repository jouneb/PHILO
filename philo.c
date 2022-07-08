/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouyer <jbouyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:04:12 by jbouyer           #+#    #+#             */
/*   Updated: 2022/07/08 12:31:25 by jbouyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"

int	main(int argc, char **argv)
{
	t_global	*params;

	if ((argc < 5) || (argc > 6) || (check_args_digit(argv) == 1))
		return (printf("Arguments incorrects"));
	params = init_dinner(argv);
	(void) params;
	// destroy_philo(params);
	return (0);
}
