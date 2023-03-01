//User List Class

#include "userT.h"

#include <vector>

class UserListT {

public:

UserListT();
~UserListT();

int GetSize();
void PrintUsers();

private:
std::vector<UserT> list;


};