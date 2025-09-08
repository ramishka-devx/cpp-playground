#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;

enum Category {
    STANDARD = 0,
    DUO = 1,
    TRIO = 2,
    ORDERED = 3,
    PALINDROME = 4,
    QUINTESSENTIAL = 5
};

struct WordRank {
    Category category;
    char tieBreaker;
    int length;
    string word;
};

// Check if word has 5 or more identical letters
bool isQuintessential(const string& word, char& letter) {
    map<char, int> freq;
    for (char c : word) {
        freq[c]++;
        if (freq[c] >= 5) {
            letter = c;
            return true;
        }
    }
    return false;
}

// Check if word is palindrome with length >= 3
bool isPalindrome(const string& word) {
    if (word.length() < 3) return false;
    string rev = word;
    reverse(rev.begin(), rev.end());
    return word == rev;
}

// Check if letters are in non-decreasing order
bool isOrdered(const string& word) {
    for (size_t i = 1; i < word.length(); i++) {
        if (word[i] < word[i-1]) {
            return false;
        }
    }
    return true;
}

// Check if word has exactly three of the same letter and no other pairs
bool isTrio(const string& word, char& letter) {
    map<char, int> freq;
    for (char c : word) {
        freq[c]++;
    }
    
    int threeCount = 0;
    char threeLetter = 0;
    
    // First, check if there's exactly one letter that appears exactly three times
    for (auto& p : freq) {
        if (p.second == 3) {
            threeCount++;
            threeLetter = p.first;
        }
    }
    
    // If we found a trio, now check if any other letters are paired (appear >= 2 times)
    if (threeCount == 1) {
        for (auto& p : freq) {
            // Skip the letter that appears three times
            if (p.first == threeLetter) continue;
            
            // If any other letter appears 2 or more times, this is not a valid trio
            if (p.second >= 2) {
                return false;
            }
        }
        letter = threeLetter;
        return true;
    }
    
    return false;
}

// Check if word has exactly two of the same letter and no other pairs
bool isDuo(const string& word, char& letter) {
    map<char, int> freq;
    for (char c : word) {
        freq[c]++;
    }
    
    int pairCount = 0;
    char pairLetter = 0;
    
    // First, check if there's exactly one letter that appears exactly twice
    for (auto& p : freq) {
        if (p.second == 2) {
            pairCount++;
            pairLetter = p.first;
        }
    }
    
    // If we found a pair, now check if any other letters are paired (appear >= 2 times)
    if (pairCount == 1) {
        for (auto& p : freq) {
            // Skip the letter that appears twice
            if (p.first == pairLetter) continue;
            
            // If any other letter appears 2 or more times, this is not a valid duo
            if (p.second >= 2) {
                return false;
            }
        }
        letter = pairLetter;
        return true;
    }
    
    return false;
}

WordRank analyzeWord(const string& word) {
    WordRank rank;
    rank.word = word;
    rank.length = word.length();
    
    char letter;
    
    if (isQuintessential(word, letter)) {
        rank.category = QUINTESSENTIAL;
        rank.tieBreaker = letter;
    } else if (isPalindrome(word)) {
        rank.category = PALINDROME;
        rank.tieBreaker = word.back(); // Last character for alphabetical comparison
    } else if (isOrdered(word)) {
        rank.category = ORDERED;
        rank.tieBreaker = *max_element(word.begin(), word.end()); // Highest letter
    } else if (isTrio(word, letter)) {
        rank.category = TRIO;
        rank.tieBreaker = letter;
    } else if (isDuo(word, letter)) {
        rank.category = DUO;
        rank.tieBreaker = letter;
    } else {
        rank.category = STANDARD;
        rank.tieBreaker = word.back(); // Last character for alphabetical comparison
    }
    
    return rank;
}

int compareWords(const WordRank& black, const WordRank& white) {
    // First compare categories
    if (black.category != white.category) {
        return (black.category > white.category) ? 1 : -1;
    }
    
    // Same category, apply tie-breaking rules
    switch (black.category) {
        case QUINTESSENTIAL:
            // More valuable letter wins
            if (black.tieBreaker != white.tieBreaker) {
                return (black.tieBreaker > white.tieBreaker) ? 1 : -1;
            }
            break;
            
        case PALINDROME:
            // Longer word wins, then alphabetically later
            if (black.length != white.length) {
                return (black.length > white.length) ? 1 : -1;
            }
            if (black.word != white.word) {
                return (black.word > white.word) ? 1 : -1;
            }
            break;
            
        case ORDERED:
            // Longer word wins, then more valuable highest letter
            if (black.length != white.length) {
                return (black.length > white.length) ? 1 : -1;
            }
            if (black.tieBreaker != white.tieBreaker) {
                return (black.tieBreaker > white.tieBreaker) ? 1 : -1;
            }
            break;
            
        case TRIO:
            // More valuable three-of-a-kind letter wins
            if (black.tieBreaker != white.tieBreaker) {
                return (black.tieBreaker > white.tieBreaker) ? 1 : -1;
            }
            break;
            
        case DUO:
            // More valuable two-of-a-kind letter wins
            if (black.tieBreaker != white.tieBreaker) {
                return (black.tieBreaker > white.tieBreaker) ? 1 : -1;
            }
            break;
            
        case STANDARD:
            // Alphabetically later word wins
            if (black.word != white.word) {
                return (black.word > white.word) ? 1 : -1;
            }
            break;
    }
    
    return 0; // Tie
}

// Function to convert Category enum to string name for debugging
string getCategoryName(Category cat) {
    switch(cat) {
        case STANDARD: return "STANDARD";
        case DUO: return "DUO";
        case TRIO: return "TRIO";
        case ORDERED: return "ORDERED";
        case PALINDROME: return "PALINDROME";
        case QUINTESSENTIAL: return "QUINTESSENTIAL";
        default: return "UNKNOWN";
    }
}

int main() {
    string blackWord, whiteWord;
    
    while (cin >> blackWord >> whiteWord) {
        WordRank blackRank = analyzeWord(blackWord);
        WordRank whiteRank = analyzeWord(whiteWord);
        
        int result = compareWords(blackRank, whiteRank);
        
        // Print category names for debugging
        cout << "Black word: " << blackWord << " - Category: " << getCategoryName(blackRank.category) 
             << ", Tie-breaker: " << blackRank.tieBreaker << endl;
        cout << "White word: " << whiteWord << " - Category: " << getCategoryName(whiteRank.category) 
             << ", Tie-breaker: " << whiteRank.tieBreaker << endl;
        
        if (result > 0) {
            cout << "Black wins." << endl;
        } else if (result < 0) {
            cout << "White wins." << endl;
        } else {
            cout << "Tie." << endl;
        }
        cout << "--------" << endl; // Add separator for clarity
    }
    
    return 0;
}