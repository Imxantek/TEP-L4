#include "CResult.h"
#include <vector>
#include "CError.h" // potrzeba do eksplicytnej instancjacji

template<typename T, typename E>
CResult<T, E>::CResult(const T& value) {
	this->pc_value = new T(value);
}
template<typename T, typename E>
CResult<T, E>::CResult(E* pcError) {
	this->pc_value = nullptr;
	this->v_errors.push_back(pcError);
}
template<typename T, typename E>
CResult<T, E>::CResult(vector<E*>& vErrors) {
	this->pc_value = nullptr;
	this->v_errors = vErrors;
}
template<typename T, typename E>
CResult<T, E>::CResult(const CResult<T, E>& pcOther) {
	if (pcOther.pc_value != nullptr) {
		this->pc_value = new T(*(pcOther.pc_value));
	}
	else {
		this->pc_value = nullptr;
	}
	this->v_errors = pcOther.v_errors;
}
template<typename T, typename E>
CResult<T, E>::~CResult() {
	if (this->pc_value != nullptr) {
		delete this->pc_value;
	}
	for (E* error : this->v_errors) {
		delete error;
	}
}
template<typename T, typename E>
CResult<T, E> CResult<T, E>::Ok(const T& value) {
	return CResult<T, E>(value);
}
template<typename T, typename E>
CResult<T, E> CResult<T, E>::Fail(E* pcError) {
	return CResult<T, E>(pcError);
}
template<typename T, typename E>
CResult<T, E> CResult<T, E>::Fail(vector<E*>& vErrors) {
	return CResult<T, E>(vErrors);
}
template<typename T, typename E>
CResult<T, E> CResult<T, E>::eDivide(double Dividend, double Divisor) {
	if (Divisor == 0) {
		E* error = new E("Division by zero");
		return CResult<T, E>::Fail(error);
	}
	else {
		T result = static_cast<T>(Dividend / Divisor);
		return CResult<T, E>::Ok(result);
	}
}
template<typename T, typename E>
CResult<T, E>& CResult<T, E>::operator=(const CResult<T, E>& pcOther) {
	if (this != &pcOther) {
		if (this->pc_value != nullptr) {
			delete this->pc_value;
		}
		if (pcOther.pc_value != nullptr) {
			this->pc_value = new T(*(pcOther.pc_value));
		}
		else {
			this->pc_value = nullptr;
		}
		for (E* error : this->v_errors) {
			delete error;
		}
		this->v_errors = pcOther.v_errors;
	}
	return *this;
}
template<typename T, typename E>
bool CResult<T, E>::isSuccess() const {
	return this->pc_value != nullptr;
}
template<typename T, typename E>
T CResult<T, E>::cGetValue() const {
	return *(this->pc_value);
}
template<typename T, typename E>
vector<E*>& CResult<T, E>::vGetErrors() {
	return this->v_errors;
}

// Eksplicytna instancjacja dla u¿ywanego typu, aby unikn¹æ b³êdu LNK2019
template class CResult<double, CError>;