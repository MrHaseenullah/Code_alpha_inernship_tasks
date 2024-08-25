#include <iostream>   // For input/output operations (cin, cout)
#include <vector>     // For using the vector container (dynamic array)
#include <map>        // For using the map container (key-value pairs)
#include <fstream>    // For file handling (reading/writing files)
#include <string>     // For string manipulation
#include <cctype>     // For character handling functions like isalpha, isdigit

using namespace std;

// User class to store user information
class User {
    string username;   // Username for the user
    string password;   // Password for the user
    int score;         // User's score in the quiz

public:
    // Default constructor
    User() : username(""), password(""), score(0) {}  // Initializes an empty user with a score of 0

    // Parameterized constructor
    User(string u, string p) : username(u), password(p), score(0) {}  // Initializes user with provided username and password, score set to 0

    // Getter for username
    string getUsername() const { return username; }

    // Getter for score
    int getScore() const { return score; }

    // Method to increment the user's score
    void incrementScore() { score++; }

    // Method to check if the provided password matches the user's password
    bool checkPassword(const string& p) const { return p == password; }
};

// Question class to manage questions, options, and correct answers
class Question {
    string questionText;          // The question text
    vector<string> options;       // List of possible answers (options)
    int correctOptionIndex;       // Index of the correct option

public:
    // Constructor to initialize the question, options, and correct answer index
    Question(const string& q, const vector<string>& opts, int correct) 
        : questionText(q), options(opts), correctOptionIndex(correct) {}

    // Method to display the question and its options
    void displayQuestion() const {
        cout << questionText << endl;
        for (int i = 0; i < options.size(); ++i) {
            cout << i + 1 << ". " << options[i] << endl;  // Display options with numbers starting from 1
        }
    }

    // Method to check if the user's answer is correct
    bool checkAnswer(int userAnswer) const {
        return (userAnswer - 1) == correctOptionIndex;  // Adjust user input to 0-based index and compare with correct answer index
    }

    // Method to get the correct answer text
    string getCorrectAnswer() const {
        return options[correctOptionIndex];
    }
};

// Quiz class to manage the quiz game logic
class Quiz {
    map<string, User> users;  // Map to store users with username as the key
    vector<Question> questions;  // List of quiz questions

public:
    // Method to register a new user
    void registerUser(const string& username, const string& password) {
        if (users.find(username) == users.end()) {  // Check if the username is not already taken
            users[username] = User(username, password);  // Create and store the new user
            cout << "User registered successfully!" << endl;
        } else {
            cout << "Username already exists. Try a different one or login." << endl;
        }
    }

    // Method to login a user; returns a pointer to the User object if successful, nullptr otherwise
    User* loginUser(const string& username, const string& password) {
        auto it = users.find(username);
        if (it != users.end() && it->second.checkPassword(password)) {  // Check if the user exists and the password matches
            cout << "Login successful!" << endl;
            return &(it->second);  // Return pointer to the logged-in user
        }
        cout << "Invalid username or password." << endl;
        return nullptr;  // Return nullptr if login fails
    }

    // Method to add a new question to the quiz
    void addQuestion(const Question& q) {
        questions.push_back(q);  // Add the question to the list
    }

    // Method to start the quiz for a given user
    void startQuiz(User& user) {
        int userAnswer;
        for (const auto& q : questions) {  // Iterate over all questions
            q.displayQuestion();  // Display the current question
            cout << "Your answer: ";
            cin >> userAnswer;  // Get the user's answer
            if (q.checkAnswer(userAnswer)) {  // Check if the answer is correct
                user.incrementScore();  // Increment the user's score if the answer is correct
            }
        }
        displayResults(user);  // Display the results after the quiz
    }

    // Method to display the user's results after the quiz
    void displayResults(const User& user) const {
        cout << "Quiz Completed! Your score: " << user.getScore() << endl;  // Show the user's score
        cout << "Correct answers were:" << endl;
        for (const auto& q : questions) {  // Show the correct answers for all questions
            cout << q.getCorrectAnswer() << endl;
        }
    }

    // Method to load existing users from a file
    void loadUsersFromFile(const string& filename) {
        ifstream file(filename);  // Open the file for reading
        if (file.is_open()) {
            string username, password;
            while (file >> username >> password) {  // Read username and password pairs from the file
                users[username] = User(username, password);  // Create and store the user
            }
            file.close();  // Close the file
        }
    }

    // Method to save the current users to a file
    void saveUsersToFile(const string& filename) const {
        ofstream file(filename);  // Open the file for writing
        if (file.is_open()) {
            for (const auto& pair : users) {  // Write each user to the file
                file << pair.second.getUsername() << " " << pair.second.getScore() << endl;
            }
            file.close();  // Close the file
        }
    }

    // Method to check if a username is valid (no spaces allowed)
    bool isValidUsername(const string& username) {
        for (char c : username) {
            if (isspace(c)) {  // Check if the username contains any spaces
                return false;
            }
        }
        return true;  // Return true if no spaces are found
    }

    // Method to check if a password is valid (must contain both letters and digits)
    bool isValidPassword(const string& password) {
        bool hasLetter = false, hasDigit = false;
        for (char c : password) {
            if (isalpha(c)) hasLetter = true;  // Check for letters
            if (isdigit(c)) hasDigit = true;  // Check for digits
        }
        return hasLetter && hasDigit;  // Return true if both letters and digits are present
    }
};

int main() {
    Quiz quiz;

    // Load existing users from a file (if any)
    quiz.loadUsersFromFile("users.txt");

    // Add some questions to the quiz
    quiz.addQuestion(Question("What is the capital of France?", {"Paris", "London", "Berlin", "Madrid"}, 0));
    quiz.addQuestion(Question("2 + 2 equals?", {"3", "4", "5", "6"}, 1));
    quiz.addQuestion(Question("What is the largest planet?", {"Earth", "Mars", "Jupiter", "Saturn"}, 2));

    string username, password;
    char choice;

    cout << "Welcome to the quiz game!" << endl;
    do {
        cout << "Choose an option:" << endl;
        cout << "1. Register User" << endl;
        cout << "2. Login" << endl;
        cout << "Enter your choice (1 or 2): ";
        cin >> choice;

        switch (choice) {
            case '1': {
                // Registration process
                cout << "Register a new user:" << endl;
                do {
                    cout << "Username (no spaces): ";
                    cin >> username;
                    if (!quiz.isValidUsername(username)) {
                        cout << "Invalid username. Please enter a username without spaces." << endl;
                    }
                } while (!quiz.isValidUsername(username));

                do {
                    cout << "Password (must contain letters and digits): ";
                    cin >> password;
                    if (!quiz.isValidPassword(password)) {
                        cout << "Invalid password. Please enter a password with both letters and digits." << endl;
                    }
                } while (!quiz.isValidPassword(password));

                quiz.registerUser(username, password);  // Register the new user
                break;
            }
            case '2': {
                // Login process
                User* user = nullptr;
                while (user == nullptr) {  // Keep asking for username and password until login is successful
                    cout << "Login to start quiz:" << endl;
                    cout << "Username: ";
                    cin >> username;
                    cout << "Password: ";
                    cin >> password;

                    user = quiz.loginUser(username, password);  // Attempt to login
                }

                // Start the quiz and repeat based on user input
                do {
                    quiz.startQuiz(*user);  // Start the quiz for the logged-in user
                    cout << "Do you want to play again? (y/n): ";
                    cin >> choice;
                } while (choice == 'y' || choice == 'Y');

                return 0;  // Exit the program after the quiz
            }
            default:
                cout << "Invalid choice. Please select 1 or 2." << endl;
        }
    } while (choice != '2');

    // Save users to a file before exiting
    quiz.saveUsersToFile("users.txt");

    return 0;
}
