 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelkaid <fbelkaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 12:26:21 by fbelkaid          #+#    #+#             */
/*   Updated: 2024/02/08 13:19:29 by fbelkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include"get_next_line.h"
#include<stdio.h>
#include<fcntl.h>
#include<limits.h>
#include<stdlib.h>
#include<unistd.h>
#define BUFFER_SIZE 5

void *ft_addback(char *str, char *res)
{
    size_t i;

    i=0;  
    if (!str)
	{
		str = malloc(sizeof(char));
		if (!str)
			return (NULL);
		*str = '\0';
	}    
    while(str[i])
    {
        res[i]= str[i];
        i++;
    }
    res[i]='\0';
    return res;
}

size_t check_line(char *str )
{
    size_t plc;

    plc=0;
    while(str[plc++])
    {
        if(str[plc]=='\n')
            return plc;
    }
    return plc;
}

char	*ft_free(char *buf, char **p)
{
    free (buf);
    free(*p);
    *p=NULL;
    return (NULL);
}

size_t ft_strlen(char *str)
{
    size_t i;

    i=0;
    while(*str){
        i++;
        str++;
    }
    return i;
}

char *ft_substr(char *str,size_t from , size_t to)
{
    char *res;
    size_t i;

    i=from;
    res=malloc(to+1 * sizeof(char));
    if (!res)
        return NULL;
    while(i<to)
    {
        res[i]=str[i];
        i++;
    }
    return res;    
}

void ft_edditline(char *str, char **res, size_t plc)
{
    char *bfrline;
    char *aftrline;
    
    bfrline=ft_substr(str,0,plc+2);
    ft_addback(bfrline,res);
    free (bfrline);
    (*res)[ft_strlen(*res)]='\n';
    aftrline=ft_substr(str,plc,(ft_strlen(str)-plc+1));
    ft_addback(aftrline,res);
    free (aftrline);
    
}
char *ft_read(char *str,int fd)
{
    ssize_t bytesread ;
    char *tmp;
    int i;

    bytesread =1 ;
    i=0;
    
    if(!str)
        str =ft_calloc(1,1); 
    tmp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
    if (!tmp)
        return NULL;
    while(bytesread>0)
    {
        bytesread = read(fd,tmp,BUFFER_SIZE);
        if (bytesread == -1 )
        {
            free(tmp);
            return NULL;
        }
        tmp[bytesread]=0;
       str= ft_addback(tmp,str);
    }
    free (tmp);
    return (str);
}

char *get_next_line(int fd)
{
    static char *dep;
    char *buff;
    size_t plc;

    plc=0 ;
   buff = ft_calloc ((BUFFER_SIZE+1 )*sizeof(char));
   if(!buff)
        return NULL;
    if(BUFFER_SIZE <= 0 || fd < 0 || BUFFER_SIZE>INT_MAX)
        return NULL;
    buff= ft_read(buff,fd);
    if(check_line(buff) == 0)
        {   
            ft_addback(buff,&dep);
            free (buff);
        }
    else
        {
            free (dep);
            dep =NULL;
            ft_edditline(buff,&dep,plc);
            
        }
    return (dep);
}

int main ()
{
    int fd ;
    char *res;
    fd = open("txt.txt",O_RDONLY);
    res = get_next_line(fd);
    // while (res != NULL)
    // {
        printf("%s",res);
    //     res=get_next_line(fd);
    // }
    close (fd);
}
