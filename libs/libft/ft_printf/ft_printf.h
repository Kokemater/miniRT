/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:16:50 by dmoraled          #+#    #+#             */
/*   Updated: 2024/11/18 18:16:58 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

int	print_str(const char *str);
int	print_char(char c);
int	print_num(int num);
int	print_unum(unsigned int num);
int	print_hex_lower(unsigned long num);
int	print_hex_upper(unsigned long num);
int	print_ptr(void *ptr);

int	ft_printf(const char *fmt, ...);

#endif
