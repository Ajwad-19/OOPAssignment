#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<fstream>
#include<stdlib.h>
using namespace std;

class FlashCard {
public:
    string question;
    string answer;
    int score;

    FlashCard() : question(""), answer(""), score(0) {}

    FlashCard(string q, string a) : score(0) {question=q; answer=a;}
};

class FlashCardSet {
public:
    vector<FlashCard> cards;
    int count;
    FlashCardSet() :count(0){}

    void addCard(string question, string answer) {

        // If not found, add as new
        cards.push_back(FlashCard(question, answer));
        cout << endl <<"Student added successfully!" << endl;
        count++;
    }

    void displayCard()
    {
        if (count == 0)
        {
            cout << endl << "No flashcard to display." << endl;

        }

        else
        {
            cout << endl <<"Total flashcard = " << count << endl;
            for (int i = 0; i < count; i++)
            {
                cout << "Q: " << cards[i].question << endl;
                cout << "A: " << cards[i].answer << endl;
                cout << endl;
            }
        }
    }

    vector<FlashCard>& getCards() {
        return cards;
    }
};

class MemoryReview {
public:
    void runReview(vector<FlashCard> &cards) {
        for (int i=0;i<cards.size();i++) {
            cout << endl << "Q: " << cards[i].question << endl;
            cout << "Do you remember the answer? (y/n): ";
            char input;
            cin >> input;
            cin.ignore(); // clear newline

            if (input == 'n' || input == 'N') {
                cout << "Answer: " << cards[i].answer << endl;
                if (cards[i].score > 0) cards[i].score--;
            } else {
                cout << "Great! Let's move on."<<endl;
                cards[i].score++;
            }
            cout<<"Current score:"<<cards[i].score<<endl;
        }
    }
};

class App {
    FlashCardSet cardSet;
    MemoryReview memoryReview;
    string filename;

public:
    App(const string &file = "flashcards_data.dat") : filename(file) {}

    void saveData(){
        ofstream wf(filename, ios::out | ios::binary);
        if (!wf)
        {
            cout << "Cannot open file for writing!" << endl;
            return;
        }

        wf.write((char *)&cardSet, sizeof(FlashCardSet));
        wf.close();
        cout << endl << "Saving all flashcards data into file done " << endl;
    }

    void loadData()
    {

        ifstream rf(filename, ios::in | ios::binary);
        if (!rf)
        {
            cout << "Cannot open file for reading!" << endl;
            return;
        }

        rf.read((char *)&cardSet, sizeof(FlashCardSet));
        rf.close();
        cardSet.displayCard();
        cout << "Loading all flashcards data from file done" << endl;
    }

    void run() {
        int choice;


        do {
            cout << endl << "===== Flashcard Menu =====" << endl;
            cout << "1. Add new card" << endl;
            cout << "2. Show all cards" << endl;
            cout << "3. Memory Review Mode (Do you remember?)" << endl;
            cout << "4. Save flashcard to the file" << endl;
            cout << "5. Load flashcard from the file" << endl;
            cout << "6. Exit" << endl;
            cout << "Enter choice: ";
            cin >> choice;
            cin.ignore();

            switch (choice) {
                case 1: {
                    string q, a;
                    cout << "Enter question: ";
                    getline(cin, q);
                    cout << "Enter answer: ";
                    getline(cin, a);
                    cardSet.addCard(q, a);
                    break;
                }
                case 2:
                    cardSet.displayCard();
                    break;
                case 3:
                    memoryReview.runReview(cardSet.getCards());
                    break;
                case 4:
                    saveData();
                    break;
                case 5:
                    loadData();
                    break;
                case 6:
                    cout << "Goodbye!\n";
                    break;
                default:
                    cout << "Invalid choice.\n";
            }

        } while (choice != 6);
    }
};

int main() {
    App app;
    app.run();
    return 0;
}
