#include "CEvaluation.h"
#include "iostream"
#include "sstream"
#include "fstream"
#include "ncurses.h"

bool CChooseFromSet::importAll(ifstream &ifstream1) {

    string data;

    //shouldnt happend
    if (m_Answers.m_NumOfAll == 0)
        return false;
    for (int i = 0; i < m_Answers.m_NumOfAll; i++) {
        getline(ifstream1, m_LineInput, '\n');
        istringstream str(m_LineInput);
        str >> m_Answers.m_AnswerID;

        while (str >> data)
            m_Answers.m_AnswerString.append(data + " ");

        data.clear();
        if (m_Answers.m_AnswerString[m_Answers.m_AnswerString.length() - 1] == ' ')
            m_Answers.m_AnswerString.pop_back();

        m_Answers.m_Answers[m_Answers.m_AnswerID] = m_Answers.m_AnswerString;

        //clear streams
        m_Answers.m_AnswerString.clear();
        str.clear();
    }
    return true;
}

bool CChooseFromSet::importCorrect(ifstream &ifstream1) {
    string data;

    //multichoice
    if (m_Answers.m_NumOfCorrect == 0) {
        getline(ifstream1, m_LineInput, '\n');
        istringstream str(m_LineInput);
        str >> data;
        return data.empty();
    }
    for (int i = 0; i < m_Answers.m_NumOfCorrect; i++) {
        getline(ifstream1, m_LineInput, '\n');
        istringstream str(m_LineInput);
        str >> m_Answers.m_AnswerID;
        while (str >> data)
            m_Answers.m_AnswerString.append(data + " ");
        if (m_Answers.m_AnswerString[m_Answers.m_AnswerString.length() - 1] == ' ')
            m_Answers.m_AnswerString.pop_back();

        m_Answers.m_CorrectAnswers[m_Answers.m_AnswerID] = m_Answers.m_AnswerString;
        //clear streams
        m_Answers.m_AnswerString.clear();
        str.clear();
    }


    return true;
}


bool CChooseFromSet::importTerminate(ifstream &ifstream1) {

    string data;

    //no terminate
    if (m_Answers.m_NumOfTerminate == 0){
        getline(ifstream1, m_LineInput, '\n');
        istringstream str(m_LineInput);
        str >> data;
        return data.empty();
    }

    //nice amount of answers
    for (int i = 0; i < m_Answers.m_NumOfTerminate; i++) {
        getline(ifstream1, m_LineInput, '\n');
        istringstream str(m_LineInput);
        str >> m_Answers.m_AnswerID;
        while (str >> data)
            m_Answers.m_AnswerString.append(data + " ");

        if (m_Answers.m_AnswerString[m_Answers.m_AnswerString.length() - 1] == ' ')
            m_Answers.m_AnswerString.pop_back();

        m_Answers.m_TerminateAnswers[m_Answers.m_AnswerID] = m_Answers.m_AnswerString;

        m_Answers.m_AnswerString.clear();
        str.clear();
    }


    return true;
}


bool CChooseFromSet::importAnswers(ifstream &ifstream1) {
    string data;

    //all possibilities
    getline(ifstream1, m_LineInput, '\n');
    istringstream str(m_LineInput);
    str >> data >> m_Answers.m_NumOfAll >> m_Leftover;


    if (m_Answers.m_NumOfAll < 0 || !m_Leftover.empty() || data != "Possibilities")
        return false;
    data.clear();
    m_LineInput.clear();
    m_Leftover.clear();

    if (!importAll(ifstream1))
        return false;

    //correct answers
    getline(ifstream1, m_LineInput, '\n');
    istringstream str2(m_LineInput);
    str2 >> data >> m_Answers.m_NumOfCorrect >> m_Leftover;

    if (m_Answers.m_NumOfCorrect <= 0 || !m_Leftover.empty() || data != "Correct-Answer")
        return false;

    data.clear();

    m_LineInput.clear();
    m_Leftover.clear();
    if (!importCorrect(ifstream1))
        return false;

    //terminate answer
    getline(ifstream1, m_LineInput, '\n');
    istringstream str3(m_LineInput);
    str3 >> data >> m_Answers.m_NumOfTerminate >> m_Leftover;

    if (m_Answers.m_NumOfTerminate < 0 || !m_Leftover.empty() || data != "Terminate-answer")
        return false;
    data.clear();
    m_LineInput.clear();
    m_Leftover.clear();
    return  importTerminate(ifstream1);

}
//is not needed
bool CEvaluation::importAll(ifstream &ifstream1) { return true; }

bool CEvaluation::importCorrect(ifstream &ifstream1) {

    //text of answer
    string data;
    getline(ifstream1, m_LineInput, '\n');
    istringstream str(m_LineInput);

    m_Answers.m_CorrectAnswers[0] = m_LineInput;
    m_Answers.m_Answers[0] = m_LineInput;

    return true;

}

bool CEvaluation::importTerminate(ifstream &ifstream1) {

    string data;

    m_LineInput.clear();

    // no/all terminate
    if (m_Answers.m_NumOfTerminate == 0 || m_Answers.m_NumOfTerminate == INT16_MAX) {
        getline(ifstream1, m_LineInput);
        return m_LineInput.empty();
    }
    //reasonable amount of terminate
    else {
        for (int i = 0; i < m_Answers.m_NumOfTerminate; i++) {
            getline(ifstream1, m_LineInput, '\n');
            istringstream str(m_LineInput);
            str >> m_Answers.m_AnswerID;

            if (m_Answers.m_AnswerID < 0  ||m_Answers.m_AnswerID > m_Answers.m_NumOfTerminate)
                return false;

            while (str >> data)
                m_Answers.m_AnswerString.append(data + " ");

            if (m_Answers.m_AnswerString[m_Answers.m_AnswerString.length() - 1] == ' ')
                m_Answers.m_AnswerString.pop_back();

            m_Answers.m_TerminateAnswers[m_Answers.m_AnswerID] = m_Answers.m_AnswerString;
            m_Answers.m_AnswerString.clear();
            str.clear();
        }
        return true;
    }

}

bool CEvaluation::importAnswers(ifstream &ifstream1) {
    string data;
    //correct answers
    getline(ifstream1, m_LineInput, '\n');
    istringstream str(m_LineInput);
    str >> data >> m_Answers.m_NumOfCorrect >> m_Leftover;

    if (m_Answers.m_NumOfAll < 0 || !m_Leftover.empty() || data != "Correct-Answer")
        return false;
    if (!importCorrect(ifstream1))
        return false;
    //clean up
    data.clear();
    m_LineInput.clear();
    m_Leftover.clear();

    //terminate answers
    getline(ifstream1, m_LineInput, '\n');
    istringstream str2(m_LineInput);
    str2 >> data >> m_Answers.m_NumOfTerminate >> m_Leftover;

    if (m_Answers.m_NumOfTerminate < 0 || !m_Leftover.empty() || data != "Terminate-answer")
        return false;

    return importTerminate(ifstream1);
}

bool CWriteCountedValue::importCorrect(ifstream &ifstream1) {

    //metadata
    string data;
    istringstream str;

    //reads correct
    getline(ifstream1, m_LineInput, '\n');
    str.str(m_LineInput);
    str >> data >> m_Answers.m_NumOfCorrect >> m_Leftover;

    if (m_Answers.m_NumOfCorrect != 1 || !m_Leftover.empty() || data != "Correct-Answer")
        return false;

    //reads value
    m_LineInput.clear();
    getline(ifstream1, m_LineInput, '\n');
    istringstream str2(m_LineInput);
    //reads main value
    str2 >> m_Value;

    m_LineInput.clear();

    //decimals
    getline(ifstream1, m_LineInput, '\n');
    istringstream str3(m_LineInput);
    str3 >> data >> m_Precious >> m_Leftover;

    if (m_Answers.m_NumOfCorrect != 1 || !m_Leftover.empty() || data != "Number-of-decimals")
        return false;

    return true;
}

bool CWriteCountedValue::importTerminate(ifstream &ifstream1) {

    //metadata
    istringstream str;
    string data, text, input;


    //infinum
    getline(ifstream1, m_LineInput, '\n');
    str.str(m_LineInput);
    str >> data >> text >> input >> m_Leftover;

    if (data != "Terminate-answer" || text != "INFINUM" || !m_Leftover.empty() || !isDouble(input))
        return false;

    //clean up
    data.clear();
    text.clear();
    if (input != "N") {
        str.str(input);
        str >> m_Inifinum;
    } else
        m_SetInfinum = false;
    input.clear();

    //supremum
    getline(ifstream1, m_LineInput, '\n');
    istringstream str2(m_LineInput);
    str2 >> data >> text >> input >> m_Leftover;

    if (data != "Terminate-answer" || text != "SUPREMUM" || !m_Leftover.empty() || !isDouble(input))
        return false;

    input.clear();
    if (input != "N") {
        str.str(input);
        str >> m_Supremum;
    } else
        m_SetSupremum = false;


    return true;

}

bool CWriteCountedValue::importAnswers(ifstream &ifstream1) {

    if (!importCorrect(ifstream1))
        return false;

    return importTerminate(ifstream1);


}


