
#ifndef KOD_CQUIZ_H
#define KOD_CQUIZ_H


#include "vector"
#include "memory"
#include "CQuestion.h"
#include "CEvaluation.h"
#include "CPage.h"
using namespace std;


class  CQuiz{
public:
    /**
     * Constructor  initials empty instance
     */
    CQuiz() {
        m_NumOfQuestions = 0;
        m_NumOfPages = 0;
    }
    ~CQuiz() =default;
    /**show menu to choose from question
     *
     * @return
     */
    int printQuestionMenu();
    /**
     * creates new question
     */
    void addQuestion();
    /**
     * changes properties of question
     * @param type detects type of question
     */
    void editQuestion(const int & type );
    /**
     * add question to page
     * @param cQuestion  ptr to question that is added to page
     */
    void addToPage( const shared_ptr<CQuestion> & cQuestion );
    /**reads quiz from imput
     * @param ifstream1 stream that reads values
     * @return if there was no problem with file
     */
    bool readQuizResults(ifstream & ifstream1);
    /**
     * open filling fills data to question
     *
     */
    void fillQuiz();
    /**
     * ends filling when pressed wrong/terminate answers
     *  prints messege to user
     */
    void endFillingBad();
    /**ends filling when succes
     * prints messege to user
     */
    void endFillingGood();


    /**
     * pages of quiz with questions

     */
    vector<CPage> m_Pages;
    /** number of question in pages
     */
    int m_NumOfQuestions;
    /**number of pages
     */
    int m_NumOfPages;



};

#endif //KOD_CQUIZ_H
