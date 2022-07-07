/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouyer <jbouyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 16:25:44 by jbouyer           #+#    #+#             */
/*   Updated: 2022/07/07 17:30:58 by jbouyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*print_fork(void)
{
	char *str;

	str = "has taken a fork";
	return(str);
}

char	*print_eating(void)
{
	char *str;

	str = "is eating";
	return(str);
}

void	print_sleep(void)
{
	printf("is sleeping");
}

void	print_think(void)
{
	printf("is thinking");
}

void	print_died(void)
{
	printf("died");
}
