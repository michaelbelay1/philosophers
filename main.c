/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 21:12:09 by mhaile            #+#    #+#             */
/*   Updated: 2024/02/08 23:20:10 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

int	is_numeric(int count)
{
	if (count >= 48 && count <= 57)
		return (1);
	else
		return (0);
}

int	is_str_numeric(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (is_numeric(str[i]) == 0)
			return (0);
	}
	return (1);
}

int	args_all_num(char **av)
{
	int	i;

	i = 0;
	while (av[++i])
	{
		if (!is_str_numeric(av[i]))
		{
			ft_putstr_fd("Invalid arguments\n", 2);
			return (1);
		}
	}
	return (0);
}

int	arg_num(int ac)
{
	if (ac == 5 || ac == 6)
		return (0);
	else
	{
		ft_putstr_fd("Invalid number of arguments\n", 2);
		return (1);
	}
}

int	main(int ac, char **av)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	if (arg_num(ac) || args_all_num(av))
		return (1);
	init_philos(&data, av);
	printf("time to die %d\n", data.time_to_die);
	printf("time to eat %d\n", data.time_to_eat);
	printf("time to sleep %d\n", data.time_to_sleep);
	printf("must eat %d\n", data.must_eat_count);
}
