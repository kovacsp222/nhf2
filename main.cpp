
#include <iostream>
#include "ternary_tree.h"
#include "binary_tree.h"
#include "ternary_app.h"

#include "woodpecker.hpp"

TEST("TernaryTree - Copy construction, assignment") {
    {
        TernaryTree t1;
        std::vector<long int> elts = {4, 3, 10, 9, 1};
        for (long int i = 1l; i <= 5l; i++) {
            t1.addValue(i);
        }

        TernaryTree t2(t1);
        TernaryTree t3 = t1;

        CHECK_EQ(t1.dumpTree(), t2.dumpTree());
        CHECK_EQ(t1.dumpTree(), t3.dumpTree());
    }
}

TEST("TernaryTree - Single value insert", 1) {
    {
        TernaryTree t;
        t.addValue(1);

        CHECK_EQ(t.dumpTree(), "(1)");
    }
}

TEST("TernaryTree - Left fill", 1) {
    {
        TernaryTree t;
        for (long int i = 1l; i <= 6l; i++) {
            t.addValue(i);
        }

        std::string result = t.dumpTree();
        std::string expected = "(1(2(5)(6)(-))(3)(4))";
    
        CHECK_EQ(result, expected);
    }
}

TEST("TernaryTree - Left fill (left node full)", 1) {
    {
        TernaryTree t;
        for (long int i = 1l; i <= 8l; i++) {
            t.addValue(i);
        }

        std::string result = t.dumpTree();
        std::string expected = "(1(2(5)(6)(7))(3(8)(-)(-))(4))";
    
        CHECK_EQ(result, expected);
    }
}

TEST("TernaryTree - Left fill (left & middle nodes full)", 1) {
    {
        TernaryTree t;
        for (long int i = 1l; i <= 11l; i++) {
            t.addValue(i);
        }

        std::string result = t.dumpTree();
        std::string expected = "(1(2(5)(6)(7))(3(8)(9)(10))(4(11)(-)(-)))";
    
        CHECK_EQ(result, expected);
    }
}

TEST("TernaryTree - Left fill, multiple levels", 2) {
    {
        TernaryTree t;
        for (long int i = 1l; i <= 23l; i++) {
            t.addValue(i);
        }

        std::string result = t.dumpTree();
        std::string expected = 
            "(1(2(5(14)(15)(16))(6(17)(18)(19))(7(20)(21)(22)))"
            "(3(8(23)(-)(-))(9)(10))(4(11)(12)(13)))";
    
        CHECK_EQ(result, expected);
    }
}

TEST("TernaryTree - Move cursor", 2) {
    {
        TernaryTree t;
        t.addValue(1);

        CHECK_EXC(NoLeftChildException, t.moveCursor(CursorDirection::left));
        CHECK_EXC(NoRightChildException, t.moveCursor(CursorDirection::right));
        CHECK_EXC(NoMiddleChildException, t.moveCursor(CursorDirection::middle));

        t.addValue(2);
        t.addValue(2);
        t.addValue(2);
        // TODO check correct function
        CHECK_NOEXC(t.moveCursor(CursorDirection::left));
        CHECK_NOEXC(t.moveCursor(CursorDirection::up));
        CHECK_NOEXC(t.moveCursor(CursorDirection::right));
        CHECK_NOEXC(t.moveCursor(CursorDirection::up));
        CHECK_NOEXC(t.moveCursor(CursorDirection::middle));
        CHECK_NOEXC(t.moveCursor(CursorDirection::up));
    }
}

TEST("TernaryTree - Rotate clockwise", 2) {
    {
        TernaryTree t;
        for (long int i = 1l; i <= 7l; i++) {
            t.addValue(i);
        }

        t.rotateClockwise();

        std::string result = t.dumpTree();
        std::string expected = "(2(5)(6)(1(7)(3)(4)))";

        CHECK_EQ(result, expected);
    }
}

TEST("TernaryTree - Rotate anticlockwise", 3) {
    {
        TernaryTree t;
        for (long int i = 1l; i <= 7l; i++) {
            t.addValue(i);
        }

        t.rotateClockwise();
        t.moveCursor(CursorDirection::top);
        t.rotateAnticlockwise();

        std::string result = t.dumpTree();
        std::string expected = "(1(2(5)(6)(7))(3)(4))";

        CHECK_EQ(result, expected);
    }
}


TEST("TernaryTree - Left fill after rotation", 2) {
    {
        TernaryTree t;
        for (long int i = 1l; i <= 6l; i++) {
            t.addValue(i);
        }

        t.rotateClockwise();
        t.addValue(7);
        t.addValue(8);
        t.addValue(9);
        t.addValue(10);
        t.addValue(11);
        t.addValue(12);
        t.addValue(13);
        t.addValue(14);

        std::string result = t.dumpTree();
        std::string expected = "(2(5(7(14)(-)(-))(8)(9))(6(10)(11)(12))(1(13)(3)(4)))";

        CHECK_EQ(result, expected);
    }
}

TEST("TernaryTree - Binary tree conversion", 2) {
    {
        TernaryTree t;
        for (long int i = 1l; i <= 6l; i++) {
            t.addValue(i);
        }

        std::string result = t.generateBinaryTree().dumpTree();
        std::string expected = "(1(2(5(-)(6))(3(-)(4)))(-))";

        CHECK_EQ(result, expected);
    }
}

TEST("TernaryApp - Insertion", 3) {
    {
        TernaryApp app("1,2,3,4,5,-6");
        std::string ternary = "(1(2(5)(-6)(-))(3)(4))";
        std::string binary = "(1(2(5(-)(-6))(3(-)(4)))(-))";

        CHECK_EQ(app.dumpTernaryTree(), ternary);
        CHECK_EQ(app.dumpBinaryTree(), binary);
    }
}

// etc.

WOODPECKER_MAIN()
