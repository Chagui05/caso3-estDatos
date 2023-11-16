#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int calculateRating(const std::string& paragraph, const std::vector<std::string>& words) {
    // Tokenize the paragraph into words
    std::vector<std::string> paragraphWords;
    size_t startPos = 0;
    size_t endPos = paragraph.find(' ');
 
    while (endPos != std::string::npos) {
        paragraphWords.push_back(paragraph.substr(startPos, endPos - startPos));
        startPos = endPos + 1;
        endPos = paragraph.find(' ', startPos);
    }
    paragraphWords.push_back(paragraph.substr(startPos));
 
    // Initialize a vector to store the positions of the words in the paragraph
    std::vector<int> positions;
 
    // Find the positions of the target words in the paragraph
    for (const std::string& word : words) {
        auto it = std::find(paragraphWords.begin(), paragraphWords.end(), word);
        while (it != paragraphWords.end()) {
            int position = std::distance(paragraphWords.begin(), it);
            positions.push_back(position);
            it = std::find(std::next(it), paragraphWords.end(), word);
        }
    }
 
    // Calculate the rating based on the presence and distances of words
    if (positions.empty()) {
        return 0; // No words found in the paragraph
    }
 
    int rating = 0;
    for (size_t i = 0; i < positions.size() - 1; i++) {
        // Calculate the distance between positions
        int distance = positions[i + 1] - positions[i];
        // Increase the rating inversely with the distance
        rating += INT_MAX - distance;
    }
 
    // Adding a constant value for each found word
    rating += positions.size() * INT_MAX;
 
    return rating;
}

// int main() {
//     string paragraph = "THe beast of the night returns, as the beast arises, the night does so, the night is young beast beast beast beast night night hello hello hello beast night";
//     vector<string> wordsToLookFor = {"fourth", "attempt"};
//     string parra = "Our visitor gave a rather shamefaced laugh. �Shillings have not been so plentiful with me as they once were,� he remarked. �I had no doubt that the gang of roughs who assaulted me had carried off both my hat and the bird. I did not care to spend more money in a hopeless attempt at";

//     int rating = calculateRating(paragraph, wordsToLookFor);
//     int rate = calculateRating(parra, wordsToLookFor);
//     std::cout << "Rating: " << rate << std::endl;

//     return 0;
// }
