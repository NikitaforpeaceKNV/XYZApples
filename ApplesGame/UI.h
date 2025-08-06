#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include <string>

namespace ui
{
	struct Leaderboard {
		sf::Text position_on_leaderboard;
		sf::Text nickName;
		sf::Text scores;
		int scores_count = 0;
	};

	struct UIState
	{
		bool isGameOverTextVisible = false;

		sf::Text scoreText;
		sf::Text inputHintText;
		sf::Text gameOverText;
		sf::Text gameSettings;
		std::vector<Leaderboard> leaderboard;


		void LeaderBoardInit(std::vector<Leaderboard>& leaderboard)
		{
			leaderboard.resize(10);
			int j = 0;

			//random name creating
			for (int i = 0; i < 9; ++i)
			{
				while (j < 13)
				{
					char c = rand()%255;

					if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
					{
						if (leaderboard[i].nickName.getString().isEmpty())
						{
							leaderboard[i].nickName.setString(c);
						}
						else 
						{
							leaderboard[i].nickName.setString(leaderboard[i].nickName.getString() + c);
						}
						++j;
					}
				}
				j = 0;
			}

			//random scores filling
			for (int i = 0; i < 9; ++i)
			{
				leaderboard[i].scores_count = rand() % 20;
				leaderboard[i].scores.setString(std::to_string(leaderboard[i].scores_count));
			}
			leaderboard.back().nickName.setString("Player");
		}
	};
}
