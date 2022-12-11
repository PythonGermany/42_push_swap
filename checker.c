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

void	sort_list(t_list **lst)
{
	t_list	*tmp;
	char	*str;

	tmp = 0;
	str = get_next_line(0);
	while (str)
	{
		str[ft_strlen(str) - 1] = '\0';
		do_operation(lst, &tmp, str, 0);
		free(str);
		str = get_next_line(0);
	}
	if (check_sorted(*lst) && !ft_lstsize(tmp))
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
	ft_free_list(*lst);
}

int	main(int argc, char **argv)
{
	char	**param;
	t_list	*stack;

	if (argc == 2)
		param = ft_split(argv[1], ' ');
	else if (argc > 2)
		param = &argv[1];
	if (argc > 1 && check_stack(param))
		write(2, "Error\n", 6);
	else if (argc > 1)
	{
		stack = arg_to_list(param);
		sort_list(&stack);
	}
	if (argc == 2)
		ft_free2d((void **)param);
	return (0);
}
