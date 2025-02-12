/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:27:22 by juhenriq          #+#    #+#             */
/*   Updated: 2024/11/13 19:08:51 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

static int	obtain_nb_of_digits(int n)
{
	int	i;

	i = 0;
	while (n != 0)
	{
		n = (n / 10);
		i++;
	}
	return (i);
}

static int	edge_cases(int *n, int fd)
{
	if (*n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return (1);
	}
	if (*n == 0)
	{
		write(fd, "0", 1);
		return (1);
	}
	if (*n < 0)
	{
		write(fd, &"-", 1);
		*n = (*(n) * -1);
	}
	return (0);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	nb_as_str[11];
	int		nb_of_digits;
	int		i;

	if ((edge_cases(&n, fd)))
		return ;
	nb_of_digits = obtain_nb_of_digits(n);
	nb_as_str[nb_of_digits] = '\0';
	i = (nb_of_digits - 1);
	while (i >= 0)
	{
		nb_as_str[i--] = ((n % 10) + '0');
		n = (n / 10);
	}
	while (nb_as_str[++i])
		ft_putchar_fd(nb_as_str[i], fd);
}
