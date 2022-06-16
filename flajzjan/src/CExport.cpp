
#include <fstream>
#include <sstream>
#include "CExport.h"
#include "ostream"
#include "CQuiz.h"
#include <sys/stat.h>


bool CExport::isEmpty(const string &path, fstream &stream) const {
    string testString;

    while (getline(stream, testString)) {
        if (!testString.empty()) {
            stream.clear();
            return false;
        }
    }
    return testString.empty();
}

/**
 * @param suffix is fileType
 * @param fileName is prefered name for quiz file
 * @param newPath is path to file created to insert new quiz
 **/
string CExport::createFile(string newPath) {

    string fileName = "/quiz";
    string suffix = ".txt";
    stringstream appending;
    int fileCount = 0;
    fstream stream;
    //creates new file
    appending << fileName << fileCount << suffix;
    newPath.append(appending.str());

    stream.open(newPath, ios::out | ios::in | std::fstream::app);
    //finds file that has not been already used
    while (!isEmpty(newPath, stream)) {
        stream.close();
        fileCount++;
        newPath.erase(newPath.length() - appending.str().length());
        appending.str("");
        appending << fileName << fileCount << suffix;
        newPath.append(appending.str());
        stream.open(newPath, ios::out | ios::in | std::fstream::app);
    }
    return newPath;
}


bool CExport::correctPath(const string &path) const {

    struct stat buffer;
    return (stat(path.c_str(), &buffer) == 0);

}


void CExportText::exportToFile(const CQuiz &cQuiz) {
    //creates folder to export;
    m_Path = "examples/export";
    if (!correctPath(m_Path))
        mkdir(m_Path.c_str(), 0777);


    ofstream ofstream1(createFile(m_Path));
    ofstream1 << "\t\t\t\t" << "NEW QUIZ" << endl;
    int count = 1;
    for (int i = 0; i < cQuiz.m_NumOfPages; i++) {
        int max = cQuiz.m_Pages[i].m_NumOfQuestions;
        for (int j = 0; j < max; j++) {
            cQuiz.m_Pages[i].m_Questions[j]->printDataTextFile(ofstream1, count);
        }
    }
}

void CExportTextWithResults::exportToFile(const CQuiz &cQuiz) {
    //creates folder to export;
    m_Path = "examples//export";
    if (!correctPath(m_Path))
        mkdir(m_Path.c_str(), 0777);

    ofstream ofstream1(createFile(m_Path));
    ofstream1 << "\t\t\t\t" << "NEW QUIZ" << endl;
    int count = 1;
    for (int i = 0; i < cQuiz.m_NumOfPages; i++) {
        int max = cQuiz.m_Pages[i].m_NumOfQuestions;
        for (int j = 0; j < max; j++) {
            cQuiz.m_Pages[i].m_Questions[j]->printDataTextFile(ofstream1, count);
            cQuiz.m_Pages[i].m_Questions[j]->printResults(ofstream1, count);
        }

    }
}

void CExportToFillWithResults::exportToFile(const CQuiz &cQuiz) {
    m_Path = "examples/import";
    if (!correctPath(m_Path))
        mkdir(m_Path.c_str(), 0777);

    ofstream ofstream1(createFile(m_Path));
    ofstream1 << "QUIZ-WITH-RESULTS" << endl;
    ofstream1 << "Num-of-pages " << cQuiz.m_NumOfPages << endl;
    int start = 1;
    for (int i = 0; i < cQuiz.m_NumOfPages; i++) {
        ofstream1 << "Page " << i + 1 << endl;
        ofstream1 << "Num-of-questions " << cQuiz.m_Pages[i].m_NumOfQuestions << endl;
        cQuiz.m_Pages[i].exportQuestionsWithResults(ofstream1, start);
    }
    ofstream1 << "ENDQUIZ";
}
