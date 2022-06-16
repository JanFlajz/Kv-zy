
#ifndef KOD_CIMPORT_H
#define KOD_CIMPORT_H

#include <string>

using namespace std;

class CImporter {
public:
    /**
  * Constructor initilize empty instance
  */
    CImporter() = default;

    ~CImporter() = default;

    /**decides if input file is okay
     * @return true if file is okey for import
     */
    bool correctFile() const;

    /**reads header and whole quiz
     * @param head header of quiz
     * @param ifstream1 file strem to read from
     * @return true if quiz is imported succsesfully
     */
    bool correctHeader(const string &head, ifstream &ifstream1) const;

    /**
     * imports given file = start of importing
     */
    void importFile();

    /**reads the file name
     * @param posY termianal posY to start printing
     * @param posX termianal posX to start printing
     * @return path to file
     */
    static string readFile(int &posY, int &posX);

    /**
     * detects right file format
     * @return true if file is .txt
     */
    bool correctSuffix() const;


    /**path for every import file*/
    string m_Path ;

};


#endif //KOD_CIMPORT_H
