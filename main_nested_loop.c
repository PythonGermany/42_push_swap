/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburgsta <rburgsta@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 16:14:21 by rburgsta          #+#    #+#             */
/*   Updated: 2022/12/03 16:14:21 by rburgsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>
#include <unistd.h>

int	check_sorted(t_list *lst)
{
	while (lst->next)
	{
		if (*(int *)lst->content >= \
			*(int *)lst->next->content)
			return (0);
		lst = lst->next;
	}
	return (1);
}

//Works with a nested loop and is very inefficient
int	main(int argc, char **argv)
{
	char	**param;
	int		i;
	t_list *a;
	t_list *b;
	t_list *tmp;

	if (argc == 2)
		param = ft_split(argv[1], ' ');
	else if (argc > 2)
		param = &argv[1];
	if (argc > 1 && check_stack(param))
		write(2, "Error\n", 6);
	else if (argc > 1)
	{
		b = 0;
		a = arg_to_list(param);
		int i2;
		i = 0;
		while (i < ft_lstsize(a) - 1 && !check_sorted(a))
		{
			i2 = 0;
			while (i2 < ft_lstsize(a) - 1)
			{
				if (*(int *)a->content > *(int *)a->next->content)
					do_operation(&a, &b, "sa");
				do_operation(&a, &b, "ra");
				i2++;
			}
			do_operation(&a, &b, "ra");
			i++;
		}
		while (a != NULL)
		{
			tmp = a->next;
			free(a);
			a = tmp;
		}
	}
	if (argc == 2)
	{
		i = 0;
		while (param[i])
			free(param[i++]);
		free(param);
	}
	return (0);
}
