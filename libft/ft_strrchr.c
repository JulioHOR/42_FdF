/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 19:05:04 by juhenriq          #+#    #+#             */
/*   Updated: 2024/11/02 19:31:55 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*latest_ocurrence;
	int		was_it_found;

	was_it_found = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if ((unsigned char) c == (unsigned char) s[i])
		{
			latest_ocurrence = ((char *)&(s[i]));
			was_it_found = 1;
		}
		i++;
	}
	if ((unsigned char) c == '\0')
	{
		latest_ocurrence = ((char *) &(s[i]));
		was_it_found = 1;
	}
	if (was_it_found)
		return (latest_ocurrence);
	return ((void *) 0);
}
