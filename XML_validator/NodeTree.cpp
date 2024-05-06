#include <iostream>
#include <vector>
#include "NodeTree.h"

using namespace std;

NodeTree::NodeTree(string key, string value)
{
    this->key = key;
    this->value = value;
}
void NodeTree::addChild(NodeTree *node)
{
    children.push_back(node);
}

void NodeTree::setElement(string element)
{
    this->key = element;
}
void NodeTree::setValue(string value)
{
    this->value= value;
}
string NodeTree::getValue()
{
    return this->value;
}
string NodeTree:: getKey()
{
    return this->key;
}
string NodeTree::getData()
{
    string out = '"'+key+'"'+":"+ '"'+value+'"';
    return out;
}

std::vector<NodeTree*> NodeTree::getChildren()
{
    return children;
}

bool NodeTree::hasMultipleChildrenWithSameKey()
{
    int countt = 0;
    string key;
    if (children.size()!=0) key = children[0]->getKey();
    for ( NodeTree* child : children) {
      if (child->getKey() == key) {
        ++countt;
      }
    }
      if (countt > 1) {
        for ( NodeTree* child : children) {
      if (child->getKey() == key) {
        isRepeated=true;
      }
    }
        return true;
      }
    return false;
}



