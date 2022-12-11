/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburgsta <rburgsta@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:51:02 by rburgsta          #+#    #+#             */
/*   Updated: 2022/12/07 22:09:40 by rburgsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void op_swap(t_list **lst)
{
	t_list	*tmp;
	
	if (ft_lstsize(*lst) > 1)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		tmp->next = (*lst)->next;
		(*lst)->next = tmp;
	}
}

void	op_push(t_list **dst, t_list **src)
{
	t_list	*temp;

	if (ft_lstsize(*src) > 0)
	{
		temp = (*src)->next;
		ft_lstadd_front(dst, *src);
		*src = temp;
	}
}

void	op_rotate(t_list **lst)
{
	t_list	*temp;

	if (ft_lstsize(*lst) > 1)
	{
		temp = *lst;
		*lst = (*lst)->next;
		ft_lstadd_back(lst, temp);
	}
}

void	op_reverse_rotate(t_list **lst)
{
	t_list	*temp;
	if (ft_lstsize(*lst) > 1)
	{
		temp = *lst;
		while (temp->next->next)
			temp = temp->next;
		ft_lstadd_front(lst, ft_lstlast(*lst));
		temp->next = 0;
	}
}

static void	do_multi_operation(t_list **a, t_list **b, const char *op)
{
	if (!ft_strncmp(op, "ss", 4))
	{
		op_swap(a);
		op_swap(b);
	}
	else if (!ft_strncmp(op, "rr", 4))
	{
		op_rotate(a);
		op_rotate(b);
	}
	else if (!ft_strncmp(op, "rrr", 4))
	{
		op_reverse_rotate(a);
		op_reverse_rotate(b);
	}
}

void	do_operation(t_list **a, t_list **b, const char *op, int out)
{
	if (!ft_strncmp(op, "sa", 4))
		op_swap(a);
	else if (!ft_strncmp(op, "sb", 4))
		op_swap(b);
	else if (!ft_strncmp(op, "pa", 4))
		op_push(a, b);
	else if (!ft_strncmp(op, "pb", 4))
		op_push(b, a);
	else if (!ft_strncmp(op, "ra", 4))
		op_rotate(a);
	else if (!ft_strncmp(op, "rb", 4))
		op_rotate(b);
	else if (!ft_strncmp(op, "rra", 4))
		op_reverse_rotate(a);
	else if (!ft_strncmp(op, "rrb", 4))
		op_reverse_rotate(b);
	else
		do_multi_operation(a, b, op);
	if (out)
		ft_printf("%s\n", op);
}