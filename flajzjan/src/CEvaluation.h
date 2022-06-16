
#ifndef KOD_CEVALUATION_H
#define KOD_CEVALUATION_H

#include "string"
#include "vector"
#include "CAnswer.h"
#include "memory"


using namespace std;

class CEvaluation {
public:
    CEvaluation() = default;

    ~CEvaluation() = default;

    /**
     * read answers from user
     */
    virtual void getAnswers() = 0;


    /**reads text of Answers
     * @param posY terminal pos Y
     * @param posX terminal pos X
     * @return inputed value - answer for question and evl
     */
    string readAnswers(int posY, int posX);


    /**
     * reads metadata of the answer
     * @param text
     * @param tposX erminal pos X
     * @param posY erminal pos Y
     * @param rightWasalreadyUsed detects if answer was selected as correct
     * @param currID id of answer in evaluation
     */
    virtual void readMetaData(const string &text, const int &posX, int posY,
                              bool &rightWasalreadyUsed, const int &currID) ;

    /**
     * @return wraped evaluation as smart ptr
     */
    virtual shared_ptr<CEvaluation> Clone() const = 0;

    //
    /**
     *import evaluation meta data
     * @param ifstream1 read answers  with evl from stream
     * @return true if there were no problems with reading
     */
    virtual bool importAnswers(ifstream &ifstream1);

    /**
       * import all possibilites to evl
       * @param ifstream1 read answers  with evl from stream
       * @return true if there were no problems with reading
       */
    virtual bool importAll(ifstream &ifstream1);

    /**imports correct answers to evl
     * @param ifstream1  read answers  with evl from stream
     * @return true if there were no problems with reading
     */
    virtual bool importCorrect(ifstream &ifstream1);

    /**imports terminate answers to evl
   * @param ifstream1  read answers  with evl from stream
   * @return true if there were no problems with reading
   */
    virtual bool importTerminate(ifstream &ifstream1);

    /**type of evaluation ID*/
    int m_ID = 0;
    /**type description*/
    string m_Type;
    /**a in ascii*/
    int m_Alphabet = 97;
    /**string to read answer text;*/
    string m_Input;
    /**stores answers for this evaluation on this question*/
    CAnswers m_Answers;
    /**number of all answers, solves indexing*/
    int m_NumOfAnswers = 0;
    /**detects writing answer as exact text for setchoice*/
    bool m_TextFill;
    /**line input*/
    string m_LineInput;
    /**detects right amount of strings*/
    string m_Leftover;


};

class CChooseFromSet : public CEvaluation {
public:
    CChooseFromSet() {
        m_ID = 1;
        m_Type = "Choose-from-Set";
    }

    ~CChooseFromSet() = default;

    void getAnswers() override;

    void readMetaData(const string &text, const int &posX, int posY, bool &correctWasalreadyUsed,
                      const int &currID) override;

    shared_ptr<CEvaluation> Clone() const override;

    bool importAnswers(ifstream &ifstream1) override;


    bool importAll(ifstream &ifstream1) override;

    bool importCorrect(ifstream &ifstream1) override;

    bool importTerminate(ifstream &ifstream1) override;


    /**
        read numbers from users
        to detect correct and terminate answers

     */
    void getAnswersYesNo();

    /**detects single choice*/
    bool m_OneCorrect = false;
    /**detects use of right answer in single choice question*/
    bool m_SingleChoice = false;
    /**detects yes/no choice*/
    bool m_YesNoChoice = false;


};

class CWriteTextExactMatch : public CEvaluation {
public:
    /**
   * Constructor  initials empty instance
   */
    CWriteTextExactMatch() {
        m_ID = 2;
        m_Type = "Written-text";
    }

    ~CWriteTextExactMatch() = default;

    void getAnswers() override;

    shared_ptr<CEvaluation> Clone() const override;


};

class CCWriteTextRegex : public CEvaluation {
public:
    /**
   * Constructor  initials empty instance
   */
    CCWriteTextRegex() {
        m_ID = 3;
        m_Type = "Regex";
    }

    ~CCWriteTextRegex() = default;

    void getAnswers() override;
    shared_ptr<CEvaluation> Clone() const override;


};

class CWriteCountedValue : public CEvaluation {
public:
    /**
     * Constructor  initials empty instance
     */
    CWriteCountedValue() {
        m_ID = 4;
        m_Type = "Counted-Value";
    }

    ~CWriteCountedValue() = default;

    void getAnswers() override;

    void readMetaData(const string &text, const int &posX, int posY,
                      bool &corWasalreadyUsed, const int &currID) override;

    shared_ptr<CEvaluation> Clone() const override;

    bool importAnswers(ifstream &ifstream1) override;

    bool importCorrect(ifstream &ifstream1) override;

    bool importTerminate(ifstream &ifstream1) override;



    /**
     * detects if number is written correctly
     * @param input string that should contain double value
     * @return true if its nice double or N
     */
    bool isDouble(const string &input) const;

    /**detects if number of decimals to round is written correctly
     * @param input string that should contain only int 0-10
     * @return true if its nice int
     */
    bool isInt(const string &input) const;

    /**
     * reads border line values for ending the quiz
     * @param posY terminal pos Y
     * @param posX terminal pos X
     * @return
     */
    string readBorder(const int &posY, const int &posX);

    /**number of decimals to round expected result*/
    int m_Precious;
    /**stores counted value*/
    double m_Value;
    /**heighest of lowest terminate answers*/
    double m_Inifinum;
    /**lowest of heighest terminate answers*/
    double m_Supremum;
    /**detects chosen infinum*/
    bool m_SetInfinum  = true;
    /**detects chosen supremum*/
    bool m_SetSupremum = true;

};


#endif //KOD_CEVALUATION_H