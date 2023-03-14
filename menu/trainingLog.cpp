#include <iostream>

using namespace std;

void OutputChoices();
int GetUserSelection();
int ValidInput();
void TrainingMenu();
void SwimData();
void RunData();
void BikeData();
void DataAnalysis();
void GetMean();
void GetMax();
void GetOverall();

int main() {

    OutputChoices();
    GetUserSelection();

    return 0;
}

void OutputChoices() {
    cout << R"(                                                               
                                              ████                  ████      
                                              ████                  ████      
              ████                        ▓▓▓▓                ▓▓  ▓▓          
      ██████  ████                      ▓▓▓▓▓▓▓▓            ██  ▓▓▓▓▓▓██      
    ██      ████  ████████          ██▓▓▓▓    ▓▓██        ██    ▓▓▓▓    ████  
        ▓▓██▓▓██▓▓                ████          ████          ▓▓▓▓▓▓▓▓        
  ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓    ██    ██      ██    ██      ██▓▓    ▓▓████    
                                ██    ██      ██    ██    ████          ██    
                                  ████          ████      ██            ████  
        )" << '\n';
    cout << "-----------------------------------------------------------------------------" << endl;
    cout << endl;

    cout << '\t'<< '\t'<<"   Welcome to your Triathlon Training Log! " << endl;
    cout << endl;

    cout << '\t'<< '\t'<<'\t'<<"Enter 1 for Training Log" << endl;
    cout << endl;
 
    cout << '\t'<< '\t'<< '\t'<< "Enter 2 for Data Analysis" << endl;
    cout << endl;

    cout << '\t'<< '\t'<< '\t'<< "Enter 3 to Exit" << endl;
    cout << endl;

    cout << "-----------------------------------------------------------------------------" << endl;

}


int GetUserSelection() {
    int userChoice;

    cout << endl;
    cout << '\t'<<'\t'<< "     What would you like to select?";
    cout << '\t' ;
    userChoice = validInput();;
    cout << endl;

    if (userChoice == 1) {
        TrainingMenu();
    } else if (userChoice == 2) {
        DataAnalysis();
    } else if (userChoice == 3) {
        exit(-1);
    } else {
        while (userChoice <= 0 || userChoice > 3) {
            cout << '\t'<< '\t'<< "   Invalid selection. Please enter 1, 2, or 3." << endl;
            cout << endl;
            cout << '\t'<<'\t'<< "     What would you like to select?";
            cout << '\t' ;
            userChoice = validInput();;
            cout << endl;

            if (userChoice == 1) {
                TrainingMenu();
            } else if (userChoice == 2) {
                DataAnalysis();
            } else if (userChoice == 3) {
                exit(-1);
            }
        }
    }

    return userChoice;
}

int validInput()
{
    int x;
    cin >> x;
    while(cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << endl;
        cout <<  '\t'<<'\t'<< "    Invalid selection. Please enter 1, 2, or 3.";
        cout << endl << endl;
        cout << '\t'<<'\t'<< "     What would you like to select?";
        cout << '\t' ;
        cin >> x;
    }
    return x;
}

void TrainingMenu() {
    int trainingChoice;

    cout << "-----------------------------------------------------------------------------" << endl;
    cout << endl;

    cout << '\t'<< '\t'<<'\t'<<'\t'<< "Training Log" << endl;
    cout << endl;

    cout << '\t'<< '\t'<<'\t'<<"Enter 1 to log a swim training" << endl;
    cout << endl;

    cout << '\t'<<'\t'<<'\t'<< "Enter 2 to log a run training" << endl;
    cout << endl;

    cout << '\t'<< '\t'<<'\t'<<"Enter 3 to log a bike training" << endl;
    cout << endl;

    cout << '\t'<< '\t'<<'\t'<<"Enter 4 to go back to the Main Menu" << endl;
    cout << endl;
    cout << '\t'<< '\t'<<'\t';

    cout << "Selection: ";
    cout << '\t' ;

    cin >> trainingChoice;
    cout << endl << endl;
    cout << "-----------------------------------------------------------------------------";
    cout << endl;

    if (trainingChoice == 1) {
        SwimData();
    } else if (trainingChoice == 2) {
        RunData();
    } else if (trainingChoice == 3) {
        BikeData();
    } else if (trainingChoice ==4){
        OutputChoices();
        GetUserSelection();
    }

    while (trainingChoice <= 0 || trainingChoice > 3) {
        cout << '\t'<< '\t'<< "   Invalid selection. Please try again." << endl;
        cout << endl;

        cout << '\t'<<'\t'<< '\t'<< "Selection: ";
        cout << '\t' ;
        cin >> trainingChoice;
        cout << endl;

         if (trainingChoice == 1) {
            SwimData();
        } else if (trainingChoice == 2) {
            RunData();
        } else if (trainingChoice == 3) {
            BikeData();
        } else if (trainingChoice ==4){
            OutputChoices();
            GetUserSelection();
        }

    }
}

void SwimData() {
    string heartRate;
    string distance;
    string notes;
    string speed;
    string date;
    string duration;

    cout << R"(
                                      _                                  
                                     (_)                         
                         _____      ___ _ __ ___  
                        / __\ \ /\ / / | '_ ` _ \
                        \__ \\ V  V /| | | | | | |
                        |___/ \_/\_/ |_|_| |_| |_|
                                  
        )" << '\n';

    cout << "-----------------------------------------------------------------------------" << endl;
    cout << endl;

    cout << '\t' << '\t'<<'\t'<<"Enter swim training data: " << endl;
    cout << endl;

    cout << '\t' << '\t'<<'\t'<<"Date of Workout (dd/mm/yy): ";
    cin >> date;
    cout << endl;

    cout << '\t' << '\t'<<'\t'<<"Workout Duration (minutes):  ";
    cin >> duration;
    cout << endl;

    cout << '\t' << '\t'<<'\t'<<"Total Distance (miles): ";
    cin >> distance;
    cout << endl;
    
    cout << '\t' << '\t'<<'\t'<<"Workout Speed (mph): ";
    cin >> speed;
    cout << endl;

    cout << '\t' << '\t'<<'\t'<<"Heart Rate: ";
    cin >> heartRate;
    cout << endl;

    cout << '\t' << '\t'<<'\t'<<"Notes: "; 
    cin >> notes;
    cout << endl;

    TrainingMenu();

}

void RunData() {
    string heartRate;
    string distance;
    string notes;
    string speed;
    string date;
    string duration;

    cout << R"(

                             _ __ _   _ _ __  
                            | '__| | | | '_ \
                            | |  | |_| | | | |
                            |_|   \__,_|_| |_|
                                  
        )" << '\n';

    cout << "-----------------------------------------------------------------------------" << endl;
    cout << endl;

    cout << '\t' << '\t'<<'\t'<<"Enter run training data: " << endl;
    cout << endl;

    cout << '\t' << '\t'<<'\t'<<"Date of Workout (dd/mm/yy): ";
    cin >> date;
    cout << endl;

    cout << '\t' << '\t'<<'\t'<<"Workout Duration (minutes):  ";
    cin >> duration;
    cout << endl;

    cout << '\t' << '\t'<<'\t'<<"Total Distance (miles): ";
    cin >> distance;
    cout << endl;
    
    cout << '\t' << '\t'<<'\t'<<"Workout Speed (mph): ";
    cin >> speed;
    cout << endl;

    cout << '\t' << '\t'<<'\t'<<"Heart Rate: ";
    cin >> heartRate;
    cout << endl;

    cout << '\t' << '\t'<<'\t'<<"Notes: "; 
    cin >> notes;
    cout << endl;

    TrainingMenu();


}

void BikeData() {
    string heartRate;
    string distance;
    string notes;
    string speed;
    string date;
    string duration;

    cout << R"(
                             _     _ _        
                            | |   (_) |       
                            | |__  _| | _____ 
                            | '_ \| | |/ / _ \
                            | |_) | |   <  __/
                            |_.__/|_|_|\_\___|
        )" << '\n';
    cout << "-----------------------------------------------------------------------------" << endl;
    cout << endl;

    cout << '\t' << '\t'<<'\t'<<"Enter swim training data: " << endl;
    cout << endl;

    cout << '\t' << '\t'<<'\t'<<"Date of Workout (dd/mm/yy): ";
    cin >> date;
    cout << endl;

    cout << '\t' << '\t'<<'\t'<<"Workout Duration (minutes):  ";
    cin >> duration;
    cout << endl;

    cout << '\t' << '\t'<<'\t'<<"Total Distance (miles): ";
    cin >> distance;
    cout << endl;
    
    cout << '\t' << '\t'<<'\t'<<"Workout Speed (mph): ";
    cin >> speed;
    cout << endl;

    cout << '\t' << '\t'<<'\t'<<"Heart Rate: ";
    cin >> heartRate;
    cout << endl;

    cout << '\t' << '\t'<<'\t'<<"Notes: "; 
    cin >> notes;
    cout << endl;

    TrainingMenu();

}

void DataAnalysis() {
    int dataAnalysisChoice = 0;

    cout << "-----------------------------------------------------------------------------" << endl;
    cout << endl;

    cout << '\t'<< '\t'<<"   What kind of data analysis are you looking for?" << endl;
    cout << endl;

    cout << '\t'<< '\t'<<'\t'<<"Enter 1 to for show mean" << endl;
    cout << endl;

    cout << '\t'<<'\t'<<'\t'<< "Enter 2 to for show max" << endl;
    cout << endl;

    cout << '\t'<< '\t'<<'\t'<<"Enter 3 to for show overall performance" << endl;
    cout << endl;

    cout << '\t'<< '\t'<<'\t'<<"Enter 4 to go back to the Main Menu" << endl;
    cout << endl;

    cout << '\t' ;
    cout << '\t'<<'\t'<<"Selection: ";
   

    cin >> dataAnalysisChoice;
    cout << endl;

    if (dataAnalysisChoice == 1) {
        GetMean();
    } else if (dataAnalysisChoice == 2) {
        GetMax();
    } else if (dataAnalysisChoice == 3) {
        GetOverall();
    } else if (dataAnalysisChoice == 4){
        OutputChoices();
        GetUserSelection();
    }

    while (dataAnalysisChoice <= 0 || dataAnalysisChoice > 3) {
        cout << '\t'<< '\t'<< "   Invalid selection. Please try again." << endl;
        cout << endl;

        cout << '\t'<<'\t'<< '\t'<< "Selection: ";
        cout << '\t' ;
        cin >> dataAnalysisChoice;
        cout << endl;
        
        if (dataAnalysisChoice == 1) {
            GetMean();
        } else if (dataAnalysisChoice == 2) {
            GetMax();
        } else if (dataAnalysisChoice == 3) {
            GetOverall();
        } else if (dataAnalysisChoice == 4){
            OutputChoices();
            GetUserSelection();
        }
    }

}

void GetMean() {
    cout << "-----------------------------------------------------------------------------" << endl;

    cout << '\t' << "Mean:" << endl;


    DataAnalysis();
}


void GetMax() {
    cout << "-----------------------------------------------------------------------------" << endl;

    cout << '\t' << "Max:" << endl;
    

    DataAnalysis();
}

void GetOverall() {
    cout << "-----------------------------------------------------------------------------" << endl;

    cout << '\t' << "Overall performance:" << endl;


    DataAnalysis();
}
