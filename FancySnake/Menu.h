#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "MenuButton.h"
#include "SettingsButton.h"
#include "ActionButton.h"

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

  Menu(const sf::Vector2u& window_size, Settings& settings);
  ~Menu();

  void update(const sf::Vector2f& mouse_pos, bool mouse_pressed);

  void draw(sf::RenderTarget& target) const;

  void doAction(uint8_t action);

  bool isLocalMultiplayer() const { return local_multiplayer; }

 private:
  sf::Font font;
  sf::SoundBuffer sound_buffer;
  sf::Sound sound;

  bool local_multiplayer = false;

  // Buttons for the main menu
  std::vector<MenuButton*> main_menu_buttons;

  // Buttons for the in game menu
  std::vector<MenuButton*> in_game_buttons;

  // Buttons for the settings menu
  std::vector<MenuButton*> settings_buttons;

  // Buttons for the game over screen
  std::vector<MenuButton*> game_over_buttons;
};
