/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chess_utils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:08:58 by scraeyme          #+#    #+#             */
/*   Updated: 2025/06/22 21:35:18 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"
#include <cctype>
#include <iostream>
bool Utils::isOpponentPiece(char piece, Player player)
{
	if (piece == '.')
		return (false);
	else if (player == WHITE && std::isupper(piece))
		return (false);
	else if (player == BLACK && !std::isupper(piece))
		return (false);
	return (true);
}

char Utils::getPieceAsChar(Piece piece)
{
	switch (piece)
	{
		case EMPTY:
			return ('.');
		case PAWN:
			return ('p');
		case ROOK:
			return ('r');
		case KNIGHT:
			return ('n');
		case BISHOP:
			return ('b');
		case KING:
			return ('k');
		case QUEEN:
			return ('q');
	}
	return ('X');
}

std::pair<short, short> Utils::getPosition(Grid &grid, char piece)
{
	for (short x = 0; x < 8; x++)
	{
		for (short y = 0; y < 8; y++)
		{
			if (grid.getGrid()[y][x] == piece)
			{
				std::cout << "King pos X: " << x << " Y: " << y << std::endl;
				return (std::pair<short, short>(x, y));
			}
		}
	}
	return (std::pair<short, short>(-1, -1));
}
