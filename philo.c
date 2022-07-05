/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouyer <jbouyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:04:12 by jbouyer           #+#    #+#             */
/*   Updated: 2022/07/05 16:12:44 by jbouyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"

// attention la fonction u_sleep est en nano secondes.

int main(int argc, char **argv)
{
    t_global    *params;
    if (argc < 5 || argc > 6)
        return (printf("Arguments incorrects"));
    //ici regarder lsi les arguments sont valides.et envoyer a parsing
    params = initialize_dinner(char **argv, t_global *params);
    //creer une premiere structure et stocker les trucs dedans>
    //renvoie a une fonction a va initiliser la globale et faire un malloc. 
}