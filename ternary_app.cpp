#include <iostream>
#include <sstream>
#include <regex>
#include "ternary_app.h"

TernaryApp::TernaryApp(): tree(new TernaryTree()){}

/*
 * A konstruktor létrehozza a hármas fát úgy, hogy
 * feldolgozza és végrehajtja a command_line-ban foglalt műveleti sort.
 * Hibás műveleti sor esetén kivételt dob és letörli a fát.
 */
TernaryApp::TernaryApp(std::string command_line) noexcept(false): tree(new TernaryTree()) {
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
    std::regex reg("^((([TURMLCABP0]|(-?[123456789][0123456789]*)),)*(([TURMLCABP0]|(-?[123456789][0123456789]*))))?$");
    if(!std::regex_match(command_line,reg)) throw FormatErrorException();

    auto* tmpTree=new TernaryTree(*tree);
    std::stringstream ss; ss<<command_line;
    for(std::string c; std::getline(ss, c, ','); ){
        try{
            if(c=="T") tree->moveCursor(top);
            else if(c=="U") tree->moveCursor(up);
            else if(c=="R") tree->moveCursor(right);
            else if(c=="M") tree->moveCursor(middle);
            else if(c=="L") tree->moveCursor(left);
            else if(c=="C") tree->rotateClockwise();
            else if(c=="A") tree->rotateAnticlockwise();
            else if(c=="B") std::cout<<tree->generateBinaryTree().dumpTree()<<std::endl;
            else if(c=="P") std::cout<<tree->dumpTree()<<std::endl;
            else{
                std::regex reg2("0|(-?[123456789][0123456789]*)");
                if(!std::regex_match(c,reg2)) throw CommandNotSupportedException();

                std::stringstream ss2; long long int li; ss2<<c; ss2>>li;
                if(li!=(long int)li) throw ValueOutOfBoundException();

                tree->addValue((long int)li);
            }
        }
        catch (NoParentException &e){
            delete tree;
            tree=tmpTree;
            std::cout<<"(NoParentException)"<<std::endl;
            throw CommandFailedException();
        }
        catch (NoLeftChildException &e){
            delete tree;
            tree=tmpTree;
            std::cout<<"(NoLeftChildException)"<<std::endl;
            throw CommandFailedException();
        }
        catch (NoMiddleChildException &e){
            delete tree;
            tree=tmpTree;
            std::cout<<"(NoMiddleChildException)"<<std::endl;
            throw CommandFailedException();
        }
        catch (NoRightChildException &e){
            delete tree;
            tree=tmpTree;
            std::cout<<"(NoRightChildException)"<<std::endl;
            throw CommandFailedException();
        }
        catch (CommandNotSupportedException &e){
            delete tree;
            tree=tmpTree;
            throw e;
        }
        catch (ValueOutOfBoundException &e){
            delete tree;
            tree=tmpTree;
            throw e;
        }
    }
    delete tmpTree;
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
