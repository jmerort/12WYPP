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
        vector <Tactic> tactics(){return t;};

        void add_tactic(Tactic tt){t.push_back(tt);};

    private:
        string n;
        vector <Tactic> t;
};



//--------------------------------------------------------------------



class Weekday
{
    public:
        Weekday(){};
        Weekday (Date dd) :d{dd},s{}{}; 

        Date date(){return d;};
        vector <double> scores(){return s;};

        void give_scores(vector <double> ss){s = ss;};

    private:
        Date d; //Date
        vector <double> s; //Scores for the tactics of the day
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
    string t;
    vector <string> tactics;
    cout << "Tactics to accomplish goal " << g.name() << "(ended by \'|\'): ";
    while (t != "|")
    {
        cin >> t;
        if (t != "|") tactics.push_back(t);
    }

    //create objectives
    double obj {0};
    for (int i {0}; i < tactics.size(); i++)
    {
        cout << "Weekly objective for tactic " << tactics[i] <<": ";
        cin >> obj;

        g.add_tactic({tactics[i], obj});
    }

    //create day
    d = Weekday{today};
}



void WY::view_stats()
{
    cout << "Current goal: " << g.name() << '\n';
    cout << "Current tactics and scores:\n";
    for (int i {0}; i < g.tactics().size(); i++)
    {
        cout << g.tactics()[i].name()
             << " - objective: " << g.tactics()[i].objective()
             << " - score: " << d.scores()[i] << '\n';
    } 

    double sum_s {0}, 
           sum_o {0};

    for (int i {0}; i < g.tactics().size(); i++)
    {
        sum_o += g.tactics()[i].objective();
        sum_s += d.scores()[i];
    }

    double percentage {sum_s/sum_o*100};
    cout << "Year % = " << percentage << "%.\n";
}



void WY::score_day()
{
    vector <double> scores;
    double s {0};

    for (int i {0}; i < g.tactics().size(); i++)
    {
        cout << "Daily score for the tactic " << g.tactics()[i].name() << ": ";
        cin >> s;
        scores.push_back(s);
    }
    
    d.give_scores(scores);
}




void WY::save_data()
{
    std::ofstream outFile("data.txt");  // Open a file for writing
    vector <int> v;

    //for every goal
    v.push_back(1);
    v.push_back(g.tactics().size());

    if (outFile.is_open()) 
    {  // Check if the file opened successfully
        outFile << v[0] << '\n';
        outFile << v[1] << '\n';
        outFile << "end_info" << '\n';

        outFile << g.name() << '\n';

        for (Tactic i : g.tactics())
            outFile << i.name() << '\n';

        for (Tactic i : g.tactics())
            outFile << i.objective() << '\n';
        
        for (double i : d.scores())
            outFile << i << '\n';
        
        outFile << "end_data" << '\n';

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
    vector <int> sizes; //vector to load control info
    vector <string> v; //vector to store file content

    std::ifstream inFile("data.txt");  // Open the file for reading
    if (inFile.is_open()) 
    {  // Check if the file opened successfully
        std::string line;
        while (std::getline(inFile, line)) 
        {
            cout << line << '\n';
            if (line != "end_info") //load control information
            {
                sizes.push_back(std::stod(line));
            }
            else break;
        }
        while (std::getline(inFile, line)) 
        {
            if (line != "end_data") //load year data
            {
                v.push_back(line);
            }
            else break;
        }
        inFile.close();  // Don't forget to close the file
        cout << "Data successfully loaded.\n";
    }
    else
    {
        std::cout << "Error opening file for reading.\n";
        return;
    }

    //use vector data to load new year
    //load goal
    g = {v[0]};

    //load tactic names and objectives
    for (int i {0}; i < sizes[1]; i++)
    {
        g.add_tactic({v[1+i], std::stod(v[1+sizes[1]])});
    }

    vector <double> scores;
    for (int i {0}; i < sizes[1]; i++)
    {
        scores.push_back(std::stod(v[sizes[1]*2+i]));
    }

    //load scores
    d.give_scores(scores);

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