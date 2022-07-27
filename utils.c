/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouyer <jbouyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 12:07:47 by jbouyer           #+#    #+#             */
/*   Updated: 2022/07/27 18:00:39 by jbouyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *s)
{
	int		result;
	int		flag_neg;
	int		i;

	result = 0;
	flag_neg = 1;
	i = 0;
	while (ft_isspace(s[i]))
		i++;
	if (s[i] == '-')
	{
		flag_neg = -1;
		i++;
	}
	else if (s[i] == '+')
		i++;
	while (ft_isdigit(s[i]))
	{
		result = result * 10 + (s[i] - 48);
		i++;
	}
	return (result * flag_neg);
}

int	check_args_digit(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) == 0)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	init_mutex_global(t_global *params)
{
	pthread_mutex_init(&params->check_dead, NULL);
	pthread_mutex_init(&params->m_global, NULL);
	pthread_mutex_init(&params->write, NULL);
}
// int	is_dead_utils(t_philosopher *philo)
// {
// 	int	last_lunch;

// 	pthread_mutex_lock(&philo->params->m_global);
// 	last_lunch = philo->last_lunch;
// 	pthread_mutex_unlock(&philo->params->m_global);
// 	return (last_lunch);
// }
