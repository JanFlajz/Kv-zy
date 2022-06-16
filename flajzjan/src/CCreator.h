
#ifndef KOD_CCREATOR_H
#define KOD_CCREATOR_H

#include <curses.h>
#include "CQuiz.h"


class CCreator {

public:
    /**
   * Constructor and destructors initials empty instance
   */
    CCreator()= default;
    ~CCreator() = default;

    /**prints that you are in question creator*/
    void welcome();
    /**ends creation and exports quiz as file*/
    void end(const CQuiz & quiz, const int & choice )const;

    /**
     * prints menu that helps you seletcts exportQuiz type
     * @param windowMenu menu that show possibilities to user
     * @param highlight  selects which poss is highlighted
     */
    void printExportMenu(WINDOW * windowMenu, const int highlight)const;

    /**
     * actually choose from menu and then procced answer
     * @param quiz quiz that will be exporter
     */
    void exportQuiz(const CQuiz & quiz )const;

};

#endif //KOD_CCREATOR_H