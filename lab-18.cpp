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

