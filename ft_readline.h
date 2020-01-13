/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 12:55:33 by yabakhar          #+#    #+#             */
/*   Updated: 2020/01/12 20:06:14 by aait-ihi         ###   ########.fr       */
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
#define BUTTON_SELECT 40899
#define BUTTON_COPY 40899
#define BUTTON_CUT 40899
#define BUTTON_PAST 40899
#define BUTTON_PUP 2117425947
#define BUTTON_PDOWN 2117491483
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
#define GET_LINE_INDEX(p, col) (t_point){p.x % col, p.y + (p.x / col);
typedef struct	s_point
{
	int x;
	int y;
}				t_point;

typedef struct s_cmd_history
{
	char *tmp_line;
	char *line;
	int len;
	int tmp_len;
	struct s_cmd_history *next;
	struct s_cmd_history *prev;
} t_cmd_history;

typedef struct s_line
{
	int *details;
	int index;
	int linecount;
}t_line;

typedef struct s_readline
{
	struct termios config;
	t_cmd_history *cmd;
	t_line line_props;
	t_point o_cursor;
	t_point ov_cursor;
	int cursor;
	int line_index;
	int col;
	int row;
	int win_col;
	int win_row;
} t_readline;

t_readline *g_readline;

/*
**	Cursor Events & Operations
*/
void cur_up(t_readline *readline);
void cur_down(t_readline *readline);
void cur_right(t_readline *readline);
void cur_left(t_readline *readline);
void cur_move_by_word(t_readline *readline, int button);
void to_start_or_end(t_readline *readline, int button);

/*
**	Cursor Helper Functions
*/
void set_virtual_origin(t_readline *readline);
void cur_goto(t_readline *readline, int cursor);
void get_cursor_position(t_readline *readline);
void set_cursor_from_index(t_readline *readline);
/*
**	Events
*/
void end_readline(t_readline *readline, int suit);
void history_previous(t_readline *readline);
void history_next(t_readline *readline);

/*
**	Helpers
*/
int output(int str);
void configure_terminal(t_readline *readline);

/*
**	Line Operations
*/
void	insert_in_line(t_readline *readline, char *str);
void	remove_from_line(t_readline *readline);
void	rewrite_line(t_readline *readline);
int		*get_line_details(t_readline *readline);

/*
**	CMD History
*/
void clean_hsitory(void);
void add_to_history(char *str, int len);
void free_history(void);
void move_in_history(t_readline *readline, int button);
t_cmd_history *get_cmd_history_head(void);

void set_signal(void);
void signal_resize(int sig);
void sig_dispatch(int a);
