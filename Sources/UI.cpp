#include "UI.h"
UI::UI(std::string id, sf::RenderWindow* window, sf::Font font)
{
  this->id = id;
  policeUI = font;
}
void
UI::Update(sf::RenderWindow* window, float deltaTime)
{
  DrawPlayerHealth(window);
  Score(window);
  if (Player::player->lifeP < 0) {
    loser = true;
  }
  // ShieldFactor
  sf::Text shieldFactor(policeUI);
  shieldFactor.setString("Shield: X" +
                         std::to_string(int(Player::player->shieldFactor)));
  shieldFactor.setPosition(
    { ((shieldFactor.getCharacterSize() * shieldFactor.getString().getSize()) *
       1.5f),
      50.0f });
  window->draw(shieldFactor);
}
void
UI::DrawPlayerHealth(sf::RenderWindow* window)
{
  sf::Text playerHealth(policeUI);
  playerHealth.setString("HP: " + std::to_string(Player::player->lifeP));
  playerHealth.setPosition(
    { ((playerHealth.getCharacterSize() * playerHealth.getString().getSize()) /
       2.0f),
      50.0f });
  window->draw(playerHealth);
}
void
UI::GameOver(sf::RenderWindow* window)
{
  sf::Text gameOver(policeUI);
  gameOver.setString("GAME OVER");
  gameOver.setPosition(
    { WINDOW_WIDTH_PTR / 2.0f -
        ((gameOver.getCharacterSize() * gameOver.getString().getSize()) / 2.0f),
      WINDOW_HEIGHT_PTR / 2.0f });
  window->draw(gameOver);
}
void
UI::Score(sf::RenderWindow* window)
{
  sf::Text textScore(policeUI);
  textScore.setString("Score : " + std::to_string(Player::player->score));
  textScore.setPosition(
    { WINDOW_WIDTH_PTR - (80.0f + (textScore.getCharacterSize() *
                                      textScore.getString().getSize())),
      50.0f });
  window->draw(textScore);
}