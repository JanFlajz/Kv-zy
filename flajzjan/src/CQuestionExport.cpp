#include "CQuestion.h"
#include "iostream"

using namespace std;



void CSingleChoice::printDataTextFile(ostream &os, int &num) const {
    os << num << "." << m_Text << " (" << m_Type << " ) " << endl;
    //formatting
    os << endl;
    char alphabet = 'a';

    for (auto &m_Answer : m_Evaluation->m_Answers.m_Answers) {

        os << "\t" << alphabet << ") " << m_Answer.second << endl;
        alphabet++;
    }
    //formatting
    os << endl;
    if (m_Evaluation->m_TextFill) {

        os << endl;
        os << "Write your answer: " << "   " << m_AprroxOneAnswer << endl << endl;
    }

    num++;
}

void CMultiChoice::printDataTextFile(ostream &os, int &num) const {
    os << num << "." << m_Text << " (" << m_Type << " ) " << endl;
    //formatting
    os << endl;
    char alphabet = 'a';

    for (auto &m_Answer : m_Evaluation->m_Answers.m_Answers) {

        os << "\t" << alphabet << ") " << m_Answer.second << endl;
        alphabet++;
    }
    //formatting
    os << endl;
    if (m_Evaluation->m_TextFill) {
        os << endl;
        os << "Write your answers: " << "   ";
        for (int i = 0; i < m_Evaluation->m_Answers.m_NumOfCorrect; i++) {
            os << m_AprroxOneAnswer << "   ";
        }
        os << endl << endl;
    }
    num++;
}

void CTextChoice::printDataTextFile(ostream &os, int &num) const {
    os << num << "." << m_Text << endl;
    for (int i = 0; i < 2; i++)
        os << endl;

    os << '\t';
    for (int i = 0; i < m_Evaluation->m_Answers.m_NumOfCorrect; i++) {
        os << m_AprroxOneAnswer << "  ";
    }

    os << endl;
    num++;
}

void CYesNoChoice::printDataTextFile(ostream &os, int &num) const {
    os << num << "." << m_Text << endl << endl;

    for (auto &m_Answer : m_Evaluation->m_Answers.m_Answers)
        os << '\t' << "#" << m_Answer.second;

    //2 empty lines
    os << endl;
    os << endl;


    if (m_Evaluation->m_TextFill) {
        os << '\t' << "Write your answer:";
        os << '\t' << m_AprroxOneAnswer << endl;
        os << endl;
    }

    num++;
}

void CQuestion::printResults(ostream &os, int &num) {

    os << endl << "Correct answer(s): ";
    for (auto &correctAnswer : m_Evaluation->m_Answers.m_CorrectAnswers) {
        os << correctAnswer.first + 1 << ") " << correctAnswer.second << " ";
    }
    os << endl << endl;
}


void CQuestion::printHeader(ostream &os, int &number) const {
    os << "Question " << number++ << endl;
    os << m_Type << endl;
    os << m_Text << endl;
    os << "Evaluation" << endl << m_Evaluation->m_ID << ' ' << m_Evaluation->m_Type;

}

void CSingleChoice::printDataFillAnswers(ostream &os, int &number) const {
    printHeader(os, number);

    if (m_Evaluation->m_TextFill)
        os << ' ' << "Text-Answer" << endl;
    else
        os << endl;

    os << "Possibilities " << m_Evaluation->m_Answers.m_Answers.size() << endl;
    for (auto &item :m_Evaluation->m_Answers.m_Answers)
        os << item.first << " " << item.second << endl;

    os << "Correct-Answer " << m_Evaluation->m_Answers.m_CorrectAnswers.size() << endl;
    for (auto &item :m_Evaluation->m_Answers.m_CorrectAnswers)
        os << item.first << " " << item.second << endl;

    os << "Terminate-answer " << m_Evaluation->m_Answers.m_TerminateAnswers.size() << endl;
    if (m_Evaluation->m_Answers.m_TerminateAnswers.empty())
        os << endl;
    for (auto &item :m_Evaluation->m_Answers.m_TerminateAnswers)
        os << item.first << " " << item.second << endl;

}

void CMultiChoice::printDataFillAnswers(ostream &os, int &number) const {
    printHeader(os, number);

    if (m_Evaluation->m_TextFill)
        os << ' ' << "Text-Answer" << endl;
    else
        os << endl;

    os << "Possibilities " << m_Evaluation->m_Answers.m_Answers.size() << endl;
    for (auto &item :m_Evaluation->m_Answers.m_Answers)
        os << item.first << " " << item.second << endl;

    os << "Correct-Answer " << m_Evaluation->m_Answers.m_CorrectAnswers.size() << endl;
    if (m_Evaluation->m_Answers.m_CorrectAnswers.empty())
        os << endl;
    for (auto &item :m_Evaluation->m_Answers.m_CorrectAnswers)
        os << item.first << " " << item.second << endl;

    os << "Terminate-answer " << m_Evaluation->m_Answers.m_TerminateAnswers.size() << endl;
    if (m_Evaluation->m_Answers.m_TerminateAnswers.empty())
        os << endl;
    for (auto &item :m_Evaluation->m_Answers.m_TerminateAnswers)
        os << item.first << " " << item.second << endl;

}

void CTextChoice::printDataFillAnswers(ostream &os, int &number) const {
    printHeader(os, number);
    os << endl;

    if (m_Evaluation->m_ID != 4) {

        os << "Correct-Answer " << '1' << endl << m_Evaluation->m_Answers.m_CorrectAnswers[0] << endl;

        os << "Terminate-answer " << m_Evaluation->m_Answers.m_NumOfTerminate << endl;
        if (m_Evaluation->m_Answers.m_TerminateAnswers.empty())
            os << endl;
        for (auto &item :m_Evaluation->m_Answers.m_TerminateAnswers)
            os << item.first << " " << item.second << endl;


    } else {

        shared_ptr<CWriteCountedValue> value = dynamic_pointer_cast<CWriteCountedValue>(m_Evaluation);
        os << "Correct-Answer " << '1' << endl << m_Evaluation->m_Answers.m_CorrectAnswers[0] << endl;
        os << "Number-of-decimals " << value->m_Precious << endl;
        os << "Terminate-answer " << "INFINUM " << m_Evaluation->m_Answers.m_TerminateAnswers[0] << endl;
        os << "Terminate-answer " << "SUPREMUM " << m_Evaluation->m_Answers.m_TerminateAnswers[1] << endl;

    }


}

void CYesNoChoice::printDataFillAnswers(ostream &os, int &number) const {
    printHeader(os, number);
    if (m_Evaluation->m_TextFill)
        os << ' ' << "Text-Answer " << endl;
    else
        os << endl;

    os << "Possibilities " << m_Evaluation->m_Answers.m_Answers.size() << endl;
    for (auto &item :m_Evaluation->m_Answers.m_Answers)
        os << item.first << " " << item.second << endl;

    os << "Correct-Answer " << m_Evaluation->m_Answers.m_CorrectAnswers.size() << endl;
    for (auto &item :m_Evaluation->m_Answers.m_CorrectAnswers)
        os << item.first << " " << item.second << endl;

    os << "Terminate-answer " << m_Evaluation->m_Answers.m_TerminateAnswers.size() << endl;
    if (m_Evaluation->m_Answers.m_TerminateAnswers.empty())
        os << endl;
    for (auto &item :m_Evaluation->m_Answers.m_TerminateAnswers)
        os << item.first << " " << item.second << endl;
}

