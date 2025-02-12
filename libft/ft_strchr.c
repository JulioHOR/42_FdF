/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 19:05:04 by juhenriq          #+#    #+#             */
/*   Updated: 2024/11/02 19:19:20 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if ((unsigned char) c == (unsigned char) s[i])
			return ((char *)&(s[i]));
		i++;
	}
	if ((unsigned char) c == '\0')
		return ((char *) &(s[i]));
	return ((void *) 0);
}
