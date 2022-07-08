/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouyer <jbouyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 16:25:44 by jbouyer           #+#    #+#             */
/*   Updated: 2022/07/08 11:41:28 by jbouyer          ###   ########.fr       */
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

char	*print_sleep(void)
{
	char *str;

	str = "is sleeping";
	return(str);
}

char	*print_think(void)
{
	char *str;

	str = "is thinking";
	return(str);
}

char	*print_died(void)
{
	char *str;

	str = "died";
	return(str);
}
