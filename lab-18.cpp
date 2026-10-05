// COMSC-210-5293 | Lab 18 | Yuyi Chen

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
using namespace std;

struct Review {
    double rating;
    string comment;
    Review *next;
};

class Movie {
    private:
        string title;
        Review *head;
    
    public:
        Movie(string);
        ~Movie();

        Movie(const Movie &);
        Movie& operator=(const Movie &);

        void addReview(double, string);
        void output() const;
};

int main() {
    // Seed the random number generator using the current time
    srand(time(0));

    ifstream fin("input.txt");

    // Stop the program if the review file cannot be opened
    if (!fin) {
        cout << "Error opening input.txt" << endl;
        return 1;
    }

    vector<string> comments;
    string comment;

    while (getline(fin, comment)) {
        comments.push_back(comment);
    }

    fin.close();

    vector<Movie> movies;

    movies.push_back(Movie("Interstellar"));
    movies.push_back(Movie("The Dark Knight"));
    movies.push_back(Movie("Inception"));
    movies.push_back(Movie("The Lord of the Rings"));

    int commentIndex = 0;

    // Give each movie three reviews from input.txt
    for (int i = 0; i < movies.size(); i++) {
        for (int j = 0; j < 3; j++) {
            // Generate a random rating from 1.0 to 5.0
            double rating = ((rand() % 41) + 10) / 10.0;

            movies[i].addReview(rating, comments[commentIndex]);

            commentIndex++;
        }
    }

    // Display all movie reviews and averages
    for (int i = 0; i < movies.size(); i++) {
        movies[i].output();
    }

    return 0;
}

// Movie() creates a Movie object with a title and an empty review list
// arguments: a string containing the movie title
// returns: none
Movie::Movie(string t) {
    title = t;
    head = nullptr;
}

// addReview() adds a new review to the head of the linked list
// arguments: a rating and a review comment
// returns: none
void Movie::addReview(double r, string c) {
    Review *newReview = new Review;

    newReview->rating = r;
    newReview->comment = c;

    // New node points to the old head, then becomes the new head
    newReview->next = head;
    head = newReview;
}

// ~Movie() deletes all reviews when a Movie object is destroyed
// argument: none
// returns: none
Movie::~Movie() {
    Review *current = head;

    // Delete each node one at a time to free dynamic memory
    while (current) {
        head = current->next;
        delete current;
        current = head;
    }

    head = nullptr;
}

// output() displays the movie title, reviews, ratings, and average rating
// arguments: none
// returns: none
void Movie::output() const {
    cout << fixed << setprecision(1);

    cout << "Movie Title: " << title << endl;

    Review *current = head;
    int count = 1;
    double total = 0.0;

    // Traverse the linked list and output each review
    while (current) {
        cout << "> Review #" << count << ": "
             << current->rating << ": "
             << current->comment << endl;
        
        total += current->rating;
        count++;
        current = current->next;
    }

    // Calculate the average only if the movie has reviews
    if (count > 1) {
        double average = total / (count - 1);
        cout << "> Average: " << average << endl;
    }

    cout << endl;
}

// Movie() creates a deep copy of another Movie object
// arguments: another Movie object passed by reference
// returns: none
Movie::Movie(const Movie &other) {
    title = other.title;
    head = nullptr;

    Review *current = other.head;
    Review *tail = nullptr;

    // Copy every review into a new linked list
    while (current) {
        Review *newReview = new Review;
        newReview->rating = current->rating;
        newReview->comment = current->comment;
        newReview->next = nullptr;

        // First copied node becomes the head
        if (!head) {
            head = newReview;
            tail = newReview;
        }
        else {
            // Add later nodes to the end to preserve review order
            tail->next = newReview;
            tail = newReview;
        }

        current = current->next;
    }
}

// operator=() copies another Movie object using a deep copy
// arguments: another Movie object passed by reference
// returns: the current Movie object
Movie& Movie::operator=(const Movie &other) {
    // Avoid deleting and copying the same object into itself
    if (this != &other) {
        Review *current = head;

        // Delete the current review list first
        while (current) {
            head = current->next;
            delete current;
            current = head;
        }

        head = nullptr;
        title = other.title;

        current = other.head;
        Review *tail = nullptr;

        // Create a completely new copy of the other review list
        while (current) {
            Review *newReview = new Review;
            newReview->rating = current->rating;
            newReview->comment = current->comment;
            newReview->next = nullptr;

            if (!head) {
                head = newReview;
                tail = newReview;
            }
            else {
                tail->next = newReview;
                tail = newReview;
            }

            current = current->next;
        }
    }

    return *this;
}