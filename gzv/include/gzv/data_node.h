/**
 * @author      : Nikita Guzhva (nik_finger@mail.ru)
 * @file        : data_node
 * @created     : Sunday Sep 26, 2021 18:51:08 MSK
 */

#ifndef DATA_NODE_H
#define DATA_NODE_H

#include <memory>


template<typename T>
class DataNode {
public:
  DataNode(T *data, DataNode *next)
    : m_data(data), m_next(next) {}

private:
  std::shared_ptr<T> m_data;
  std::shared_ptr<DataNode> m_next;
};


#endif /* end of include guard DATA_NODE_H */

