#include<iostream>
#include<string>
#include<queue>
#include<vector>
#include<cmath>
#include"CTree.h"
CTree::CTree() {
    root = nullptr;
}

CTree::CTree(const CTree& pcOther) {
    root = cloneSubtree(pcOther.root);
}

CTree::~CTree() {
    delete root;
}

CTree& CTree::operator=(const CTree& pcOther) {
    if (this != &pcOther) {
        delete root;
        root = cloneSubtree(pcOther.root);
        dict = pcOther.dict;
    }
    return *this;
}

CTree CTree::operator+(const CTree& pcOther) const {
    CTree result;
    result.root = cloneSubtree(this->root);

    if (result.root == nullptr) {
        result.root = cloneSubtree(pcOther.root);
        return result;
    }
    CNode* leafToReplace = deepestLeft(result.root);

    if (leafToReplace == nullptr) {
        delete result.root;
        result.root = cloneSubtree(pcOther.root);
    }
    else {
        CNode* otherRoot = pcOther.root;
        if (otherRoot) {
            leafToReplace->setVal(otherRoot->getVal());
            for (int i = 0; i < otherRoot->childCount(); i++) {
                leafToReplace->addChild(cloneSubtree(otherRoot->getChild(i)));
            }
        }
    }
    result.scanDict(result.root);
    return result;
}


int CTree::arityOf(const std::string& token) const {
    if (token == "+" || token == "-" || token == "*" || token == "/") return 2;
    if (token == "sin" || token == "cos") return 1;
    return 0;
}
void CTree::scanDict(CNode* node) {
    if (!node) {
        return;
    }
    int ar = arityOf(node->getVal());
    if (ar == 0) {
        dict[node->getVal()] = -1;
    }
    for (int i = 0; i < node->childCount(); i++) {
        scanDict(node->getChild(i));
    }
}

std::string CTree::getToken(std::string& exp, int& pos) {
    while (pos < exp.length() && exp[pos] == ' ') {
        pos++;
    }
    if (pos >= exp.length()) {
        return "";
    }
    std::string token = "";
    while (pos < exp.length() && exp[pos] != ' ') {
        token = token + exp[pos];
        pos++;
    }
    return token;
}

CNode* CTree::parse(std::string& exp, int& pos) {
    std::string token = getToken(exp, pos);
    std::cout << token << " ";
    int ar = arityOf(token);
    if (ar == 0) {
        dict[token] = -1;
        return new CNode(token);
    }
    else if (ar > 0) {
        CNode* node = new CNode(token);
        for (int i = 0; i < ar; i++) {
            CNode* child = parse(exp, pos);
            node->addChild(child);
        }
        return node;
    }
    return nullptr;
}


void CTree::enter(std::string& exp) {
    dict.clear();
    std::string fixed;
    int requiredOperands = 1;
    int operands = 0;
    int pos = 0;
    while (pos < exp.length()) {
        std::string token = getToken(exp, pos);
        int ar = arityOf(token);
        if (ar == 0) {
            operands++;
        }
        else if (ar > 0) {
            requiredOperands += (ar - 1);
        }
        fixed += (token + " ");
    }
    if (operands < requiredOperands) {
        throw std::invalid_argument("Not enough operands");
    }
    else if (operands > requiredOperands) {
		throw std::invalid_argument("Too many operands");
    }
    std::cout << "Processed expression:\n ";
    pos = 0;
    root = parse(fixed, pos);
    std::cout << std::endl;
}



void CTree::join(std::string& exp) {
    CTree newTree;
    newTree.enter(exp);
    *this = *this + newTree;
    std::cout << "New tree:\n";
    print();
}

CNode* CTree::cloneSubtree(CNode* node) const {
    if (!node) return nullptr;
    CNode* n = new CNode(node->getVal());
    for (int i = 0; i < node->childCount(); i++) {
        n->addChild(cloneSubtree(node->getChild(i)));
    }
    return n;
}

CNode* CTree::deepestLeft(CNode* node) const {
    if (!node) return nullptr;
    if (node->childCount() == 0) return node;
    return deepestLeft(node->getChild(0));
}

bool CTree::isNumber(const std::string& s) {
    if (s.empty()) return false;
    int start = 0;
    if (s[0] == '-') start = 1;
    for (int i = start; i < s.length(); ++i) {
        if (!isdigit(s[i])) return false;
    }
    return true;
}

void CTree::vars() {
    dict.clear();
    scanDict(root);

    // SprawdŸ czy istnieje przynajmniej jedna zmienna (nie-numeryczny klucz)
    bool hasVariable = false;
    for (const auto& kv : dict) {
        if (!isNumber(kv.first)) {
            hasVariable = true;
            break;
        }
    }

    if (!hasVariable) {
        throw std::exception("No variables in this equation.");
    }

    std::cout << "Variables used in this equation:\n";
    for (std::map<std::string, int>::iterator it = dict.begin(); it != dict.end(); ++it) {
        if (!isNumber(it->first)) {
            std::cout << it->first << " ";
        }
    }
    std::cout << std::endl;
}

void CTree::runSurvey(CNode* node, std::vector<int>* vec) {
    if (node == nullptr) {
        return;
    }
    std::string key = node->getVal();
    int ar = arityOf(key);
    if (ar == 0) {
        bool isVariable = false;
        for (int i = 0; i < key.size(); i++) {
            if ((key[i] < '0' || key[i]>'9') && key[i] != '-') {
                isVariable = true;
                break;
            }
        }
        if (isVariable) {
            if (vec->size() != 0) {
                dict[key] = vec->front();
                vec->erase(vec->begin());
            }
            else {
                throw std::exception("Insufficient variable assignments provided");
            }
        }
        else {
            dict[key] = std::stoi(key);
        }
    }
    for (int i = 0; i < node->childCount(); i++) {
        runSurvey(node->getChild(i), vec);
    }
}

void CTree::comp(std::vector<int> vec) {
    dict.clear();
    runSurvey(root, &vec);
    if (vec.size() != 0) {
		throw std::exception("Too many variable assignments provided");
        return;
    }
    try {
        std::cout << "Value of entered equation:\n" << calculateValue(root) << std::endl;
    }
    catch (std::exception) {
        throw std::exception("Division by zero");
    }
}

double CTree::calculateValue(CNode* node) const {
    if (node == nullptr) {
        return 0;
    }
    std::string token = node->getVal();
    int ar = arityOf(token);
    if (ar > 0) {
        if (token == "+") {
            double a = calculateValue(node->getChild(0));
            double b = calculateValue(node->getChild(1));
            return a + b;
        }
        if (token == "-") {
            double a = calculateValue(node->getChild(0));
            double b = calculateValue(node->getChild(1));
            return a - b;
        }
        if (token == "*") {
            double a = calculateValue(node->getChild(0));
            double b = calculateValue(node->getChild(1));
            return a * b;
        }
        if (token == "/") {
            double a = calculateValue(node->getChild(0));
            double b = calculateValue(node->getChild(1));
            if (b == 0) {
				throw std::exception("Division by zero");
                return 0;
            }
            else {
                return a / b;
            }
        }
        if (node->getVal() == "sin") {
            double a = calculateValue(node->getChild(0));
            return sin(a);
        }
        if (node->getVal() == "cos") {
            double a = calculateValue(node->getChild(0));
            return cos(a);
        }
    }
    else {
        return dict.at(node->getVal());
    }
    return 0;
}

CNode* CTree::getRoot() const {
    return root;
}

void CTree::print() const {
    if(root== nullptr) {
		throw std::exception("Tree is empty");
        return;
	}
    print(root);
}
void CTree::print(CNode* node) const {
    if (!node) {
        return;
    }
    std::cout << node->getVal() << " ";
    for (int i = 0; i < node->childCount(); i++) {
        print(node->getChild(i));
    }

}

std::string CTree::toString() const {
    return toString(root);
}
std::string CTree::toString(CNode* node) const {
    if (!node) {
        return "";
    }
    std::string result = node->getVal() + " ";
    for (int i = 0; i < node->childCount(); i++) {
        result += toString(node->getChild(i));
    }
    return result;
}

bool CTree::containsVars() {
    for (std::map<std::string, int>::iterator it = dict.begin(); it != dict.end(); ++it) {
        std::string key = it->first;
        for (int i = 0; i < key.length(); i++) {
            if ((key[i] < '0' || key[i] > '9') && key[i] != '-') {
                return true;
            }
        }
    }
    return false;
}
//