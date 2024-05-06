#include "TreetoJSON.h"
#include "NodeTree.h"
#include <iostream>
#include <stack>
#include <queue>

using namespace std;

void TreetoJSON::dfs(NodeTree *node){
    cout << node->getKey() << " " ; // print the current node's key and value
    if (node->getValue() != "") cout<< ": " << node->getValue().substr(1);
    cout << "\n";
    for (NodeTree *child : node->getChildren()) {
        dfs(child); // recursively call dfs on each child
    }
}

bool TreetoJSON::isLeaf(NodeTree *node){
    return node->getChildren().empty();
}

void TreetoJSON::treeToJson(NodeTree *node){
    int comma=0;
    int grandcomma=0;
    if (!isLeaf(node))
    {
        json+= "{\"" + node->getKey() + "\" : ";
        if (node->hasMultipleChildrenWithSameKey())
        {
            vector<NodeTree*>children = node->getChildren();
            json += "{\"" + children[0] ->getKey()+ "\": "; // get a copy of the key
            comma = children.size()-1;
                json += "[";
            for (NodeTree *child : children)
            {
                if (child->hasMultipleChildrenWithSameKey()) treeToJson(child);
                json += "{";
                vector<NodeTree*> grandchildren = child->getChildren();
                int grandcomma=grandchildren.size()-1;
                if (grandchildren.size() ==0) cout<< child->getKey() << " no children ";
                for (NodeTree *grandchild : grandchildren)
                {
                    if (grandchild->hasMultipleChildrenWithSameKey()) treeToJson(grandchild);
                    json += "\""+ grandchild->getKey() +"\":\"";
                    if(grandchild->getValue()!= "")
                    json +=grandchild->getValue().substr(1)+ "\"";
                    if (grandcomma>0){
                        json +=",";
                        grandcomma--;
                    }
                }
            json+="}";
                if (comma >0){
                    json+=",";
                    comma--;
                }
            }
                json +="]}";
        }

    }

    if (!node->hasMultipleChildrenWithSameKey()){

        for (NodeTree *child : node->getChildren())
        {
            treeToJson(child); // recursively call dfs on each child
            json+="}";
        }
    }
    else
    json+="}";
    this ->json = json;
}

string TreetoJSON::getJSON(){
    return this->json;
}


NodeTree TreetoJSON::convertxml(string xml)
{
    stack<NodeTree*> tags;
    string element="";
    string value="";
    NodeTree root("");
    int currentChar=0;
    while(xml[currentChar]!='\0')
    {
        if(xml[currentChar] == '<')
        {
            currentChar++;
            // Case 1: Not Closing Tag
            if(xml[currentChar]!='/')
            {

                while(xml[currentChar] != '>')
                {

                    element+=xml[currentChar];
                    currentChar++;

                } // element is tag

                if (tags.empty())
                {
                    root.setElement(element);    //created root
                    tags.push(&root);
                }
                else
                {
                    NodeTree* parentNode = tags.top();
                    NodeTree* node = new NodeTree(element);
                    parentNode->addChild(node);
                    tags.push(node);
                }
                if(xml[currentChar+1]!='<')
                {
                    while(xml[currentChar]!='<')
                    {
                        value += xml[currentChar];
                        currentChar++;
                    }
                    tags.top()->setValue(value);
                    //cout<< value;
                    value="";
                    tags.pop();
                }
                element=""; //reset element
            }
            else if(xml[currentChar] =='/')
            {
                tags.pop(); // remove tag from stack
            }
        }
        //cout << xml[currentChar];
        currentChar++;
    }
    //NodeTree* ptr = root.getChildren()[0];
    return root;
}
