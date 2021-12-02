/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbronwyn <sbronwyn@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 04:53:05 by sbronwyn          #+#    #+#             */
/*   Updated: 2021/12/02 06:03:17 by sbronwyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	print_status(t_philosopher *data, char *str, int save_time)
{
	static pthread_mutex_t	*display_mutex = 0;
	struct timeval			time;
	int						interval_ms;

	if (display_mutex == 0)
	{
		display_mutex = malloc(sizeof(*display_mutex));
		pthread_mutex_init(display_mutex, 0);
	}
	pthread_mutex_lock(display_mutex);
	gettimeofday(&time, 0);
	interval_ms = (int)(time.tv_sec - data->start_time.tv_sec) * 1000
		+ (int)(time.tv_usec - data->start_time.tv_usec) / 1000;
	printf("%6d %d %s\n", interval_ms, data->id, str);
	if (save_time)
		data->last_meal_time = time;
	pthread_mutex_unlock(display_mutex);
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
