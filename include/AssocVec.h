/**************************************************************************************************
* File: AssocVec.h
* Description:
* Author: Malcolm Hall
* Date: 6/9/20
* Version: 1
*
**************************************************************************************************/
#ifndef XMLBUILDER_ASSOCVEC_H
#define XMLBUILDER_ASSOCVEC_H

/**************************************************************************************************
*       INCLUDES AND DECLARATIONS
**************************************************************************************************/
#include <string>
#include <map>
#include <vector>

namespace CppXml {

/******************************************************************************
 * @brief
 * @tparam T
 */
    template<class T>
    class AssocVec {
    public:
        AssocVec();

        ~AssocVec();

        /* Overloaded [] operators so objects can be retrieved by key or index   */
        T operator[](const std::string &key);

        T operator[](int idx);

        void push(std::string key, T object);

        void pop();

        ssize_t size();

        bool empty();

        int count(const std::string &key);

        void erase(const std::string &key);

        void erase(int idx);

    protected:
        /* Map to lookup vector index by key    */
        std::map<std::string, int> _idxKeyMap;

        /* Map to lookup map key by vector index. This uses a vector for simplicity, however.*/
        std::vector<std::string> _keyIdxMap;

        /* Vector to store the objects being held by this class */
        std::vector<T> _objectStore;
    };


/******************************************************************************
 * AssocVec
 *
 * @brief
 * @tparam T
 */
    template<class T>
    AssocVec<T>::AssocVec() {

    }


/******************************************************************************
 * ~AssocVec
 *
 * @brief
 * @tparam T
 */
    template<class T>
    AssocVec<T>::~AssocVec() {

    }


/******************************************************************************
 * []
 *
 * @brief
 * @tparam T
 * @param key
 * @return
 */
    template<class T>
    T AssocVec<T>::operator[](const std::string &key) {
        return _objectStore[_idxKeyMap[key]];
    }


/******************************************************************************
 * []
 *
 * @brief
 * @tparam T
 * @param idx
 * @return
 */
    template<class T>
    T AssocVec<T>::operator[](int idx) {
        return _objectStore[idx];
    }


/******************************************************************************
 * push
 *
 * @brief
 * @tparam T
 * @param key
 * @param object
 */
    template<class T>
    void AssocVec<T>::push(std::string key, T object) {
        _objectStore.push_back(object);
        _keyIdxMap.push_back(key);
        _idxKeyMap.insert(_idxKeyMap.begin(), std::pair<std::string, int>(key, _objectStore.size() - 1));
    }


/******************************************************************************
 * pop
 *
 * @brief
 * @tparam T
 */
    template<class T>
    void AssocVec<T>::pop() {
        int idx = _objectStore.size() - 1;
        //std::string key = _keyIdxMap[idx];
    }


/******************************************************************************
 * size
 *
 * @brief
 * @tparam T
 * @return
 */
    template<class T>
    ssize_t AssocVec<T>::size() {
        return _objectStore.size();
    }


/******************************************************************************
 * empty
 *
 * @brief
 * @tparam T
 * @return
 */
    template<class T>
    bool AssocVec<T>::empty() {
        return size() == 0;
    }


/******************************************************************************
 * count
 *
 * @brief
 * @tparam T
 * @param key
 * @return
 */
    template<class T>
    int AssocVec<T>::count(const std::string &key) {
        return _idxKeyMap.count(key);
    }


/******************************************************************************
 * erase
 *
 * @brief
 * @tparam T
 * @param key
 */
    template<class T>
    void AssocVec<T>::erase(const std::string &key) {
        int vecIdx = _idxKeyMap[key];
        _objectStore.erase(vecIdx);

        for (int i = vecIdx; i < _objectStore.size(); i++) {
            _idxKeyMap[_keyIdxMap[i]]--;
        }
    }


/******************************************************************************
 * erase
 * 
 * @brief
 * @tparam T
 * @param idx
 */
    template<class T>
    void AssocVec<T>::erase(int idx) {

    }
}

#endif //XMLBUILDER_ASSOCVEC_H
/**************************************************************************************************
*       END OF FILE
**************************************************************************************************/