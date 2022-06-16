#include "CEvaluation.h"
#include <string>
#include <cstring>
#include "ncurses.h"

//ascii backspace value
#define BACKSPACE 127
//ascii space bar
#define SPACEBAR 32
//ascii eneter button
#define ENTER 10


//max answer count for one question
#define MAXANSWERS 26

/**
 * Create shared ptr out of class instance
**/

shared_ptr<CEvaluation> CChooseFromSet::Clone() const {
    return make_shared<CChooseFromSet>(*this);
}

shared_ptr<CEvaluation> CWriteTextExactMatch::Clone() const {
    return make_shared<CWriteTextExactMatch>(*this);
}

shared_ptr<CEvaluation> CCWriteTextRegex::Clone() const {
    return make_shared<CCWriteTextRegex>(*this);
}

shared_ptr<CEvaluation> CWriteCountedValue::Clone() const {
    return make_shared<CWriteCountedValue>(*this);
}


string CEvaluation::readAnswers(int posY, int posX) {
    clrtoeol();
    int ch, trough = posX, start = posX;
    ch = getch();

    //read user m_Input till enter can be empty
    while (ch != '\n') {
        if (ch == BACKSPACE) {
            if (m_Input.empty())
                move(posY, start);

            else {
                m_Input.erase(m_Input.length() - 1);
                trough--;
                move(posY, trough);
                delch();
            }
        } else {
            m_Input.push_back((char) ch);
            mvprintw(posY, trough, "%c", ch);
            trough++;
            move(posY, trough);
        }
        ch = getch();
        refresh();
    }

    return m_Input;
}
//
void CChooseFromSet::readMetaData(const string &text, const int &posY, int posX,
                                  bool &correctWasalreadyUsed, const int &currID) {

    int input = 0;

    //Write or wrong answer
    if (!correctWasalreadyUsed) {
        char question1[] = "Correct Answer ? Press A/N";
        mvprintw(posY, posX, question1);
        move(posY, posX + (int) strlen(question1) + 1);
        while (true) {
            input = getch();
            if (input == 'A' || input == 'N' || input == 'a' || input == 'n') {
                printw("%c", toupper(input));
                if (input == 'A' || input == 'a') {
                    m_Answers.m_CorrectAnswers[currID] = text;
                    m_Answers.m_NumOfCorrect++;
                    correctWasalreadyUsed = m_SingleChoice;
                }
                break;
            }

        }
    }
    char question2[] = "Terminate Answer ? Press Press A/N";
    //answer that end quiz
    if (input != 'A') {
        if (input != 'a') {
            mvprintw(posY, posX, question2);
            move(posY, posX + (int) strlen(question2) + 1);
            while (true) {
                input = getch();
                if (input == 'A' || input == 'N' || input == 'a' || input == 'n') {
                    printw("%c", toupper(input));
                    if (input == 'A' || input == 'a') {
                        m_Answers.m_TerminateAnswers[currID] = text;
                        m_Answers.m_NumOfTerminate++;
                    }
                    break;
                }
            }
        }
    }

}


void CChooseFromSet::getAnswers() {

    int start = 21;
    mvprintw(20, 0, "Insert Answers: ");
    move(start, 3);
    int i = 0, ch;

    for (; i < MAXANSWERS; i++) {
        mvprintw(start, 0, "%c.", m_Alphabet++);
        m_Input = readAnswers(start, 3);
        m_Answers.m_Answers[m_NumOfAnswers] = m_Input;

        readMetaData(m_Input, start + 1, 0, m_OneCorrect, m_NumOfAnswers++);

        m_Input.clear();
        if ((ch = getch()) == BACKSPACE && (m_OneCorrect || !m_SingleChoice))
            break;
        start += 2;
    }

    m_Alphabet = 97;

}

void CChooseFromSet::getAnswersYesNo() {

    int start = 22, i = 0, answer;
    m_Answers.m_Answers[m_NumOfAnswers++] = "Yes";
    m_Answers.m_Answers[m_NumOfAnswers++] = "No";
    mvprintw(20, 0, "Press 1 if yes is correct.");
    mvprintw(21, 0, "Press 0 if no is correct.");
    move(start, 3);
    while (true) {
        i = getch();
        if (i == '1' || i == '0')
            break;
    }
    answer = i;
    mvprintw(start, 5, "%c", i);
    if (i == '1')
        m_Answers.m_CorrectAnswers[0] = "Yes";
    else if (i == '0')
        m_Answers.m_CorrectAnswers[1] = "No";
    m_Answers.m_NumOfCorrect++;
    mvprintw(++start, 0, "Is other option terminate ?");
    mvprintw(++start, 0, "Press 1/0");
    move(++start, 3);
    while (true) {
        i = getch();
        if (i == '1' || i == '0')
            break;
    }
    if (i == '1') {
        if (answer == '1')
            m_Answers.m_TerminateAnswers[1] = "No";
        else if (answer == '0')
            m_Answers.m_TerminateAnswers[0] = "Yes";
        m_Answers.m_NumOfTerminate++;
    }


}


void CWriteTextExactMatch::getAnswers() {
    int start = 21;
    bool falseBool = false;
    mvprintw(20, 0, "Write correct answer:");
    move(start, 3);
    m_Input = readAnswers(start, 3);
    m_Answers.m_Answers[m_NumOfAnswers] = m_Input;
    m_Answers.m_CorrectAnswers[m_NumOfAnswers] = m_Input;
    m_Answers.m_NumOfCorrect++;
    readMetaData(m_Input, 0, start + 1, falseBool, m_NumOfAnswers++);


}

void CEvaluation::readMetaData(const string &text, const int &posX,
                                    int posY, bool &corWasalreadyUsed, const int &currID) {

    int input = 0;
    mvprintw(++posY, posX, "Press BACKSPACE if no wrong answer is terminate");
    mvprintw(++posY, posX, "Press SPACE if every wrong answer is terminate");
    mvprintw(++posY, posX, "Press ENTER to write specific answer to terminate");

    move(++posY, 3);
    while (true) {
        input = getch();

        if (input == BACKSPACE) {
            m_Answers.m_NumOfTerminate = 0;

            break;
        }//space
        else if (input == SPACEBAR) {
            m_Answers.m_NumOfTerminate = INT16_MAX;
            break;
        }
            //enter button
        else if (input == ENTER) {
            mvprintw(posY += 2, posX, "Press ENTER to add new, else press 0");
            while (true) {
                move(posY + 1, 0);
                m_Input.clear();
                m_Input = readAnswers(posY + 1, posX);
                m_Answers.m_TerminateAnswers[m_Answers.m_NumOfTerminate++] = m_Input;
                m_Input.clear();
                input = getch();
                if (input == '0')
                    break;
                move(++posY, posX);
            }
            break;
        }

    }

}

void CCWriteTextRegex::getAnswers() {
    int start = 21;
    bool falseBool = false;
    mvprintw(20, 0, "Write correct answer:");
    move(start, 3);
    m_Input = readAnswers(start, 3);
    m_Answers.m_Answers[m_NumOfAnswers] = m_Input;
    m_Answers.m_CorrectAnswers[m_NumOfAnswers] = m_Input;
    m_Answers.m_NumOfCorrect++;
    readMetaData(m_Input, 0, start + 1, falseBool, m_NumOfAnswers++);


}

bool CWriteCountedValue::isInt(const string &input) const {
    return ((m_Input.length() == 1) && isdigit(m_Input[0]));
}

string CWriteCountedValue::readBorder(const int &posY, const int &posX) {

    while (true) {
        m_Input.clear();
        m_Input = readAnswers(posY, posX + 27);
        if (isDouble(m_Input) || m_Input == "N")
            break;
        clrtoeol();

        move(posY, posX + 27);
    }
    return m_Input;
}


void CWriteCountedValue::readMetaData(const string &text, const int &posX,
                                      int posY, bool &rightWasalreadyUsed, const int &currID) {

    mvprintw(++posY, posX, "How many decimal places is valid ?");
    int decimals = 0;

    while (true) {
        m_Input.clear();
        m_Input = readAnswers(posY, posX + 35);
        if (isInt(m_Input)) {
            decimals = atoi(m_Input.c_str());
            if (decimals > -1)
                break;
        }
        move(posY, posX + 35);
        clrtoeol();

    }
    m_Precious = decimals;

    //highest of lowest points of ending
    mvprintw(++posY, posX, "Insert infinum terminate value, if there 's not write N:");
    m_Answers.m_TerminateAnswers[currID] = readBorder(posY, posX + 30);

    //lowest of highest points of ending
    mvprintw(++posY, posX, "Insert supremum terminate value, if there 's not write N:");
    m_Answers.m_TerminateAnswers[currID + 1] = readBorder(posY, posX + 31);

}

bool CWriteCountedValue::isDouble(const string &input) const {

    bool foundDecimal = false;
    if(input.length() == 1)
        return (isdigit(input[0]) || input[0] == 'N');

    for (char c : input) {
        if (c == '.' && !foundDecimal)
            foundDecimal = true;
        else if (!isdigit(c) && foundDecimal)
            return false;
        else if (!isdigit(c) && c != '.')
            return false;
    }

    return true;

}


void CWriteCountedValue::getAnswers() {
    int startY = 21;
    int startX = 3;
    bool falseBool = false;
    //welcome text
    mvprintw(20, 0, "Write value, \".\" for decimals:");
    while (true) {
        move(startY, startX);
        m_Input = readAnswers(startY, startX);
        if (isDouble(m_Input))
            break;
        m_Input.clear();
        move(startY, startX);
        clrtoeol();
    }
    m_Answers.m_Answers[m_NumOfAnswers] = m_Input;
    m_Answers.m_CorrectAnswers[m_NumOfAnswers] = m_Input;
    m_Answers.m_NumOfCorrect++;
    //get rids of previous input because of adding
    m_Input.clear();
    readMetaData(m_Input, startX, startY, falseBool, m_NumOfAnswers++);

}


