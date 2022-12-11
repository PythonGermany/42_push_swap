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
#include <unistd.h>
#include <stdlib.h>

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

int	read_op(t_list **op)
{
	char	*str;
	t_list	*next;

	str = get_next_line(0);
	while (str)
	{
		if (ft_strlen(str) < 3 || ft_strlen(str) > 4 \
			|| str[ft_strlen(str) - 1] != '\n')
			return (free(str), 1);
		str[ft_strlen(str) - 1] = '\0';
		if (check_valid_op(str))
			return (free(str), 1);
		next = ft_lstnew(str);
		if (!next)
			return (free(str), 1);
		ft_lstadd_back(op, next);
		str = get_next_line(0);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	char	**param;
	t_list	*stack;
	t_list	*op;

	if (argc == 2)
		param = ft_split(argv[1], ' ');
	else if (argc > 2)
		param = &argv[1];
	op = 0;
	if (argc > 1 && (check_stack(param) || read_op(&op)))
		write(2, "Error\n", 6);
	else if (argc > 1)
	{
		stack = 0;
		if (arg_to_list(&stack, param) != NULL)
			sort_list(&stack, op);
		else
			write(2, "Error\n", 6);
		ft_lstclear(&stack, &free);
	}
	if (argc == 2 && param != NULL)
		ft_free2d((void **)param);
	ft_lstclear(&op, &free);
	return (0);
}
