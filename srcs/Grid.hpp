/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Grid.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 16:58:21 by scraeyme          #+#    #+#             */
/*   Updated: 2025/06/22 17:28:09 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <utility>

enum Player
{
	NONE,
	WHITE,
	BLACK
};

constexpr char startingGrid[8][8] = {
            {'r','n','b','q','k','b','n','r'},
            {'p','p','p','p','p','p','p','p'},
            {'.','.','.','.','.','.','.','.'},
            {'.','.','.','.','.','.','.','.'},
            {'.','.','.','.','.','.','.','.'},
            {'.','.','.','.','.','.','.','.'},
            {'P','P','P','P','P','P','P','P'},
            {'R','N','B','Q','K','B','N','R'}
        };

constexpr std::pair<int, int> knightRadius[8] = {
	{-1, -2},
	{ 1, -2},
	{-1,  2},
	{ 1,  2},
	{ 2,  1},
	{ 2, -1},
	{-2,  1},
	{-2, -1},
};

class Grid
{
	public:
		Grid();
		~Grid();

		Player hasCheck();
		char (*getGrid())[8];
		char getPieceAt(int x, int y);
	private:
		char _grid[8][8];
};
