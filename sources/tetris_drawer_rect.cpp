
#include <tetris_drawer_rect.h>

constexpr SDL_Color TetrisDrawerRect::textColor;

TetrisDrawerRect::TetrisDrawerRect(TTF_Font *font, SDL_Renderer *renderer) : font(font), renderer(renderer) {
  if (font != nullptr) {
    //Render text
    if (!score_header.loadFromRenderedText(renderer, font, "Score", textColor))
      printf("Failed to render \"score header\" texture!\n");
    if (!level_header.loadFromRenderedText(renderer, font, "Level", textColor))
      printf("Failed to render \"level header\" texture!\n");
  }
}

void TetrisDrawerRect::draw(Tetromino *tetromino) {
  SDL_Rect rect = {tetromino->xpos() * unit_size, tetromino->ypos() * unit_size, unit_size, unit_size};

  for (int i = 0; i < tetromino->matrix_size(); i++) {
    for (int j = 0; j < tetromino->matrix_size(); j++) {
      if (tetromino->is_present(i, j)) {
        rect.x = (tetromino->xpos() + j) * unit_size;
        rect.y = (tetromino->ypos() + i - TOP_OFFSET) * unit_size;
        draw_rect(renderer, &rect, get_tetromino_color(tetromino->get_tile(i, j)));
      }
    }
  }
}

void TetrisDrawerRect::draw(Well *well) {
  SDL_Rect rect = {0, 0, unit_size, unit_size};

  for (int i = TOP_OFFSET; i < Well::HEIGHT; i++) {
    for (int j = 0; j < Well::WIDTH; j++) {
      if (well->get_tile(i, j) > 0) {
        rect.x = (j) * unit_size;
        rect.y = (i - TOP_OFFSET) * unit_size;
        draw_rect(renderer, &rect, get_tetromino_color(well->get_tile(i, j)));
      }
    }
  }
}

void TetrisDrawerRect::draw(ScoreLvl *score) {
  static const int WIDTH = 8;
  static const int HEIGHT = 6;
  static const int BORDER_TILE = 42;
  static const int XPOS = Well::WIDTH * unit_size;
  static const int SCORE_HEADER_XPOS = XPOS + ((WIDTH - 1) * unit_size - score_header.get_width()) / 2;
  static const int SCORE_HEADER_YPOS = unit_size + 5;
  static const int LEVEL_HEADER_XPOS = XPOS + ((WIDTH - 1) * unit_size - level_header.get_width()) / 2;
  static const int LEVEL_HEADER_YPOS = 3 * unit_size + 5;

  static int last_score = -1;
  if (last_score != score->get_score()) {
    last_score = score->get_score();
    this->score.loadFromRenderedText(renderer, font, std::to_string(last_score), textColor);
  }

  static int last_level = -1;
  if (last_level != score->get_level()) {
    last_level = score->get_level();
    level.loadFromRenderedText(renderer, font, std::to_string(last_level), textColor);
  }

  SDL_Rect rect = {0, 0, unit_size, unit_size};
  for (int i = 0; i < WIDTH; i++) {
    rect.x = XPOS + i * unit_size;
    draw_rect(renderer, &rect, get_tetromino_color(BORDER_TILE));
  }

  for (int i = 1; i < HEIGHT - 1; i++) {
    rect.y = i * unit_size;
    draw_rect(renderer, &rect, get_tetromino_color(BORDER_TILE));
  }

  rect.y += unit_size;
  for (int i = 0; i < WIDTH; i++) {
    rect.x = XPOS + i * unit_size;
    draw_rect(renderer, &rect, get_tetromino_color(BORDER_TILE));
  }

  score_header.render(renderer, SCORE_HEADER_XPOS, SCORE_HEADER_YPOS);
  level_header.render(renderer, LEVEL_HEADER_XPOS, LEVEL_HEADER_YPOS);
  this->score.render(renderer,
                     XPOS + ((WIDTH - 1) * unit_size - this->score.get_width()) / 2,
                     SCORE_HEADER_YPOS + unit_size);
  level.render(renderer, XPOS + ((WIDTH - 1) * unit_size - level.get_width()) / 2, LEVEL_HEADER_YPOS + unit_size);
}

Color TetrisDrawerRect::get_tetromino_color(int tile) {
  switch (tile) {
    case 1:
    case 2:
    case 3        :return {49, 199, 239};
    case 4        :return {247, 211, 8};
    case 5        :return {173, 77, 156};
    case 6        :return {66, 182, 66};
    case 7        :return {239, 32, 41};
    case 8        :return {90, 101, 173};
    case 9        :return {239, 121, 33};
    case 42       :return {127, 64, 20};
    default       :return {255, 255, 255, 0};
  }
}

void TetrisDrawerRect::draw_rect(SDL_Renderer *renderer, SDL_Rect *rect, Color color) {
  SDL_SetRenderDrawColor(renderer, color.red(), color.green(), color.blue(), color.alpha());
  SDL_RenderFillRect(renderer, rect);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // the rect border color (solid black)
  SDL_RenderDrawRect(renderer, rect);
}
