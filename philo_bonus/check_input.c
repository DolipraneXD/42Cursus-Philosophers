/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:32:39 by moel-fat          #+#    #+#             */
/*   Updated: 2024/07/25 11:38:09 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	else
		return (0);
}

long int	ft_atoil(char *str)
{
	int			i;
	int			sign;
	long int	rest;

	i = 0;
	rest = 0;
	sign = 1;
	while (str[i] != '\0' && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		rest = rest * 10 + (str[i] - '0');
		if (rest > 2147483648 && sign == -1)
			ft_putstr_fd("value bigger than max/min int\n", 2);
		if (rest > INT_MAX && sign == 1)
			ft_putstr_fd("value bigger than max/min int\n", 2);
		i++;
	}
	return (rest * sign);
}

static bool	check_args(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		if (av[i][j] == '-' || av[i][j] == '+')
			j++;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
			{
				printf("Error: Invalid argument\n");
				return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

bool	check_input(int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (false);
	}
	if (check_args(ac, av) == false)
		return (false);
	return (true);
}
