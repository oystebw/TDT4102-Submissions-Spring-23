#include "Gameoflife.h"

#include <algorithm>
#include <cassert>
#include <exception>
#include <fstream>
#include <iostream>
#include <vector>

#include "AnimationWindow.h"

using namespace TDT4102;

Cell::Cell(Point pos, int size)
    : state(State::Dead), pos{pos}, size{size} {}

// TASK
int Cell::get_value() const {
    // BEGIN: C1

    return static_cast<int>(state);

    // END: C1
}

// TASK
void Cell::kill() {
    // BEGIN: C3
    state = State::Dead;
    // END: C3
}

// TASK
void Cell::resurrect() {
    // BEGIN: C4
    state = State::Live;
    // END: C4
}

// TASK
void Cell::set_state(char c) {
    // BEGIN: C5
    assert(c == '.' || c == '#');

    state = char_to_state.at(c);
    
    // END: C5
}

// TASK
std::istream& operator>>(std::istream& is, Cell& cell) {
    // BEGIN: C6
    char state;
    is >> state;

    cell.set_state(state);
    return is;
    // END: C6
}

// TASK
bool Cell::is_alive() const {
    // BEGIN: C7
    return state == State::Live;
    // END: C7
}

// TASK
char Cell::as_char() const {
    // BEGIN: C8
    
    return chars[get_value()];

    // END: C8
}

// TASK
Gameoflife::Gameoflife(int x_cells,
                       int y_cells,
                       const std::string& window_title)
    : AnimationWindow{50, 50, x_cells * cell_size + 5 * button_width + 2 * margin,
                      y_cells * cell_size + 2 * margin,
                      window_title},
      x_cells{x_cells},
      y_cells{y_cells},

      step_btn{{x_cells * cell_size + 2 * margin + 3 * button_width, 3 * margin}, button_width, button_height, "Step"},
      steps_input{{x_cells * cell_size + 2 * margin + button_width, 3 * margin}, button_width * 2, button_height, "Number of steps"},
      filename_input{{x_cells * cell_size + 2 * margin + button_width, button_height + 5 * margin}, button_width * 2, button_height, "Filename"},
      load_btn{{x_cells * cell_size + 2 * margin + 3 * button_width, button_height + 5 * margin}, button_width, button_height, "Load"},
      save_btn{{x_cells * cell_size + 2 * margin + 3 * button_width, 2 * button_height + 7 * margin}, button_width, button_height, "Save"},
      play_pause_btn{{x_cells * cell_size + margin + button_width, 2 * button_height + 7 * margin}, button_width * 2, button_height, "Play/Pause"} {
    // Provided (asserts and attach() calls)
    // Asserts are here to make sure any unintended changes to
    // compile-time constants makes the exercise less hard to debug.
    assert(x_cells > 0);
    assert(y_cells > 0);
    assert(button_width > 0);
    assert(margin > 0);

    step_btn.setCallback(std::bind(&Gameoflife::step_pressed, this));
    add(step_btn);
    play_pause_btn.setCallback(std::bind(&Gameoflife::play_pause, this));
    add(play_pause_btn);
    load_btn.setCallback(std::bind(&Gameoflife::load_state, this));
    add(load_btn);
    save_btn.setCallback(std::bind(&Gameoflife::save_state, this));
    add(save_btn);

    add(filename_input);
    add(steps_input);

    // BEGIN: G1
    for(int row{0}; row < y_cells; ++row){
        get_scratch_grid().emplace_back();
        for(int col{0}; col < x_cells; ++col){
            get_scratch_grid().back().emplace_back(Point{col, row}, cell_size);
        }
    }
    get_current_grid() = get_scratch_grid();
    load("glider.cgol");
    // END: G1
}

// TASK
std::istream& operator>>(std::istream& is, Gameoflife& gameoflife) {
    // BEGIN: G2
    for(auto& row: gameoflife.get_scratch_grid()){
        for(auto&& cell: row){
            is >> cell;
        }
    }
    gameoflife.get_current_grid() = gameoflife.get_scratch_grid();
    return is;
    // END: G2
}

// TASK
void Gameoflife::load(const std::string& filename) {
    // BEGIN: G3
    std::ifstream file(filename);
    if(!file){
        std::cout << "File not found" << '\n';
        return;
    }
    file >> *this;
    file.close();
    step();
    // END: G3
}

// TASK

void Gameoflife::drawState() {
    // BEGIN: drawState() C2
    TDT4102::Color color;
    for(int row{0}; row < y_cells; ++row){
        for(int col{0}; col < x_cells; ++col){
            int x = col * cell_size + margin;
            int y = row * cell_size + margin;
            if(get_current_grid()[row][col].is_alive()){
                color = TDT4102::Color::white;
            }
            else{
                color = TDT4102::Color::black;
            }
            draw_rectangle({x, y}, cell_size, cell_size, color, TDT4102::Color::black);
        }
    }
    next_frame();
    // END: drawState() C2
}

void Gameoflife::step() {
    // BEGIN: G4
    int alive;
    int x;
    int y;

    for(int row{0}; row < y_cells; ++row){
        for(int col{0}; col < x_cells; ++col){
            alive = 0;

            for(int rowOffset{-1}; rowOffset < 2; ++rowOffset){
                for(int colOffset{-1}; colOffset < 2; ++colOffset){
                    if((rowOffset | colOffset) == 0){
                        continue;
                    }

                    x = col + colOffset;
                    if(x == -1){
                        x = x_cells - 1;
                    }
                    if(x == x_cells){
                        x = 0;
                    }

                    y = row + rowOffset;
                    if(y == -1){
                        y = y_cells - 1;
                    }
                    if(y == y_cells){
                        y = 0;
                    }

                    alive += get_current_grid()[y][x].is_alive();
                }
            }
            if(get_current_grid()[row][col].is_alive() && (alive == 2 || alive == 3)){
                get_scratch_grid()[row][col].resurrect();
            }
            else if(!get_current_grid()[row][col].is_alive() && alive == 3){
                get_scratch_grid()[row][col].resurrect();
            }
            else{
                get_scratch_grid()[row][col].kill();
            }
        }
    }
    get_current_grid() = get_scratch_grid();
    drawState();
    // END: G4
}

// TASK
void Gameoflife::step(int steps) {
    // BEGIN: G5
    for(int x{0}; x < steps; ++x){
        step();
    }
    // END: G5
}

// TASK
Cell* Gameoflife::cell_at_pos(Point pos) {
    // BEGIN: E1
    if(pos.x < 0 || pos.y < 0 || pos.x >= x_cells || pos.y >= y_cells){
        return nullptr;
    }
    return &grid[current_grid][pos.y][pos.x];
    // END: E1
}

// TASK
void Cell::toggle() {
    // BEGIN: E2
    if(state == State::Dead){
        state = State::Live;
    }
    else{
        state = State::Dead;
    }
    // END: E2
}

// TASK
bool Gameoflife::toggle_cell(Point pos) {
    // BEGIN: E3
    if (not(pos.x >= 0 && pos.y >= 0 && pos.x < x_cells && pos.y < y_cells)){
        return 0;
    }

    grid[scratch_grid][pos.y][pos.x].toggle();
    return 1;
    // END: E3
}

// Provided
std::ostream& operator<<(std::ostream& os, const Cell& cell) {
    return os << cell.as_char();
}

// Provided
void Gameoflife::save(const std::string& filename) {
    constexpr std::string_view ext = ".cgol";
    if (filename.size() < ext.size() ||
        filename.substr(filename.size() - 5, 5) != ext) {
        throw std::runtime_error{"'" + filename +
                                 "' does not have the correct file extension: "
                                 "'.cgol' or is too short."};
    }

    std::ofstream ofs{filename};
    if (!ofs) {
        throw std::runtime_error{"Could not save the CGoL state to '" +
                                 filename + "'."};
    }

    ofs << *this;
}

// Provided
std::ostream& operator<<(std::ostream& os, const Gameoflife& gameoflife) {
    for (auto& row : gameoflife.get_current_grid()) {
        for (auto&& cell : row) {
            os << cell;
        }
        os << '\n';
    }

    return os;
}

// Provided
void Gameoflife::step_pressed() {
    int steps;
    try {
        steps = stoi(steps_input.getText());
    } catch (std::invalid_argument) {
        steps = 1;
    }
    steps = std::clamp(steps, min_steps, max_steps);
    step(steps);
}

// Provided
void Gameoflife::load_state() {
    const std::string& filename = filename_input.getText();
    try {
        load(filename);
    } catch (const std::runtime_error& e) {
        alert(e.what());
    }
}

// Provided
void Gameoflife::save_state() {
    const std::string& filename = filename_input.getText();
    try {
        save(filename);
    } catch (const std::runtime_error& e) {
        alert(e.what());
    }
}

// Provided
Gameoflife::Grid& Gameoflife::get_current_grid() { return grid[current_grid]; }
Gameoflife::Grid& Gameoflife::get_scratch_grid() { return grid[scratch_grid]; }
const Gameoflife::Grid& Gameoflife::get_current_grid() const {
    return grid[current_grid];
}
const Gameoflife::Grid& Gameoflife::get_scratch_grid() const {
    return grid[scratch_grid];
}

// Provided
void Gameoflife::alert(const std::string& message) {
    AnimationWindow::show_info_dialog(message);
}

// Provided
int Gameoflife::click_handler(Point pos) { return toggle_cell(pos); }

// Provided
void Gameoflife::play_pause() {
    playing = !playing;
}

// Provided
void Gameoflife::run() {
    Uint64 last_updated = 0;
    while (!should_close()) {
        if (left_mouse_clicked()) {
            click_handler(get_mouse_coordinates());
        }
        drawState();
        if (playing) {
            Uint64 current = SDL_GetTicks64();
            if (current - last_updated > animation_interval) {
                step(1);
                last_updated = current;
            }
        }
    }
}

// Provided
bool Gameoflife::left_mouse_clicked() {
    static bool was_down = false;
    bool is_down = is_left_mouse_button_down();
    if (is_down && was_down) {
        return false;
    } else if (is_down) {
        was_down = true;
        return true;
    } else {
        was_down = false;
        return false;
    }
}

// Provided
Gameoflife::~Gameoflife() {
    playing = false;
}
