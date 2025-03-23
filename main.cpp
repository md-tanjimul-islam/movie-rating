#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Movie {
    string title;
    string director;
    int releaseYear;
    float rating;
};

vector<Movie> movies;

void addMovie();
void displayMovies();
void searchMovie();
void updateMovie();
void saveToFile();
void loadFromFile();
void displayMenu();
string toLower(const string& str);

int main() {
    loadFromFile();
    int choice;

    cout << "\n=======================================================================================================================\n";
    cout << "\n                                          WELCOME TO MOVIE MANIA\n";
    cout << "\n=======================================================================================================================\n";
    do {
        displayMenu();
        cout << "\nEnter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                addMovie();
                break;
            case 2:
                displayMovies();
                break;
            case 3:
                searchMovie();
                break;
            case 4:
                updateMovie();
                break;
            case 5:
                saveToFile();
                break;
            case 6:
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}

void displayMenu() {
    cout << "\n                                       === Movie Rating Database ===\n";
    cout << "                                         1. Add Movie\n";
    cout << "                                         2. Display Movies\n";
    cout << "                                         3. Search Movie\n";
    cout << "                                         4. Update Movie\n";
    cout << "                                         5. Save Movies to File\n";
    cout << "                                         6. Exit\n";
}

void addMovie() {
    Movie movie;

    cout << "Enter movie title: ";
    getline(cin, movie.title);

    cout << "Enter director's name: ";
    getline(cin, movie.director);

    cout << "Enter release year: ";
    cin >> movie.releaseYear;

    do {
        cout << "Enter rating (0.0 - 10.0): ";
        cin >> movie.rating;
    } while (movie.rating < 0.0 || movie.rating > 10.0);
    cin.ignore();

    movies.push_back(movie);
    cout << "Movie added successfully.\n";
}

void displayMovies() {
    if (movies.empty()) {
        cout << "No movies to display.\n";
        return;
    }

    cout << "\n                                         === Movie List ===\n";
    for (size_t i = 0; i < movies.size(); i++) {
        cout << "                                       Movie #" << i + 1 << ":\n";
        cout << "                                       Title: " << movies[i].title << "\n";
        cout << "                                       Director: " << movies[i].director << "\n";
        cout << "                                       Release Year: " << movies[i].releaseYear << "\n";
        cout << "                                       Rating: " << movies[i].rating << "\n\n";
    }
}

void searchMovie() {
    string query;
    cout << "Enter movie title or director to search: ";
    getline(cin, query);
    query = toLower(query);

    bool found = false;
    for (const auto& movie : movies) {
        if (toLower(movie.title).find(query) != string::npos || toLower(movie.director).find(query) != string::npos) {
            cout << "\n                                       === Movie Found ===\n";
            cout << "                                          Title: " << movie.title << "\n";
            cout << "                                          Director: " << movie.director << "\n";
            cout << "                                          Release Year: " << movie.releaseYear << "\n";
            cout << "                                          Rating: " << movie.rating << "\n\n";
            found = true;
        }
    }

    if (!found) {
        cout << "                                       === No movie found with the given title or director. ===\n";
    }
}

void updateMovie() {
    string query;
    cout << "Enter the title of the movie to update: ";
    getline(cin, query);

    for (auto& movie : movies) {
        if (movie.title == query) {
            cout << "Updating movie: " << movie.title << "\n";
            cout << "Enter new director's name: ";
            getline(cin, movie.director);

            cout << "Enter new release year: ";
            cin >> movie.releaseYear;

            do {
                cout << "Enter new rating (0.0 - 10.0): ";
                cin >> movie.rating;
            } while (movie.rating < 0.0 || movie.rating > 10.0);
            cin.ignore();

            cout << "Movie updated successfully.\n";
            return;
        }
    }

    cout << "Movie not found.\n";
}

void saveToFile() {
    ofstream file("movies.txt");
    if (!file) {
        cerr << "Error saving movies to file.\n";
        return;
    }

    for (const auto& movie : movies) {
        file << movie.title << "," << movie.director << "," << movie.releaseYear << "," << movie.rating << "\n";
    }

    cout << "Movies saved to file successfully.\n";
}

void loadFromFile() {
    ifstream file("movies.txt");
    if (!file) {
        cout << "No existing movie database found. Starting fresh.\n";
        return;
    }

    Movie movie;
    string line;
    while (getline(file, movie.title, ',') && getline(file, movie.director, ',') && file >> movie.releaseYear && file.ignore() && file >> movie.rating && file.ignore()) {
        movies.push_back(movie);
    }

    cout << "Movies loaded from file successfully.\n";
}

string toLower(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}
