/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chess_utils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:08:58 by scraeyme          #+#    #+#             */
/*   Updated: 2025/06/22 17:16:23 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"

std::pair<int, int> Utils::getPosition(Grid &grid, char piece)
{
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			if (grid.getGrid()[y][x] == piece)
				return (std::pair<int, int>(x, y));
		}
	}
	return (std::pair<int, int>(-1, -1));
}
