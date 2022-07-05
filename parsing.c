/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouyer <jbouyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 16:32:56 by jbouyer           #+#    #+#             */
/*   Updated: 2022/07/04 16:36:59 by jbouyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	unsigned long	nb;
	unsigned long	a;
	int				b;

	a = 0;
	nb = 0;
	b = 1;
	while ((str[a] >= 9 && str[a] <= 13) || (str[a] == 32))
		a++;
	if (str[a] == '-')
	{
		b = -1;
		a++;
	}
	else if (str[a] == '+')
		a++;
	while (str[a] >= '0' && str[a] <= '9')
	{
		nb = (nb * 10 + (str[a] - '0'));
		a++;
	}
	nb = nb * b;
	return ((int)nb);
}
