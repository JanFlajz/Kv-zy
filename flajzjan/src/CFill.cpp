#include "CQuiz.h"
#include "CPage.h"
#include "ncurses.h"
#include "CQuestion.h"

#define QUIZSTARTX 30
#define QUIZSTARTY 0

void CQuiz::fillQuiz() {

    clear();

    mvprintw(QUIZSTARTY, QUIZSTARTX, "Let`s answer the questions! ");
    //fills all pages
    for (int i = 0; i < m_NumOfPages; i++) {
        mvprintw(i + 2, QUIZSTARTX / 2, "Page %d", i + 1);
        if (!m_Pages[i].fillPage()) {
            endFillingBad();
            return;
        }
    }
    endFillingGood();

}


void CQuiz::endFillingGood() {

    clear();
    refresh();

    bool noBadAnswers = true;
    for (int i = 0; i < (int) m_NumOfPages; i++) {
        //detects if any answer was incorrect
        if (!m_Pages[i].m_WrongAnswered.empty()) {
            noBadAnswers = false;

            break;
        }
    }

    //everything was alright
    if (noBadAnswers) {
        mvprintw(QUIZSTARTY, QUIZSTARTX, "Your answers were 100 percent correct.");
        mvprintw(QUIZSTARTY + 1, QUIZSTARTX, "Congratulations!");
        mvprintw(QUIZSTARTY + 2, QUIZSTARTX, "Press any key to go back to menu.");
        getch();
        return;
    }

    mvprintw(QUIZSTARTY, QUIZSTARTX, "These answers were incorrect:");
    int start = QUIZSTARTY + 1;

    for (int i = 0; i < m_NumOfPages; i++) {
        int wrongcount = (int) m_Pages[i].m_WrongAnswered.size();

        for (int j = 0; j < wrongcount; ++j) {
            mvprintw(++start, QUIZSTARTX, "Question: %d Page: %d", m_Pages[i].m_WrongAnswered[j], i + 1);
            start++;
        }
    }

    mvprintw(++start, QUIZSTARTX, "Press any key to go back to menu.");
    getch();

}

//user inputed terminate answer
void CQuiz::endFillingBad() {
    clear();
    refresh();
    mvprintw(QUIZSTARTY, QUIZSTARTX, "Thanks for your time, but you should be better prepared.");
    mvprintw(QUIZSTARTY + 1, QUIZSTARTX, "Press any key to return to main menu.");
    getch();
}

bool CPage::fillPage() {


    vector<pair<int, int >> coordinatesAnswer;
    int startY = 4;
    int startX = 0;
    //prints question to screen

    for (int j = 0; j < m_NumOfQuestions; j++) {
        m_Questions[j]->printDataFill(startY, startX);
        coordinatesAnswer.emplace_back(make_pair(startY, startX));
        startY += 2;
        startX = 0;
    }
    //move back to first answer
    move(coordinatesAnswer[0].first, coordinatesAnswer[0].second);

    for (int i = 0; i < m_NumOfQuestions; i++) {

        if (!m_Questions[i]->fillQuestion(coordinatesAnswer[i].first, coordinatesAnswer[i].second))
            return false;
        //detects badly answered questions
        if (m_Questions[i]->m_BadAnswer)
            m_WrongAnswered.push_back(i + 1);

    }
    clear();
    refresh();
    return true;
}

void CQuestion::printDataFill(int &posY, int &posX) const {

    mvprintw(posY, posX, "%s", m_Text.c_str());
    if (m_TextFill)
        mvprintw(posY, posX + (int) m_Text.length() + 1, "Write whole answer (not only selected letter).");

    for (int i = 0; i < m_Evaluation->m_Answers.m_NumOfAll; i++)
        mvprintw(++posY, posX, "%c. %s ", i + 97, m_Evaluation->m_Answers.m_Answers[i].c_str());


    posY++;
    string answer = "Answer: ";
    mvprintw(posY, posX, answer.c_str());
    posX += (int) answer.length();

}

void CTextChoice::printDataFill(int &posY, int &posX) const {

    mvprintw(posY, posX, "%s", m_Text.c_str());
    posY++;
    string answer = "Answer: ";
    mvprintw(++posY, posX, answer.c_str());
    posX += (int) answer.length();
}

