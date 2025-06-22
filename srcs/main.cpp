/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 16:54:46 by scraeyme          #+#    #+#             */
/*   Updated: 2025/06/22 17:07:26 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_chess.hpp"
#include "Grid.hpp"
#include <SFML/Window/Event.hpp>
unsigned int WINDOW_WIDTH = 1280;
unsigned int WINDOW_HEIGHT = 720;

int main()
{
	Grid grid;

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "ft_chess");
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			
		}
		window.clear();
		window.display();
	}
}
