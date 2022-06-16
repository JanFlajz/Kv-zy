#include "CQuestion.h"
#include "CEvaluation.h"
#include "sstream"
#include "ncurses.h"

#include <cmath>
#include "regex"
#include "map"

#define BACKSPACE 127
#define ASCIIa 97

/**
 * @param posY y input start
 * @param posX x input start
 * @param limit number of letters that can be written to answer
 * @return inputed string
 */
string CQuestion::readAnswer(int &posY, int &posX, int limit) const {

    string input;
    clrtoeol();
    int ch, trough = posX, start = posX;
    ch = getch();

    //read user input till enter
    while (true ) {
        if (ch == BACKSPACE) {
            if (input.empty())
                move(posY, start);

            else {
                input.erase(input.length() - 1);
                trough--;
                move(posY, trough);
                delch();
            }
        } else {
            input.push_back((char) ch);
            mvprintw(posY, trough, "%c", ch);
            trough++;
            move(posY, trough);
        }
        ch = getch();
        //end of reading
        if(ch == '\n' && !input.empty())
            return input;


        if ((int) input.length() >= limit) {
            input.erase(input.length() - 1);
            trough--;
            move(posY, trough);
            delch();
        }


        refresh();
    }

}

//go through given map ask for right string in it
bool CQuestion::containsAnswer(map<int, string> &m, const string &answer) {

    auto it = m.begin();
    for (; it != m.end(); it++)
        if (it->second == answer)
            return true;


    return false;
}

//go through given map ask for right index in it
bool CQuestion::containsLetter(map<int, string> &m, const string &answer) {
    auto it = m.find(answer[0] - ASCIIa);
    return it != m.end();

}

bool CQuestion::fillQuestion(int &posY, int &posX) {

    //move cursor
    move(posY, posX);
    //read answer
    string answer;
    if (m_TextFill)
        answer = readAnswer(posY, posX, INT32_MAX);
    else
        answer = readAnswer(posY, posX, 2);

    return proceedAnswer(answer);
}

bool CQuestion::proceedAnswer(const string &answer) {

    if (m_TextFill) {
        if (containsAnswer(m_Evaluation->m_Answers.m_CorrectAnswers, answer))
            return true;
        else if (containsAnswer(m_Evaluation->m_Answers.m_TerminateAnswers, answer))
            return false;

        m_BadAnswer = true;

    } else {
        //found correct answer
        if (containsLetter(m_Evaluation->m_Answers.m_CorrectAnswers, answer))
            return true;
        else if (containsLetter(m_Evaluation->m_Answers.m_TerminateAnswers, answer))
            return false;

        m_BadAnswer = true;
    }

    return true;
}


bool CTextChoice::fillQuestion(int &posY, int &posX) {

    move(posY, posX);
    string answer = readAnswer(posY, posX, INT32_MAX);

    if (m_Evaluation->m_ID == 4)
        return proceedAnswerWithValue(answer);
    else
        return proceedAnswer(answer);

}

bool CTextChoice::proceedAnswer(const string &answer) {

    if (m_Evaluation->m_ID == 2) {
        shared_ptr<CWriteTextExactMatch> match = dynamic_pointer_cast<CWriteTextExactMatch>(m_Evaluation);
        if (answer == match->m_Answers.m_CorrectAnswers[0])
            return true;
        if (containsAnswer(match->m_Answers.m_TerminateAnswers, answer) ||
            match->m_Answers.m_NumOfTerminate == INT32_MAX)
            return false;
        m_BadAnswer = true;

    } else {
        shared_ptr<CCWriteTextRegex> textRegex = dynamic_pointer_cast<CCWriteTextRegex>(m_Evaluation);
        if (std::regex_match(textRegex->m_Answers.m_CorrectAnswers[0], regex(answer)))
            return true;
        //match terminate
        if (textRegex->m_Answers.m_NumOfTerminate == INT32_MAX)
            return false;
        for (auto &m_TerminateAnswer : textRegex->m_Answers.m_TerminateAnswers)
            if (std::regex_match(m_TerminateAnswer.second, regex(answer)))
                return false;

        m_BadAnswer = true;
    }


    return true;
}

bool CTextChoice::proceedAnswerWithValue(const string &answer) {

    double insertedValue;
    istringstream str(answer);
    str >> insertedValue;

    //recast back to right evaluation
    shared_ptr<CWriteCountedValue> value = dynamic_pointer_cast<CWriteCountedValue>(m_Evaluation);

    //totally equal
    if (insertedValue == value->m_Value ||
        abs(insertedValue - value->m_Value) <
        abs(pow(10, -value->m_Precious) * abs((insertedValue + value->m_Value) / 2)))
        return true;
    if (value->m_SetInfinum)
        if (insertedValue < value->m_Inifinum)
            return false;
    if (value->m_SetSupremum)
        if (insertedValue > value->m_Supremum)
            return false;


    m_BadAnswer = true;
    return true;
}


bool CMultiChoice::fillQuestion(int &posY, int &posX) {
    move(posY, posX);
    string answer;


    if (m_TextFill)
        answer = readAnswer(posY, posX, INT32_MAX);
    else
        answer = readAnswer(posY, posX, m_Evaluation->m_NumOfAnswers + 20);

    return proceedAnswer(answer);
}

bool CMultiChoice::proceedAnswer(const string &answer) {

    istringstream str(answer);
    string subanswer;

    //read answers in text
    if (m_TextFill) {
        for (int i = 0; i < m_Evaluation->m_Answers.m_NumOfCorrect; i++) {
            getline(str, subanswer, ',');
            if (containsAnswer(m_Evaluation->m_Answers.m_TerminateAnswers, subanswer))
                return false;

            if (!containsAnswer(m_Evaluation->m_Answers.m_CorrectAnswers, subanswer)
                || m_UsedCorrectAnswers.find(subanswer) != m_UsedCorrectAnswers.end())
                m_BadAnswer = true;
            else
                m_UsedCorrectAnswers.insert(subanswer);
        }

        if((int) m_UsedCorrectAnswers.size() != m_Evaluation->m_Answers.m_NumOfCorrect)
            m_BadAnswer = true;

        //reads rest of okay input
        str >> m_Leftover;
        if (!str.eof()) {
            if (containsAnswer(m_Evaluation->m_Answers.m_TerminateAnswers, m_Leftover))
                return false;

            m_BadAnswer = true;
        }

    } else {
        for (int i = 0; i < m_Evaluation->m_Answers.m_NumOfCorrect; i++) {
            getline(str, subanswer, ',');
            if (containsLetter(m_Evaluation->m_Answers.m_TerminateAnswers, subanswer))
                return false;
            if (!containsLetter(m_Evaluation->m_Answers.m_CorrectAnswers, subanswer)
                || m_UsedCorrectIndex.find((int) subanswer[0]) != m_UsedCorrectIndex.end())
                m_BadAnswer = true;
            else
                m_UsedCorrectIndex.insert(subanswer[0]);

        }
        if((int)m_UsedCorrectIndex.size() != m_Evaluation->m_Answers.m_NumOfCorrect)
            m_BadAnswer = true;
        str >> m_Leftover;
        if (!str.eof()) {
            if (containsLetter(m_Evaluation->m_Answers.m_TerminateAnswers, m_Leftover))
                return false;
            m_BadAnswer = true;
        }

    }


    return true;
}
