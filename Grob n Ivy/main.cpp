#include "cGameManager.h"
#include <memory>

using namespace std;

int main()
{
    shared_ptr<cGameManager> myGame(new cGameManager());

    return 0;
}