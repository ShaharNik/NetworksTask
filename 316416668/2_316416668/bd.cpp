//
// Created by Shahar on 29/07/2020.
//
#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
#include <fstream>



using namespace std;
struct packet
{
    int amount;
    int slack;
    int value;
};

int totalArrivedPackets = 0;
int totalDroppedPackets = 0;
int totalValueTransmitted = 0;
int countPacketsTransmitted = 0;
int bufferCapacity;


void inputToPacket(string input, packet &triple)
{
    int s1,s2,s3;
    char c;
    //cout << input << endl; // (a,s,v)
    istringstream s(input);
    s >> c >> s1 >> c >> s2 >> c >> s3 >> c;

    triple.amount = s1;
    triple.slack = s2;
    triple.value = s3;
}

void cleanVector(vector<packet> &bufferVec) {
    for (int i = 0; i < bufferVec.size();)
    {
        if (bufferVec.at(i).slack <= 0) {
            bufferVec.erase(bufferVec.begin() + i);
            totalDroppedPackets++;
        }
        else // if we didn't erase
        {
            ++i;
        }
    }
}

void processing(vector<packet> &bufferVec)
{
    int indexMaxValue = 0;
    // bufferVec.at(0).slack;
    //bool flag = false;
    for (int i = 0; i < bufferVec.size(); ++i)
        bufferVec.at(i).slack--;
    cleanVector(bufferVec);
    for (int i = 0; i < bufferVec.size(); ++i) // save max value index to transmit
    {
        if (bufferVec.at(i).value > bufferVec.at(indexMaxValue).value) {
            indexMaxValue = i; // 0
        }
    }

    // T1       T2      T3    T4    T5
    // (2,3,6)(2,3,6)(3,4,1)(3,4,1)(3,4,1)
    if (bufferVec.size() > 0) {
        totalValueTransmitted += bufferVec.at(indexMaxValue).value;
        bufferVec.erase(bufferVec.begin() + indexMaxValue);
        countPacketsTransmitted++;
    }
}
bool findMinValue(vector<packet> &bufferVec, packet triple, int &indexMinValue)
{
    // if packet with higher value (maximum) founded, update indexMaxValue and return true
    // else return false;
    bool found = false;
    int MinValue = bufferVec.at(0).value;

    for(int i = 0; i < triple.amount; i++)
    {
        if (bufferVec.at(i).value < triple.value && bufferVec.at(i).value <= MinValue) {
            found = true;
            MinValue = bufferVec.at(i).value;
            indexMinValue = i;
        }
    }
    if (found == true)
        return true;
    else
        return false;
}
void processLine(vector<string> &input, vector<packet> &bufferVec)
{

    if (input.size() > 0)
    {
        for (int i = 0; i < input.size(); ++i) // -----=======  running on all packets ====---
        {
            // --=== create a packet "triple" from string (amount,slack,value) ===----
            packet triple;
            inputToPacket(input.at(i), triple);
            totalArrivedPackets += triple.amount;

            if (triple.amount > bufferCapacity) // CHECK
            {
                totalDroppedPackets += triple.amount - bufferCapacity;
                triple.amount = bufferCapacity;
            }

            for(int i = 0; i < triple.amount; i++)
            {

                // There is place
                if (bufferVec.size() < bufferCapacity)
                    bufferVec.push_back(triple); // why SEG FAULT ?! (2nd iteration)
                else // No place - need replacement
                {
                    // 1 packet is dropped - buffer is Full
                    totalDroppedPackets++;
                    int indexMinValue;
                    if (findMinValue(bufferVec, triple, indexMinValue))
                        bufferVec.at(indexMinValue) = triple; // Replace if founded
                }
            }
        }
        // Processing
        cleanVector(bufferVec);
        if (bufferVec.size() == 0)
            cout << "Buffer is Empty!" << endl;
        else
            processing(bufferVec);

        //cout << "Total arrived packets " << totalArrivedPackets << ", total dropped packets " << totalDroppedPackets << ", total transmitted packets " << countPacketsTransmitted << ", total transmitted value " << totalValueTransmitted << endl;
    }
    // n rows - n actions

}

int main(int argc, char **argv) // int argc, char **argv
{
    vector<packet> bufferVec;

    //  cout << argv[1] << endl; //buffer size
    //  cout << argv[2]<< endl;; // file name
    bufferCapacity = atoi(argv[1]);
    //bufferCapacity = 4;
    // ---== get vector of string (amount,slack,value) from file ===----
    //fromFileToInputVector(input);

    string line;
    ifstream myfile;
    myfile.open(argv[2]);
    //myfile.open("C:\\Users\\Shahar\\CLionProjects\\FinalTASK2\\sample_input.txt");
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            vector<string> input;
            istringstream ss(line);
            for (string s; ss >> s;)
                input.push_back(s); // format: (a,s,v)
            processLine(input, bufferVec); // vector of tripels in line
        }
        //cout << "---=== Transmit left packet ===-----" << endl;
        while (bufferVec.size() > 0)
        {
            //cout << "You need to empty buffer" << endl;
            processing(bufferVec);
            //if (bufferVec.size() > 0)
            // cout << "Total arrived packets " << totalArrivedPackets << ", total dropped packets " << totalDroppedPackets << ", total transmitted packets " << countPacketsTransmitted << ", total transmitted value " << totalValueTransmitted << endl;
        }
        cout << "Total arrived packets " << totalArrivedPackets << ", total dropped packets " << totalDroppedPackets << ", total transmitted packets " << countPacketsTransmitted << ", total transmitted value " << totalValueTransmitted << endl;
        myfile.close();
        /*
        for (int i = 0; i < input.size(); ++i) {
            cout << input.at(i) << endl; // (a,s,v)
        }
         */
    }
    else
        cout << "Unable to open file";
}




