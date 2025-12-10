#include<iostream>
#include<string>
#include"CNode.h"
CNode::CNode() {
	val = "";
}

CNode::CNode(const CNode& pcOther) {
	val = pcOther.val;
	for (CNode* c : pcOther.children) {
		if (c) {
			children.push_back(c);
		}
		else {
			children.push_back(nullptr);
		}
	}

}

CNode::CNode(const std::string& v) {
	val = v;
}

CNode::~CNode() {
	for (CNode* c : children) {
		delete c;
	}
	children.clear();
}

void CNode::setVal(const std::string& v) {
	val = v;
}

const std::string& CNode::getVal() const {
	return val;
}

void CNode::setChild(int idx, CNode* child) {
	if (idx < children.size()) {
		delete children[idx];
		children[idx] = child;
	}
}

void CNode::addChild(CNode* child) {
	children.push_back(child);
}

CNode* CNode::getChild(int idx) const {
	if (idx < children.size()) return children[idx];
	return nullptr;
}

int CNode::childCount() const {
	return children.size();
}



//