//
// Created by balin on 10/25/2021.
//

#include <iostream>
#include "ternary_app.h"

TernaryApp::TernaryApp(){
    tree=new TernaryTree;
}

/*
 * A konstruktor létrehozza a hármas fát úgy, hogy
 * feldolgozza és végrehajtja a command_line-ban foglalt műveleti sort.
 * Hibás műveleti sor esetén kivételt dob és letörli a fát.
 */
TernaryApp::TernaryApp(std::string command_line) noexcept(false) {
    tree=new TernaryTree;
    processCommandLine(command_line);
}

TernaryApp::~TernaryApp() {
    delete tree;
}

/*
 * Feldolgozza a command_line-ban foglalt műveleti sor tartalmát és végrehajtja
 * a tárolt hármas fán. Hibás műveleti sor esetén kivételt dob és visszaállítja a fát
 * a művelet előtti állapotra.
 */
void TernaryApp::processCommandLine(std::string command_line) noexcept(false) {
    //TODO: szamok
    for(char c : command_line){
        if(c=='T'){
            tree->moveCursor(top);
        }
        else if(c=='U'){
            tree->moveCursor(up);
        }
        else if(c=='R'){
            tree->moveCursor(right);
        }
        else if(c=='M'){
            tree->moveCursor(middle);
        }
        else if(c=='L'){
            tree->moveCursor(left);
        }
        else if(c=='C'){
            tree->rotateClockwise();
        }
        else if(c=='A'){
            tree->rotateAnticlockwise();
        }
        else if(c=='B'){
            tree->generateBinaryTree();
        }
        else if(c=='P'){
            std::cout<<"Tree: "<<tree<<std::endl;
        }
    }
}
/*
 * A dumpTernaryTree egy stringbe dumpolja a tárolt hármasfát a kiadott fealdatkiírásban
 * leírtak szerint
 */
std::string TernaryApp::dumpTernaryTree() {
    return tree->dumpTree();;
}

/*
 * A dumpTernaryTree egy stringbe dumpolja a tárolt hármas fából generált bináris fát a
 * kiadott fealdatkiírásban leírtak szerint
 */
std::string TernaryApp::dumpBinaryTree() {
    return tree->generateBinaryTree().dumpTree();
}


