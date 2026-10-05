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
    srand(time(0));
    cout << fixed << setprecision(1);

    ifstream fin("input.txt");

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

    for (int i = 0; i < movies.size(); i++) {
        for (int j = 0; j < 3; j++) {
            double rating = ((rand() % 41) + 10) / 10.0;

            movies[i].addReview(rating, comments[commentIndex]);

            commentIndex++;
        }
    }

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
    newReview->next = head;
    head = newReview;
}

// ~Movie() deletes all reviews when a Movie object is destroyed
// argument: none
// returns: none
Movie::~Movie() {
    Review *current = head;

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

    while (current) {
        cout << "> Review #" << count << ": "
             << current->rating << ": "
             << current->comment << endl;
        
        total += current->rating;
        count++;
        current = current->next;
    }

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

// operator=() copies another Movie object using a deep copy
// arguments: another Movie object passed by reference
// returns: the current Movie object
Movie& Movie::operator=(const Movie &other) {
    if (this != &other) {
        Review *current = head;

        while (current) {
            head = current->next;
            delete current;
            current = head;
        }

        head = nullptr;
        title = other.title;

        current = other.head;
        Review *tail = nullptr;

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