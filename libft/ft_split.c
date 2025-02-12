/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 22:04:02 by juhenriq          #+#    #+#             */
/*   Updated: 2024/11/13 19:08:22 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_substrings(char **ptr_arr, int ptr_arr_pos)
{
	while (ptr_arr_pos >= 0)
		free(ptr_arr[ptr_arr_pos--]);
}

static int	fill_pointer_array(char **ptr_arr, char const *s, char c)
{
	int	ptr_arr_pos;
	int	start;
	int	i;
	int	len;

	ptr_arr_pos = 0;
	start = -1;
	i = -1;
	while (s[++i])
	{
		if (start == -1 && s[i] != c)
			start = i;
		if (start != -1 && (s[i] == c || s[i + 1] == '\0'))
		{
			len = ((i - start) + !(s[i] == c));
			ptr_arr[ptr_arr_pos] = ft_substr(s, start, len);
			if (ptr_arr[ptr_arr_pos++] == NULL)
			{
				free_substrings(ptr_arr, (ptr_arr_pos - 2));
				return (1);
			}
			start = -1;
		}
	}
	return (0);
}

static unsigned int	determine_pointer_array_len(char const *s, char c)
{
	int				i;
	int				start;
	unsigned int	pointer_array_len;

	i = 0;
	start = -1;
	pointer_array_len = 1;
	while (s[i])
	{
		if ((s[i] == c))
			start = -1;
		if ((s[i] != c) && (start == -1))
		{
			pointer_array_len++;
			start = i;
		}
		i++;
	}
	return (pointer_array_len);
}

char	**ft_split(char const *s, char c)
{
	char			**pointer_array;
	unsigned int	pointer_array_len;

	if (!s)
		return (NULL);
	pointer_array_len = determine_pointer_array_len(s, c);
	pointer_array = (char **)malloc(pointer_array_len * sizeof(char *));
	if (!pointer_array)
		return (NULL);
	pointer_array[pointer_array_len - 1] = NULL;
	if (fill_pointer_array(pointer_array, s, c))
	{
		free(pointer_array);
		return (NULL);
	}
	return (pointer_array);
}
