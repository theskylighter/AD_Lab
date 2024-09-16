// C++ implementation that determines
// 1) maximum and minimum of the sequence
// 2) second maximum of the sequence

// There should be two constructors, First should accept a filename and read
// reads a sequence (terminated by -1 and entries separated by comma). So sequence of five elements would be 23,56,12,7,9,-1

// And second constructor should read a number n and generate random sequence of n integers

// First constructor should be used to check that function is working correctly

// Second constructor (n should range from 100000 to 10000000) be used for 100 iterations to compare number of comparisons for traditional algorithm vs what was discussed in class today.
#include <vector>
#include <limits.h>
#include <sstream>
#include <iostream>
#include <fstream>
using namespace std;

class seq
{
public:
    vector<int> sequence;

    void readfile(const string &filename)
    {
        ifstream file;
        file.open(filename);
        if (!file.is_open())
        {
            cout << "Unable to open file" << endl;
        }
        else
        {
            cout << "Reading file.." << endl;
            string line;
            while (getline(file, line, ','))
            {
                if (stoi(line) == -1)
                    break;
                sequence.push_back(stoi(line));
            }
        }
        cout << "Sequence input is : " << endl;
        for (int num : sequence)
        {
            cout << num << " ";
        }
        file.close();
    }
    // CONSTRUCTOR 1
    seq(const string &filename)
    {
        readfile(filename);
    }

    // CONSTRUCTOR 2
    seq(int n)
    {
        fillRandom(n);
    }

    void fillRandom(int n)
    {
        for (int i = 0; i < n; i++)
        {
            sequence.push_back(rand());
        }
        // to show random no. generated
        //  cout<<"Sequence is : "<<endl;
        // for (int num:sequence){
        //      cout<<num<<" ";
        //  }
    }

    void trad_method()
    {

        if (sequence.empty())
        {
            cout << "empty sequence" << endl;
            return;
        }
        long long count = 0;
        int secMax = INT_MIN;
        int max = INT_MIN;
        int min = INT_MAX;
        for (int i = 0; i < sequence.size(); i++)
        {
            if (sequence[i] > max)
            {
                max = sequence[i];
            }
            count++;
            if (sequence[i] < min)
            {
                min = sequence[i];
            }
            count++;
            if (sequence[i] > secMax && sequence[i] < max)
            {
                secMax = sequence[i];
            }
            count++;
        }

        cout << "\n1. Traditional method -" << endl;
        cout << "Max : " << max << endl;
        cout << "Min : " << min << endl;
        cout << "2nd Max : " << secMax << endl;
        cout << "Count : " << count << "\n"
             << endl;
    }
    void new_method()
    {
        if (sequence.empty())
        {
            cout << "empty sequence" << endl;
            return;
        }
        vector<int> v1, v2, v3;
        v1 = sequence;
        long count = 0;
        while (v1.size() != 1)
        {
            v2 = v1;
            v1.clear();

            for (int i = 0; i < v2.size() - 1; i += 2)
            {
                v1.push_back(max(v2[i], v2[i + 1]));
                count++;
            }
            if (v2.size() % 2 == 1)
            {
                v1.push_back(v2.back());
            }
        }
        v3 = sequence;
        while (v3.size() != 1)
        {
            v2 = v3;
            v3.clear();
            for (int i = 0; i < v2.size() - 1; i += 2)
            {
                v3.push_back(min(v2[i], v2[i + 1]));
                count++;
            }
            if (v2.size() % 2 == 1)
            {
                v3.push_back(v3.back());
            }
                count++;
        }

        cout << "2. New Method" << endl;
        cout << "Max : " << v1[0] << endl;
        cout << "Min : " << v3[0] << endl;
        cout << "Count : " << count << "\n"
             << endl;
    }
};

int main()
{
    // cout<<"Menu :\n"<<"1. use sequence from file\n"<<"input n for random integers\n"<<endl;
    cout << "Using Constructor 1(file) " << endl;
    seq obj1("seq.txt");
    obj1.trad_method();
    obj1.new_method();

    cout << "\n\nUsing Constructor 2(random)" << endl;
    int n;
    cout << "enter n" << endl;
    cin >> n;
    seq obj2(n);
    obj2.trad_method();
    obj2.new_method();

    return 0;
}