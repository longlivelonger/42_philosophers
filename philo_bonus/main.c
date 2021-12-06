/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbronwyn <sbronwyn@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 18:26:47 by sbronwyn          #+#    #+#             */
/*   Updated: 2021/12/06 11:20:27 by sbronwyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	philosopher(t_philosopher *data)
{
	int	i;

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

void	run_philosophers(t_philosopher *philo_data, t_args args)
{
	int	i;

	i = 0;
	while (i < args.n_philosophers)
	{
		philo_data[i].pid = fork();
		if (philo_data[i].pid == 0)
			exit(philosopher(philo_data + i));
		usleep(50);
		i += 2;
	}
	i = 1;
	while (i < args.n_philosophers)
	{
		philo_data[i].pid = fork();
		if (philo_data[i].pid == 0)
			exit(philosopher(philo_data + i));
		usleep(50);
		i += 2;
	}
}

void	monitor(t_philosopher *philo_data, t_args args)
{
	int	i;
	int	eaten_philo_count;

	while (1)
	{
		usleep(1000);
		eaten_philo_count = 0;
		i = -1;
		while (++i < args.n_philosophers)
		{
			eaten_philo_count += philo_data[i].eaten_n_times;
			if (is_died(philo_data + i) && !philo_data[i].eaten_n_times)
			{
				print_status(philo_data + i, "is died", 1);
				free_philo_data(philo_data, &args);
			}
		}
		if (eaten_philo_count == args.n_philosophers)
			free_philo_data(philo_data, &args);
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
	run_philosophers(philo_data, args);
	monitor(philo_data, args);
	return (0);
}
