/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 01:18:50 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/12/10 03:47:25 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	delete_char(t_ft_select *ft_select, size_t num)
{
	char buffer[num];

	tputs(tgetstr("sc", 0), 0, output);
	ft_memset(buffer, ' ', num);
	write(ft_select->fd, buffer, num);
	tputs(tgetstr("rc", 0), 0, output);
}

void	delete_last_line(t_ft_select *ft_select)
{
	char buffer[ft_select->max_len];

	ft_memset(buffer, ' ', ft_select->max_len);
	tputs(tgetstr("sc", 0), 0, output);
	cur_goto(ft_select, ft_select->count - 1);
	write(ft_select->fd, buffer, ft_select->max_len);
	tputs(tgetstr("rc", 0), 0, output);
}

void	active_modes(t_ft_select *ft_select, int cursor)
{
	if (ft_select->items[cursor].selected)
		tputs(tgetstr("mr", 0), 0, output);
	if (ft_select->cursor == cursor)
		tputs(tgetstr("us", 0), 0, output);
	tputs(ft_select->items[cursor].color, 0, output);
}

void	deactive_modes(void)
{
	tputs(tgetstr("me", 0), 0, output);
}
