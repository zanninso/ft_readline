/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 10:41:21 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/01/15 03:15:21 by aait-ihi         ###   ########.fr       */
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

int key_handel(t_readline *readline,int s,int e)
{
    char buff[5];
    int button;
    
    ft_bzero(buff, 5);
    tputs(tgetstr("sc", 0), 0, output);
    if ((read(0, buff, 4)) > 0)
    {
        button = *((int *)buff);
        if (button == BUTTON_RIGHT)
            cur_right(readline);
        else if (button == BUTTON_LEFT)
            cur_left(readline);
        else if (button == BUTTON_COPY)
        {
            if(s > e)
                ft_swap(&s, &e);
            readline->to_past = ft_strsub(readline->cmd->tmp_line, s, s - e);
            return(0);
        }
        else if (button == BUTTON_ESC)
            return(0);
    }
    return (1);
}

void selection(t_readline *readline)
{
    int start;
    int end;
    int loop;

    start = readline->line_index;
    end = start;
    loop = 1;
    while (loop)
    {
        loop = key_handel(readline, start, end);
        rewrite_select(readline, start, end);
        end = readline->line_index;
    }
    rewrite_line(readline);
}