/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburgsta <rburgsta@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 22:11:30 by rburgsta          #+#    #+#             */
/*   Updated: 2022/12/07 22:11:30 by rburgsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>

int	check_int(char *str)
{
	size_t	i;

	if ((ft_strlen(str + (str[0] == '-')) > 10))
		return (1);
	else if ((ft_strlen(str + (str[0] == '-')) < 10))
		return (0);
	i = (str[0] == '-') - 1;
	while (++i < ft_strlen(str))
		if (str[i] > "2147483647"[i - (str[0] == '-')] + \
			(i == ft_strlen(str) - 1 && str[0] == '-'))
			return (1);
	return (0);
}

int	check_stack(char **v)
{
	int	i;
	int	i2;

	i2 = -1;
	while (v[++i2] != NULL)
	{
		i = -1;
		while (v[i2][++i] != '\0')
			if ((v[i2][i] < '0' || v[i2][i] > '9') && !(!i && v[i2][i] == '-'))
				return (1);
		if (!ft_strlen(v[i2]) || check_int(v[i2]))
			return (1);
	}
	i2 = -1;
	while (v[++i2] != NULL)
	{
		i = i2;
		while (v[++i] != NULL)
			if (ft_atoi(v[i]) == ft_atoi(v[i2]))
				return (1);
	}
	return (0);
}

t_list	*arg_to_list(char **argv)
{
	t_list	*lst;
	t_list	*next;
	int		i;
	int		*nb;

	lst = 0;
	i = 0;
	while (argv[i] != NULL)
	{
		nb = (int *)ft_calloc(1, sizeof(int));
		if (!nb)
			return (NULL);
		*nb = ft_atoi(argv[i++]);
		next = ft_lstnew((void *)nb);
		if (next == NULL)
			return (free(nb), NULL);
		ft_lstadd_back(&lst, next);
	}
	return (lst);
}

void	ft_free2d(void **ptr)
{
	int	i;

	i = -1;
	while (((char **)ptr)[++i])
		free(((char **)ptr)[i]);
	free(ptr);
}
