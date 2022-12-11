/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburgsta <rburgsta@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 19:46:43 by rburgsta          #+#    #+#             */
/*   Updated: 2022/11/28 19:46:43 by rburgsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft.h"

//push_swap_utils
int		check_int(char *str);
int		check_stack(char **v);
t_list	*arg_to_list(char **argv);
void	ft_free2d(void **ptr);
void	ft_free_list(t_list *lst);

void	do_operation(t_list **a, t_list **b, const char *op, int out);

#endif