
#ifndef KOD_CQUESTION_H
#define KOD_CQUESTION_H

#include <string>
#include "memory"
#include "CEvaluation.h"


using namespace std;

class CQuestion {
public:
    /**
     * COnstructor initilize empty instance
     */

    CQuestion() = default;

    /**
     * show evaluation and get respond
     */
    virtual void showPossibleEvaluations() ;

    /**
      * decides evaluation of question
     */
    virtual void setEvaluation(const int &) = 0;

    /**makes shared pointer out of instance
     *
     * @return ptr to instance
     */
    virtual shared_ptr<CQuestion> Clone() const = 0;

    /**prints question attributes to text fill
     * @param os stream for printing
     * @param num question index
     */
    virtual void printDataTextFile(ostream &os, int &num) const = 0;

    /**prints question to get fill with answers

     * @param os  stream for printing
     * @param number question index
     */
    virtual void printDataFillAnswers(ostream &os, int &number) const = 0;


    /**detect if answer was not okay
     * @param answer inputed string from user
     * @return true if answer wsnt terminate
     */
    virtual bool proceedAnswer(const string &answer);

    /**imports the question attributes
     * @param ifstream1 stream for input
     * @return true if file was okay
     */
    bool importData(ifstream &ifstream1);

    /**detects evaluation type
     *
     * @param ifstream1 stream for input
     * @return true if file was okay
     */
    virtual bool importEvaluation(ifstream &ifstream1);

    /**chosses evaluation type
     *
       @param ifstream1 stream for input
     * @return true if file was okay
     */
    virtual bool selectEvaluation(ifstream &ifstream1);

    /**fill the question with answers
     *
     * @param posY terminal posY to read
     * @param posX  terminal posX to read
     * @return true if texts were okay
     */
    virtual bool fillQuestion(int &posY, int &posX);

    /**prints question to get fill
     *
     * @param posY terminal posY to print to user
     * @param posX terminal posX to print to user
     */
    virtual void printDataFill(int &posY, int &posX) const;

    /**prints head of every question
     *
     * @param os stream to print question header
     * @param number index of question
     */
    void printHeader(ostream &os, int &number) const;

    /**prints answers to text file
     *
     * @paramos stream to print metadata of question
     * @param number index of question
     */
    void printResults(ostream &os, int &num);

    /**gets name of question
     *
     * @param posY terminal posY to read name
     * @param posX  terminal posX to read name
     */
    void insertQuestionName(int &posY, int &posX);

    /**get answer at input
     *
     * @param posY terminal posY to print
     * @param posX terminal posX to print
     * @param limit number of possible inputed chars
     * @return written text
     */
    string readAnswer(int &posY, int &posX, const int limit) const;

    /**detects if correct answer for evalution
     *
     * @param m map of answers
     * @param answer string - user inputed answer
     * @return true if answer is contained in value part of map
     */
    static bool containsAnswer(map<int, string> &m, const string &answer);
    /**
     *
     * @param m map of answers
     * @param answer string - user inputed answer
     * @return true if first letter of answer is contained in key part of map
     */
    static bool containsLetter(map<int, string> &m, const string &answer);


    /**returns given number - selects evalution*/
    int readNumber();

    /**m_Input for many purposes*/
    int m_Input = 0;
    /**id of question type*/
    int m_Key;
    /**text of question*/
    string m_Text;
    /**type of question in words*/
    string m_Type;
    /**evaluation*/
    shared_ptr<CEvaluation> m_Evaluation;
    /**detects if correct answer was already inputed*/
    bool m_Correct = false;
    /**line input*/
    string m_LineInput;
    /**detects right amount of strings*/
    string m_Leftover;
    /**stores evaluation ID*/
    int m_EvaluationID;
    /**detects text fill*/
    bool m_TextFill;
    /**detects if user answers incorrectly*/
    bool m_BadAnswer = false;


    /**small imput string for printing*/
    string m_AprroxOneAnswer = "___________";

};

class CSingleChoice : public CQuestion {
public:
    /**
  * Constructor initilize empty instance
  */
    CSingleChoice() {
        m_Key = 1;
        m_Type = "Single-choice";
    };


    void setEvaluation(const int &) override;

    shared_ptr<CQuestion> Clone() const override;

    void printDataTextFile(ostream &os, int &num) const override;

    void printDataFillAnswers(ostream &os, int &number) const override;

};

class CMultiChoice : public CQuestion {

    /**num of correct answers*/
    int m_numOfCorrect;
public:
    /**
   * COnstructor initilize empty instance
   */
    CMultiChoice() {
        m_Key = 2;
        m_Type = "Multi-choice";
        m_numOfCorrect = 0;
    };


    void setEvaluation(const int &) override;

    shared_ptr<CQuestion> Clone() const override;

    void printDataTextFile(ostream &os, int &num) const override;

    void printDataFillAnswers(ostream &os, int &number) const override;

    bool fillQuestion(int &posY, int &posX) override;

    bool proceedAnswer(const string &answer) override;

    /**detects already used correct answers*/
    set<string> m_UsedCorrectAnswers;
    /**detects already used correct indexes*/
    set<int> m_UsedCorrectIndex;
};

class CTextChoice : public CQuestion {
public:
    /**
   * Constructor initilize empty instance
   */
    CTextChoice() {
        m_Key = 3;
        m_Type = "Text-choice";
    };


    void showPossibleEvaluations() override;

    void setEvaluation(const int &) override;

    shared_ptr<CQuestion> Clone() const override;

    void printDataTextFile(ostream &os, int &num) const override;

    void printDataFillAnswers(ostream &os, int &number) const override;


    bool importEvaluation(ifstream &ifstream1) override;

    bool fillQuestion(int &posY, int &posX) override;

    bool selectEvaluation(ifstream &ifstream1) override;

    void printDataFill(int &posY, int &posX) const override;

    bool proceedAnswer(const string &answer)override;

    /**detects if given evalution key is okay
     *
     * @param text that stores evl key
     * @return return if evaluation match qiven value
     */
    static bool rightEvaluation(const string &text);
    /**
     * @param answer user inputed string
     * @return if value in string is legitimate within right value
     */
    bool proceedAnswerWithValue(const string &answer);
};

class CYesNoChoice : public CQuestion {
public:
    /**
  * Constructor initilize empty instance
  */
    CYesNoChoice() {
        m_Key = 4;
        m_Type = "Yes\\No";
    };

    void showPossibleEvaluations() override;

    void setEvaluation(const int &) override;

    shared_ptr<CQuestion> Clone() const override;

    void printDataTextFile(ostream &os, int &num) const override;

    void printDataFillAnswers(ostream &os, int &number) const override;


};


#endif //KOD_CQUESTION_H
