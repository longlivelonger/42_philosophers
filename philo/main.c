/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbronwyn <sbronwyn@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 18:26:47 by sbronwyn          #+#    #+#             */
/*   Updated: 2021/11/30 19:04:38 by sbronwyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	print_status(t_philosopher *data, char *str, int save_time)
{
	struct timeval	time;

	gettimeofday(&time, 0);
	printf("%ld%d %d %s\n", time.tv_sec,
		time.tv_usec / 1000, data->num, str);
	if (save_time)
		data->time = time;
}

int	is_died(t_philosopher *data)
{
	struct timeval	time;
	int				interval;

	gettimeofday(&time, 0);
	interval = (int)(time.tv_sec - data->time.tv_sec) * 1000
		+ (int)(time.tv_usec - data->time.tv_usec);
	if (interval > data->args->time_to_die)
		return (1);
	return (0);
}

void	*philosopher(void *arg)
{
	t_philosopher	*data;
	int				i;

	data = (t_philosopher *)arg;
	i = -1;
	while (++i < data->args->n_times_to_eat || data->args->n_times_to_eat == -1)
	{
		pthread_mutex_lock(data->left_fork);
		print_status(data, "has taken a fork", 0);
		pthread_mutex_lock(data->right_fork);
		print_status(data, "has taken a fork", 0);
		print_status(data, "is eating", 1);
		usleep(data->args->time_to_eat * 1000);
		if (is_died(data))
			return (0);
		pthread_mutex_unlock(data->left_fork);
		pthread_mutex_unlock(data->right_fork);
		print_status(data, "is sleeping", 0);
		usleep(data->args->time_to_sleep * 1000);
		print_status(data, "is thinking", 0);
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
	usleep(10 * 1000 * 1000);
	return (0);
}
