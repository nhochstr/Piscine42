/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhochstr <nhochstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 14:29:27 by nhochstr          #+#    #+#             */
/*   Updated: 2019/07/20 23:20:05 by nhochstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while(str[i] != '\0')
		i++;
	return i;
}

int	compteur_chiffre(int nbr)
{
	int i;

	i = 0;
	while (nbr > 0)
	{
		nbr = nbr / 10;
		i++;
	}
	return (i);
}

void	ft_rev_tab(char *tab, int size)
{
	char	c;
	int		i;

	i = 0;
	if (tab[0] == '-')
		i = 1;
	size--;
	while (i < size)
	{
		c = tab[i];
		tab[i] = tab[size];
		tab[size] = c;
		i++;
		size--;
	}
}

char	*ft_itoa(int chf)
{
	char	*str;
	int		i;
	int		size;

	size = compteur_chiffre(chf);
	i = 0;
	if(!(str = malloc(sizeof(char) * (size + 1))))
		return (0);
	while (chf > 9)
	{
		str[i] = (chf % 10) + 48;
		chf = chf / 10;
		i++;
	}
	str[i] = chf + 48;
	str[i + 1] = '\0';
	ft_rev_tab(str, i + 1);
	return (str);
}

void	ft_print(int chf)
{
	if (chf > 0)
	{
		char 	*str;
		int		i;
	
		i = 0;
		str = ft_itoa(chf);
		while (str[i] != '\0')
		{
			write(1, &str[i], 1);
			i++;
		}
		write(1, " ", 1);
	}
}

void  ft_affiche_centaine(int cent, int centaine, int dix, int u)
{
	ft_print(cent);
	ft_print(centaine);
	ft_print(dix);
	ft_print(u);
}

int	ft_iterative_power(int nb, int power)
{
	int	i;
	int	j;

	j = 1;
	i = 1;
	if (power < 0)
		return (0);
	if (nb < 0 && (power % 2) != 0)
	{
		j = -1;
		nb = nb * -1;
	}
	while (power != 0)
	{
		i = i * nb;
		power--;
	}
	return (i * j);
}

int	ft_verif_blocs(int nblocs)
{
	if (nblocs > 1)
	{
		if ( ft_iterative_power(1000, (nblocs - 1)) == 0) // puissance
			return (1);
	}
	else
	{
		if ( ft_iterative_power(100, (nblocs - 1)) == 0) // puissance
			return (1);
	}
	return (0);
}

void ft_sep_centaine(int nbr)
{
	int cent;
	int dix;
	int u;
	int centaine;

	cent = 0;
	centaine = 0;
	dix = 0;
	u = 0;
	if (nbr > 99)
		centaine = 100;
	if (nbr > 199)
		cent = nbr / 100;
	nbr = nbr % 100;
	if (nbr < 20 && nbr > 9)
		dix = nbr;
	else if (nbr < 10)
	{
		dix = 0;
		u = nbr;
	}
	else
	{
		u = nbr % 10;
		dix = nbr - u;
	}
	ft_affiche_centaine(cent, centaine, dix, u);
}

int	ft_atoi(char *str)
{
	int	i;
	int	j;
	int s;

	s = 1;
	i = 0;
	j = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v' || str[i] == '\f'
		|| str[i] == '\r')
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s = s * -1;
		i++;
	}
	while (str[i] > 47 && str[i] < 58)
	{
		j = j * 10 + (str[i] - 48);
		i++;
	}
	return (j * s);
}

void	ft_separateur(char *str, int size, int blocs)
{
	char tab[3];
	int i;
	int j;
	(void)blocs;
	i = 0;
	if (size < 3)
	{
		while (i <  3 - size)
		{
			tab[i] = '0';
			i++; 
		}
	}
	j = 0;
	while (i < 3)
	{
		tab[i] = str[j];
		i++;
		j++;
	}
	ft_sep_centaine(ft_atoi(tab));
	if (blocs > 0)
		ft_print(ft_iterative_power(1000, (blocs)));
}

void	ft_change_nbr(char *str)
{
	int	size;
	int	nblocs;
	int init;
	int j;

	init = 3;
	size = ft_strlen(str);
	nblocs = size / 3;
	if (size % 3)	
		nblocs++;
	if (size % 3)	
		init = size % 3;
	if (ft_verif_blocs(nblocs))
		return ;
	j = 0;
	while (nblocs-- > 0)
	{
		ft_separateur(&str[j], init, nblocs);
		j = j + init;
		init = 3;
	}
}

int main(int ac, char **av)
{

	(void)ac;
	ft_change_nbr(av[1]);
	//printf("nbr de chiffres: %d\n", compteur_chiffre(atoi(av[1])));
	//ft_compeur_centaine(atoi(av[1]));
	return (0);
}