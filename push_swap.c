/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburgsta <rburgsta@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 00:07:33 by rburgsta          #+#    #+#             */
/*   Updated: 2022/12/09 00:07:33 by rburgsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <unistd.h>
#include <stdlib.h>

int	nthsmallest(t_list *lst, int n)
{
	t_list	*tmp;
	t_list	*start;
	int		i;
	int		val;

	i = 0;
	start = lst;
	while (lst)
	{
		val = 0;
		tmp = start;
		while (tmp)
		{
			if (*(int *)lst->content > *(int *)tmp->content)
				val++;
			tmp = tmp->next;
		}
		if (val == n)
			return (i);
		i++;
		lst = lst->next;
	}
	return (0);
}

void	sort_stack(t_list **a, t_list **b)
{
	if (ft_lstsize(*a) > 2 && !nthsmallest(*a, ft_lstsize(*a) - 1))
		do_operation(a, b, "ra");
	else if (ft_lstsize(*a) > 2 && nthsmallest(*a, ft_lstsize(*a) - 1) == 1)
		do_operation(a, b, "rra");
	if (nthsmallest(*a, 0) > nthsmallest(*a, 1))
		do_operation(a, b, "sa");
	while (ft_lstsize(*b) > 0)
	{
		if (!nthsmallest(*b, ft_lstsize(*b) - 1))
			do_operation(a, b, "pa");
		else if (nthsmallest(*b, ft_lstsize(*b) - 1) < ft_lstsize(*b) / 2)
			do_operation(a, b, "rb");
		else
			do_operation(a, b, "rrb");
	}
}

void	solve_stack(t_list **a, t_list **b, int stack_size)
{
	int	next;
	int	curr;
	int	i;

	while (ft_lstsize(*a) > 3)
	{
		next = nthsmallest(*a, 0);
		next -= ft_lstsize(*a) * (next > ft_lstsize(*a) / 2);
		i = ft_lstsize(*a) / (stack_size * 3 / 200 + 3.5) - 1;
		while (i >= 0 && ft_lstsize(*a) > 5)
		{
			curr = nthsmallest(*a, i--);
			curr -= ft_lstsize(*a) * (curr > ft_lstsize(*a) / 2);
			if (next * next > curr * curr)
				next = curr;
		}
		if (next > 0)
			while (next-- > 0)
				do_operation(a, b, "ra");
		else
			while (next++ < 0)
				do_operation(a, b, "rra");
		do_operation(a, b, "pb");
	}
	sort_stack(a, b);
}

//Searches for nearest element inside of the current chunk in a. 
//Rotates to make it head. Pushes it to b. When a is empty searches
//for biggest element in b, rotates to make it head and pushes it to a.
int	main(int argc, char **argv)
{
	char	**param;
	t_list	*a;
	t_list	*b;

	if (argc == 2)
		param = ft_split(argv[1], ' ');
	else if (argc > 2)
		param = &argv[1];
	if (argc > 1 && check_stack(param))
		write(2, "Error\n", 6);
	else if (argc > 1)
	{
		b = 0;
		a = 0;
		if (arg_to_list(&a, param) != NULL && !check_sorted(a))
			solve_stack(&a, &b, ft_lstsize(a));
		else if (param == NULL)
			write(2, "Error\n", 6);
		ft_lstclear(&a, &free);
	}
	if (argc == 2 && param != NULL)
		ft_free2d((void **)param);
	return (0);
}
