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

/*int	check_sorted(t_list *lst)
{
	while (lst->next)
	{
		if (ft_atoi((char *)lst->content) >= \
			ft_atoi((char *)lst->next->content))
			return (0);
		lst = lst->next;
	}
	return (1);
}*/

// void	print_list(t_list *lst, const char *str)
// {
// 	ft_printf("%s: ", str);
// 	while (lst != NULL)
// 	{
// 		ft_printf("%s, ", (char *)lst->content);
// 		lst = lst->next;
// 	}
// 	ft_printf("\n");
// }

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
			if (ft_atoi((char *)lst->content) > ft_atoi((char *)tmp->content))
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

void	stack_chunking(t_list **a, t_list **b, int chunk_size)
{
	int	next;
	int	curr;
	int	i;

	next = ft_lstsize(*a) / 2;
	i = chunk_size - 1;
	while (i >= 0)
	{
		curr = nthsmallest(*a, i--);
		if (curr > ft_lstsize(*a) / 2)
			curr -= ft_lstsize(*a);
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

void	stack_sorting(t_list **a, t_list **b)
{
	if (!nthsmallest(*b, ft_lstsize(*b) - 1))
		do_operation(a, b, "pa");
	if (nthsmallest(*b, ft_lstsize(*b) - 1) < ft_lstsize(*b) / 2)
		do_operation(a, b, "rb");
	else
		do_operation(a, b, "rrb");
}

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
		a = arg_to_list(param);
		while (ft_lstsize(a) > 0)
			stack_chunking(&a, &b, ft_lstsize(a) / \
			((ft_lstsize(a) + ft_lstsize(b)) * 3 / 200 + 3.5));
		while (ft_lstsize(b) > 0)
			stack_sorting(&a, &b);
		// print_list(a, "A");
		// print_list(b, "B");
		// if (check_sorted(a))
		// 	ft_printf("Sorted!\n");
		ft_free_list(a);
	}
	if (argc == 2)
		ft_free2d((void **)param);
	return (0);
}
