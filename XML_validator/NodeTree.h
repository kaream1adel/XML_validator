#ifndef NODETREE_H
#define NODETREE_H

#include <string>
#include <vector>


class NodeTree {
  private:
    std::string key;
    std::string value;
  public:
    bool isRepeated=false;
    std::vector<NodeTree*> children;
    NodeTree(std::string key, std::string value = "");
    void addChild(NodeTree *node);
    void setElement(std::string element);
    std::string getValue() ;
    std::string getKey() ;
    void setValue(std::string value);
    std::string getData() ;
    std::vector<NodeTree*> getChildren() ;
    bool hasMultipleChildrenWithSameKey() ;
};

#endif
