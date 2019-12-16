/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 12:55:33 by yabakhar          #+#    #+#             */
/*   Updated: 2019/12/16 03:19:00 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <curses.h>
#include <term.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "libft/includes/libft.h"
#include <sys/ioctl.h>
#define BUTTON_UP 4283163
#define BUTTON_DOWN 4348699
#define BUTTON_RIGHT 4414235
#define BUTTON_ALT_RIGHT 26139
#define BUTTON_LEFT 4479771
#define BUTTON_ALT_LEFT 25115
#define BUTTON_SPACE 32
#define BUTTON_ENTER 10
#define BUTTON_DEL 127
#define BUTTON_DEL2 2117294875
#define BUTTON_END 4610843
#define BUTTON_HOME 4741915
#define BUTTON_R 114

typedef struct	s_cmd_history
{
	char *line;
	int len;
	struct s_cmd_history *next;
	struct s_cmd_history *prev;
}				t_cmd_history;

typedef struct s_readline
{
	struct termios config;
	t_cmd_history *current_cmd_history;
	char *line;
	char *tmp_line;
	int history_index;
	int line_len;
	int tmp_len;
	int col;
	int row;
	int win_col;
	int win_row;
	int cursor;
	int origin_cursor;
} t_readline;

t_readline *g_readline;

/*
**	Cursor Events & Operations
*/
void			cur_up(t_readline *readline);
void			cur_down(t_readline *readline);
void			cur_right(t_readline *readline);
void			cur_left(t_readline *readline);
void			cur_move_by_word(t_readline *readline, int button);
void			cur_goto(t_readline *readline, int cursor);
void			get_cursor_position(t_readline *readline);

/*
**	Events
*/
void end_readline(t_readline *readline);
void history_previous(t_readline *readline);
void history_next(t_readline *readline);

/*
**	Helpers
*/
int				output(int str);
void			configure_terminal(t_readline *readline);

/*
**	Line Operations
*/
void			insert_in_line(t_readline *readline, char *str);
void			remove_from_line(t_readline *readline);
void			rewrite_line(t_readline *readline);

/*
**	CMD History
*/
void			add_to_history(char *str, int len);
void			free_history(void);
t_cmd_history	*get_cmd_history_head(void);

void			set_signal(void);
void		signal_resize(int sig);
void sig_dispatch(int a);
