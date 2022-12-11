/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburgsta <rburgsta@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 21:51:47 by rburgsta          #+#    #+#             */
/*   Updated: 2022/12/07 21:51:47 by rburgsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>
#include <unistd.h>

int	check_sorted(t_list *lst)
{
	while (lst->next)
	{
		if (ft_atoi((char *)lst->content) >= \
			ft_atoi((char *)lst->next->content))
			return (0);
		lst = lst->next;
	}
	return (1);
}

void	sort_list(t_list **lst, t_list *op)
{
	t_list	*tmp;

	tmp = 0;
	while (op)
	{
		do_operation(lst, &tmp, (char *)op->content);
		op = op->next;
	}
	if (check_sorted(*lst) && !ft_lstsize(tmp))
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
	ft_free_list(*lst);
}

int	check_valid_op(char *op)
{
	if (!ft_strncmp(op, "sa", 4) || !ft_strncmp(op, "sb", 4))
		return (0);
	else if (!ft_strncmp(op, "pa", 4) || !ft_strncmp(op, "pb", 4))
		return (0);
	else if (!ft_strncmp(op, "ra", 4) || !ft_strncmp(op, "rb", 4))
		return (0);
	else if (!ft_strncmp(op, "rra", 4) || !ft_strncmp(op, "rrb", 4))
		return (0);
	else if (!ft_strncmp(op, "ss", 4) || !ft_strncmp(op, "rr", 4))
		return (0);
	else if (!ft_strncmp(op, "rrr", 4))
		return (0);
	return (1);
}

int	read_instructions(t_list **op)
{
	char	*str;

	str = get_next_line(0);
	while (str)
	{
		if (ft_strlen(str) < 3 || ft_strlen(str) > 4 \
			|| str[ft_strlen(str) - 1] != '\n')
			return (1);
		str[ft_strlen(str) - 1] = '\0';
		if (check_valid_op(str))
			return (1);
		ft_lstadd_back(op, ft_lstnew(str));
		str = get_next_line(0);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	char	**param;
	t_list	*stack;
	t_list	*op;

	op = 0;
	if (argc == 2)
		param = ft_split(argv[1], ' ');
	else if (argc > 2)
		param = &argv[1];
	if (argc > 1 && (check_stack(param) || read_instructions(&op)))
		write(2, "Error\n", 6);
	else if (argc > 1)
	{
		stack = arg_to_list(param);
		sort_list(&stack, op);
	}
	if (argc == 2)
		ft_free2d((void **)param);
	ft_free_list(op);
	return (0);
}
