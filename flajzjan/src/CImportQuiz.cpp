#include "CQuiz.h"
#include "CPage.h"
#include "sstream"
#include "fstream"
#include "ncurses.h"

using namespace std;


void clear(istringstream &str) {
    str.str("");
    str.clear();
}

bool CQuiz::readQuizResults(ifstream &ifstream1) {
    //whole line
    string line;
    //information part
    string pages;
    //only valid string on line
    string leftover;


    int pageTag;
    getline(ifstream1, line, '\n');
    istringstream str(line);

    //detects wrong input

    str >> pages >> m_NumOfPages >> leftover;
    if (pages != "Num-of-pages" || m_NumOfPages <= 0 || !leftover.empty())
        return false;

    pages.clear();

// goes trough pages till the end
    for (int i = 1; i < m_NumOfPages + 1; i++) {

        getline(ifstream1, line, '\n');
        //new stringstream
        istringstream stream(line);
        stream >> pages >> pageTag >> leftover;


        if (pages != "Page" || pageTag != i || !leftover.empty())
            return false;


        CPage newPage;
        //imports questions for every page
        if (!newPage.importQuestionsWithResults(ifstream1))
            return false;

        m_Pages.push_back(newPage);

        //clear string at the end
        clear(stream);
    }

    getline(ifstream1,line);

    if(line == "ENDQUIZ"){
        getline(ifstream1,line);
        if(!ifstream1.eof())
            return false;
        //go to fill process

        fillQuiz();
        return true;
    }


    return false;

}

bool CPage::importQuestionsWithResults(ifstream &ifstream1) {

    string line;
    //information part
    string questions;
    //only valid string on line
    string leftover;
    //question meta data
    string questionType;
    int questionTag;

    getline(ifstream1, line, '\n');
    istringstream str(line);


    str >> questions >> m_NumOfQuestions >> leftover;


    if (!leftover.empty() || m_NumOfQuestions > 5 || m_NumOfQuestions <= 0 || questions != "Num-of-questions")
        return false;

    questions.clear();
    //reads pages
    for (int i = 1; i < m_NumOfQuestions + 1; i++) {

        getline(ifstream1, line, '\n');
        //new stringstream
        istringstream stream(line);
        stream >> questions >> questionTag >> leftover;


        if (questions != "Question" || !leftover.empty() || questionTag <= 0)
            return false;
        //imports questions for every page
        line.clear();
        getline(ifstream1, line, '\n');
        istringstream stream2(line);
        stream2 >> questionType >> leftover;

        if (!decideQuestion(questionType, ifstream1) || !leftover.empty())
            return false;

        clear();
        refresh();

        //clear streams at the end
        clear(stream);
        clear(stream2);
    }
    return true;
}

bool CPage::decideQuestion(const string &str, ifstream &ifstream1) {

    //appereantly u cannot do string-based switch statements bcs of low support for string
    if (str == "Single-choice") {
        CSingleChoice singleChoice;
        if (!singleChoice.importData(ifstream1))
            return false;
        m_Questions.push_back(singleChoice.Clone());
    } else if (str == "Multi-choice") {
        CMultiChoice multiChoice;
        if (!multiChoice.importData(ifstream1))
            return false;

        m_Questions.push_back(multiChoice.Clone());
    } else if (str == "Text-choice") {
        CTextChoice textChoice;
        if (!textChoice.importData(ifstream1))
            return false;

        m_Questions.push_back(textChoice.Clone());
    } else if (str == "Yes\\No") {
        CYesNoChoice yesNoChoice;
        if (!yesNoChoice.importData(ifstream1))
            return false;

        m_Questions.push_back(yesNoChoice.Clone());
    } else
        return false;


    return true;
}

