/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 21:12:09 by mhaile            #+#    #+#             */
/*   Updated: 2024/02/26 22:01:47 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

int	main(int ac, char **av)
{
	t_data	data;
	int		philo_dead;

	if (arg_num(ac) || args_all_num(av))
		return (1);
	if (init_struct(&data, av))
	{
		printf("Invalid argument\n");
		return (1);
	}
	create_threads(&data);
	philo_dead = begin_monitoring(&data);
	if (philo_dead)
	{
		pthread_mutex_lock(&data.mutex_dead);
		printf("%lu %d died\n", get_time()
			- data.philo->data->start_time, philo_dead);
		pthread_mutex_unlock(&data.mutex_dead);
	}
	join_threads(&data);
	free(data.forks_taken);
	free(data.forks);
	free(data.philo);
}
