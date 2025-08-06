#include <SFML/Graphics.hpp>
#include "GameLogic.h"




void HandleWindowEvents(sf::RenderWindow& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		// Close window if close button or Escape key pressed
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
		if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
		{
			window.close();
		}
	}
}

int main()
{
    // Инициализация генератора случайных чисел
    unsigned int seed = (unsigned int)time(nullptr);
    srand(seed);

    // Создание окна
    sf::RenderWindow window(
        sf::VideoMode(settings::SCREEN_WIDTH, settings::SCREEN_HEGHT),
        "AppleGame",
        sf::Style::Close
    );
    window.setFramerateLimit(60);

    // Инициализация состояния игры
    init::GameState gameState;
    init::InitGame(gameState);
    init::InitMainMenu(gameState);  // Инициализация меню

    // Игровые часы
    sf::Clock gameClock;
    sf::Time lastTime = gameClock.getElapsedTime();

    // Главный игровой цикл
    while (window.isOpen())
    {
        // Обработка событий окна
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // Обработка ESC для возврата в меню из любых состояний
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                if (gameState.currentState == init::GameState::State::Gameplay ||
                    gameState.currentState == init::GameState::State::Leaderboard)
                {
                    gameState.currentState = init::GameState::State::MainMenu;
                }
            }
        }

        // Расчет времени между кадрами
        sf::Time currentTime = gameClock.getElapsedTime();
        float timeDelta = currentTime.asSeconds() - lastTime.asSeconds();
        lastTime = currentTime;

        // Очистка экрана
        window.clear();

        // Обработка разных состояний игры
        switch (gameState.currentState)
        {
        case init::GameState::State::MainMenu:
        {
            // Обработка ввода в меню
            logic::HandleMainMenuInput(gameState, window);

            // Отрисовка меню
            draw::DrawMainMenu(gameState, window);

            // Подсказка управления
            sf::Text hint;
            hint.setString("Use UP/DOWN arrows to navigate, ENTER to select");
            hint.setFont(gameState.font);
            hint.setCharacterSize(20);
            hint.setPosition(50.f, settings::SCREEN_HEGHT - 50.f);
            hint.setFillColor(sf::Color(150, 150, 150));
            window.draw(hint);
            break;
        }

        case init::GameState::State::Gameplay:
        {
            // Обработка игрового ввода
            logic::HandleInput(gameState);

            // Обновление игровой логики
            logic::UpdateGame(gameState, timeDelta);

            // Отрисовка игры
            draw::DrawGame(gameState, window);
            break;
        }

        case init::GameState::State::Settings:
        {
            logic::HandleSettingsInput(gameState);
            draw::DrawSettings(gameState, window);
            break;
        }

        case init::GameState::State::Leaderboard:
        {
            // Отрисовка таблицы лидеров
            draw::DrawLeaderboard(gameState, window);

            // Подсказка возврата
            sf::Text hint;
            hint.setString("Press ESC to return to menu");
            hint.setFont(gameState.font);
            hint.setCharacterSize(20);
            hint.setPosition(settings::SCREEN_WIDTH / 2.f - 100.f, settings::SCREEN_HEGHT - 50.f);
            hint.setFillColor(sf::Color::White);
            window.draw(hint);
            break;
        }
        }

        // Отображение на экране
        window.display();
    }

    return 0;
}
