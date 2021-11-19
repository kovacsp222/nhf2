#include "ternary_tree.h"
#include <vector>

TernaryTree::TernaryTree(){
    root=cursor=nullptr;
}

TernaryTree::TernaryTree(const TernaryTree& _other){
    this->root= _copyOf(_other.root, nullptr);
    this->cursor=this->root; //vagy =_other.cursor;
}

TernaryTree &TernaryTree::operator=(const TernaryTree& _other){
    if(&_other==this) return *this;
    _destroy(this->root);
    this->root= _copyOf(_other.root, nullptr);
    this->cursor=this->root; //vagy =_other.cursor;
    return *this;
}

TernaryTree::~TernaryTree() {
    _destroy(root);
}

/*
 * Balra tömörítve hozzáad a fához egy értéket.
 */
void TernaryTree::addValue(long val){
    auto* n=new TernaryNode(val, nullptr);
    if(root==nullptr){
        root=cursor=n;
        return;
    }
    std::vector<TernaryNode*>prevV;
    std::vector<TernaryNode*>nextV;
    while(true){
        for(size_t i=0;i<prevV.size();i++){
            if(prevV[i]->left==nullptr){
                prevV[i]->left=n;
                n->parent=prevV[i];
                break;
            }else nextV.push_back(prevV[i]->left);

            if(prevV[i]->middle==nullptr){
                prevV[i]->middle=n;
                n->parent=prevV[i];
                break;
            }else nextV.push_back(prevV[i]->middle);

            if(prevV[i]->right==nullptr){
                prevV[i]->right=n;
                n->parent=prevV[i];
                break;
            }else nextV.push_back(prevV[i]->right);
        }
        prevV=nextV;
        nextV.clear();
    }
}

/*
 * Óra járásával ellentétes irányba forgatja a fát.
 * NoRightChildException-t dob, ha nincs jobb gyerek, amit
 * "felforgatna" a metódus.
 */
void TernaryTree::rotateAnticlockwise() noexcept(false) {
    if(cursor==nullptr) throw EmptyException();

    TernaryNode* x=cursor->right;
    if(cursor->right==nullptr) throw NoRightChildException();

    cursor->right=x->left;
    if(x->left!=nullptr) x->left->parent=cursor;

    x->parent=cursor->parent;
    if(cursor->parent==nullptr) root=x;
    else if(cursor==cursor->parent->left) cursor->parent->left=x;
    else cursor->parent->right=x;

    x->left=cursor;
    cursor->parent=x;
}

/*
 * Óra járásával megegyező irányba forgatja a fát.
 * NoLeftChildException-t dob, ha nincs bal gyerek, amit
 * "felforgatna" a metódus
 */
void TernaryTree::rotateClockwise() noexcept(false) {
    if(cursor==nullptr) throw EmptyException();

    TernaryNode* x=cursor->left;
    if(cursor->left==nullptr) throw NoLeftChildException();

    cursor->left=x->right;
    if(x->right!=nullptr) x->right->parent=cursor;

    x->parent=cursor->parent;
    if(cursor->parent==nullptr) root=x;
    else if(cursor==cursor->parent->left) cursor->parent->left=x;
    else cursor->parent->right=x;

    x->right=cursor;
    cursor->parent=x;
}

/*
 * A moveCursor metódus a kurzort a kívánt irányba mozgatja.
 * Ha az adott irányba nem mozgatható a kurzor, akkor a vonatkozó
 * kivételt dobja (NoLeftChildException, NoRightChildException,
 * NoMiddleChildException, NoParentException).
 */
void TernaryTree::moveCursor(CursorDirection dir) noexcept(false){
    if(dir==top){
        if(root==nullptr) throw EmptyException();
        else cursor=root;
    }
    else if(dir==up){
        if(cursor->parent==nullptr) throw NoParentException();
        else cursor=cursor->parent;
    }
    else if(dir==left){
        if(cursor->left==nullptr) throw NoLeftChildException();
        else cursor=cursor->left;
    }
    else if(dir==middle){
        if(cursor->middle==nullptr) throw NoMiddleChildException();
        else cursor=cursor->middle;
    }
    else if(dir==right){
        if(cursor->right==nullptr) throw NoRightChildException();
        else cursor=cursor->right;
    }
}

/*
 * Ez a metódus elvégzi a hármas fán a Knuth-transzformációt.
 */
BinaryTree &TernaryTree::generateBinaryTree() const {
    BinaryTree bt(root);
    return bt;
}

/*
 * A << operátor kinyomtatja a hármas fa tartalmát.
 */
std::ostream &operator<<(std::ostream &os, const TernaryTree &tt) {
    std::ostream o;
    o<<"PreOrder: ";
    treeOrderV.resize(0);
    _preorder();
    for(size_t i=0; i<treeOrderV.size(); i++){
        o<<treeOrderV[i]<<", ";
    }
    return o;
}

/*
 * A metódus dumpolja a tárolt hármas fát a feladatkiírásban leírtak szerint
 */
std::string TernaryTree::dumpTree() const{
    treeOrderV.resize(0);
    _preorder();
    //TODO
}

void TernaryTree::_destroy(TernaryNode *n){
    if(n!=nullptr){
        _destroy(n->left);
        _destroy(n->middle);
        _destroy(n->right);
    }
}

TernaryNode* TernaryTree::_copyOf(TernaryNode* n, TernaryNode* p){
    if(n==nullptr) return nullptr;
    auto* x=new TernaryNode(n->value, p);
    x->left= _copyOf(n->left, x);
    x->middle= _copyOf(n->middle, x);
    x->right= _copyOf(n->right, x);
    return x;
}

void TernaryTree::_preorder(TernaryNode* i) {
    treeOrderV.push_back(i->value);
    if(i->left!=nullptr) _preorder(i->left, o);
    if(i->right!=nullptr) _preorder(i->right, o);
    return o;
}
