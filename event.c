/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 14:44:12 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/12/10 05:13:57 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	select_item(t_ft_select *ft_select)
{
	ft_select->items[ft_select->cursor].selected ^= 1;
	active_modes(ft_select, ft_select->cursor);
	cur_goto(ft_select, ft_select->cursor);
	ft_putstr_fd(ft_select->items[ft_select->cursor].content, ft_select->fd);
	deactive_modes();
	cur_down(ft_select);
}

void	delete_item(t_ft_select *ft_select)
{
	const int	count = ft_select->count - 1;
	const int	cursor = ft_select->cursor;
	t_item		*items;

	if (count == 0)
		end(ft_select);
	items = ft_select->items;
	delete_last_line(ft_select);
	delete_char(ft_select, ft_select->max_col);
	ft_select->count--;
	if (cursor < ft_select->count)
		ft_memcpy(&items[cursor], &items[cursor + 1],
											sizeof(t_item) * (count - cursor));
	else
		ft_select->cursor--;
	print_args(ft_select);
}

void	end(t_ft_select *ft_select)
{
	int	i;

	i = 0;
	ft_select->config.c_lflag |= (ICANON | ECHO);
	tcsetattr(0, 0, &ft_select->config);
	tputs(tgetstr("te", 0), 0, output);
	tputs(tgetstr("ve", 0), 0, output);
	while (i < ft_select->count)
	{
		if (ft_select->items[i].selected)
		{
			ft_putstr_fd(ft_select->items[i].content, 1);
			if (i < ft_select->count - 1)
				ft_putstr_fd(" ", 1);
		}
		i++;
	}
	free(ft_select->items);
	exit(0);
}

void	reset(int ac, char **av, t_ft_select *ft_select)
{
	ft_select->count = ac;
	set_items(ac, av, ft_select);
	signal_resize(0);
	cursor_move(ft_select, ft_select->cursor, 0);
}
