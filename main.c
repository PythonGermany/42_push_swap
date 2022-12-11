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

int	check_int(char *str)
{
	size_t	i;

	if ((ft_strlen(str + (str[0] == '-')) > 10))
		return (1);
	else if ((ft_strlen(str + (str[0] == '-')) < 10))
		return (0);
	i = (str[0] == '-') - 1;
	while (++i < ft_strlen(str))
		if (str[i] > "2147483647"[i - (str[0] == '-')] + \
			(i == ft_strlen(str) - 1 && str[0] == '-'))
			return (1);
	return (0);
}

int	check_stack(char **v)
{
	int	i;
	int	i2;
	
	i2 = -1;
	while (v[++i2] != NULL)
	{
		i = -1;
		while (v[i2][++i] != '\0')
			if ((v[i2][i] < '0' || v[i2][i] > '9') && !(!i && v[i2][i] == '-'))
				return (1);
		if (check_int(v[i2]))
			return (1);
	}
	i2 = -1;
	while (v[++i2] != NULL)
	{
		i = i2;
		while (v[++i] != NULL)
			if (ft_atoi(v[i]) == ft_atoi(v[i2]))
				return (1);
	}
	return (0);
}

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

t_list	*arg_to_list(char **argv)
{
	t_list	*lst;
	int		i;

	i = 0;
	while (argv[i] != NULL)
		ft_lstadd_back(&lst, ft_lstnew((void *)argv[i++]));
	return (lst);
}

void	print_list(t_list *lst, const char *str)
{
	ft_printf("%s: ", str);
	while (lst != NULL)
	{
		ft_printf("%s, ", (char *)lst->content);
		lst = lst->next;
	}
	ft_printf("\n");
}

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
		i = -1;
		b = 0;
		a = arg_to_list(param);
		do_operation(&a, &b, "pb");
		i = 0;
		while (ft_lstsize(a) > 0)
		{
			// if (ft_lstsize(a) > 1 && ft_atoi((char *)a->content) > ft_atoi((char *)a->next->content))
			// 	do_operation(&a, &b, "sa");
			// print_list(a, "A");
			// print_list(b, "B");
			// if (ft_lstsize(b) > 1 && ft_atoi((char *)b->content) > ft_atoi((char *)b->next->content))
			// 	do_operation(&a, &b, "rb");
			while (i < ft_lstsize(b) && ft_atoi((char *)a->content) < ft_atoi((char *)b->content))
			{
				do_operation(&a, &b, "rb");
				i++;
			}
			do_operation(&a, &b, "pb");
			if (i > ft_lstsize(b) / 2)
			{
				while (i < ft_lstsize(b))
				{
					do_operation(&a, &b, "rb");
					i++;
				}
				i = 0;
			}
			else
			{
				while (i > 0)
				{
					do_operation(&a, &b, "rrb");
					i--;
				}
			}
			i = 0;
		}
		while (ft_lstsize(b) > 0)
			do_operation(&a, &b, "pa");
		// print_list(a, "A");
		// print_list(b, "B");
		if (check_sorted(a))
			ft_printf("Sorted!\n");
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
