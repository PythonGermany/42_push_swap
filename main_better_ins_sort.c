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

int	getsmallest(t_list *lst)
{
	int i = 0;
	int min;
	int i_min = 0;

	min = *(int *)lst->content;
	while (lst)
	{
		if (*(int *)lst->content < min)
		{
			min = *(int *)lst->content;
			i_min = i;
		}
		i++;
		lst = lst->next;
	}
	return (i_min);
}

//Search for smallest element in a, rotate until it is the head and push to b. 
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
		while (ft_lstsize(a) > 0)
		{
			if (getsmallest(a) && getsmallest(a) < ft_lstsize(a) / 2)
				do_operation(&a, &b, "ra");
			else if (getsmallest(a) && getsmallest(a) >= ft_lstsize(a) / 2)
				do_operation(&a, &b, "rra");
			else
				do_operation(&a, &b, "pb");
		}
		while (ft_lstsize(b) > 0)
			do_operation(&a, &b, "pa");
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
