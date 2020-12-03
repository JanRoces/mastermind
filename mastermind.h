#include <string>
using namespace std;

class mastermind
{
    public:
        mastermind(int);
        mastermind(int, string[]);
        int move(string[], int&, int&);
        int getMoveIndex();
        string getPegs(int);

    private:
        const int MAX_MOVES;
        string pegs[10];
        int moves;
        int cols;
};

struct guess
{
    public:
        string guess[4];
        int x;
        int o;
        int turn;
};



