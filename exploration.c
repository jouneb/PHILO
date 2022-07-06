/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exploration.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouyer <jbouyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 11:48:48 by jbouyer           #+#    #+#             */
/*   Updated: 2022/07/06 17:08:45 by jbouyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//https://sites.uclouvain.be/SystInfo/notes/Theorie/Threads/coordination.html

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t wait_me;

void   *test(void *lol)
{
    pthread_mutex_lock(&wait_me);
    if (lol == "a")
        printf("Kant se promene\n");
    if (lol == "b")
        printf("Kirkegaard pense\n");
    if (lol == "c")
        printf("Nietzsche dort\n");
    pthread_mutex_unlock(&wait_me);
    return (NULL);
}

int main()
{
    pthread_t   Kant;
    pthread_t   Kierkegaard;
    pthread_t   Nietzsche;
    char *str;
    char *lol;
    char *tmp;

    str = "b";
    lol = "a";
    tmp = "c";
    pthread_mutex_init(&wait_me, NULL);
    pthread_create(&Kant, NULL, test, lol);
    pthread_create(&Kierkegaard, NULL, test, str);
    pthread_create(&Nietzsche, NULL, test, tmp);
    pthread_join(Kant, NULL);
    pthread_join(Kierkegaard, NULL);
    pthread_join(Nietzsche, NULL);
    pthread_mutex_destroy(&wait_me);
    return (0);

}

