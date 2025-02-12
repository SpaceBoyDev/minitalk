/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:42:59 by dario             #+#    #+#             */
/*   Updated: 2024/09/27 18:03:20 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	s1_len;
	size_t	s2_len;
	char	*str;

	i = 0;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = ft_calloc((s1_len + s2_len + 1), sizeof(char));
	if (str == NULL)
		return (NULL);
	while (i < s1_len)
	{
		str[i] = s1[i];
		++i;
	}
	while (i < (s1_len + s2_len))
	{
		str[i] = s2[i - s1_len];
		++i;
	}
	return (str);
}
