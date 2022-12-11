/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburgsta <rburgsta@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:51:02 by rburgsta          #+#    #+#             */
/*   Updated: 2022/12/09 00:23:00 by rburgsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	swap(t_list **lst)
{
	t_list	*tmp;

	if (ft_lstsize(*lst) > 1)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		tmp->next = (*lst)->next;
		(*lst)->next = tmp;
	}
	return (0);
}

void	push(t_list **dst, t_list **src)
{
	t_list	*temp;

	if (ft_lstsize(*src) > 0)
	{
		temp = (*src)->next;
		ft_lstadd_front(dst, *src);
		*src = temp;
	}
}

int	rotate(t_list **lst)
{
	t_list	*temp;

	if (ft_lstsize(*lst) > 1)
	{
		temp = *lst;
		*lst = (*lst)->next;
		ft_lstadd_back(lst, temp);
	}
	return (0);
}

int	rev_rotate(t_list **lst)
{
	t_list	*temp;

	if (ft_lstsize(*lst) > 1)
	{
		temp = *lst;
		while (temp->next->next != NULL)
			temp = temp->next;
		ft_lstadd_front(lst, ft_lstlast(*lst));
		temp->next = 0;
	}
	return (0);
}

void	do_operation(t_list **a, t_list **b, const char *op)
{
	if (!ft_strncmp(op, "sa", 4))
		swap(a);
	else if (!ft_strncmp(op, "sb", 4))
		swap(b);
	else if (!ft_strncmp(op, "pa", 4))
		push(a, b);
	else if (!ft_strncmp(op, "pb", 4))
		push(b, a);
	else if (!ft_strncmp(op, "ra", 4))
		rotate(a);
	else if (!ft_strncmp(op, "rb", 4))
		rotate(b);
	else if (!ft_strncmp(op, "rra", 4))
		rev_rotate(a);
	else if (!ft_strncmp(op, "rrb", 4))
		rev_rotate(b);
	else if (!ft_strncmp(op, "ss", 4) && !swap(a) && !swap(b))
		;
	else if (!ft_strncmp(op, "rr", 4) && !rotate(a) && !rotate(b))
		;
	else if (!ft_strncmp(op, "rrr", 4) && !rev_rotate(a) && !rev_rotate(b))
		(void)op;
	ft_printf("%s\n", op);
}
