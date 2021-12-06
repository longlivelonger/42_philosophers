/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbronwyn <sbronwyn@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:35:02 by sbronwyn          #+#    #+#             */
/*   Updated: 2021/12/06 11:22:09 by sbronwyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_philosopher	*create_philosophers_data(t_args *args)
{
	t_philosopher	*philo_data;
	int				i;

	philo_data = malloc(args->n_philosophers * sizeof(*philo_data));
	if (philo_data == 0)
		return (0);
	i = -1;
	while (++i < args->n_philosophers)
	{
		philo_data[i].id = i + 1;
		philo_data[i].eaten_n_times = 0;
		gettimeofday(&philo_data[i].start_time, 0);
		philo_data[i].last_meal_time = philo_data[i].start_time;
		philo_data[i].args = args;
	}
	return (philo_data);
}

void	free_philo_data(t_philosopher *philo_data, t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->n_philosophers)
		kill(philo_data[i].pid, SIGKILL);
	free(philo_data);
	exit(0);
}

int	is_died(t_philosopher *data)
{
	struct timeval	time;
	int				interval_ms;

	gettimeofday(&time, 0);
	interval_ms = (int)(time.tv_sec - data->last_meal_time.tv_sec) * 1000
		+ (int)(time.tv_usec - data->last_meal_time.tv_usec) / 1000;
	if (interval_ms > data->args->time_to_die)
		return (1);
	return (0);
}
