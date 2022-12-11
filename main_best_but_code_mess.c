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

int	main(int argc, char **argv)
{
	char	**param;
	int		i;
	t_list	*a;
	t_list	*b;
	t_list	*tmp;

	if (argc == 2)
		param = ft_split(argv[1], ' ');
	else if (argc > 2)
		param = &argv[1];
	if (argc > 1 && check_stack(param))
		write(2, "Error\n", 0);
	else if (argc > 1)
	{
		b = 0;
		a = arg_to_list(param);
		int temp;
		int next = ft_lstsize(a);
		int chunk_size = ft_lstsize(a) / 5;
		while (ft_lstsize(a) > 0)
		{
			next = ft_lstsize(a);
			for (int x = chunk_size - 1; x >= 0; x--)
			{
				temp = nthsmallest(a, x);
				if (temp > ft_lstsize(a) / 2)
					temp = nthsmallest(a, x) - ft_lstsize(a);
				if (next * next > temp * temp)
					next = temp;
			}
			if (next > 0)
				while (next-- > 0)
					do_operation(&a, &b, "ra");
			else if (next < 0)
				while (next++ < 0)
					do_operation(&a, &b, "rra");
			do_operation(&a, &b, "pb");
		}
		while (ft_lstsize(b) > 0)
		{
			if (!nthsmallest(b, ft_lstsize(b) - 1))
				do_operation(&a, &b, "pa");
			if (nthsmallest(b, ft_lstsize(b) - 1) < ft_lstsize(b) / 2)
				do_operation(&a, &b, "rb");
			else
				do_operation(&a, &b, "rrb");
		}
		print_list(a, "A");
		print_list(b, "B");
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