/*
+---------------------------------------------+
|    ___ _  _  __  ___ __ __  __  ___ ___     |
|   | _,\ || |/  \| _ \  V  |/  \| _,\ _,\    |
|   | v_/ >< | /\ | v / \_/ | /\ | v_/ v_/    |
|   |_| |_||_|_||_|_|_\_| |_|_||_|_| |_|      |
|+--------------------------------------------+
| @authors : Jérémy Morin & Louis Lainé       |
+---------------------------------------------+
| @usage   : mainGui                          |
+---------------------------------------------+
*/


#include "Abstract/Controller.cpp"
#include <gtkmm.h>
#include <glibmm/ustring.h>
#define pathFichierListe "liste.txt"
typedef std::map<int, Medicament> dataMap;
typedef std::map<int, Medicament>::iterator dataMapIterator;

typedef std::map<string, double> dataEffet;
typedef std::map<string, double>::iterator dataEffetIterator;

//GTKmm 




/*
Graphical Class
@ Code isn't split for reading pleasure
*/
class mywindow : public Gtk::Window
{
        typedef Gtk::ListStore ListStore;
        typedef Glib::RefPtr<ListStore> PtrListStore;
        typedef Gtk::Box Box;
        typedef Gtk::Grid Grid;
        typedef Gtk::TreeModelColumn<Glib::ustring> StringColumn;
        typedef Gtk::MenuItem MenuItem;
        typedef Gtk::Notebook Notebook;
        typedef Gtk::ScrolledWindow ScrollWin;
        typedef Gtk::TreeModel::Row Row;
        typedef Gtk::Label Label;
        typedef Gtk::Button Button;
        typedef Gtk::TreeView TreeView;
        typedef Gtk::MenuBar MenuBar;
        typedef Gtk::Entry Entry;
        

    public:
        mywindow(Controller control);
        virtual ~mywindow();

    protected:
        void on_quit_click();
        void on_button_click();
        void credits();
        void on_search_click(Entry *emedicament);

        class ModelColumns : public Gtk::TreeModel::ColumnRecord
        {
            public:
                ModelColumns(){ add(col_cnt); add(col_text); add(col_effet);}
                Gtk::TreeModelColumn<int> col_cnt;
                StringColumn col_text;
                StringColumn col_effet;
        };

        class ModelColumnsHistogramme : public Gtk::TreeModel::ColumnRecord
        {
            public:
                ModelColumnsHistogramme(){add(effets); add(histo);}
                StringColumn effets;
                StringColumn histo;
        };
        ModelColumns columns;
        ModelColumnsHistogramme columnsHisto;
        PtrListStore refTreeModelHisto;
        PtrListStore refTreeModel;



};

/*
=======================================================================================
||                                                                                   ||
||  @methods : Display methods with gtkmm                                            ||
||  @usage   : GTKmm librairies                                                      ||
||                                                                                   ||
=======================================================================================



*/


mywindow::mywindow(Controller control)
{
    /*
        set_default_size : adjust size of windows
        nombre : medicament's number
        set title : application name
    */
    set_default_size(400, 400);
    int nombre=0;
    set_title("Gestionnaire des médiacaments");

    /* Create Box in myWindow*/
    Box *vbox = Gtk::manage(new Box(Gtk::ORIENTATION_VERTICAL, 0));
    add(*vbox);

    /* Create MenuBar & item */
    MenuBar *menubar = Gtk::manage(new MenuBar());
    vbox->pack_start(*menubar, Gtk::PACK_SHRINK, 0);
    MenuItem *menuitem_file = Gtk::manage(new MenuItem("_Menu", true));
    menubar->append(*menuitem_file);
    Gtk::Menu *filemenu = Gtk::manage(new Gtk::Menu());
    menuitem_file->set_submenu(*filemenu);
    MenuItem *menuitem_propos = Gtk::manage(new MenuItem("_About", true));
    menuitem_propos->signal_activate().connect(sigc::mem_fun(*this, &mywindow::credits));
    filemenu->append(*menuitem_propos);
    MenuItem *menuitem_quit = Gtk::manage(new MenuItem("_Quitter", true));
    menuitem_quit->signal_activate().connect(sigc::mem_fun(*this, &mywindow::on_quit_click));
    filemenu->append(*menuitem_quit);

    /* Create a grid*/
    Grid *grid = Gtk::manage(new Grid);
    grid->set_border_width(10);
    grid->set_row_spacing(5);
    vbox->add(*grid);

    /* Create Notebook */
    Notebook *barreOnglets = Gtk::manage(new Notebook);
    barreOnglets->set_scrollable();
    barreOnglets->popup_enable();


    /* Create scrollbar */
    ScrollWin *barresDeDefillementPharmacie= Gtk::manage(new ScrollWin);
    barresDeDefillementPharmacie->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

    ScrollWin *barresDeDefillementSearch= Gtk::manage(new ScrollWin);
    barresDeDefillementSearch->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

    ScrollWin *barresDeDefillementHisto= Gtk::manage(new ScrollWin);
    barresDeDefillementHisto->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

    ScrollWin *barresDeDefillementAdd= Gtk::manage(new ScrollWin);
    barresDeDefillementAdd->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

    /* Treview with medoc name */
    TreeView *list = Gtk::manage(new TreeView);
    list->set_hexpand(true);
    list->set_vexpand(true);

    refTreeModel = ListStore::create(columns);
    list->set_model(refTreeModel);
    list->append_column("Id", columns.col_cnt);
    list->append_column("Medicaments", columns.col_text);
    list->append_column("Effets", columns.col_effet);

    dataMap tabTemp;
    tabTemp = control.dispMedocWithEffet<dataMap>(false, true);
    int i=0;
    int nbEffets;

    Row row[25] = *(refTreeModel->append());

    for(dataMapIterator it = tabTemp.begin(); it != tabTemp.end(); ++it)
    {
        row[i][columns.col_cnt] = i+1;
        row[i][columns.col_text] = it->second.getNomMedicament();
        string effets;

        nbEffets = it->second.getLesEffetsIndesirables().size();
		for (int j = 0; j < nbEffets; ++j)
		{
			string effet = it->second.getLesEffetsIndesirables()[j].getNomEffet();
			effets=effets+effet+'\n';

		}
		row[i][columns.col_effet] = effets;
        i++;
        if (it->second.getNomMedicament().compare("")==0) break;
    }

    /* Search */
    Grid *gridSearch = Gtk::manage(new Grid);
    gridSearch->set_border_width(10);
    gridSearch->set_row_spacing(5);

    Label *labelMedicament = Gtk::manage(new Label("Nom medicament: "));
    gridSearch->attach(*labelMedicament, 0, 0, 1, 1);

    Entry *inputMedicament = Gtk::manage(new Entry());
    inputMedicament->set_hexpand(true);
    gridSearch->attach(*inputMedicament, 1, 0, 2, 1);

    Button *search = Gtk::manage(new Button("Search"));
    //string nameMedicament=(const string)inputMedicament->get_text();

    search->signal_clicked().connect(sigc::bind<Entry*>(sigc::mem_fun(*this, &mywindow::on_search_click), inputMedicament));
    gridSearch->attach(*search, 2, 2, 1, 1);

    
    /*Histogramme*/
     /* Treview with medoc name */
    TreeView *listHisto = Gtk::manage(new TreeView);
    listHisto->set_hexpand(true);
    listHisto->set_vexpand(true);

    refTreeModelHisto = ListStore::create(columnsHisto);
    listHisto->set_model(refTreeModelHisto);
    listHisto->append_column("Id", columnsHisto.effets);
    listHisto->append_column("test", columnsHisto.histo);

       dataEffet tabTempEffet = control.dispHistogrammeEffet<dataEffet>(false, true);
        int j=0;
        Row rowHisto[25] = *(refTreeModelHisto->append());
        for(dataEffetIterator it2 = tabTempEffet.begin() ; it2 != tabTempEffet.end(); ++it2){
            // if (it2->first.compare("")==1)break;
            // rowHisto[j][columnsHisto.effets]=it2->first;
            // std::string pourcentage;
            // {
            //     std::ostringstream oss;
            //     oss << it2->second;
            //     pourcentage = oss.str();
            // }
            // rowHisto[j][columnsHisto.histo]=pourcentage;
            // j++;


        //cout << it->getNomEffet() << "---" << it->getNbOccurence() << endl;
    }


    //AJOUT DES CONTAINER SCROLLBAR A LA BARRE D'ONGLET
    barresDeDefillementSearch->add(*gridSearch);
    barresDeDefillementPharmacie->add(*list);
    barresDeDefillementHisto->add(*listHisto);
    //TODO AJOUT DES CONTAINER A AU SCROLLBAR

    barreOnglets->append_page(*barresDeDefillementPharmacie, "Pharmacie");
    barreOnglets->append_page(*barresDeDefillementSearch, "Rechercher");
    barreOnglets->append_page(*barresDeDefillementHisto, "Histogramme");
    barreOnglets->append_page(*barresDeDefillementAdd, "Ajouter");

    grid->attach(*barreOnglets,0,0,2,1);
    vbox->show_all();
}

mywindow::~mywindow()
{
}

void mywindow::on_quit_click()
{
    hide();
}

void mywindow::credits(){
    Gtk::AboutDialog dialogue;
    dialogue.set_program_name("PharmaGTKmm");
    dialogue.set_version("0.1");
    dialogue.set_copyright("© 2014");
    dialogue.set_comments("Projet L3 MIAGe");
    dialogue.set_license("GNU/GPL");
    std::vector<Glib::ustring> listeAuteurs;
    listeAuteurs.push_back("Jérémy MORIN");
    listeAuteurs.push_back("Louis LAINE");
    dialogue.set_authors(listeAuteurs);
    dialogue.run();
}
void mywindow::on_search_click(Entry *emedicament)
{
    Controller control(false);
    dataMap tabTemp;
    try{
        tabTemp = control.dispEffetFromMedoc<dataMap>(emedicament->get_text(),false,true);
    }catch(DataProvider::DBException e){
        e.getMessage();
    }

    string lesEffets = "";
    for(dataMapIterator it = tabTemp.begin(); it != tabTemp.end(); ++it)
    {
        lesEffets = lesEffets + " " + it->second.getNomMedicament();
    }

    Gtk::MessageDialog dlg(lesEffets, false, Gtk::MESSAGE_INFO,Gtk::BUTTONS_OK, true);
    dlg.set_title("L'effet " + emedicament->get_text() + " est contenu dans : ");
    dlg.run();


}


int main(int argc, char *argv[])
{

	Controller control(false);

	// test();
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "com.gtkmm.PharmaGTKmm");
    mywindow window(control);
    return app->run(window);
	// return 0;
}
