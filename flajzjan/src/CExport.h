
#ifndef SRC_CEXPORT_H
#define SRC_CEXPORT_H

#include "CQuiz.h"
using namespace std;


class CExport{
public:
    /**
    * Constructor  initials empty instance
    */
    CExport() = default;
     ~CExport() = default;
    /**creates file from imported quiz
     * @param cQuiz quiz that is exportet by pages
     */
    virtual void exportToFile(const CQuiz & cQuiz) = 0;
    /**creates new file thats name is unique
     * @param path path to file that will be exteded
     * @return path to new unique file
     */
    string createFile(string path);
    /**detects if file is empty
     * @param path path to file that will be exported to
     * @param stream filestrem to in/out
     * @return if file is empty
     */
    bool isEmpty(const  string & path, fstream & stream)const;
    /**checks if folder exists
     * @param path path to inport to if is okay
     * @return true if is path okay
     */
    bool correctPath(const string & path)const;

    /**file into which i save quiz file*/
    string m_Path;

};



class CExportText: public CExport{
public:
    /**
   * Constructor initials empty instance
   */
    CExportText() = default;
    ~CExportText() =default;
    void exportToFile(const CQuiz & cQuiz) override;

};
class CExportTextWithResults: public CExport{
public:
    /**
   * Constructor  initials empty instance
   */
    CExportTextWithResults() = default;
    ~CExportTextWithResults() =default;
    void exportToFile(const CQuiz & cQuiz) override;
};
class CExportToFillWithResults : public CExport{
public:
    /**
   * Constructor  initials empty instance
   */
    CExportToFillWithResults() = default;
    ~CExportToFillWithResults() =default;
    void exportToFile(const CQuiz & cQuiz) override;
};



#endif //SRC_CEXPORT_H
