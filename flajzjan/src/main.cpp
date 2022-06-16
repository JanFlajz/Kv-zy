#include "CCreator.h"
#include <ncurses.h>
#include "cstring"
#include "CImport.h"

using namespace std;

//menu width
#define BOXWIDTH 40
//menu height
#define BOXHEIGHT 8
//num of choices
#define MENUSIZE 4
#define MAXSIZE 50

/**
 * ends the program go back to terminal
 *
 */
void goExit() {
    mvprintw(20, 50, "Press any key to exit program.\n");
    getch();
    endwin();
    exit(1);
}

/**
 * creates new quiz and move on to specification
 * @param windowMenu menu of choices that will disappear
 * after creation returns to main menu
 */
void goCreate(WINDOW *windowMenu) {
    CCreator c1;
    clear();
    werase(windowMenu);
    c1.welcome();
}

/**
 * move to filling porcess
 * @param windowMenu menu of choices that will disappear
 */
void goFill(WINDOW *windowMenu) {
    //new screen
    clear();
    werase(windowMenu);
    refresh();

    mvprintw(1, 20, "Press any key to continue");
    refresh();
    getch();

    //continue to import and fill
    CImporter import;
    import.importFile();

}

/**show help to user
 *
 * @param windowMenu window menu of choices
 */
void goHelp(WINDOW *windowMenu) {

    int posY = 20, posX = 50;
    mvprintw(posY, posX, "Use UP and DOWN ARROW to move and ENTER to select your choice.\n");
    mvprintw(posY+1, posX, "Press DOWN ARROW to go back.\n");
    refresh();

    while (true) {
        int i = wgetch(windowMenu);
        if (i == KEY_DOWN)
            break;
    }

    //deletes text lines
    move(posY, posX);
    clrtoeol();
    move(posY+1,posX);
    clrtoeol();
    refresh();

}


/**Function that displays menu to terminal
 * @param windowMenu: the menu to print
 * @param highlight: value that gets highlighted
 */
void displayMenu(WINDOW *windowMenu, int highlight) {

    char choices[][MAXSIZE] = {"1. Create a new quiz", "2. Fill an existing quiz", "3. Help", "4. Exit"};

    int x = 2;
    int y = 2;

    box(windowMenu, 0, 0);
    for (int i = 0; i < MENUSIZE; i++) {
        if (highlight == i + 1) {
            wattron(windowMenu, A_REVERSE);
            mvwprintw(windowMenu, y, x, "%s", choices[i]);
            wattroff(windowMenu, A_REVERSE);
        } else {
            mvwprintw(windowMenu, y, x, "%s", choices[i]);
        }
        y++;
    }
    wrefresh(windowMenu);

}
/**
 * initilize main menu and get user answer
 * insipired by: https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/menus.html
 */
void init() {

    //winfow initialization
    WINDOW *windowMenu;
    refresh();
    initscr();
    clear();
    noecho();
    cbreak();
    //box properties set
    int startx = (150 - BOXWIDTH) / 2;
    int starty = (24 - BOXHEIGHT) / 2;
    int highlight = 1;
    int chosen = 0;
    int input;


    //Greets user to this program
    mvprintw(1, 50, "Hello and welcome to Parast quiz creator and executioner!");
    //dumps cursor
    curs_set(0);

    //print menu
    windowMenu = newwin(BOXHEIGHT, BOXWIDTH, starty, startx);
    //enable keyboard
    keypad(windowMenu, TRUE);
    refresh();
    displayMenu(windowMenu, highlight);
    /**Displays menu of possible choices
     * 1. Create new Quiz
     * 2. Fill Quiz
     * 3. Exit
     **/
//going through menu
    while (true) {
        input = wgetch(windowMenu);
        if (input == KEY_UP) {
            if (highlight == 1)
                highlight = MENUSIZE;
            else
                highlight--;
        } else if (input == KEY_DOWN) {
            if (highlight == MENUSIZE)
                highlight = 1;
            else
                highlight++;
        } else if (input == 10) {
            chosen = highlight;
            if (chosen == 3) {
                goHelp(windowMenu);
            } else {
                if (chosen == 1) {
                    goCreate(windowMenu);
                    break;
                } else if (chosen == 2) {
                    goFill(windowMenu);
                    break;
                } else {
                    goExit();
                    break;
                }
            }

        } else
            refresh();

        displayMenu(windowMenu, highlight);
        if (chosen > MENUSIZE)
            break;
    }
    clrtoeol();
    refresh();

}

int main() {
    //prints menu till it program isnot exited by user
    while (true)
        init();
    return 0;
}
