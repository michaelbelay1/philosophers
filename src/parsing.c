/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:26:31 by mhaile            #+#    #+#             */
/*   Updated: 2024/03/03 10:07:02 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

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
	if (str[0] == '\0')
		return (0);
	if (str[0] == '-' || str[0] == '+')
		i++;
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
		if (ft_atoi_l(av[i]) > INT_MAX)
		{
			ft_putstr_fd("Inputs should be below INT_MAX\n", 2);
			return (1);
		}
		if (ft_atoi_l(av[i]) <= 0)
		{
			ft_putstr_fd("Inputs should be greater than 0\n", 2);
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
