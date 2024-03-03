/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 10:01:45 by mhaile            #+#    #+#             */
/*   Updated: 2024/03/03 10:17:21 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	handle_sign(const char *str, int *i)
{
	int	sign;

	sign = 1;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
		{
			sign = -1;
		}
		(*i)++;
	}
	return (sign);
}

long long int	ft_atoi_l(const char *str)
{
	int				i;
	int				sign;
	long long int	res;
	int				digit;

	i = 0;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	sign = handle_sign(str, &i);
	while (ft_isdigit(str[i]))
	{
		digit = str[i] - '0';
		if ((res > (9223372036854775807 - digit) / 10) && sign == 1)
			return ((long long int)INT_MAX + 1);
		else if ((res > (9223372036854775807 - digit) / 10) && sign == -1)
			return ((long long int)INT_MAX + 1);
		res = (res * 10) + digit;
		i++;
	}
	return ((int) sign * res);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}
