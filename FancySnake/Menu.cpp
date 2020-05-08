#include "Menu.h"

#include <iostream>

Menu::Menu(const sf::Vector2u& window_size) {
  // Font
  font.loadFromFile("SlimSansSerif.ttf");

  // Sound
  sound_buffer.loadFromFile(CLICK_SOUND_FILE);
  sound.setBuffer(sound_buffer);

  // Buttons
  sf::Vector2f size(window_size.x * .5f, window_size.y * .1f);
  sf::Vector2f start_pos(window_size.x * .5f, window_size.y * .25f);

  //// Main menu buttons
  // Start singleplayer game
  main_menu_buttons[0] =
      MenuButton(sf::FloatRect(start_pos, size), std::string("Singleplayer"),
                 font, this, (uint8_t)Action::StartSinglePlayer);
  // Start local multiplayer game
  start_pos.y += size.y * 2.f;
  main_menu_buttons[1] =
      MenuButton(sf::FloatRect(start_pos, size), std::string("Multiplayer"),
                 font, this, (uint8_t)Action::StartLocalMultiPlayer);
  // Open settings
  start_pos.y += size.y * 2.f;
  main_menu_buttons[2] =
      MenuButton(sf::FloatRect(start_pos, size), std::string("Settings"), font,
                 this, (uint8_t)Action::OpenSettings);
  // Exit to desktop
  start_pos.y += size.y * 2.f;
  main_menu_buttons[3] =
      MenuButton(sf::FloatRect(start_pos, size), std::string("Desktop"), font,
                 this, (uint8_t)Action::ExitToDesktop);
  start_pos.y = window_size.y * .25f;

  //// In game menu buttons
  // Resume
  in_game_buttons[0] =
      MenuButton(sf::FloatRect(start_pos, size), std::string("Resume"), font,
                 this, (uint8_t)Action::ResumeGame);
  // Back to main menu
  start_pos.y += size.y * 2.f;
  in_game_buttons[1] =
      MenuButton(sf::FloatRect(start_pos, size), std::string("Main Menu"), font,
                 this, (uint8_t)Action::BackToMenu);
  // Exit to desktop
  start_pos.y += size.y * 2.f;
  in_game_buttons[2] =
      MenuButton(sf::FloatRect(start_pos, size), std::string("Desktop"), font,
                 this, (uint8_t)Action::ExitToDesktop);
  start_pos.y = window_size.y * .25f;

  //// Settings buttons
  // Back to main menu
  settings_buttons[0] =
      MenuButton(sf::FloatRect(start_pos, size), std::string("Main Menu"), font,
                 this, (uint8_t)Action::BackToMenu);
  start_pos.y = window_size.y * .25f;

  //// Game over screen buttons
  // Back to main menu
  game_over_buttons[0] =
      MenuButton(sf::FloatRect(start_pos, size), std::string("Main Menu"), font,
                 this, (uint8_t)Action::BackToMenu);
  // Exit to desktop
  start_pos.y += size.y * 2.f;
  game_over_buttons[1] =
      MenuButton(sf::FloatRect(start_pos, size), std::string("Desktop"), font,
                 this, (uint8_t)Action::ExitToDesktop);
  start_pos.y = window_size.y * .25f;
}

void Menu::update(const sf::Vector2f& mouse_pos, bool mouse_pressed) {
  switch (state) {
    case State::InGame:
      return;

    case State::MainMenu:
      for (MenuButton& b : main_menu_buttons) {
        b.update(mouse_pos, mouse_pressed);
      }
      break;

    case State::InGameMenu:
      for (MenuButton& b : in_game_buttons) {
        b.update(mouse_pos, mouse_pressed);
      }
      break;

    case State::Settings:
      for (MenuButton& b : settings_buttons) {
        b.update(mouse_pos, mouse_pressed);
      }
      break;

    case State::GameOver:
      for (MenuButton& b : game_over_buttons) {
        b.update(mouse_pos, mouse_pressed);
      }
      break;
  }
}

void Menu::draw(sf::RenderTarget& target) const {
  switch (state) {
    case State::InGame:
      return;

    case State::MainMenu:
      for (const MenuButton& b : main_menu_buttons) {
        b.draw(target);
      }
      break;

    case State::InGameMenu:
      for (const MenuButton& b : in_game_buttons) {
        b.draw(target);
      }
      break;

    case State::Settings:
      for (const MenuButton& b : settings_buttons) {
        b.draw(target);
      }
      break;

    case State::GameOver:
      for (const MenuButton& b : game_over_buttons) {
        b.draw(target);
      }
      break;
  }
}

void Menu::doAction(const MenuButton* sender, uint8_t action) {
  sound.play();
  switch ((Action)action) {
    case Action::StartSinglePlayer:
      state = State::InGame;
      break;

    case Action::StartLocalMultiPlayer:
      state = State::InGame;
      break;

    case Action::OpenSettings:
      state = State::Settings;
      break;

    case Action::ExitToDesktop:
      state = State::Exit;
      break;

    case Action::ResumeGame:
      state = State::InGame;
      break;

    case Action::BackToMenu:
      state = State::MainMenu;
      break;
  }
}
