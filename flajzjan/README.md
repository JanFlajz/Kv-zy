# CZ
Můj program Parast má za úkol umět vytvářet a testovat kvízy.
Testovat se mohou jak ty kvízy, které ve svém programu vytvořím, tak ty,
které importuji.

Při spuštění programu si uživatel bude moci vybrat, jestli chce kvíz vytvářet
nebo vyplnovat.


Při vytváření kvízů bude uživateli k dispozici několik druhů otázek, které 
budou na základě svého typu ohodnoceny určitým způsobem. Uživatel musí do
kvízu zadat svou správnou odpověď a v závislosti na typu ohodnocení i odpovědi další.
Otázky se budou ukládat na stránky, podle kterých se budou při testování 
i zobrazovat.

Po vytvoření kvízu se nahraje do testovací části programu, která bude na základě
dat od tvůrce zobrazovat jednotlivé stránky s otázkami. Pokud tak tvůrce určí,
bude se přeskakovat v kvizu na různé pozice na základě odpovědí. Když testovaný 
dosáhne na konec, zobrazí se mu jeho hodnocení, které má na základě pokynů
tvůrce.


Po zapnutí aplikace se před uživatelem objeví menu, které vám dá na výběr importovat nebo exportovat kvíz,
ukončit a zobrazit nápovědu. V menu se uživatel pohybuje pomocí šipek a vybírá enterem. Tyto instrukce se mu zobrazí
v nápovědě.

Když vyberete Vytvoření kvízu, budete si moci vybrat ze 4 typů otázek:

-Singlechoice
-Multichoice
-TextChoice
-Yes/no choice

Po vybrání typu otázky se pak program ptá na její název a v závislosti na otázce vybírá uživatel různá ohodnocení.
Kromě správných odpovědí může uživatel vybrat tzv. terminate answers, které ukončují vyplňování
kvízu při špatné odpovědi. Po vyplnění všech odpovědí uživatel zmáčkne backspace a může kvíz
exportovat buď jako tisknutelný formát s výsledky/bez výsledků nebo k vyplnění v programu.

Když uživatel vybere možnost, program se vrátí zpět do menu a nechá uživatele pokračovat.
Když potom uživatel vybere vyplnění kvízu, program ho nechá napsat jméno .txt souboru v flajzjan/examples/import.
Pokud se soubor přečte správně, program se posune k vyplňovací části, kde se vždy na stránku zobrazí veškeré
otázky a ty uživatel postupně vyplňuje. Na konci vyplňování se objeví statistika, jak a které otázky nebyly
vyplněné správně.
#EN
This program called Parast is able to create and test quizzes. The quizzes that can be tested are both those that I create in my program and those that I import.
After start of the program, the user will be able to choose whether they want to create or fill the quiz.
While creating quizzes, several types of questions are available to the user for usage. Each type of question is differently evaluated. The user must enter their correct answer and, depending on the type of rating, other answers into the quiz. The questions will be stored on the pages and displayed accordingly during testing.

Once the quiz is created, it will be uploaded to the testing part of the program, which will display the individual question pages based on data from the creator. If the creator so specifies, it will jump to different positions in the quiz based on the answers. When the test taker reaches the end, they will be shown their score based on the creator's instructions.

After the application is turned on, a menu appears in front of the user, which gives you the choice to import or export the quiz, quit and see the instruction. In the menu the user moves with the arrow keys and selects the quiz with the enter key. These instructions are displayed
in the instruction tab. 
When Create Quiz tab is selected, you will be able to choose from 4 types of questions:
-Singlchoice
-Multichoice
-TextChoice
-Yes/no choice 
After selecting the question type, the program then asks for the question name and depending on the question, the user selects possible question evaluation.
In addition to the correct answers, the user can select the so-called termianate answers, which terminate the filling in
After filling in all the answers and their data, the user presses the backspace key and can take the quiz 
can export the quiz either as a printable format with/ without results or for filling in the program.
When the user selects the option the program returns to the menu and lets the user continue.
If the user then selects to fill in the quiz the program will let the user write the name of the .txt file in flajzjan/examples/import.
If the file is read correctly, the program will move to the fill-in section where all the
questions and the user fills them in one by one. At the end of the filling, statistics will appear showing how and which questions were not
were filled in correctly.


Translated with DeepL.com (free version)






