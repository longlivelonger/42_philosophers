/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbronwyn <sbronwyn@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 18:26:47 by sbronwyn          #+#    #+#             */
/*   Updated: 2021/11/29 23:13:35 by sbronwyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	*philosopher(void *arg)
{
	t_philosopher	*data;

	data = (t_philosopher *)arg;
	while (1)
	{
		pthread_mutex_lock(data->left_fork);
		gettimeofday(&data->time, 0);
		printf("%ld%d %d has taken a fork\n", data->time.tv_sec,
			data->time.tv_usec / 1000, data->num);
		pthread_mutex_lock(data->right_fork);
		gettimeofday(&data->time, 0);
		printf("%ld%d %d has taken a fork\n", data->time.tv_sec,
			data->time.tv_usec / 1000, data->num);
		printf("%ld%d %d is eating\n", data->time.tv_sec,
			data->time.tv_usec / 1000, data->num);
		usleep(data->args->time_to_eat * 1000);
		pthread_mutex_unlock(data->left_fork);
		pthread_mutex_unlock(data->right_fork);
	}
	return (0);
}

void	run_threads(t_philosopher *philo_data, t_args args)
{
	pthread_t	thread;
	int			i;

	i = 0;
	while (i < args.n_philosophers)
	{
		if (pthread_create(&thread, NULL, &philosopher,
				(void *)(philo_data + i)))
			exit(1);
		pthread_detach(thread);
		i += 2;
	}
	i = 1;
	while (i < args.n_philosophers)
	{
		if (pthread_create(&thread, NULL, &philosopher,
				(void *)(philo_data + i)))
			exit(1);
		pthread_detach(thread);
		i += 2;
	}
}

int	main(int argc, char **argv)
{
	t_args			args;
	t_philosopher	*philo_data;

	if (argc < 5 || argc > 6)
		return (1);
	parse_args(&args, argc - 1, argv + 1);
	philo_data = create_philosophers_data(&args);
	if (philo_data == 0)
		return (1);
	run_threads(philo_data, args);
	// free_philo_data(philo_data, &args);
	usleep(10000 * 1000);
	return (0);
}
