
#ifndef KOD_CANSWER_H
#define KOD_CANSWER_H

#include "set"
#include "vector"
#include "string"
#include "map"


using namespace std;

class CAnswers {
public:
    /**
* Constructor initilize empty instance
*/
    CAnswers() {
        m_NumOfAll = 0;
        m_NumOfCorrect = 0;
        m_NumOfTerminate = 0;
    };

    ~CAnswers() = default;

    /**map of all answers*/
    map<int, string> m_Answers;
    /**map of right and wrong answers*/
    map<int, string> m_CorrectAnswers;
    /**map that detects answers that switches pages*/
    map<int, string> m_TerminateAnswers;
    /**stores number of all answers for better import*/
    int m_NumOfAll;
    /**stores number of correct answers for better import*/
    int m_NumOfCorrect;
    /**stores number of terminate answers for better import*/
    int m_NumOfTerminate;
    /**detects answer ID*/
    int m_AnswerID;
    /**detects answer text*/
    string m_AnswerString;


};

#endif //KOD_CANSWER_H