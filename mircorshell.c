#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

void err(char *str)
{
    while(*str)
    write ( 2, str++, 1);
}

int cd(char **av, int i)
{
    if (i !=2)
    return err("error: cd: bad argiment"),1;
    if (chdir(av[1] < 0))
    return err("error: cd :cannot change directory to "),err(av[1]),err("\n"),1;
}


int main(int ac, char **av, char **envp)
{
    (void)ac;
    int i = 0, status = 0;
    while (av[i])
    {
        av +=i + 1;;
        i = 0;
        while(av[i] && strcmp(av[i], "|") &&(av[i],";"))
        i++;
        if(i)
        status = exec(av, i, envp);
    }
    return status;

    }