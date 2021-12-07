/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbronwyn <sbronwyn@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 03:06:54 by sbronwyn          #+#    #+#             */
/*   Updated: 2021/12/07 03:07:24 by sbronwyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	*philosopher(void *arg)
{
	t_philosopher	*data;
	int				i;

	data = (t_philosopher *)arg;
	i = -1;
	while (++i < data->args->n_times_to_eat || data->args->n_times_to_eat == -1)
	{
		take_forks(data);
		print_status(data, "is eating", 1);
		usleep(data->args->time_to_eat * 1000);
		if (is_died(data))
			return (0);
		release_forks(data);
		print_status(data, "is sleeping", 0);
		usleep(data->args->time_to_sleep * 1000);
		print_status(data, "is thinking", 0);
	}
	data->eaten_n_times = 1;
	return (0);
}
