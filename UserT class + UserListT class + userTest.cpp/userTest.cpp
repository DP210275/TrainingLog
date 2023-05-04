//User Test File

//To Do:
//Fix username searching, needs to be exact, instead of pieces

#include "userT.h"
#include "userListT.h"

using namespace std;

bool Search(string name);
float FloatCheck(string input);
void ProgressCheck();

int main () {

    ofstream outFile;
    string username;
    //int newID;
    UserT testUser("tester", 999);

    UserListT list = UserListT();

    //newID = list.GetSize() + 1;
    list.PrintUsers();
/*
    while (true) {
        cout << "Input a username: ";
        cin >> username;

        if (!Search(username)) {

            UserT user(username, newID);

            outFile.open(USER_FILE, std::ios::app);
            outFile << username << "," << newID << endl;
            outFile.close();

            newID++;
        }
    }
    */
    testUser.SetSwim(static_cast<float>(10.2));
    testUser.SetRun(static_cast<float>(8.4));
    testUser.SetBike(static_cast<float>(15.3));

    testUser.SwimCheck(static_cast<float>(8.0));
    testUser.RunCheck(static_cast<float>(9));
    testUser.BikeCheck(static_cast<float>(12.4));

    ProgressCheck();

    return 0;
};

bool Search(string name){

    ifstream file;
    std::string line;
    bool found = false;
    string user;
    file.open(USER_FILE, std::ios::app);

    while(getline(file, line)) {
        user = {};
        for (size_t i = 0; line[i] != ','; i++) {
            user = user + line[i];
            cout << user << endl;
            cout << name << endl;
        }
        if (user == name) {
            std::cout << name << " already exists!" << std::endl;
            std::cout << "Signing In!" << std::endl;
            found = true;
        }
    }

    file.close();
    return found;
};

void SignIn(std::string username) {
    UserT currentUser(username, 999);
};

/*
if (userExists) {
    SignIn(username);
}
*/
float FloatCheck(string input) {
    bool notValid = true;
    float number;
    while(notValid) {
        if (input.find_first_not_of("123456789.") != string::npos) {
            cout << "Invalid Number: " << input << endl;
            cout << "Enter a valid float value: ";
            cin >> input;
            cout << endl << endl;
        } else {
            number = static_cast<float>(atof(input.c_str()));
            notValid = false;
        }
    }
    return number;
}

void ProgressCheck() {
    UserT progressChecker ("Progress", 999);
    string swim;
    string bike;
    string run;

    float swimNum;
    float bikeNum;
    float runNum;

    char choice;

    bool notValid {true};

    cout << "--------------------------------------------------------------------------------------" << endl << endl;;
    cout << "                    WELCOME TO THE {BETA} OF THE PROGRESS TRACKER!" << endl;
    cout << "         Disclaimer: Bugs may be present! Please Report them to the retailer!" << endl << endl;

    cout << "--------------------------------------------------------------------------------------" << endl << endl;
    cout << "                       Enter your SWIM event speed (mph): ";
    cin >> swim;
    swimNum = FloatCheck(swim);
    cout << endl;
    cout << "--------------------------------------------------------------------------------------" << endl;
    cout << endl;
    cout << "                       Enter your BIKE event speed (mph): ";
    cin >> bike;
    bikeNum = FloatCheck(bike);
    cout << endl;
    cout << "--------------------------------------------------------------------------------------" << endl;
    cout << endl;
    cout << "                       Enter your RUN event speed (mph):  ";
    cin >> run;
    runNum = FloatCheck(run);
    cout << endl;
    cout << "--------------------------------------------------------------------------------------" << endl;
    cout << endl;

    while(notValid) {

        cout << "                       Select a comparison goal (A, B, C, D)" << endl << endl;
        cout << "                                   {A} Beginner" << endl;
        cout << "                                   {B} Intermediate" << endl;
        cout << "                                   {C} Expert" << endl;
        cout << "                                   {D} Custom" << endl << endl;
        cout << "--------------------------------------------------------------------------------------" << endl << endl;
        cout << "                                    Choice: ";
        cin >> choice;
        cout << endl;
        cout << "--------------------------------------------------------------------------------------" << endl << endl;
    
        if (tolower(choice) == 'a') {
            cout << "                                   Beginner Selected!" << endl;
            notValid = false;
            progressChecker.SetSwim(static_cast<float>(1.0));
            progressChecker.SetRun(static_cast<float>(12.0));
            progressChecker.SetBike(static_cast<float>(6.0));

        } else if (tolower(choice) == 'b') {
            cout << "                               Intermediate Selected!" << endl;
            notValid = false;
            progressChecker.SetSwim(static_cast<float>(2.0));
            progressChecker.SetRun(static_cast<float>(16.0));
            progressChecker.SetBike(static_cast<float>(8.0));

        } else if (tolower(choice) == 'c') {
            cout << "                                   Expert Selected!" << endl;
            notValid = false;
            progressChecker.SetSwim(static_cast<float>(2.5));
            progressChecker.SetRun(static_cast<float>(20.0));
            progressChecker.SetBike(static_cast<float>(10.0));
            
        } else if (tolower(choice) == 'd') {
            cout << "                                   Custom Selected!" << endl;
            progressChecker.CheckTargets();
            notValid = false;
        } else {
            cout << "                                   Input Invalid!" << endl;
        }

    }
    notValid = true;
    cout << "--------------------------------------------------------------------------------------" << endl << endl;
    progressChecker.SwimCheck(swimNum);
    cout << "--------------------------------------------------------------------------------------" << endl << endl;
    progressChecker.BikeCheck(bikeNum);
    cout << "--------------------------------------------------------------------------------------" << endl << endl;
    progressChecker.RunCheck(runNum);
    cout << "--------------------------------------------------------------------------------------" << endl << endl;
    return;
}

