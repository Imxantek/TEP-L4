#pragma once
#include <vector>
#include<iostream>
using std::vector;
template<typename T, typename E>
class CResult {
private:
	T* pc_value;
	vector<E*> v_errors;
public:
	CResult(const T& value);
	CResult(E* pcError);
	CResult(vector<E*>& vErrors);
	CResult(const CResult<T, E>& pcOther);
	~CResult();
	static CResult<T, E> cOk(const T& value);
	static CResult<T, E> cFail(E* pcError);
	static CResult<T, E> cFail(vector<E*>& vErrors);

	CResult<T, E>& operator=(const CResult<T, E>& pcOther);
	bool bIsSuccess() const;
	T cGetValue() const;
	vector<E*>& vGetErrors();
	void printErrors() const;
};

template<typename E>
class CResult<void, E> {
private:
	vector<E*> v_errors;
public:
	CResult();
	CResult(E* pcError);
	CResult(vector<E*>& vErrors);
	CResult(const CResult<void, E>& cOther);
	~CResult();
	static CResult<void, E> cOk();
	static CResult<void, E> cFail(E* pcError);
	static CResult<void, E> cFail(vector<E*>& vErrors);
	CResult<void, E>& operator=(const CResult<void, E>& cOther);
	bool bIsSuccess() const;
	vector<E*>& vGetErrors();
	void printErrors() const;
	
};



#include "CResult.tpp"
//