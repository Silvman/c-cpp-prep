#include <iostream>
#include <fstream>
#include <set>

using namespace std;

class logic {
private:
    fstream text;
    set<string> data;

public:
    logic(const string& name) {
        text.open(name);
    }

    void analyse() {
        while(!text.eof()) {
            string line;
            while(text.peek() != '\n' && !text.eof()) {
                string buf;
                text >> buf;
                line += buf + " ";
            }
            data.insert(line);
            text.get();
        }
        return;
    }

    void printAscend() {
        for (auto it : data) {
            cout << it << endl;
        }
        return;
    }

    ~logic() {
        text.close();
    }
};


int main(int argc, char** argv) {
    if (argc != 3) {
        cout << "Mistake!" << endl;
        return EXIT_FAILURE;
    }

    logic text(argv[1]);

    text.analyse();
    text.printAscend();

    return 0;
}
