#include <iostream>
#include <vector>
#include <fstream>

#include "date.h"

using std::vector,
      std::string,
      std::cout,
      std::cin;



//--------------------------------------------------------------------------



class Tactic
{
    public:
        Tactic (){};
        Tactic (string name, double oo = 0) :n{name}, o{oo}{};  

        string name(){return n;};
        double objective(){return o;};

    private:
        string n;
        double o; // Objective: desired weekly score
};



//--------------------------------------------------------------------



class Goal
{
    public:
        Goal (){};
        Goal (string nn):n{nn}{};

        string name(){return n;};
        Tactic tactic(){return t;};

        void add_tactic(Tactic tt){t = tt;};

    private:
        string n;
        Tactic t;
};



//--------------------------------------------------------------------



class Weekday
{
    public:
        Weekday(){};
        Weekday (Date dd) :d{dd},s{0}{}; 

        Date date(){return d;};
        double score(){return s;};

        void give_score(double ss){s = ss;};

    private:
        Date d; //Date
        double s; //Score for the tactic of the day
};



//----------------------------------------------------------------------------



class WY
{
    public:
        WY (){};

        void create_year(); 
        void score_day();
        void load_data();
        void save_data();
        void view_stats();

    private:
        Goal g; //Yearly goal
        Weekday d; //Day of the year
};



Date today {2025, Month::jan, 26};



void WY::create_year()
//Start a new 12WY, giving goals, tactics and objectices
{
    //create goal
    string goal;
    cout << "Goal for the year: ";
    cin >> goal;
    g = {goal};

    //create tactic
    string tactic;
    cout << "Tactic to accomplish goal " << g.name() << ": ";
    cin >> tactic;

    //create objective
    double obj {0};
    cout << "Desired weekly score for tactic " << g.tactic().name() <<": ";
    cin >> obj;
    g.add_tactic({tactic, obj});

    //create day
    d = Weekday{today};
}



void WY::view_stats()
{
    cout << "Current goal: " << g.name() << '\n';
    cout << "Current tactic: " << g.tactic().name() << '\n';
    cout << "Desired score for tactic: " << g.tactic().objective() << '\n';
    cout << "Current day score: " << d.score() << '\n';

    double percentage {d.score()/g.tactic().objective()*100};
    cout << "Year % = " << percentage << "%.\n";
}



void WY::score_day()
{
    cout << "Enter the daily score for the tactic " << g.tactic().name() << ": ";
    int score;
    cin >> score;
    d.give_score(score);
}




void WY::save_data()
{
    std::ofstream outFile("data.txt");  // Open a file for writing

    if (outFile.is_open()) 
    {  // Check if the file opened successfully
        outFile <<g.name() << '\n'
                << g.tactic().name() << '\n'
                << g.tactic().objective() << '\n'
                << d.score() << '\n';
        outFile.close();  // Close the file after writing
        std::cout << "Data written to file successfully.\n";
    } 
    else 
    {
        std::cout << "Error opening file for writing.\n";
    }
}


void WY::load_data()
{
    string l_goal; //loaded goal
    string l_tactic;
    double l_objective;
    double l_score;

    vector <string> v;

    std::ifstream inFile("data.txt");  // Open the file for reading

    if (inFile.is_open()) 
    {  // Check if the file opened successfully
        std::string line;
        while (std::getline(inFile, line)) 
        {
            v.push_back(line); //save file content in a vector
        }
        inFile.close();  // Don't forget to close the file
        cout << "Data successfully loaded.\n";
    }
    else
    {
        std::cout << "Error opening file for reading.\n";
    }

    //use vector data to load new year
        //create goal
    g = {v[0]};

    //create tactic
    g.add_tactic({v[1], std::stod(v[2])});

    //create day
    d.give_score(std::stod(v[3]));

    return;
}



//----------------------------------------------------------------------------------



void menu()
{
    WY año;
    while (true)
    {
        int opt {0};
        cout << "\n--12 WEEK YEAR--\nChoose an option:\n"
             << "1 - Start new 12 Week Year\n"
             << "2 - Score current day\n"
             << "3 - See current day stats\n"
             << "4 - Exit the program\n"
             << "5 - Load data from file\n"
             << "6 - Save data in file\n";
        cin >> opt;
        switch(opt)
        {
            case 1:
                //ano.reset();
                año.create_year();
                break;
            case 2:
                año.score_day();
                break;
            case 3:
                año.view_stats();
                break;
            case 4:
                cout << "-EXIT-\n";
                return;
                break;
            case 5:
                año.load_data();
                break;
            case 6:
                año.save_data();
                break;
            default:
                cout << "Enter a valid option.\n";
                break; 
        }

    }
}



int main()
{
    try 
    {
        menu();
        return 0;
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
    catch (...)
    {
        std::cerr << "Unknown error.\n";
        return 2;
    }
    return 0;
}