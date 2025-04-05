#ifndef GUI_H
#define GUI_H

#include <array>
#include <memory>
#include <string>
#include <gtkmm.h>
#include "jeu.h"

class My_window : public Gtk::Window
{
public:
    My_window(std::string file_name);

private:
    Gtk::Box main_box, panel_box, command_box;
    Gtk::Frame command_frame, info_frame;
    Gtk::Grid info_grid;
    bool activated;
    sigc::connection loop_conn;
    std::array<Gtk::Button, 6> buttons;
    std::array<Gtk::CheckButton, 2> checks;
    std::array<Gtk::Label, 4> info_text, info_value;
    Gtk::DrawingArea drawing;
    std::string previous_file_name;
	// ajouter un attribut pour accéder au jeu (instance ou pointeur)
	
    void set_commands();

    void exit_clicked();
    void open_clicked();
    void save_clicked();
    void restart_clicked();
    void start_clicked();
    void step_clicked();
    void build_clicked();
    void guide_clicked();

    void set_key_controller();
    bool key_pressed(guint keyval, guint keycode, Gdk::ModifierType state);

    void set_dialog(Gtk::FileChooserDialog *dialog);
    void dialog_response(int response, Gtk::FileChooserDialog *dialog);

    bool loop();
    void update();

    void set_infos();
    void update_infos();

    void set_drawing();
    void on_draw(const Cairo::RefPtr<Cairo::Context> &cr, int width, int height);

    void set_mouse_controller();
    void on_drawing_left_click(int n_press, double x, double y);
    void on_drawing_right_click(int n_press, double x, double y);
    void on_drawing_move(double x, double y);
    S2d scaled(S2d const &pos) const;

    void set_jeu(std::string file_name);
};

#endif
