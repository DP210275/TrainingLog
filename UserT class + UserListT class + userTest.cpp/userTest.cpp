//User Test File

//To Do:
//Fix username searching, needs to be exact, instead of pieces

#include "userT.h"
#include "userListT.h"

using namespace std;

bool Search(string name);

int main () {

    ofstream outFile;
    string username;
    int newID;

    UserListT list = UserListT();

    newID = list.GetSize() + 1;
    list.PrintUsers();

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
    return 0;
};

bool Search(string name){

    ifstream file;
    std::string line;
    int i;
    bool found = false;

    file.open(USER_FILE, std::ios::app);

    while(getline(file, line)) {
        i++;
        if (line.find(name) != std::string::npos) {
            std::cout << "Error: " << name << " already exists!" << std::endl;
            found = true;
        }
    }
    file.close();
    return found;
};

