#ifndef MENU_OPTIONS_H
#define MENU_OPTIONS_H

#include <functional>
#include "engine.h"
#include "menu.h"
#include "menu_command.h"
#include "options.h"
#include "tetris_renderer.h"

class MenuOptions : public Menu {

public:
  MenuOptions(int width, int height, int nb_displays, TetrisRenderer *renderer, MenuCommand *save_options,
              MenuCommand *close_menu);
  ~MenuOptions() override = default;

  void render() override { renderer->draw(this); }
  int get_nb_options() override { return options.size(); }
  int get_selected_option_index() override { return selected_index; }
  std::vector<std::string> get_options() override { return options; }
  void handle_key(EngineWrapper::Key key) override;
  void set_options(Options::GameOptions options) { game_options = options; }
  Options::GameOptions& get_game_options() { return game_options; }

protected:
  void exec_option() override;

private:
  int nb_index = 0;
  int nb_displays = 0;
  MenuCommand *save_options;
  MenuCommand *close_menu;
  Options::GameOptions game_options;
  void next();
  void previous();
  TetrisRenderer *renderer;
};

#endif //MENU_OPTIONS_H
