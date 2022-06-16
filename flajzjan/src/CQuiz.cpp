#include "CQuiz.h"
#include "CQuestion.h"
#include "CPage.h"

#include "ncurses.h"

#define MAXQUESTIONSINPAGE 5
#define MENUSIZE 4
#define WINDOWSIZEY 8
#define WINDOWSTARTY 2
#define WINDOWSTARTX 40
#define WINDOWSIZEX 20
#define BACKSPACE 127
#define TEXTLENGTH 38


using namespace std;

void printMenu(WINDOW *windowMenu, int highlight) {

    char choices[][WINDOWSIZEX] = {"Single choice", "Multi choice", "Text", "Yes/No"};

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


int CQuiz::printQuestionMenu() {

    WINDOW *windowMenu;
    initscr();
    int highlight = 1;
    int chosen = 0;
    int input;

    curs_set(0);
    windowMenu = newwin(WINDOWSIZEY, WINDOWSIZEX, WINDOWSTARTY, WINDOWSTARTX);
    keypad(windowMenu, true);
    refresh();
    printMenu(windowMenu, highlight);

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
            return chosen;
        } else
            refresh();

        printMenu(windowMenu, highlight);
        if (chosen > MENUSIZE)
            break;
    }
    refresh();

    return chosen;
}



void CQuiz::editQuestion(const int &type) {
    endwin();
    curs_set(1);

    refresh();
    mvprintw(12, 0, "Insert question text. End with enter:\n");
    curs_set(1);
    move(12, TEXTLENGTH);
    int startY = 12;
    int startX = TEXTLENGTH;
    switch (type) {
        case 1: {
            CSingleChoice singleChoice;
            singleChoice.insertQuestionName(startY,startX);
            singleChoice.showPossibleEvaluations();
            addToPage(singleChoice.Clone());
            break;
        }
        case 2: {
            CMultiChoice multiChoice;
            multiChoice.insertQuestionName(startY,startX);
            multiChoice.showPossibleEvaluations();
            addToPage(multiChoice.Clone());
            break;
        }
        case 3: {
            CTextChoice textChoice;
            textChoice.insertQuestionName(startY,startX);
            textChoice.showPossibleEvaluations();
            addToPage(textChoice.Clone());
            break;
        }
        case 4: {
            CYesNoChoice yesNoChoice;
            yesNoChoice.insertQuestionName(startY,startX);
            yesNoChoice.showPossibleEvaluations();
            addToPage(yesNoChoice.Clone());
            break;
        }
        default:
            return;
    }

}


void CQuiz::addQuestion() {

    int i;

    while (true) {
        mvprintw(2, 0, "Select type of question num. %d:", m_NumOfQuestions + 1);
        i = printQuestionMenu();
        editQuestion(i);
        m_NumOfQuestions++;
        clear();
        refresh();
        mvprintw(2,0,"Press Enter to continue adding question.");
        mvprintw(3,0,"Press Backspace to export quiz.");

        i = getch();
        if (i == BACKSPACE)
            break;
        refresh();
        clear();
    }

}
void CQuiz::addToPage(const shared_ptr<CQuestion> & cQuestion) {

    //creating new page
    if (m_Pages.empty() || m_Pages[m_Pages.size() - 1].m_NumOfQuestions == MAXQUESTIONSINPAGE) {
        CPage newPage;
        newPage.addQuestion(cQuestion);
        m_Pages.push_back(newPage);
        m_NumOfPages++;
    }
        //add to last page in vector
    else {
        m_Pages[m_Pages.size() - 1].addQuestion(cQuestion);
        m_Pages[m_Pages.size() - 1].m_NumOfQuestions++;
    }
}



