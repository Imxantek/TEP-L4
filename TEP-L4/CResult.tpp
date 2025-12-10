template<typename T, typename E>
CResult<T, E>::CResult(const T& cValue){
    pc_value = new T(cValue);
}

template<typename T, typename E>
CResult<T, E>::CResult(E* pcError){
    pc_value = nullptr;
    v_errors.push_back(pcError);
}

template<typename T, typename E>
CResult<T, E>::CResult(std::vector<E*>& vErrors){
    pc_value = nullptr;

    for (int i = 0; i < vErrors.size(); ++i)
        v_errors.push_back(vErrors[i]);
}

template<typename T, typename E>
CResult<T, E>::CResult(const CResult<T, E>& other){
    if (other.pc_value != nullptr)
        pc_value = new T(*other.pc_value);
    else
        pc_value = nullptr;

   
    for (int i = 0; i < other.v_errors.size(); ++i)
        v_errors.push_back(new E(*other.v_errors[i]));
}

template<typename T, typename E>
CResult<T, E>::~CResult(){
    if (pc_value != nullptr)
        delete pc_value;

    for (int i = 0; i < v_errors.size(); ++i)
        delete v_errors[i];
}

template<typename T, typename E>
CResult<T, E> CResult<T, E>::cOk(const T& cValue){
    return CResult<T, E>(cValue);
}

template<typename T, typename E>
CResult<T, E> CResult<T, E>::cFail(E* pcError){
    return CResult<T, E>(pcError);
}

template<typename T, typename E>
CResult<T, E> CResult<T, E>::cFail(std::vector<E*>& vErrors){
    return CResult<T, E>(vErrors);
}

template<typename T, typename E>
CResult<T, E>& CResult<T, E>::operator=(const CResult<T, E>& other){
    if (this != &other)
    {
        if (pc_value != nullptr)
            delete pc_value;

        for (size_t i = 0; i < v_errors.size(); ++i)
            delete v_errors[i];

        v_errors.clear();

        if (other.pc_value != nullptr)
            pc_value = new T(*other.pc_value);
        else
            pc_value = nullptr;

        for (int i = 0; i < other.v_errors.size(); ++i)
            v_errors.push_back(new E(*other.v_errors[i]));
    }

    return *this;
}

template<typename T, typename E>
bool CResult<T, E>::bIsSuccess() const{
    return pc_value != nullptr;
}

template<typename T, typename E>
T CResult<T, E>::cGetValue() const{
    return *pc_value; 
}

template<typename T, typename E>
std::vector<E*>& CResult<T, E>::vGetErrors(){
    return v_errors;
}

template<typename T, typename E>
void CResult<T, E>::printErrors() const {
    for (size_t i = 0; i < v_errors.size(); ++i) {
        std::cout << v_errors[i]->strGetMessage() << std::endl;
    }
}


// <void, E>

template<typename E>
CResult<void, E>::CResult() {
    // No errors, so nothing to do here
}

template<typename E>
CResult<void, E>::CResult(E* pcError) {
    v_errors.push_back(pcError);
}

template<typename E>
CResult<void, E>::CResult(std::vector<E*>& vErrors) {
    for (int i = 0; i < vErrors.size(); ++i)
        v_errors.push_back(vErrors[i]);
}

template<typename E>
CResult<void, E>::CResult(const CResult<void, E>& other) {
    for (int i = 0; i < other.v_errors.size(); ++i)
        v_errors.push_back(new E(*other.v_errors[i]));
}

template<typename E>
CResult<void, E>::~CResult() {
    for (int i = 0; i < v_errors.size(); ++i)
        delete v_errors[i];
}

template<typename E>
CResult<void, E> CResult<void, E>::cOk() {
    return CResult<void, E>();
}

template<typename E>
CResult<void, E> CResult<void, E>::cFail(E* pcError) {
    return CResult<void, E>(pcError);
}

template<typename E>
CResult<void, E> CResult<void, E>::cFail(std::vector<E*>& vErrors) {
    return CResult<void, E>(vErrors);
}

template<typename E>
CResult<void, E>& CResult<void, E>::operator=(const CResult<void, E>& other) {
    if (this != &other) {
        for (int i = 0; i < v_errors.size(); ++i)
            delete v_errors[i];
        v_errors.clear();
        for (int i = 0; i < other.v_errors.size(); ++i)
            v_errors.push_back(new E(*other.v_errors[i]));
    }
    return *this;
}

template<typename E>
bool CResult<void, E>::bIsSuccess() const {
    return v_errors.empty();
}

template<typename E>
std::vector<E*>& CResult<void, E>::vGetErrors() {
    return v_errors;
}   

template<typename E>
void CResult<void, E>::printErrors() const {
    std::cout<<"\n";
    for (int i = 0; i < v_errors.size(); ++i) {
        std::cout << v_errors[i]->strGetMessage() << std::endl;
    }
}
//