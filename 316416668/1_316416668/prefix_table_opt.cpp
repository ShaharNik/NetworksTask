#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
using namespace std;

struct Node
{
	string input;
	Node *Left0;  // 0
	Node *Right1; // 1
	Node *Parent;
	int depth;
	bool isEnd;
};

struct Root
{
	string input;
	Node *Left0;  // 0
	Node *Right1; // 1
	int depth;
	int totalNodes;
	bool isEnd;
};

Root *buildRoot()
{

	string input = "";
	Root *trie = new Root;
	trie->depth = 0;
	trie->totalNodes = 0;
	trie->Left0 = nullptr;
	trie->Right1 = nullptr;
	return trie;
}

Node *buildNode()
{
	string input = "";
	Node *trie = new Node;
	trie->depth = 0;
	trie->Left0 = nullptr;
	trie->Right1 = nullptr;
	trie->Parent = nullptr;
	return trie;
}

void toBinary(int byte1, int byte2, int byte3, int byte4, int* binary)
{
    int start = 0;
    int counter = 7;
    while(byte1 != 0)
    {
        *(binary+start+counter) = (byte1 % 2 == 0 ? 0:1);
        byte1/=2;
        counter--;

    }
    counter = 7;
    start = 8;
    while(byte2 != 0)
    {
        *(binary+start+counter) = (byte2 % 2 == 0 ? 0:1);
        byte2/=2;
        counter--;

    }
    counter = 7;
    start = 16;
    while(byte3 != 0)
    {
        *(binary+start+counter) = (byte3 % 2 == 0 ? 0:1);
        byte3/=2;
        counter--;

    }
    counter = 7;
    start = 24;
    while(byte4 != 0)
    {
        *(binary+start+counter) = (byte4 % 2 == 0 ? 0:1);
        byte4/=2;
        counter--;

    }
}

void add(vector<string> input, Root *trie)
{
	// cout << input[0] << " " << input[1] << endl;
	int byte1, byte2, byte3, byte4;
	char dot;
	int subnet;

	string addr = input[0];
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


		pos->input = input[1];
		pos->isEnd = true;
         if(pos->Parent->Left0 != nullptr && pos->Parent->Right1 != nullptr)
        {
            if(pos->Parent->Left0->isEnd == true && pos->Parent->Right1->isEnd == true)
            {
                if(pos->Parent->Left0->input == pos->Parent->Right1->input)
                {
                    pos = pos->Parent;
                    delete(pos->Left0);
                    delete(pos->Right1);
                    pos->Left0=nullptr;
                    pos->Right1=nullptr;
                    trie->totalNodes -=2;
                    subnet--;
                }
            }
        }
		
		pos->input = input[1];
		pos->isEnd = true;


    

		cout << "Added " << input[0] << " " << input[1] << " at the depth " << pos->depth << ", total Nodes " << trie->totalNodes << endl;
	}
}
void find(vector<string> input, Root *trie)
{
	int byte1, byte2, byte3, byte4;
	char dot;

	string addr = input[0];
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
			cout << "Not Found" << endl;
			return;
		}
		pos = trie->Left0;
	}
	else
	{
		if (trie->Right1 == nullptr)
		{
			cout << "Not Found" << endl;
			return;
		}
		pos = trie->Right1;
	}

	for (int i = 1; i < 32; i++)
	{
		if (pos->isEnd == true)
		{
			ans = pos->input;
			depthAns = pos->depth;
			
		}
		if (binary[i] == 0)
		{
			if (pos->Left0 == nullptr)
			{
				if (ans.empty())
				{
					cout << "Not Found" << endl;
					return;
				}
				else
				{

					cout << "Found " << input[0] << " " << ans << " at the depth " << depthAns << endl;
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
					cout << "Not Found" << endl;
					return;
				}
				else
				{

					cout << "Found " << input[0] << " " << ans << " at the depth " << depthAns << endl;
					return;
				}
			}
			pos = pos->Right1;
		}
	}
}
void remove(vector<string> input, Root *trie)
{
	int byte1, byte2, byte3, byte4;
	char dot;
	int subnet;

	string addr = input[0];
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
				cout << "Unable to delete" << endl;
				return;
			}
			pos = trie->Left0;
		}
		else
		{
			if (trie->Right1 == nullptr)
			{
				cout << "Unable to delete" << endl;
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
					cout << "Unable to delete" << endl;
					return;
				}
				pos = pos->Left0;
			}
			else
			{
				if (pos->Right1 == nullptr)
				{
					cout << "Unable to delete" << endl;
					return;
				}
				pos = pos->Right1;
			}
		}
		if (pos->input == input[1])
		{
			int depthAns = pos->depth;
			bool finish = false;
			pos->isEnd=false;
			pos->input="";
			while (!finish)
			{
				if (pos != nullptr)
				{

					if (pos->Left0 == nullptr && pos->Right1 == nullptr && (pos->isEnd == false || pos->depth == depthAns))
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
							finish = true;
						}

						trie->totalNodes--;
					}
					else
					{
						finish = true;
					}
				}
				else
				{
					finish = true;
				}
			}
			cout << "Removed " << input[0] << " " << input[1] << " at the depth " << depthAns << ", total Nodes " << trie->totalNodes << endl;
		}
	}
}

void requests(vector<string> input, Root *trie)
{
	if (input.size() >= 0)
	{
		string act = input[0];
		if (act.compare("ADD") == 0)
		{
			input.erase(input.begin());
			add(input, trie);
		}
		else if (act.compare("FIND") == 0)
		{
			input.erase(input.begin());
			find(input, trie);
		}
		else if (act.compare("REMOVE") == 0)
		{
			input.erase(input.begin());
			remove(input, trie);
		}
	}
}

int main(int argc, char **argv)
{
	// argv[1] inputfile
	Root *trie = buildRoot();
	string line;
	ifstream myfile(argv[1]);
	if (myfile.is_open())
	{

		while (getline(myfile, line))
		{
			vector<string> input;
			istringstream ss(line);
			for (string s; ss >> s;)
			{
				input.push_back(s);
			}
			requests(input, trie);
		}
		myfile.close();
	}
	return 0;
}