// COMSC-210-5293 | Lab 18 | Yuyi Chen

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
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