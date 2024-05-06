#ifndef TREETOJSON_H
#define TREETOJSON_H

#include "NodeTree.h"
#include <string>

class TreetoJSON
{
    private:
        std::string json="";

    public:
        void dfs(NodeTree *node);
        void treeToJson(NodeTree *node);
        bool isLeaf(NodeTree *node);
        std::string getJSON();
        NodeTree convertxml(std::string xml);
};

#endif // TREETOJSON_H
