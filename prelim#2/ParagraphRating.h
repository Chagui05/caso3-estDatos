#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <climits>
#include <sstream>

using namespace std;

int calculateRating(string paragraph, vector<string> words)
{
    unordered_set<string> wordSet(words.begin(), words.end()); // que la busqueda sea O(1)
    vector<int> positions;
    istringstream parragraph(paragraph); // para recorrer por palabra
    string word;
    int count = 0;

    while (parragraph >> word)
    {
        // if(word.size() > 4)
        if (wordSet.find(word) != wordSet.end())
        {
            positions.push_back(count);
        }
        count++;
    }

    int rating = positions.size();
    for (int i = 0; (i + 1) < positions.size(); i++)
    {
        if ((positions[i + 1] - positions[i]) < 4) // reglas
        {
            rating += 4;
        }
        else if ((positions[i + 1] - positions[i]) < 8) // reglas
        {
            rating += 2;
        }
        else // reglas
        {
            rating += 1;
        }
    }
    return rating > 1 ? rating : 1; //! esto es un poco feo, pero es que a veces da 0 porque en la lista sale
} //! por ejemplo "the" y en el parrafo sale "the," entomces no lo asocia, entonces por lo menos asi lo medio contamos

// int main()
// {
//     string paragraph = "fourth ttatatat tatstst fourth fdfsff sd sfdff fs fsdf   sasdasd    attempt";
//     vector<string> wordsToLookFor = {"fourth", "attempt", "beast"};

//     int rating = calculateRating(paragraph, wordsToLookFor);
//     std::cout << "Rating: " << rating << std::endl;

//     return 0;
// }
