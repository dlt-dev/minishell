#include "minishell.h"

char *delete_new_line(char *line)
{
    char *str;
    t_cb buffer;
    int i;

    i = 0;
    init_chunk_buffer(&buffer, 20, 2);
    while(line[i] != '\0')
    {
        if(line[i] != '\n')
        {
            if(cb_append_char(&buffer, line[i]) == ERROR)
                return(free_chunk_buffer(&buffer), NULL);
        }
        i++;
    }
    str = fusion_all_chunk(&buffer);
    if(str == NULL)
        return(NULL);
    return(str);
}


int non_interactive_shell(t_shell *shell)
{
    char *tmp;
    tmp = get_next_line(0);
    if(tmp == NULL)
        return(ERROR);
    shell->rd_line = delete_new_line(tmp);
    if(shell->rd_line == NULL)
        return(free(tmp), ERROR);
    free(tmp);
    return(0);
}