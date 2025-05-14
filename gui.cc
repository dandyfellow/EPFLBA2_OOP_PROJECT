#include <iostream>
#include <cassert>
#include "graphic_gui.h"
#include "gui.h"
#include "constantes.h"

using namespace std;

enum Response {
    CANCEL,
    OPEN,
    SAVE
};

// enum pour noms de boutons
enum ButtonName {
    B_EXIT,
    B_OPEN,
    B_SAVE,
    B_RESTART,
    B_START,
    B_STEP
};

constexpr unsigned taille_dessin(500);

My_window::My_window(string file_name)
    : main_box(Gtk::Orientation::HORIZONTAL),
      panel_box(Gtk::Orientation::VERTICAL),
      command_box(Gtk::Orientation::VERTICAL),
      command_frame("General"),
      info_frame("Info : nombre de..."),
      activated(false),
      buttons({Gtk::Button("exit"), Gtk::Button("open"), Gtk::Button("save"),
               Gtk::Button("restart"), Gtk::Button("start"), Gtk::Button("step")}),
      checks({Gtk::CheckButton("Construction"), Gtk::CheckButton("Guidage")}),
      info_text({Gtk::Label("score:"),
                 Gtk::Label("particules:"),
                 Gtk::Label("faiseurs:"),
                 Gtk::Label("articulations:")}),
      previous_file_name(file_name),
      // ici éventuelle initialisation de l'attribut pour l'accès au jeu
//=====================================================================================
      jeu(Jeu())
//=====================================================================================
{
    set_title("Linked-Crossing Challenge");
    set_child(main_box);
    main_box.append(panel_box);
    main_box.append(drawing);
    panel_box.append(command_frame);
    panel_box.append(info_frame);

    set_commands();
    set_key_controller();
    set_mouse_controller();
    set_infos();
    set_drawing();
    set_jeu(file_name);
}
void My_window::set_commands() {
    command_frame.set_child(command_box);
    for (auto &button : buttons) {
        command_box.append(button);
        button.set_margin(1);
    }
    for (auto &check : checks) {
        command_box.append(check);
        check.set_margin(1);
    }

    buttons[B_EXIT].signal_clicked().connect(sigc::mem_fun(*this,
                                                      &My_window::exit_clicked));
    buttons[B_OPEN].signal_clicked().connect(sigc::mem_fun(*this,
                                                      &My_window::open_clicked));
    buttons[B_SAVE].signal_clicked().connect(sigc::mem_fun(*this,
                                                      &My_window::save_clicked));
    buttons[B_RESTART].signal_clicked().connect(sigc::mem_fun(*this,
                                                      &My_window::restart_clicked));
    buttons[B_START].signal_clicked().connect(sigc::mem_fun(*this,
                                                      &My_window::start_clicked));
    buttons[B_STEP].signal_clicked().connect(sigc::mem_fun(*this,
                                                      &My_window::step_clicked));
    checks[0].set_active(true);
    checks[0].set_group(checks[1]);
    checks[0].signal_toggled().connect(sigc::mem_fun(*this,
                                                     &My_window::build_clicked));
    checks[1].signal_toggled().connect(sigc::mem_fun(*this,
                                                     &My_window::guide_clicked));
}

void My_window::exit_clicked() {
    hide();
}

void My_window::open_clicked() {
    auto dialog = new Gtk::FileChooserDialog("Choose a text file",
                                             Gtk::FileChooserDialog::Action::OPEN);
    set_dialog(dialog);
}
void My_window::save_clicked() {
    auto dialog = new Gtk::FileChooserDialog("Choose a text file",
                                             Gtk::FileChooserDialog::Action::SAVE);
    set_dialog(dialog);
}

void My_window::restart_clicked() {
//=====================================================================================
    jeu.reset();
    set_jeu(previous_file_name);
   /* if (buttons[B_START].get_label() == "start") {
        buttons[B_EXIT].set_sensitive(true);
        buttons[B_OPEN].set_sensitive(true);
        buttons[B_SAVE].set_sensitive(true);
        buttons[B_RESTART].set_sensitive(true);
        buttons[B_STEP].set_sensitive(true);
    } else {
        buttons[B_EXIT].set_sensitive(false);
        buttons[B_OPEN].set_sensitive(false);
        buttons[B_SAVE].set_sensitive(false);
        buttons[B_RESTART].set_sensitive(false);
        buttons[B_STEP].set_sensitive(false);
    }*/
    Jeu::set_status(ONGOING);
//=====================================================================================
    cout << __func__ << endl;
}

void My_window::start_clicked() {
    cout << __func__ << endl;
   if(victoire()){
        Jeu::set_status(WON);
    }

    if (activated) { // variable d'état: true si le jeu est en cours
    
        loop_conn.disconnect();
        activated = false;
        buttons[B_EXIT].set_sensitive(true);
        buttons[B_OPEN].set_sensitive(true);
        buttons[B_SAVE].set_sensitive(true);
        buttons[B_RESTART].set_sensitive(true);
        buttons[B_START].set_label("start");
        buttons[B_STEP].set_sensitive(true);
    }
    else if (jeu.get_status() == ONGOING) {// voir jeu.h
   
        loop_conn = Glib::signal_timeout().connect(sigc::mem_fun(*this,
                                                                 &My_window::loop),
                                                   25);
        activated = true;
        buttons[B_EXIT].set_sensitive(false);
        buttons[B_OPEN].set_sensitive(false);
        buttons[B_SAVE].set_sensitive(false);
        buttons[B_RESTART].set_sensitive(false);
        buttons[B_START].set_label("stop");
        buttons[B_STEP].set_sensitive(false);
    }
}

void My_window::step_clicked() {
//=====================================================================================
    if(!activated) {
        update(); 
    }
//=====================================================================================
    cout << __func__ << endl;
}

void My_window::build_clicked() {
//=====================================================================================
    if(checks[0].get_active()) {
        Chaine::set_mode(CONSTRUCTION);
        checks[1].set_sensitive(true);
        checks[0].set_sensitive(false);
    }
//=====================================================================================
    cout << __func__ << endl;
}
void My_window::guide_clicked() {
//=====================================================================================
    if(checks[1].get_active()) {
        Chaine::set_mode(GUIDAGE);
        checks[1].set_sensitive(false);
        checks[0].set_sensitive(true);
    }
//=====================================================================================
    cout << __func__ << endl;
}

void My_window::set_key_controller() {
    auto contr = Gtk::EventControllerKey::create();
    contr->signal_key_pressed().connect(sigc::mem_fun(*this, &My_window::key_pressed),
                                        false);
    add_controller(contr);
}

bool My_window::key_pressed(guint keyval, guint keycode, Gdk::ModifierType state) {

    switch (keyval){
    case '1'://step - 1 mise a jour 
//=====================================================================================
        if(buttons[B_STEP].get_sensitive() == true) step_clicked();
//=====================================================================================
		cout << keyval <<"  " << __func__ << endl;
        return true;
    case 's'://start - depause 
//=====================================================================================
        if(buttons[B_START].get_sensitive() == true) start_clicked();
//=====================================================================================
		cout << keyval <<"  " << __func__ << endl;

        return true;
    case 'r'://restart - reset et relancer 
//=====================================================================================
        if(buttons[B_RESTART].get_sensitive() == true) restart_clicked();
//=====================================================================================
		cout << keyval <<"  " << __func__ << endl;

        return true;
    default:
        return false;
    }
    return false;
}

void My_window::set_dialog(Gtk::FileChooserDialog *dialog) {
    dialog->set_modal(true);
    dialog->set_transient_for(*this);
    dialog->set_select_multiple(false);
    dialog->signal_response().connect(sigc::bind(
        sigc::mem_fun(*this, &My_window::dialog_response), dialog));

    dialog->add_button("_Cancel", CANCEL);
    switch (dialog->get_action())
    {
    case Gtk::FileChooserDialog::Action::OPEN:
        dialog->add_button("_Open", OPEN);
        break;
    case Gtk::FileChooserDialog::Action::SAVE:
        dialog->add_button("_Save", SAVE);
        break;
    default:
        break;
    }

    auto filter_text = Gtk::FileFilter::create();
    filter_text->set_name("Text files");
    filter_text->add_pattern("*.txt");
    dialog->add_filter(filter_text);

    auto filter_any = Gtk::FileFilter::create();
    filter_any->set_name("Any files");
    filter_any->add_pattern("*");
    dialog->add_filter(filter_any);

    dialog->show();
}

void My_window::dialog_response(int response, Gtk::FileChooserDialog *dialog){
    string file_name = "";
    if (dialog->get_file()) {
        file_name = dialog->get_file()->get_path();
        if (file_name.size() < 4 or file_name.substr(file_name.size() - 4) != ".txt")
        {
            file_name = "";
        }
    }
    switch (response) {
    case CANCEL:
        dialog->hide();
        break;
    case OPEN:
        Jeu::set_status(ONGOING);
        if (file_name != ""){
//=====================================================================================
            jeu.set_status(ONGOING);
            set_jeu(file_name);
            previous_file_name = file_name;
//=====================================================================================
            cout << file_name <<"  " << __func__ << endl;
            dialog->hide();
        }
        break;
    case SAVE:
        if (file_name != ""){
//=====================================================================================
            jeu.save_file(file_name);
//=====================================================================================
			cout << file_name <<"  " << __func__ << endl;
            dialog->hide();
        }
        break;
    default:
        break;
    }
}

bool My_window::loop(){
    if (activated) {
        update();
        return true;
    }
    return false;
}
void My_window::update(){
	//cout <<  __func__ << endl;
//=====================================================================================
if (jeu.get_status() == ONGOING) {
    jeu.update();
}
//=====================================================================================
    update_infos();
    drawing.queue_draw();

    if (jeu.get_status() != ONGOING){
		buttons[B_RESTART].set_sensitive(true);
        buttons[B_OPEN].set_sensitive(true);
        buttons[B_EXIT].set_sensitive(true);
        //-----^^^ truc rajouté par nous
        buttons[B_SAVE].set_sensitive(false);
        buttons[B_START].set_sensitive(false);
        buttons[B_STEP].set_sensitive(false);
        checks[0].set_active(true);
        checks[0].set_sensitive(false);
        checks[1].set_sensitive(false);
        if (jeu.get_status() == LOST){
           cout << "! Game Over !" << endl;
           buttons[B_STEP].set_sensitive(false);
           
        }
        if (jeu.get_status() == WON){
           cout << "! You win !" << endl;
           buttons[B_SAVE].set_sensitive(false);
           buttons[B_STEP].set_sensitive(false);
           show_victory_dialog();
        }
    }
}

    void My_window::on_victory_dialog_response(int response_id, Gtk::Dialog* dialog) {
        dialog->hide(); 
    
        switch (response_id) {
            case Gtk::ResponseType::CANCEL:
                hide(); 
                break;
            case 1:
                restart_clicked();
                break;
            case 2:
                open_clicked();
                break;
            default:
                break;
        }
    
        delete dialog; 
    }

    void My_window::show_victory_dialog() {
        auto dialog = new Gtk::Dialog("🎉Victory🎉", *this);
        dialog->set_modal(true);
        dialog->set_transient_for(*this);
        dialog->set_default_size(400, 220);
    
        
        auto* label_main = Gtk::make_managed<Gtk::Label>("<span size='xx-large' "
            "weight='bold'>🎉 YOU WON!</span>");
        label_main->set_use_markup(true);
        label_main->set_margin_top(15);
        label_main->set_margin_bottom(10);
        label_main->set_halign(Gtk::Align::CENTER);
   
        auto* label_secondary = Gtk::make_managed<Gtk::Label>("What would you"
            "like to do next?");
        label_secondary->set_margin_bottom(15);
        label_secondary->set_halign(Gtk::Align::CENTER); 
    
        auto* content_area = dialog->get_content_area();
        content_area->append(*label_main);
        content_area->append(*label_secondary);
        content_area->set_halign (Gtk::Align::CENTER);
    
        dialog->add_button("❌ Quit", Gtk::ResponseType::CANCEL);
        dialog->add_button("🔁 Restart", 1);
        dialog->add_button("📂 Open File", 2);
    
        // Connexion du signal
        dialog->signal_response().connect(sigc::bind(
            sigc::mem_fun(*this, &My_window::on_victory_dialog_response), dialog));
    
        dialog->show();
    }
    

void My_window::set_infos(){
    info_frame.set_child(info_grid);
    info_grid.set_column_homogeneous(true);

    for (size_t i(0); i < info_text.size(); ++i){
        info_grid.attach(info_text[i], 0, i, 1, 1);
        info_grid.attach(info_value[i], 1, i, 1, 1);
        info_text[i].set_halign(Gtk::Align::START);
        info_value[i].set_halign(Gtk::Align::END);
        info_text[i].set_margin(3);
        info_value[i].set_margin(3);
    }
}

void My_window::update_infos(){
    //cout <<  __func__ << endl;
//=====================================================================================
     info_value[0].set_text(to_string(jeu.get_score()));
     info_value[1].set_text(to_string(Particule::get_nbrs_particules()));
     info_value[2].set_text(to_string(Faiseur::get_liste_faiseurs().size()));
     info_value[3].set_text(to_string(Chaine::get_chaine().size()));
//=====================================================================================
}

void My_window::set_drawing(){
    drawing.set_content_width(taille_dessin);
    drawing.set_content_height(taille_dessin);
    drawing.set_expand();
    drawing.set_draw_func(sigc::mem_fun(*this, &My_window::on_draw));
}

void My_window::on_draw(const Cairo::RefPtr<Cairo::Context> &cr,
                        int width, int height){
    graphic_set_context(cr);
    double side(min(width, height));
    cr->translate(width / 2, height / 2);
    cr->scale(side / (2 * r_max), -side / (2 * r_max));

//================================remplacer affichage par votre code===================
	//cout <<  __func__ << endl;
    //draw a blank canvas for when lecture fails
    cr->set_source_rgb(1, 1, 1);
    cr->paint();
    
    if(jeu.get_lecture_success() == true) {
        //draw the arena
        jeu.draw_arene();//ne sont pas dans les includes a modifier leur position 
        //draw the rest
        jeu.draw_particules();
        jeu.draw_faiseurs();
        jeu.draw_chaine();

        jeu.draw_but_final();
        if(Chaine::get_longueur_chaine()==0) jeu.draw_start();
    }
//=======================================FIN DE NOTRE CODE=============================
}

void My_window::set_mouse_controller(){
    auto left_click = Gtk::GestureClick::create();
    auto right_click = Gtk::GestureClick::create();
    auto move = Gtk::EventControllerMotion::create();

    left_click->set_button(GDK_BUTTON_PRIMARY);
    right_click->set_button(GDK_BUTTON_SECONDARY);

    left_click->signal_pressed().connect(
        sigc::mem_fun(*this, &My_window::on_drawing_left_click));
    right_click->signal_pressed().connect(
        sigc::mem_fun(*this, &My_window::on_drawing_right_click));
    move->signal_motion().connect(
        sigc::mem_fun(*this, &My_window::on_drawing_move));

    drawing.add_controller(left_click);
    drawing.add_controller(right_click);
    drawing.add_controller(move);
}

// cette fonction convertit l'entrée pos contenant les coordonnées (x,y) de la souris 
// dans l'espace GTKmm vers l'espace du Modèle => sortie de la fonction.
S2d My_window::scaled(S2d const &pos) const{
    int width = drawing.get_width();
    int height = drawing.get_height();
    double ratio((2 * r_max) / min(width, height));
    return {ratio * (-width / 2 + pos.x),
            ratio * (height / 2 - pos.y)};
}

void My_window::on_drawing_left_click(int n_press, double x, double y){
	// remplacer affichage par votre code
	cout <<  __func__ << endl;
     //==============================================================================
     step_clicked();
     checks[0].set_active();
     if (Chaine::get_mode() != CONSTRUCTION){
         build_clicked();
     } else {
        ajouter_chaine(Particule::get_liste_particules());
     }
     
     drawing.queue_draw();
     //==============================================================================
}
void My_window::on_drawing_right_click(int n_press, double x, double y){
	// remplacer affichage par votre code
	cout <<  __func__ << endl;
        //=============================================================================
        checks[1].set_active();
        step_clicked();

        if (Chaine::get_mode() != GUIDAGE){
            guide_clicked();
        }
        drawing.queue_draw();

        //=============================================================================
}
void My_window::on_drawing_move(double x, double y){
	// remplacer affichage par votre code
	//cout <<  __func__ << endl;
    //=============================================================================
    set_drawing();
    //cout << "P(x,y)=(" << x << "," << y << ")" << endl;
    S2d mouse_pos = scaled({x,y});
    Chaine::set_mouse_pos(mouse_pos.x, mouse_pos.y);
    
    //=============================================================================
}


void My_window::set_jeu(string file_name){
//=====================================================================================
	cout <<  __func__ << endl;

    Cercle::epsilFalse(); // désactive epsil pour les tests
    bool success = jeu.lecture(file_name);

    if(success) jeu.set_lecture_success(true);
    else jeu.set_lecture_success(false);

    Cercle::epsilTrue(); // réactive epsil

//=====================================================================================
    if (!Jeu::get_lecture_success()) {// cas d'erreur de lecture : maxwc
        buttons[2].set_sensitive(false);
        buttons[4].set_sensitive(false);
        buttons[5].set_sensitive(false);
        checks[0].set_active(true);
        checks[0].set_sensitive(false);
        checks[1].set_sensitive(false);
        // éventuelle mise à jour de l'attribut jeu
    } else {
        buttons[2].set_sensitive(true);
        buttons[4].set_sensitive(true);
        buttons[5].set_sensitive(true);
        checks[0].set_sensitive(true);
        checks[1].set_sensitive(true);
    switch (Chaine::get_mode()) {
        case CONSTRUCTION:
            checks[0].set_active(true);
            Chaine::set_mode(CONSTRUCTION);
            break;
        case GUIDAGE:
            checks[1].set_active(true);
            Chaine::set_mode(GUIDAGE);
            break;
        }
    }
    update_infos();
    drawing.queue_draw();
}
