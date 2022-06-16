

#ifndef KOD_CPAGE_H
#define KOD_CPAGE_H

#define MAXQUESTIONS 5

#include "CQuestion.h"
#include "vector"
#include "memory"


class CPage {

public:
/**
  * Constructor and  initials empty instance
  */
    CPage() {
        m_NumOfQuestions = 1;
    }

    ~CPage() = default;

    /**adds question to current page
     * @param cQuestion ptr to new question
     */
    void addQuestion(const shared_ptr<CQuestion> &cQuestion);

    /**
     * export questions without result
     * @param os stream to print to
     * @param number index of question
     */
    void exportQuestions(ostream &os,int & number) const;
    /**export question with results to file to get filled
     * @param os stream to export to
     * @param number
     */
    void exportQuestionsWithResults(ostream &os, int &number) const;

    /**import questions on  pages
     * @param ifstream1 stream to import from
     * @return if page was okay imputed
     */
    bool importQuestionsWithResults(ifstream &ifstream1);

    /**decides type of question
     * @param str question type
     * @param ifstream1 readQuestion from
     * @return if page was okay imputed
     */
    bool decideQuestion(const string & str, ifstream &ifstream1);

    /**prints question on page
     * @return wether page was inputed correctly
     */
    bool fillPage();

    /**stores questions with their evaluation
     * */
    vector<shared_ptr<CQuestion>> m_Questions;

    /** total num of question in page 1-5*/
    int m_NumOfQuestions;

    /**stores ids of wrong answered questions*/
    vector<int > m_WrongAnswered;



};


#endif //KOD_CPAGE_H
