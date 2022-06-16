TARGET_EXEC = flajzjan


CXX = g++
CXXFLAGS = -Wall -pedantic -Wextra -std=c++14  -g
VALGRINDFLAGS = -v --track-origins=yes --leak-check=full --show-leak-kinds=all

.PHONY: all
all: compile doc

.PHONY: run
run: compile
	./$(TARGET_EXEC)

.PHONY: clean
clean:
	rm -rf $(TARGET_EXEC) src/build/ doc


.PHONY: debug
debug: compile
	valgrind $(VALGRINDFLAGS) ./$(TARGET_EXEC)
compile: $(TARGET_EXEC)


doc: src/main.cpp src/CAnswer.h src/CCreator.h src/CEvaluation.h src/CExport.h src/CImport.h src/CPage.h src/CQuestion.h src/CQuiz.h
	doxygen Doxyfile

$(TARGET_EXEC): src/build/main.o src/build/CCreator.o src/build/CEvaluation.o src/build/CEvaluationImport.o src/build/CFill.o src/build/CFillEvaluate.o src/build/CImportQuiz.o src/build/CPage.o src/build/CQuestion.o src/build/CQuestionImport.o src/build/CQuestionExport.o src/build/CQuiz.o src/build/Cimport.o src/build/CExport.o
	$(CXX) $^ -o $@ -lncurses

src/build/%.o: src/%.cpp
	mkdir -p src/build
	$(CXX) $(CXXFLAGS) -c $< -o $@



CCreator.o: src/CCreator.cpp src/CCreator.h src/CQuiz.h src/CQuestion.h \
 src/CEvaluation.h src/CAnswer.h src/CPage.h src/CExport.h
CEvaluation.o: src/CEvaluation.cpp src/CEvaluation.h src/CAnswer.h
CEvaluationImport.o: src/CEvaluationImport.cpp src/CEvaluation.h \
 src/CAnswer.h
CExport.o: src/CExport.cpp src/CExport.h src/CQuiz.h src/CQuestion.h \
 src/CEvaluation.h src/CAnswer.h src/CPage.h
CFill.o: src/CFill.cpp src/CQuiz.h src/CQuestion.h src/CEvaluation.h \
 src/CAnswer.h src/CPage.h
CFillEvaluate.o: src/CFillEvaluate.cpp src/CQuestion.h src/CEvaluation.h \
 src/CAnswer.h
Cimport.o: src/Cimport.cpp src/CImport.h src/CQuiz.h src/CQuestion.h \
 src/CEvaluation.h src/CAnswer.h src/CPage.h
CImportQuiz.o: src/CImportQuiz.cpp src/CQuiz.h src/CQuestion.h \
 src/CEvaluation.h src/CAnswer.h src/CPage.h
CPage.o: src/CPage.cpp src/CPage.h src/CQuestion.h src/CEvaluation.h \
 src/CAnswer.h
CQuestion.o: src/CQuestion.cpp src/CQuestion.h src/CEvaluation.h \
 src/CAnswer.h
CQuestionExport.o: src/CQuestionExport.cpp src/CQuestion.h \
 src/CEvaluation.h src/CAnswer.h
CQuestionImport.o: src/CQuestionImport.cpp src/CQuestion.h \
 src/CEvaluation.h src/CAnswer.h
CQuiz.o: src/CQuiz.cpp src/CQuiz.h src/CQuestion.h src/CEvaluation.h \
 src/CAnswer.h src/CPage.h
main.o: src/main.cpp src/CCreator.h src/CQuiz.h src/CQuestion.h \
 src/CEvaluation.h src/CAnswer.h src/CPage.h src/CImport.h

