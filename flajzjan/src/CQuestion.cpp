#include "CQuestion.h"
#include "CEvaluation.h"
#include "iostream"
#include "string"
#include "vector"
#include "set"
#include "ncurses.h"

using namespace std;

#define TEXTLENGTH 38
//ascii backspace value
#define BACKSPACE 127
#define ASCIIZERO 48


/**
    reads user m_Input into small text editor - able to delete
**/
void CQuestion::insertQuestionName(int &posY, int &posX) {


    int ch;
    int start = posX;
    int trough = start;

    ch = getch();
    //read user m_Input till enter
    while (true) {
        if (ch == '\n' && !m_Text.empty())
            break;

        if (ch == BACKSPACE) {
            if (m_Text.empty())
                move(posY, start);
            else {
                m_Text.erase(m_Text.length() - 1);
                trough--;
                move(posY, trough);
                delch();
            }
        } else {
            m_Text.push_back((char) ch);
            mvprintw(posY, trough, "%c", ch);
            trough++;
            move(posY, trough);
        }
        ch = getch();
        refresh();
    }
    curs_set(0);
}


/**
 * Create shared ptr out of class instance
 **/
shared_ptr<CQuestion> CSingleChoice::Clone() const {
    return make_shared<CSingleChoice>(*this);
}

shared_ptr<CQuestion> CMultiChoice::Clone() const {
    return make_shared<CMultiChoice>(*this);
}

shared_ptr<CQuestion> CTextChoice::Clone() const {
    return make_shared<CTextChoice>(*this);
}

shared_ptr<CQuestion> CYesNoChoice::Clone() const {
    return make_shared<CYesNoChoice>(*this);
}

int CQuestion::readNumber() {
    curs_set(1);
    move(18, 5);
    while (true) {
        m_Input = getch();
        if (m_Input == '1' || m_Input == '2')
            break;
    }
    printw("%c", m_Input);
    return m_Input;
}


/**
  For every question type selected print and get values
**/
void CQuestion::showPossibleEvaluations() {

    mvprintw(15, 10, "Choose evaluation:");
    mvprintw(16, 0, "Press 1 to choose from Set of answers.");
    mvprintw(17, 0, "Press 2 to write correct answer in text.");

    setEvaluation(readNumber() - ASCIIZERO);
}

void CTextChoice::showPossibleEvaluations() {

    mvprintw(15, 10, "Choose evaluation:");
    mvprintw(15, 0, "Press 1 to get whole text correctly.");
    mvprintw(16, 0, "Press 2 to get answer as regex.");
    mvprintw(17, 0, "Press 3 to answer with counted value.");
    curs_set(1);
    move(18, 5);
    while (true) {
        m_Input = getch();
        if (m_Input == '1' || m_Input == '2' || m_Input == '3')
            break;
    }
    printw("%c", m_Input);
    setEvaluation(m_Input - ASCIIZERO);

}

void CYesNoChoice::showPossibleEvaluations() {

    mvprintw(15, 10, "Choose evaluation:");
    mvprintw(15, 0, "Press 1 to choose from 2 possible answers");
    mvprintw(16, 0, "Press 2 to write correct answer in text.");
    setEvaluation(readNumber() - ASCIIZERO);
}

/**
 * Polymorf function for getting the evaluation
 * @param i determines which evaluation is chosen
**/

void CSingleChoice::setEvaluation(const int &i) {
    CChooseFromSet newSet;
    newSet.m_SingleChoice = true;
    newSet.m_OneCorrect = false;

    switch (i) {
        case 1: {
            newSet.m_TextFill = false;
            newSet.getAnswers();
            break;
        }
        case 2: {
            newSet.m_TextFill = true;
            newSet.getAnswers();
            break;
        }
        default:
            return;
    }
    //cast to CEVALUATION
    m_Evaluation = newSet.Clone();
    m_Evaluation->m_TextFill = newSet.m_TextFill;


}

void CMultiChoice::setEvaluation(const int &i) {

    CChooseFromSet newSet;

    switch (i) {
        case 1: {
            newSet.m_TextFill = false;
            newSet.getAnswers();
            break;
        }
        case 2: {
            newSet.m_TextFill = true;
            newSet.getAnswers();
            break;
        }
        default:
            return;
    }
    //cast to CEVALUATION
    m_Evaluation = newSet.Clone();
    m_Evaluation->m_TextFill = newSet.m_TextFill;

}

void CTextChoice::setEvaluation(const int &i) {

    switch (i) {
        case 1: {
            CWriteTextExactMatch textExactMatch;
            textExactMatch.getAnswers();
            //cast to CEVALUATION
            m_Evaluation = textExactMatch.Clone();
            break;
        }
        case 2: {
            CCWriteTextRegex writeTextRegex;
            writeTextRegex.getAnswers();
            //cast to CEVALUATION
            m_Evaluation = writeTextRegex.Clone();
            break;
        }
        case 3: {
            CWriteCountedValue writeCountedValue;
            writeCountedValue.getAnswers();
            //cast to CEVALUATION
            m_Evaluation = writeCountedValue.Clone();
            break;
        }
        default:
            return;
    }


}

void CYesNoChoice::setEvaluation(const int &i) {


    CChooseFromSet newSet;
    newSet.m_SingleChoice = true;
    newSet.m_OneCorrect = true;
    switch (i) {
        case 1: {
            newSet.m_TextFill = false;
            newSet.getAnswersYesNo();
            break;
        }
        case 2: {
            newSet.m_TextFill = true;
            newSet.getAnswersYesNo();
            break;
        }
        default:
            return;

    }
    //cast to CEVALUATION
    m_Evaluation = newSet.Clone();
    m_Evaluation->m_TextFill = newSet.m_TextFill;
}


