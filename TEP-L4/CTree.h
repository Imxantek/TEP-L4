#ifndef CTREE_H_
#define CTREE_H_
#include "CNode.h"
#include<queue>
#include<map>
#include<vector>
class CTree {
private:
	CNode* root;
	std::map<std::string, int> dict;



public:
	CTree();
	CTree(const CTree& pcOther);
	~CTree();

	CTree& operator=(const CTree& pcOther);
	CTree operator+(const CTree& pcOther) const;

	std::string toString() const;
	std::string toString(CNode* node) const;

	std::string getToken(std::string& exp, int& pos);
	CNode* parse(std::string& exp, int& pos);
	int arityOf(const std::string& token) const;
	CNode* cloneSubtree(CNode* node) const;
	CNode* deepestLeft(CNode* node) const;

	void enter(std::string& exp);
	void join(std::string& exp);
	void print() const;
	void print(CNode* node) const;
	void scanDict(CNode* node);
	bool containsVars();
	bool isNumber(const std::string& s);
	void vars();
	void comp(std::vector<int> vec);
	void runSurvey(CNode* node, std::vector<int>* vec);
	double calculateValue(CNode* node) const;

	CNode* getRoot() const;
};
#endif
//