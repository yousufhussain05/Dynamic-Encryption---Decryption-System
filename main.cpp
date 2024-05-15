#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <sstream>

using namespace std;

// Function to encrypt a message with a given initial shift and direction
string encryptedMessage (string message, int initialShift, char direction) {
    int currentShift = initialShift;
    string changedString = "";

    for (int i = 0; i < message.length(); i++) {
        char currChar = message.at(i);
        currChar = toupper(currChar);
        int num;

        // Convert character to a number 
        if (isalpha(currChar)) {
            num = currChar - 'A';
        }    
        else if (currChar == ' ') {
            num = 26;
        }
        // If character is not a letter or space, keep it unchanged
        else {
            changedString += currChar;
            continue;
        }
        int shiftedValue;

        // Calculate the shifted value based on the current direction
        if (direction == 'f') {
            shiftedValue = (num + currentShift) % 27;
        }
        else if (direction == 'b') {
            shiftedValue = (num + currentShift) % 27;
        }

        // Convert the shifted value back to a character
        if (shiftedValue == 26) {
            currChar = ' ';
        }
        else {
            currChar = 'A' + shiftedValue;
        }

        changedString += currChar;

        // Update the shift for the next character
        currentShift = (currentShift + num + initialShift) % 27;
    }   

        // If direction is backward, reverse the encrypted string
        if (direction == 'b') {
            reverse(changedString.begin(), changedString.end());
        }
    return changedString;
}

// Function to decrypt a message with a given initial shift and direction
string decryptedMessage (string message, int initialShift, char direction) {
    int currentShift = initialShift;
    string changedString = "";

    // If direction is backward, reverse the message first
    if (direction == 'b') {
        reverse(message.begin(), message.end());
    }

    for (int i = 0; i < message.length(); i++) {
        char currChar = message.at(i);
        currChar = toupper(currChar);
        int num;

        // Convert character to a number 
        if (isalpha(currChar)) {
            num = currChar - 'A';
        }    
        else if (currChar == ' ') {
            num = 26;
        }

        // If character is not a letter or space, keep it unchanged
        else {
            changedString += currChar;
            continue;
        }

        // Calculate the shifted value for decryption
        int shiftedValue = (num - currentShift + 27) % 27;

        // Convert the shifted value back to a character
        if (shiftedValue == 26) {
            currChar = ' ';
        }
        else {
            currChar = 'A' + shiftedValue;
        }

        if (isalpha(currChar)) {
            num = currChar - 'A';
        }    
        else if (currChar == ' ') {
            num = 26;
        }

        changedString += currChar;

        // Update the shift for the next character
        currentShift = (currentShift + num + initialShift) % 27;
    }  

    return changedString;
}

// Function to display all possible decrypted strings using every possible shift
void decryptedPossibilites (string message) {
    for (int i = 1; i < 27; i++) {
        string changedStringF = decryptedMessage(message, i, 'f');
        string changedStringB  = decryptedMessage(message, i, 'b');
        cout << i << "f: " << changedStringF << endl;
        cout << i << "b: " << changedStringB << endl;
    }
}

// Function to attempt breaking the code by finding the 10 most common words in the English language
bool brokenCode (string message) {
    vector <string> commonWords = {"THE", "BE", "TO", "OF", "AND", "A", "IN", "THAT", "HAVE", "I"};
    bool found = false; 
    string bestMatch;
    int maxCommonWordCount = 0;

    for (int i = 1; i < 27; i++) {

        // Try decrypting with every possible key and check for common words
        string changedStringF = decryptedMessage(message, i, 'f');
        string changedStringB  = decryptedMessage(message, i, 'b');

        for (int j = 0; j < 2; j++) {
            string currentString;
            if (j == 0) {
                currentString = changedStringF;
            }
            else {
                currentString = changedStringB; 
            }

            stringstream messageStream(currentString);
            string word;
            int commonWordCount = 0;

            // Count the number of common words in the decrypted message
            while (messageStream >> word) {
                for (int k = 0; k < commonWords.size(); k++) {
                    if (word == commonWords.at(k)) {
                        commonWordCount++;
                        break;
                    }
                }
            }

            // Update best match if current decryption has more common words
            if (commonWordCount > maxCommonWordCount) {
                maxCommonWordCount = commonWordCount;
                bestMatch = currentString;
                cout << "Decrypted message is: " << currentString << endl;
                found = true;
            }
        }
    }

    return found;
}


int main() 
{
    // Main message:
	cout << "1. Encrypt message" << endl;
	cout << "2. Decrypt message" << endl;
	cout << "3. Show decrypted possibilities" << endl;
	cout << "4. Break code" << endl;
	cout << "Enter choice: " << endl;

    int choice;
    cin >> choice;
    cin.ignore();

    int shift;
    char direction;
    string message;   
    
    switch (choice) {

        case 1: {

            // Encrypt message
            cout << "Enter shift (1-26): " << endl;
            cin >> shift;
            cin.ignore();
            
            cout << "Enter direction (f or b): " << endl;
            cin >> direction;
            cin.ignore();

            cout << "Enter message: " << endl;
            getline(cin, message);

            string encryptedMessageResult = encryptedMessage (message, shift, direction);
            
            cout << "Encrypted message: " << encryptedMessageResult << endl;
            break;
        }

        case 2: {
            // Decrypt message
            cout << "Enter shift (1-26): " << endl;
            cin >> shift;
            cin.ignore();

            cout << "Enter direction (f or b): " << endl;
            cin >> direction;
            cin.ignore();

            cout << "Enter message: " << endl;
            getline(cin, message);
            
            string decryptedMessageResult = decryptedMessage (message, shift, direction);
            cout << "Decrypted message: " << decryptedMessageResult << endl;
            break;
        }
        case 3: {

            // Show all possible decrypted messages
            cout << "Enter message: " << endl;
            getline(cin, message);
            decryptedPossibilites(message);
            break;
        }
        case 4: {

            // Attempt to break the code
            cout << "Enter message: " << endl;
            getline(cin, message);
            bool brokenCodeResult = brokenCode(message);

            if (brokenCodeResult == false) {
                cout << "Unable to find a decrypted message." << endl;
            }
            break;
        }    

    }

}
