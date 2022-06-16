#include "CPage.h"
#include "memory"
#include "CQuestion.h"

using namespace std;


void CPage::addQuestion(const shared_ptr<CQuestion> &cQuestion) {
    m_Questions.push_back(cQuestion);
}

void CPage::exportQuestionsWithResults(ostream &os,int & number) const {

    for (int i = 0; i < m_NumOfQuestions; i++) {
         m_Questions[i]->printDataFillAnswers(os, number);
    }
}
void CPage::exportQuestions(ostream &os,int & number) const {

    for (int i = 0; i < m_NumOfQuestions; i++) {
        m_Questions[i]->printDataFillAnswers(os, number);
    }
}

