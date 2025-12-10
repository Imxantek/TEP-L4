#ifndef CNODE_H_
#define CNODE_H_
#include<string>
#include<vector>
class CNode {
private:
	std::string val;
	std::vector<CNode*> children;
public:
	CNode();
	CNode(const std::string& v);
	CNode(const CNode& pcOther);
	~CNode();
	void setVal(const std::string& v);
	const std::string& getVal() const;

	void addChild(CNode* child);
	void setChild(int idx, CNode* child);
	CNode* getChild(int idx) const;
	int childCount() const;
};

#endif //CNODE_H_
//