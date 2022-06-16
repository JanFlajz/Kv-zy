#include "CImport.h"
#include "ncurses.h"
#include "fstream"
#include "sstream"
#include "CQuiz.h"
#define BACKSPACE 127

string CImporter::readFile(int &posY, int &posX) {
    string newPath;

    clrtoeol();
    int ch, trough = posX, start = posX;
    ch = getch();

    //read user input till enter
    while (ch != '\n') {
        if (ch == BACKSPACE) {
            if (newPath.empty())
                move(posY, start);

            else {
                newPath.erase(newPath.length() - 1);
                trough--;
                move(posY, trough);
                delch();
            }
        } else {
            newPath.push_back((char) ch);
            mvprintw(posY, trough, "%c", ch);
            trough++;
            move(posY, trough);
        }
        ch = getch();
        refresh();
    }

    return newPath;
}

void CImporter::importFile() {

    clear();
    int posY = 1;
    int posX = 10;
    curs_set(1);
    move(1, 30);
    mvprintw(posY, posX, "Insert name of your file: ");
    posX += 27;
    m_Path  = "examples/import/";

    m_Path.append(readFile(posY, posX));

    if (!correctFile()) {
        clear();
        refresh();

        mvprintw(posY++, posX, "Your file is Wrong/File does not exist.");
        mvprintw(posY, posX, "Press any key to return to main menu.");
        curs_set(0);
        getch();
        return;
    }


}

bool CImporter::correctSuffix()const {
    string suffix = ".txt";

    //suffix detection
    return (m_Path.length() >= suffix.length())
           && (0 == m_Path.compare(m_Path.length() - suffix.length(), m_Path.length(), suffix));
}


bool CImporter::correctFile() const {

    if (!correctSuffix())
        return false;


    ifstream ifstream1;
    ifstream1.open(m_Path);

    if (ifstream1.fail())
        return false;
    string line;
    getline(ifstream1, line);
    if (!correctHeader(line, ifstream1))
        return false;


    return true;

}

bool CImporter::correctHeader(const string &head, ifstream & ifstream1) const {
    CQuiz newQuiz;
    return head == "QUIZ-WITH-RESULTS" && newQuiz.readQuizResults(ifstream1);
}




