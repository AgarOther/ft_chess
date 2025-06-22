/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:15:49 by scraeyme          #+#    #+#             */
/*   Updated: 2025/06/22 17:16:26 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <utility>
#include "../Grid.hpp"

class Utils
{
	public:
		static std::pair<int, int> getPosition(Grid &grid, char piece);
};
