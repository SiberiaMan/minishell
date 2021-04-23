#include "history.h"

void sig_slash(int signum)
{
    (void)(signum);
}

void sig_c(int signum)
{
    write(1, "\n", 1);
    tputs("minishell=):", 1, ft_putint);
}

char *backspace(char *line)
{
    size_t i;
    char *new;

    i = ft_strlen(line);
    if (i > 1)
    {
        if(!(new = ft_calloc(i-1, 1)))
            return(NULL);
        new = ft_memcpy(new, line, i-2);
        return(new);
    }
    return(NULL);
}

int main(int argc, char const **argv)
{
    (void)(argv);
    (void)(argc);
    int l;
    size_t i;
    char str[2000];
    struct termios term;
    char *term_name = "xterm-256color"; // env | grep TERM
    char *line;
    t_list *history;
    char *history_line;
    char *tmp;
    t_list *current_history;
    int cursor = 0;
    int symbols = 0;


    signal(SIGQUIT, sig_slash); // ctrl + slash
    signal(SIGINT, sig_c); //ctrl + C
    history = NULL;
    if(!(line = malloc(sizeof(char) * 1)))
        return(-1);
    line[0] = '\0';
    tcgetattr(0, &term); //получить атрибут терминала
    term.c_lflag &= ~(ECHO); //отключает отображение набираемых символов при 
    term.c_lflag &= ~(ICANON); //отключает канонический режим терминала
    //read завершается нажатием enter, это надо отключить
    term.c_cc[VTIME] = 0;//сколько в секундах read будет ожидать перед тем как отключиться, 0 - завершится тут же
    term.c_cc[VMIN] = 1;//минимальное кол-во символов, которое считает
    tcsetattr(0, TCSANOW, &term); //установить атрибут терминала
    tgetent(0, term_name); //(проверять на возвращаемые значения) термкап достает данные по нашему терминалу
    ft_putstr("minishell=):");
    tputs(cursor_right, 1, ft_putint);
    tputs(save_cursor, 1, ft_putint);
    tputs(cursor_left, 1, ft_putint);
    while (1/*strcmp(str, "\4")*/) //пока не нажали CTRL+D
    {
        // tputs(save_cursor, 1, ft_putint); //сохранит положение курсора
            l = read(0, str, 100);
            str[l] = 0;
            //сtrl+d это пустой символ, т.e. '\0'
            if(!strcmp(str, "\e[D"))
            {
                //стрелка влевo
            }
            if(!strcmp(str, "\n"))
            {
                write(1, "\n", 1);
                tputs("minishell=):", 1, ft_putint);
                tputs(cursor_right, 1, ft_putint);
                tputs(save_cursor, 1, ft_putint);
                tputs(cursor_left, 1, ft_putint);
                i = ft_strlen(line);
                //printf("i = %zu\n", i);
                if(!(history_line = ft_calloc(i+1, sizeof(char))))
                    return(-1);
                ft_memcpy(history_line, line, i);
                if (history_line[0] != '\0')
                {
                    lst_create_add(&history, history_line);
                    //включить нормальный терминал!!!!!!!!!!!!!!!
                    //МИША, ТЫ СЕБЕ ЗАБИРАЙ history_line в парсер
                }
                free(line);
                if(!(line = malloc(sizeof(char) * 1)))
                    return(-1);
                line[0] = '\0';
            }
            if (!strcmp(str, "\e[A"))
            {
                //up
                tputs(restore_cursor, 1, ft_putint);
                tputs(cursor_left, 1, ft_putint);
                if(history)
                {
                    tputs(delete_line, 1, ft_putint);
                    tputs("minishell=):", 1, ft_putint);
                    current_history = history;
                    line = history->line;
                    current_history = history;
                    ft_putstr(line);
                    if(history->prev)
                        history = history->prev;
                }
            }
            else if (!strcmp(str, "\e[B"))
            {
                //down
                tputs(restore_cursor, 1, ft_putint);
                tputs(cursor_left, 1, ft_putint);
                if(history)
                {
                    if(history->next)
                        history=history->next;
                    tputs(delete_line, 1, ft_putint);
                    tputs("minishell=):", 1, ft_putint);
                    current_history = history;
                    line = history->line;
                    current_history = history;
                    ft_putstr(line);
                }
            }
            else if (strcmp(str, "\n"))
            {
                symbols = write(1, str, l);
                if(current_history)
                    current_history->line = ft_strjoin(current_history->line, str);
                else
                    line = ft_strjoin(line, str);
            }
            if (!strcmp(str, "\177"))
            {
                //backspace
                tputs(delete_line, 1, ft_putint);
                tputs("minishell=):", 1, ft_putint);
                if((tmp = backspace(line)))
                {
                    ft_putstr(tmp);
                    free(line);
                    line = tmp;
                    if (current_history)
                    {
                        free(current_history->line);
                        current_history->line = tmp;
                    }
                }
            }
            if(!strcmp(str, "\4"))
            {
                write(1, " exit\n", 6);
                exit(0);
            }
    }
    write(1, "\n", 1);  
    return(0);
}