#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>

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
        auto it = paragraphWords.begin();
        while (it != paragraphWords.end()) {
            it = std::find(it, paragraphWords.end(), word);
            if (it != paragraphWords.end()) {
                int position = std::distance(paragraphWords.begin(), it);
                positions.push_back(position);
                it++; // Move to the next position
            }
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
        rating += 1 + (INT_MAX - distance);
    }

    return rating;
}

// int main() {
//     std::string paragraph = "THe beast of the night returns, as the beast arises, the night does so, the night is young beast beast beast beast night night hello hello hello beast night";
//     std::vector<std::string> wordsToLookFor = {"beast", "night"};

//     int rating = calculateRating(paragraph, wordsToLookFor);
//     std::cout << "Rating: " << rating << std::endl;

//     return 0;
// }
