#include <iostream>

using namespace std;

void OutputChoices();
int GetUserSelection();
void TrainingMenu();
void SwimData();
void RunData();
void BikeData();
void RunDataAnalysis();
void GetMean();
void GetMax();
void GetOverall();

int main() {

    OutputChoices();
    GetUserSelection();

    return 0;
}

void OutputChoices() {
    cout << "------------------------------------------------" << endl;
    cout << endl;

    cout << '\t'<< "Enter 1 for Training Log" << endl;
    cout << endl;
 
    cout << '\t'<< "Enter 2 for Data Analysis" << endl;
    cout << endl;

    cout << '\t'<< "Enter 3 to exit" << endl;
    cout << endl;

    cout << "------------------------------------------------" << endl;

}

int GetUserSelection() {
    int userChoice;

    cout << endl;
    cout << '\t'<< "What would you like to select?";
    cout << '\t' ;
    cin >> userChoice;
    cout << endl;

    if (userChoice == 1) {
        TrainingMenu();
    } else if (userChoice == 2) {
        RunDataAnalysis();
    }

    return userChoice;
}

void TrainingMenu() {
    int trainingChoice;

    cout << "------------------------------------------------" << endl;
    cout << endl;

    cout << '\t'<< "Welcome to the Training Log!" << endl;
    cout << endl;

    cout << '\t'<< "Enter 1 to log a swim training" << endl;
    cout << endl;

    cout << '\t'<< "Enter 2 to log a run training" << endl;
    cout << endl;

    cout << '\t'<< "Enter 3 to log a bike training" << endl;
    cout << endl;

    cout << '\t'<< "Enter 4 to go back to the Main Menu" << endl;
    cout << endl;
    cout << '\t' ;

    cout << "Selection: ";
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

void SwimData() {
    string heartRate;
    string distance;
    string notes;

    cout << "------------------------------------------------" << endl;
    cout << endl;

    cout << '\t' << "Enter swim training data: " << endl;
    cout << endl;

    cout << '\t' << "Distance: ";
    cin >> distance;
    cout << endl;


    cout << '\t' << "Heart Rate: ";
    cin >> heartRate;
    cout << endl;

    cout << '\t' << "Notes: "; 
    cin >> notes;
    cout << endl;

    TrainingMenu();

}

void RunData() {
    string heartRate;
    string distance;
    string notes;

    cout << "------------------------------------------------" << endl;
    cout << endl;

    cout << '\t' << "Enter run training data: " << endl;
    cout << endl;

    cout << '\t' << "Distance: ";
    cin >> distance;
    cout << endl;


    cout << '\t' << "Heart Rate: ";
    cin >> heartRate;
    cout << endl;

    cout << '\t' << "Notes: "; 
    cin >> notes;
    cout << endl;

    TrainingMenu();


}

void BikeData() {
    string heartRate;
    string distance;
    string notes;

    cout << "------------------------------------------------" << endl;
    cout << endl;

    cout << '\t' << "Enter bike training data: " << endl;
    cout << endl;

    cout << '\t' << "Distance: ";
    cin >> distance;
    cout << endl;


    cout << '\t' << "Heart Rate: ";
    cin >> heartRate;
    cout << endl;

    cout << '\t' << "Notes: "; 
    cin >> notes;
    cout << endl;

    TrainingMenu();

}

void RunDataAnalysis() {
    int dataAnalysisChoice = 0;

    cout << "------------------------------------------------" << endl;
    cout << endl;

    cout << '\t'<< "What kind of data analysis are you looking for?" << endl;
    cout << endl;

    cout << '\t'<< "Enter 1 to for show mean" << endl;
    cout << endl;

    cout << '\t'<< "Enter 2 to for show max" << endl;
    cout << endl;

    cout << '\t'<< "Enter 3 to for show overall performance" << endl;
    cout << endl;

    cout << '\t'<< "Enter 4 to go back to the Main Menu" << endl;
    cout << endl;

    cout << '\t' ;
    cout << "Selection: ";
   

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

void GetMean() {
    cout << "------------------------------------------------" << endl;

    cout << '\t' << "Mean:" << endl;


    RunDataAnalysis();
}


void GetMax() {
    cout << "------------------------------------------------" << endl;

    cout << '\t' << "Max:" << endl;
    

    RunDataAnalysis();
}

void GetOverall() {
    cout << "------------------------------------------------" << endl;

    cout << '\t' << "Overall performance:" << endl;


    RunDataAnalysis();
}