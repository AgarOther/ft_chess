/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:15:49 by scraeyme          #+#    #+#             */
/*   Updated: 2025/06/23 20:06:52 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <utility>
#include "../Grid.hpp"

#define PIECE(piece, player) (Utils::getPieceAsChar(piece) - ((player) == WHITE ? 32 : 0))
#define INVERT_PLAYER(player) ((player) == WHITE ? BLACK : WHITE)

class Utils
{
	public:
		static std::pair<short, short> getPosition(Grid &grid, Piece piece, Player player);
		static char getPieceAsChar(Piece piece);
		static bool isOpponentPiece(char piece, Player player);
		static Piece getPiece(char piece);
};
