/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 10:40:10 by moel-fat          #+#    #+#             */
/*   Updated: 2024/07/24 15:46:13 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_table	*table;

	if (check_input(ac, av) == false)
		return (EXIT_FAILURE);
	table = initialize_simulation(ac, av);
	start_dinner(table);
	return (EXIT_SUCCESS);
}
