/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:41:38 by juhenriq          #+#    #+#             */
/*   Updated: 2024/11/14 23:04:06 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	it_matches(char char_to_match, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (char_to_match == set[i])
			break ;
		i++;
	}
	if (set[i])
		return (1);
	return (0);
}

static int	find_it_for_me(char const *s1, char const *set, \
	int flag_start_or_end)
{
	int	i;

	if (flag_start_or_end == 0)
	{
		i = 0;
		while (s1[i])
		{
			if (!(it_matches(s1[i], set)))
				return (i);
			i++;
		}
	}
	if (flag_start_or_end == 1)
	{
		i = (ft_strlen(s1) - 1);
		while (s1[i])
		{
			if (!(it_matches(s1[i], set)))
				return (i);
			i--;
		}
	}
	return (-1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	start;
	int	end;

	if (!s1 || !set)
		return (((void *) 0));
	if (ft_strlen(s1) == 0 || ft_strlen(set) == 0)
		return (ft_strdup(s1));
	start = find_it_for_me(s1, set, 0);
	end = find_it_for_me(s1, set, 1);
	if (start == -1 || end == -1)
		return (ft_calloc(1, 1));
	return (ft_substr(s1, start, ((end - start) + 1)));
}
