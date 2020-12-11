#ifndef MANAGER_H
#define MANAGER_H

#include <inttypes.h>
#include <vector>
#include "defines.h"

template<class T>
class Manager
{
private:
    std::vector<T*> data_;
    uint16_t currentIdx_ = 0;
public:
    std::vector<T*>* getVectorOfData();
    std::size_t getSize() const;
    void add(T* element);
    void setCurrent(uint16_t id);
    T* getCurrent() const;
    T* operator()() const;
};

// Template implementation
template<typename T>
ALWAYS_INLINE std::vector<T*>* Manager<T>::getVectorOfData(){
    return &data_;
}

template<typename T>
ALWAYS_INLINE std::size_t Manager<T>::getSize() const {
    return data_.size();
}

template<typename T>
void Manager<T>::add(T* element) {
    data_.push_back(element);
}

template<typename T>
void Manager<T>::setCurrent(uint16_t id) {
    if(!data_.size()) {
        return;
    }
    currentIdx_ = id >= data_.size() ? data_.size() - 1 : id;
}

template<typename T>
ALWAYS_INLINE T* Manager<T>::getCurrent() const {
    return data_[currentIdx_];
}

template<typename T>
ALWAYS_INLINE T* Manager<T>::operator()() const {
    return this->getCurrent();
}

#endif // MANAGER_H
