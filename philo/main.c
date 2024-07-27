/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:14:06 by moel-fat          #+#    #+#             */
/*   Updated: 2024/07/25 09:13:16 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	*table;

	if (check_input(ac, av) == false)
		return (1);
	table = safe_malloc(sizeof(t_table));
	if (!table)
		return (1);
	if (table_init(table, ac, av) == -1)
		return (free(table), 1);
	if (serving_table(table) == -1)
		return (clean_up(table), 1);
	if (start_dinner(table) == -1)
		return (clean_up(table), 1);
	clean_up(table);
	return (0);
}
