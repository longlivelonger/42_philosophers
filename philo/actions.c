/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbronwyn <sbronwyn@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 04:53:05 by sbronwyn          #+#    #+#             */
/*   Updated: 2021/12/02 05:05:22 by sbronwyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	print_status(t_philosopher *data, char *str, int save_time)
{
	struct timeval	time;

	gettimeofday(&time, 0);
	printf("%ld%03d %d %s\n", time.tv_sec,
		time.tv_usec / 1000, data->id, str);
	if (save_time)
		data->meal_time = time;
}

void	take_forks(t_philosopher *data)
{
	if (data->id % 2)
	{
		pthread_mutex_lock(data->left_fork);
		print_status(data, "has taken a fork", 0);
		pthread_mutex_lock(data->right_fork);
		print_status(data, "has taken a fork", 0);
	}
	else
	{
		pthread_mutex_lock(data->right_fork);
		print_status(data, "has taken a fork", 0);
		pthread_mutex_lock(data->left_fork);
		print_status(data, "has taken a fork", 0);
	}
}

void	release_forks(t_philosopher *data)
{
	pthread_mutex_unlock(data->left_fork);
	pthread_mutex_unlock(data->right_fork);
}
