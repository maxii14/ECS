#include "ComponentStorage.h"
#include <iostream>


template <typename T>
ComponentStorage<T>::ComponentStorage(World& world, int storagesCount)
:_world(world)
{
    Resize(storagesCount, storagesCount);
}

template <typename T>
void ComponentStorage<T>::Resize(const int sparseSize, const int dataSize) {
    int oldSparseSize = _sparse.size();
    if (oldSparseSize < sparseSize) {
        _sparse.resize(sparseSize);
        std::fill_n(_sparse.data() + oldSparseSize, sparseSize - oldSparseSize, -1);
    }

    int oldDataSize = _dense.size();
    if (oldDataSize < dataSize) {
        _dense.resize(dataSize);
        _data.resize(dataSize);
        std::fill_n(_dense.data() + oldDataSize, dataSize - oldDataSize, -1);
    }
}

template <typename T>
bool ComponentStorage<T>::Has(const int entityIid) {
    return entityIid < _sparse.size() && _sparse[entityIid] != -1;
}

template <typename T>
T& ComponentStorage<T>::Get(const int entityIid) {
    return _data[_sparse[entityIid]]; // _sparse[entityIid] - индекс в _data, соответственно получаем компонент из _data по entityIid
}

template <typename T>
void ComponentStorage<T>::Add(const int entityIid, const T& value) {
    Resize((entityIid / 64 + 1) * 64, _data.size() == _count + 1 ? _data.size() + 64 : _data.size());
    _data[_count] = value; // кладём в data ссылку на компонент
    _dense[_count] = entityIid; // в _dense в конец кладём entityId
    _sparse[entityIid] = _count; // в sparse в качестве индекса entityId, в качестве значения индекс на _data и _dense
    _count++;
}

template <typename T>
void ComponentStorage<T>::Remove(const int entityIid) {
    int arrayIndex = _sparse[entityIid]; // индекс на _data и _dense (то, что хотим удалить)
    int lastEntityIid = _dense[--_count]; // берём предыдущий entityId
    _data[arrayIndex] = _data[_count]; 
    _dense[arrayIndex] = lastEntityIid;
    _sparse[lastEntityIid] = arrayIndex;
    _sparse[entityIid] = -1;
}

template <typename T>
const std::span<const T> ComponentStorage<T>::All() {
    return std::span(_data.begin(), _count);
}

template <typename T>
const std::span<const int> ComponentStorage<T>::Entities() {
    return std::span(_dense.begin(), _count);
}

template <typename T>
int ComponentStorage<T>::Count() {
    return _count;
}