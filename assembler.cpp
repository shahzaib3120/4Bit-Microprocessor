#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>

using namespace std;
int int2bin(int n)
{
    int bin = 0;
    int rem, i = 1, step = 1;
    while (n != 0)
    {
        rem = n % 2;
        n /= 2;
        bin += rem * i;
        i *= 10;
    }
    return bin;
}
int main()
{
    // read a txt file and save its .bin file
    map<string, int> word2bin;
    word2bin["nop"] = 0;
    word2bin["ldi"] = 1;
    word2bin["add"] = 2;
    word2bin["mov"] = 3;
    word2bin["jmp"] = 4;
    word2bin["brne"] = 5;
    word2bin["inc"] = 6;
    word2bin["sub"] = 7;
    word2bin["out"] = 8;
    string line;
    ifstream myfile("test.txt");
    ofstream outfile("test.bin", ios::binary);
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            stringstream ss(line);
            string item;
            while (getline(ss, item, '\n'))
            {
                // get words in item
                string word;
                stringstream ss2(item);
                bool firtWord = true;
                while (getline(ss2, word, ' '))
                {
                    // for first word
                    // convert word to small letters
                    for (int i = 0; i < word.length(); i++)
                    {
                        word[i] = tolower(word[i]);
                    }
                    if (firtWord)
                    {
                        firtWord = false;
                        outfile << word2bin[word];
                    }
                    else
                    {
                        // for second word
                        if (word[0] == 'r')
                        {
                            outfile << int2bin(stoi(word.substr(1, word.length() - 1)));
                        }
                        else if (word[0] == '0' && word[1] == 'x')
                        {
                            outfile << int2bin(stoi(word.substr(2, word.length() - 1), nullptr, 16));
                        }
                        else
                        {
                            outfile << int2bin(stoi(word));
                        }
                    }
                }
            }
        }
        myfile.close();
    }
    else
        cout << "Unable to open file";
}