#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <climits>

using namespace std;

int calculateRating(string paragraph,vector<string>words) {
    unordered_set<string> wordSet(words.begin(), words.end());// que la busqueda sea O(1)
    vector<int> positions;
    istringstream parragraph(paragraph);//para recorrer por palabra
    string word;
    int count = 0;

    while (parragraph >> word)
    {
        //if(word.size() > 4)
        if (wordSet.find(word) != wordSet.end())
        {
            positions.push_back(count);
        }
        count++;
    }

    int rating = positions.size();
    for(int i = 0; i < positions.size(); i++)
    {
        if((positions[i] - positions[i-1]) < 4)         //reglas
        {
            rating += 4;
        }
        else if((positions[i] - positions[i-1]) < 8)    //reglas
        {
            rating += 2;
        }
        else                                            //reglas
        {
            rating += 1;
        }
    }
    return rating > 1 ? rating : 1; //!esto es un poco feo, pero es que a veces da 0 porque en la lista sale 
    }                               //!por ejemplo "the" y en el parrafo sale "the," entomces no lo asocia, entonces por lo menos asi lo medio contamos 






// int main() {
//     string paragraph = "The beast of the fourth returns, as the beast arises , the night does so, the night is young beast beast beast beast night night hello hello hello beast night";
//     vector<string> wordsToLookFor = {"fourth", "attempt", "beast"};

//     int rating = calculateRating(paragraph, wordsToLookFor);
//     int rate = calculateRating(paragraph, wordsToLookFor);
//     std::cout << "Rating: " << rate << std::endl;

//     return 0;
// }
