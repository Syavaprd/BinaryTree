#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;
class TreeNode;
class Tree;

class TreeNode
{
        friend class Tree;
    public:
        TreeNode(const string &key, const int &a);
        TreeNode* left;
        TreeNode* right;
        TreeNode* parent;
        int data;
        string key;
};

TreeNode::TreeNode(const string &key, const int &a)
{
        data = a;
        this->key = key;
        left = right = nullptr;
}

class Tree
{
    public:
        Tree()
        {
            root=nullptr;
        }
        ~Tree() { deleteTree(root); }
        vector<TreeNode *> AllNode;
        size_t amountOfKeys = 0;
        int insert(const string &key, const int &x);
        int getMaxDepth(TreeNode *,int);
        int getLeaves();
        void remove(const string &key);
        void removeSubTree(TreeNode* n, const string &key);
        void allData(TreeNode* n);
        TreeNode* max(TreeNode* x);
        TreeNode* min(TreeNode* x);
        TreeNode* findNode(TreeNode* n, const string &key);
        TreeNode* findNext(const string& key);
        bool KeyEx(const string &key, TreeNode* n);
        void fullVect(TreeNode *n);
        TreeNode *root;
        bool a;
        void deleteTree(TreeNode* node);
};

int Tree::insert(const string &key, const int &x)
{
        this->KeyEx(key, this->root);
        if (amountOfKeys && a) {cout << "Trying to insert existing Node, nothing happened" << endl; a = false; return 0;}
        a = false;
        TreeNode* n = new TreeNode(key, x);
        TreeNode* ptr;
        TreeNode* ptr1=nullptr;

        n->parent=n->left=n->right=nullptr;
        ptr=root;
        while(ptr!=nullptr)
        {
                ptr1=ptr;
                if(key < ptr->key)
                        ptr=ptr->left;
                else
                        ptr=ptr->right;
        }
        n->parent=ptr1;
        if(ptr1==nullptr)
                root=n;
        else
        {
                if(key < ptr1->key)
                        ptr1->left=n;
                else
                        ptr1->right=n;
        }
        AllNode.clear();
        fullVect(root);
        amountOfKeys++;
        cout << "Node added!" << endl;
        return 0;
}

int Tree::getMaxDepth(TreeNode* n, int depth)
{
    if (n == nullptr)
    return depth;
    return getMaxDepth(n->left, depth + 1) > getMaxDepth(n->right, depth + 1) ? getMaxDepth(n->left, depth + 1) : getMaxDepth(n->right, depth + 1);
}

int Tree::getLeaves()
{
    int a = 0;
    for (size_t i = 0; i < AllNode.size(); i++) if (AllNode[i]->left == nullptr && AllNode[i]->right == nullptr) a++;
    return a;
}

void Tree::remove(const string &key)
{
        if (!amountOfKeys) {cout << "Empty tree!" << endl; return ;}
        this->KeyEx(key, this->root);
        if (!a) {cout << "Trying to delete nonexisting Node" << endl; a = false; return ;}
        a = false;
        amountOfKeys--;
        TreeNode* vertice = findNode(this->root, key);
        TreeNode* y;
        TreeNode* x;
        if(vertice->left == nullptr || vertice->right == nullptr)
                y = vertice;
        else
                y = findNext(vertice->key);
        if(y->left != nullptr)
                x = y->left;
        else
                x=y->right;
        if(x != nullptr)
                x->parent = y->parent;

        if(y->parent == nullptr)
                root = x;
        else
        {
                if (y == (y->parent)->left) (y->parent)->left=x;
                else (y->parent)->right = x;
        }
        if(y != vertice) vertice->data = y->data;
        AllNode.clear();
        fullVect(root);
        cout << "Deleted!" << endl;
        delete y;
        return;
}

TreeNode* Tree::max(TreeNode* x)
{
        while(x->right != nullptr)
                x = x->right;
        return x;
}

TreeNode* Tree::min(TreeNode* x)
{
        while(x->left != nullptr)
                x = x->left;
        return x;
}

TreeNode* Tree::findNext(const string &key)
{
        TreeNode* x=findNode(root, key);
        TreeNode* y;
        if(x == nullptr)
                return nullptr;
        if(x->right != nullptr)
                return min(x->right);
        y = x->parent;
        while(y != nullptr && x == y->right)

        {
                x = y;
                y = y->parent;
        }

        return y;
}

TreeNode* Tree::findNode(TreeNode* n, const string &key)
{
        if(n==nullptr || key==n->key)
                return n;
        if(key > n->key)
                return findNode(n->right, key);
        else
                return findNode(n->left, key);
}

void Tree::allData(TreeNode* n)
{
        if(n != nullptr)
        {
                allData(n->left);
                cout<< n->key << " " << n->data <<endl;
                allData(n->right);
        }
}

bool Tree::KeyEx(const string &key, TreeNode *n)
{
    if (n != nullptr)
    {
        KeyEx(key, n->left);
        if (n->key == key) {this->a = true; return true;}
        KeyEx(key, n->right);
    }
    return false;
}

void Tree::fullVect(TreeNode* n)
{
    if (n != nullptr)
    {
        fullVect(n->left);
        AllNode.push_back(n);
        fullVect(n->right);
    }
}

void Tree::deleteTree(TreeNode *node)
{
    if (node)
        {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
}

void Tree::deleteSubTree(TreeNode *node, const string &key)
{
    TreeNode* node = findNode(node, key);
    if (node) {
        deleteTree(node);
    }
}

int main()
{
    Tree intTree;
    char command[8];
    int test;
    FILE *ftest;

    cout << "Do you want to read commands from test.txt (0) or from console (1)?" << endl;
    if (fscanf(stdin, "%d", &test)) cout << endl;
    else {cout << "Bad data" << endl; return  -1;}
    test == 0 ? ftest = fopen("test.txt", "r") : ftest = stdin;

    if (test)
    {
        cout << "1) Create new Node" << endl;
        cout << "-1) Delete Node by key" << endl;
        cout << "2) See the Node's parameters" << endl;
        cout << "3) See all the parameters" << endl;
        cout << "4) Look on a data in the Node" << endl;
        cout << "5) Amount of Nodes" << endl;
        cout << "6) Max" << endl;
        cout << "7) Min" << endl;
        cout << "8) Depth" << endl;
        cout << "9) Amount of leaves" << endl;

        cout << "10) To exit the programm" << endl;
        cout << "list) To see the list of all commands" << endl;
        cout << endl;
    }

    while(1)
    {
        if(fscanf(ftest, "%s", command) != EOF) cout << "" << endl;

        else
        {
            cout << "Test ended" << endl;
            intTree.AllNode.clear();
            return 0;
        }

        if (!strcmp(command, "1"))
        {
            char c[64];
            int a;
            cout << "Input key and integer " << endl;
            if (fscanf(ftest, "%s", c) && fscanf(ftest, "%d", &a)) cout << "";
            else {cout << "Bad data" << endl; return  -1;}

            intTree.insert(c, a);
        }

        else if (!strcmp(command, "-1"))
        {
            char c[64];
            cout << "Input the key of the Node you want to delete" << endl;
            if (fscanf(ftest, "%s", c)) cout << "";
            else {cout << "Bad data " << endl; break;}

            intTree.remove(c);
        }

        else if (!strcmp(command, "2"))
        {
            char c[64];
            cout << "Input the key of The node you want" << endl;
            if (fscanf(ftest, "%s", c)) cout << "";
            else {cout << "Bad data " << endl; break;}
            intTree.KeyEx(c, intTree.root);
            if (!intTree.a) {cout << "No Node with this key!"; cout << endl; intTree.a = false;}
            else{intTree.a = false;
            cout << intTree.findNode(intTree.root, c)->key << " " << intTree.findNode(intTree.root, c)->data << endl;}
        }

        else if (!strcmp(command, "3"))
        {
            if (intTree.amountOfKeys == 0) cout << "Empty tree!" << endl;
            else intTree.allData(intTree.root);
        }

        else if (!strcmp(command, "4"))
        {
            char c[64];
            cout << "Input the key" << endl;
            if (fscanf(ftest, "%s", c)) cout << "";
            else {cout << "Bad data " << endl; break;}
            intTree.KeyEx(c, intTree.root);
            if (intTree.amountOfKeys == 0) cout << "Empty tree!" << endl;
            else if (!intTree.a) {cout << "No Node with this key!"; cout << endl; intTree.a = false;}
            else{intTree.a = false;
            cout << intTree.findNode(intTree.root, c)->data << endl;
            }
        }

        else if (!strcmp(command, "5"))
        {
            cout << "The amount of Nodes now is " << intTree.amountOfKeys << endl;
        }

        else if (!strcmp(command, "6"))
        {
            if (intTree.amountOfKeys == 0) cout << "Empty tree!" << endl;
            else cout << intTree.max(intTree.root)->key << " " << intTree.max(intTree.root)->data << endl;
        }

        else if (!strcmp(command, "7"))
        {
            if (intTree.amountOfKeys == 0) cout << "Empty tree!" << endl;
            else cout << intTree.min(intTree.root)->key << " " << intTree.min(intTree.root)->data << endl;
        }

        else if (!strcmp(command, "8"))
        {
            if (intTree.amountOfKeys == 0) cout << "Empty tree!" << endl;
            else cout << "Depth of the tree is " << intTree.getMaxDepth(intTree.root, 0) << endl;
        }

        else if (!strcmp(command, "9"))
        {
            if (intTree.amountOfKeys == 0) cout << "Empty tree!" << endl;
            else cout << "Amount of leaves is " << intTree.getLeaves() << endl;
        }

        else if(!strcmp(command, "10"))
        {
            cout << "Have a nice day!" << endl;
            return  0;
        }

        else if(!strcmp(command, "list"))
        {
            cout << "1) Create new Node" << endl;
            cout << "-1) Delete Node by key" << endl;
            cout << "2) See the Node's parameters" << endl;
            cout << "3) See all the parameters" << endl;
            cout << "4) Look on a data in the Node" << endl;
            cout << "5) Amount of Nodes" << endl;
            cout << "6) Max" << endl;
            cout << "7) Min" << endl;
            cout << "8) Depth" << endl;
            cout << "9) Amount of leaves" << endl;

            cout << "10) To exit the programm" << endl;
            cout << "list) To see the list of all commands" << endl;
        }

        else
        {
            system("clear");
            cout << "'" << command << "' is ";
            cout << "unknown command!" << endl << "list) To see the list of all commands" << endl << endl;
        }
}
    return 0;
}
