#include "CCreator.h"
#include "iostream"
#include "CQuiz.h"
#include "ncurses.h"
#include "CExport.h"

#define MENUSIZE 3
#define MAXQUESTIONSINPAGE 5


#define WINDOWSTARTY 3
#define WINDOWSTARTX 48

#define WINDOWSIZEX 42
#define WINDOWSIZEY 8
using namespace std;


void CCreator::welcome() {
    CQuiz m_Quiz;
    erase();
    initscr();
    mvprintw(1, 50, "Welcome to quiz creator !");
    mvprintw(2, 50, "Let´s insert the first question.");
    mvprintw(4, 50, "Press any key to continue.");
    getch();
    clear();
    m_Quiz.addQuestion();
    clear();
    refresh();
    exportQuiz(m_Quiz);
}

void CCreator::printExportMenu(WINDOW *windowMenu, const int highlight) const {

    char choices[][WINDOWSIZEX] = {"1.Export as quiz to fill with results.",
                                   "2.Export as text file with results.", "3.Export as text file."};

    int x = 2;
    int y = 2;

    box(windowMenu, 0, 0);
    for (int i = 0; i < MENUSIZE; i++) {
        if (highlight == i + 1) {
            wattron(windowMenu, A_REVERSE);
            mvwprintw(windowMenu, y, x, "%s", choices[i]);
            wattroff(windowMenu, A_REVERSE);
        } else {
            mvwprintw(windowMenu, y, x, "%s", choices[i]);
        }
        y++;
    }
    wrefresh(windowMenu);

}

void CCreator::exportQuiz(const CQuiz &quiz) const {

    mvprintw(1, 50, "Select the way to export quiz");

    //initilize new menu
    WINDOW *windowMenu;
    initscr();
    int highlight = 1;
    int chosen = 0;
    int input;

    curs_set(0);
    windowMenu = newwin(WINDOWSIZEY, WINDOWSIZEX, WINDOWSTARTY, WINDOWSTARTX);
    keypad(windowMenu, true);
    refresh();
    printExportMenu(windowMenu, highlight);

    while (true) {
        input = wgetch(windowMenu);
        if (input == KEY_UP) {
            if (highlight == 1)
                highlight = MENUSIZE;
            else
                highlight--;
        } else if (input == KEY_DOWN) {
            if (highlight == MENUSIZE)
                highlight = 1;
            else
                highlight++;
        } else if (input == 10) {
            chosen = highlight;
            endwin();
            werase(windowMenu);
            end(quiz, chosen);
            break;
        } else
            refresh();

        printExportMenu(windowMenu, highlight);
        if (chosen > MENUSIZE)
            break;
    }
    refresh();

}


void CCreator::end(const CQuiz &quiz, const int &choice) const {

//choose right quiz type
    switch (choice) {
        case 1: {
            CExportToFillWithResults cExportToFillWithResults;
            cExportToFillWithResults.exportToFile(quiz);
            break;
        }

        case 2: {
            CExportTextWithResults cExportTextWithResults;
            cExportTextWithResults.exportToFile(quiz);
            break;
        }
        case 3: {
            CExportText cExportText;
            cExportText.exportToFile(quiz);
            break;
        }
        default:
            break;


    }

}




