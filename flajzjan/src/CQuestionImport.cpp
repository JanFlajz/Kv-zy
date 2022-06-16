#include "CQuestion.h"
#include "iostream"
#include "sstream"
#include "fstream"
#include "ncurses.h"
#include "regex"

using namespace std;

bool CQuestion::importData(ifstream &ifstream1) {

    //only valid string on line
    //question meta data

    getline(ifstream1, m_Text, '\n');
    getline(ifstream1, m_LineInput, '\n');

    if (m_LineInput != "Evaluation" || !importEvaluation(ifstream1))
        return false;
    return true;
}

bool CQuestion::importEvaluation(ifstream &ifstream1) {
    //metadata
    string data;

    //evaluation type
    getline(ifstream1, m_LineInput, '\n');
    istringstream str(m_LineInput);
    str >> m_EvaluationID >> data >> m_Leftover;

    if (m_EvaluationID != 1 || data != "Choose-from-Set")
        return false;

    if (m_Leftover.empty())
        m_TextFill = false;
    else if (m_Leftover == "Text-Answer")
        m_TextFill = true;
    else
        return false;


    return selectEvaluation(ifstream1);

}

bool CTextChoice::rightEvaluation(const string &text) {

    if (text != "Written-text") {
        if (text != "Regex")
            if (text != "Counted-Value")
                return false;
    }
    return true;
}

bool CTextChoice::importEvaluation(ifstream &ifstream1) {
    string data;
    getline(ifstream1, m_LineInput, '\n');
    istringstream str(m_LineInput);

    str >> m_EvaluationID >> data;

    if (m_EvaluationID < 2 || m_EvaluationID > 4 || !rightEvaluation(data))
        return false;
    return selectEvaluation(ifstream1);
}

bool CQuestion::selectEvaluation(ifstream &ifstream1) {

    //reads answers for question
    CChooseFromSet newSet;
    if (!newSet.importAnswers(ifstream1))
        return false;

    m_Evaluation = newSet.Clone();
    return true;
}

bool CTextChoice::selectEvaluation(ifstream &ifstream1) {
    switch (m_EvaluationID) {
        case 2: {
            CWriteTextExactMatch exactMatch;
            if (!exactMatch.importAnswers(ifstream1))
                return false;
            m_Evaluation = exactMatch.Clone();
            break;
        }
        case 3: {
            CCWriteTextRegex regex;
            if (!regex.importAnswers(ifstream1))
                return false;
            m_Evaluation = regex.Clone();
            break;
        }
        case 4: {
            CWriteCountedValue value;
            if (!value.importAnswers(ifstream1))
                return false;
            m_Evaluation = value.Clone();
            break;
        }
        default:
            return false;
    }

    return true;
}