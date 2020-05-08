#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "MenuButton.h"

class Menu {
 public:
  enum class State { MainMenu, Settings, InGame, InGameMenu, GameOver, Exit };

  enum class Action : uint8_t {
    StartSinglePlayer,
    StartLocalMultiPlayer,
    OpenSettings,
    ExitToDesktop,
    ResumeGame,
    BackToMenu
  };

  const std::string CLICK_SOUND_FILE = "Audio/click.wav";

  State state = State::MainMenu;

  Menu(const sf::Vector2u& window_size);

  void update(const sf::Vector2f& mouse_pos, bool mouse_pressed);

  void draw(sf::RenderTarget& target) const;

  void doAction(const MenuButton* sender, uint8_t action);

  bool isLocalMultiplayer() const { return local_multiplayer; }

 private:
  sf::Font font;
  sf::SoundBuffer sound_buffer;
  sf::Sound sound;

  bool local_multiplayer = false;

  // Buttons for the main menu
  MenuButton main_menu_buttons[4];

  // Buttons for the in game menu
  MenuButton in_game_buttons[3];

  // Buttons for the settings menu
  MenuButton settings_buttons[1];

  // Buttons for the game over screen
  MenuButton game_over_buttons[2];
};
