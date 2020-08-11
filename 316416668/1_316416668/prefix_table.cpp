#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
using namespace std;

struct Node
{
    string result;
    Node *Left0;	 // 0
    Node *Right1; // 1
    Node *Parent;
    int depth;
    bool isEnd;
};

struct Root
{
    string result;
    Node *Left0;	 // 0
    Node *Right1; // 1
    int depth;
    int totalNodes;
    bool isEnd;
};

Root *buildRoot()
{

    string result = "";
    Root *trie = new Root;
    trie->depth = 0;
    trie->totalNodes = 0;
    trie->Left0 = nullptr;
    trie->Right1 = nullptr;
    return trie;
}

Node *buildNode()
{
    string result = "";
    Node *trie = new Node;
    trie->depth = 0;
    trie->Left0 = nullptr;
    trie->Right1 = nullptr;
    trie->Parent = nullptr;
    return trie;
}

void toBinary(int byte1, int byte2, int byte3, int byte4, int* arr)
{
    int start = 0;
    int counter = 7;
    while(byte1 != 0)
    {
        *(arr+start+counter) = (byte1 % 2 == 0 ? 0:1);
        byte1/=2;
        counter--;

    }
    counter = 7;
    start = 8;
    while(byte2 != 0)
    {
        *(arr+start+counter) = (byte2 % 2 == 0 ? 0:1);
        byte2/=2;
        counter--;

    }
    counter = 7;
    start = 16;
    while(byte3 != 0)
    {
        *(arr+start+counter) = (byte3 % 2 == 0 ? 0:1);
        byte3/=2;
        counter--;

    }
    counter = 7;
    start = 24;
    while(byte4 != 0)
    {
        *(arr+start+counter) = (byte4 % 2 == 0 ? 0:1);
        byte4/=2;
        counter--;

    }
}

void add(vector<string> result, Root *trie)
{
    // cout << result[0] << " " << result[1] << '\n';
    int byte1, byte2, byte3, byte4;
    char dot;
    int subnet;

    string addr = result[0];
    istringstream s(addr);
    s >> byte1 >> dot >> byte2 >> dot >> byte3 >> dot >> byte4 >> dot >> subnet;
    int binary[32] = {0};
    toBinary(byte1, byte2, byte3, byte4, binary);


    if (subnet > 0)
    {
        Node *pos;
        if (binary[0] == 0)
        {
            if (trie->Left0 == nullptr)
            {
                trie->Left0 = buildNode();
                trie->Left0->depth = trie->depth + 1;
                trie->totalNodes++;
            }
            pos = trie->Left0;
        }
        else
        {
            if (trie->Right1 == nullptr)
            {
                trie->Right1 = buildNode();
                trie->Right1->depth = trie->depth + 1;
                trie->totalNodes++;
            }
            pos = trie->Right1;
        }

        for (int i = 1; i < subnet; i++)
        {
            if (binary[i] == 0)
            {
                if (pos->Left0 == nullptr)
                {
                    pos->Left0 = buildNode();
                    pos->Left0->depth = pos->depth + 1;
                    pos->Left0->Parent = pos;
                    trie->totalNodes++;
                }
                pos = pos->Left0;
            }
            else
            {
                if (pos->Right1 == nullptr)
                {
                    pos->Right1 = buildNode();
                    pos->Right1->depth = pos->depth + 1;
                    pos->Right1->Parent = pos;
                    trie->totalNodes++;
                }
                pos = pos->Right1;
            }
        }

        pos->result = result[1];
        pos->isEnd= true;
        cout << "Added " << result[0] << " " << result[1] << " at the depth " << pos->depth << ", total Nodes " << trie->totalNodes << '\n';
    }
}
void find(vector<string> result, Root *trie)
{
    int byte1, byte2, byte3, byte4;
    char dot;

    string addr = result[0];
    istringstream s(addr);
    s >> byte1 >> dot >> byte2 >> dot >> byte3 >> dot >> byte4; 
    int binary[32] = {0};
    toBinary(byte1, byte2, byte3, byte4, binary);

    string ans = "";
    int depthAns;
    Node *pos;

    if (binary[0] == 0)
    {
        if (trie->Left0 == nullptr)
        {
            cout << "Not Found" << '\n';
            return;
        }
        pos = trie->Left0;
    }
    else
    {
        if (trie->Right1 == nullptr)
        {
            cout << "Not Found" << '\n';
            return;
        }
        pos = trie->Right1;
    }

    for (int i = 1; i < 32; i++)
    {
        if (pos->isEnd== true)
        {
            ans = pos->result;
            depthAns = pos->depth;
        }
        if (binary[i] == 0)
        {
            if (pos->Left0 == nullptr)
            {
                if (ans.empty())
                {
                    cout << "Not Found" << '\n';
                    return;
                }
                else
                {

                    cout << "Found " << result[0] << " " << ans << " at the depth " << depthAns << '\n';
                    return;
                }
            }
            pos = pos->Left0;
        }
        else
        {
            if (pos->Right1 == nullptr)
            {
                if (ans.empty())
                {
                    cout << "Not Found" << '\n';
                    return;
                }
                else
                {

                    cout << "Found " << result[0] << " " << ans << " at the depth " << depthAns << '\n';
                    return;
                }
            }
            pos = pos->Right1;
        }
    }
}
void remove(vector<string> result, Root *trie)
{
    int byte1, byte2, byte3, byte4;
    char dot;
    int subnet;

    string addr = result[0];
    istringstream s(addr);
    s >> byte1 >> dot >> byte2 >> dot >> byte3 >> dot >> byte4 >> dot >> subnet; 
    int binary[32] = {0};
    toBinary(byte1, byte2, byte3, byte4, binary);

    if (subnet > 0)
    {
        Node *pos;
        if (binary[0] == 0)
        {
            if (trie->Left0 == nullptr)
            {
                cout << "Unable to delete" << '\n';
                return;
            }
            pos = trie->Left0;
        }
        else
        {
            if (trie->Right1 == nullptr)
            {
                cout << "Unable to delete" << '\n';
                return;
            }
            pos = trie->Right1;
        }
        for (int i = 1; i < subnet; i++)
        {
            if (binary[i] == 0)
            {
                if (pos->Left0 == nullptr)
                {
                    cout << "Unable to delete" << '\n';
                    return;
                }
                pos = pos->Left0;
            }
            else
            {
                if (pos->Right1 == nullptr)
                {
                    cout << "Unable to delete" << '\n';
                    return;
                }
                pos = pos->Right1;
            }
        }
        if (pos->result == result[1])
        {
            int depthAns = pos->depth;
            bool done = false;
            pos->isEnd=false;
            pos->result="";
            while (!done)
            {
                if (pos != nullptr)
                {

                    if (pos->Left0 == nullptr && pos->Right1 == nullptr && (pos->isEnd
             == false || pos->depth == depthAns))
                    {
                        Node *dot = pos;
                        if (pos->Parent != nullptr)
                        {
                            pos = pos->Parent;
                            delete (dot);
                            if (pos->Left0 == dot)
                            {
                                pos->Left0 = nullptr;
                            }
                            else
                            {
                                pos->Right1 = nullptr;
                            }
                        }
                        else
                        {
                            if (trie->Left0 == pos)
                            {
                                trie->Left0 = nullptr;
                            }
                            else
                            {
                                trie->Right1 = nullptr;
                            }
                            delete (pos);
                            done = true;
                        }

                        trie->totalNodes--;
                    }
                    else
                    {
                        done = true;
                    }
                }
                else
                {
                    done = true;
                }
            }
            cout << "Removed " << result[0] << " " << result[1] << " at the depth " << depthAns << ", total Nodes " << trie->totalNodes << '\n';
        }
    }
}

void requests(vector<string> result, Root *trie)
{
    if (result.size() >= 0)
    {
        string act = result[0];
        if (act.compare("ADD") == 0)
        {
            // cout << "ADD" << '\n';;
            result.erase(result.begin());
            add(result, trie);
        }
        else if (act.compare("FIND") == 0)
        {
            // cout << "FIND" << '\n';;
            result.erase(result.begin());
            find(result, trie);
        }
        else if (act.compare("REMOVE") == 0)
        {
            // cout << "REMOVE" << '\n';;
            result.erase(result.begin());
            remove(result, trie);
        }
    }
}

int main(int argc, char **argv)
{
    // argv[1] resultfile
    Root *trie = buildRoot();
    string line;
    ifstream myfile(argv[1]);
    if (myfile.is_open())
    {

        while (getline(myfile, line))
        {
            vector<string> result;
            istringstream ss(line);
            for (string s; ss >> s;)
            {
                result.push_back(s);
            }
            requests(result, trie);
        }
        myfile.close();
    }
    else
        cout << "Unable to open file";
    return 0;
}