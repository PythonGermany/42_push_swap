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

//Rotates b until the head of a is in the right position when pushed to b. Then pushes to b.
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
			i = 0;
			while (ft_lstsize(a) > 1 && *(int *)a->next->content < ft_atoi((char *)a->content))
				do_operation(&a, &b, "ra");
			while (i < ft_lstsize(b) && *(int *)a->content < *(int *)b->content)
			{
				do_operation(&a, &b, "rb");
				i++;
			}
			do_operation(&a, &b, "pb");
			if (i > ft_lstsize(b) / 2 && *(int *)a->next->content < *(int *)a->content)
				while (*(int *)a->next->content < *(int *)a->content && i++ < ft_lstsize(b))
					do_operation(&a, &b, "rr");
			if (i > ft_lstsize(b) / 2)
				while (i++ < ft_lstsize(b))
					do_operation(&a, &b, "rb");
			else if (i > 0)
				while (i-- > 0)
					do_operation(&a, &b, "rrb");
			// print_list(a, "\nA");
			// print_list(b, "B");
		}
		while (ft_lstsize(b) > 0)
			do_operation(&a, &b, "pa");
		// print_list(a, "A");
		// print_list(b, "B");
		// if (check_sorted(a))
		// 	ft_printf("Sorted!\n");
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
