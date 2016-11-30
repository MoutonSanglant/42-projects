/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blind.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 16:57:28 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/17 17:13:16 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>


#define FMT1 "arguments count: %i\n"
#define FMT2 "program_name: %s\n"
#define P1 argc
#define P2 argv
#define VAL 42
#define PRINT_INT(fmt, int) printf(fmt, int);
#define PRINT_STR(fmt, str) printf(fmt, str);
#define CODE PRINT_INT(FMT1, P1) PRINT_STR(FMT2, P2[0]) return (VAL);
#define BLOCK(x) { x }
#define PARAMS int P1, char **P2
#define START main (PARAMS) BLOCK(CODE)
#define RETURN_T(x) int x

RETURN_T(START)
