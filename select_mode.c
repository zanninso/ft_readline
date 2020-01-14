/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 10:41:21 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/01/14 13:00:07 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void rewrite_select(t_readline *readline, int start, int end)
{
    if (ABS(start - end) > ABS(start - readline->line_index))
    {
        tputs(tgetstr("rc", 0), 0, output);
        ft_putchar(readline->cmd->tmp_line[end]);
         cur_goto(readline, readline->cursor);
    }
    tputs(tgetstr("mr", 0), 0, output);
    tputs(tgetstr("sc", 0), 0, output);
    ft_putchar(readline->cmd->tmp_line[readline->line_index]);
    tputs(tgetstr("rc", 0), 0, output);
    tputs(tgetstr("me", 0), 0, output);
}

void selection(t_readline *readline)
{
    int start;
    int end;
    char buff[5];
    int button;

    start = readline->line_index;
    end = start;
    while (1)
    {
        ft_bzero(buff, 5);
        tputs(tgetstr("sc", 0), 0, output);
        if ((read(0, buff, 4)) > 0)
        {
            button = *((int *)buff);
            if (button == BUTTON_RIGHT)
                cur_right(readline);
            else if (button == BUTTON_LEFT)
                cur_left(readline);
            else if (button == BUTTON_PUP)
                cur_up(readline);
            else if (button == BUTTON_PDOWN)
                cur_down(readline);
            rewrite_select(readline, start, end);
            end = readline->line_index;
        }
    }
}