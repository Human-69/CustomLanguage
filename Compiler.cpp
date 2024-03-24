#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <istream>
#include <sstream>
#include <cstring>

bool CompareStringToArr(std::string &target, std::vector<std::string> &Strings)
{
    for (const auto & String : Strings)
    {
        if (target == String)
        {
            return true;
        }
    }
    return false;
}
std::vector<int> findAll(std::string sample, char Target)
{
    std::vector<int> characterLocations;
    for(int i =0; i < sample.size(); i++)
        if(sample[i] == Target)
            characterLocations.push_back(i);

    return characterLocations;
}
std::string removeWhitespace(std::string string)
{
    for (int i = 0;i<=string.length();i++)
    {
        if (string[i] == ' ')
        {
            string.erase(i, 1);
        }
    }
    return string;
}
typedef enum
{
    EQ,
    LT, GT, E, GTE, LTE, NE,
    ADD, SUB, MUL, DIV, POW, SQRT,
    AND, OR, XOR, NOT, NAND, NOR, XNOR,
    IF, ELSE, WHILE, FOR, RETURN,
    VALUE,
    DECLARATION
} nodeType;
std::vector<std::string> VariableTypes = {"int", "float", "string", "bool"};
class Node
{
public:
    Node *A;
    Node *B;
    nodeType type;
    std::vector<int> value;
    std::string Name;
    bool isString;
    std::string Variabletype;
    Node(nodeType Type, Node *A, Node *B, std::vector<int> Value, std::string ValueName, bool IsString=false, std::string variableType="");
    std::string ValueToStr()
    {
        if(isString) {
            std::string NewString;
            for (auto &character: this->A->value) {
                NewString += static_cast<char>(character);
            }
            return NewString;
        }
        else if(this->type!=EQ and this->type!=VALUE)
        {
            std::cout<<"This node is not an Value or Assigment node";
            return "";
        }
        else
        {
            std::cout<<"This node is not holding a string value";
            return "";
        }
    }
};
std::vector<Node*> Nodes;
Node::Node(nodeType Type, Node *A, Node *B, std::vector<int> Value, std::string ValueName, bool IsString, std::string variableType)
{
    this->type = Type;
    this->A = A;
    this->B = B;
    this->value = std::move(Value);
    if (variableType == "string")
    {
        this->Variabletype="std::string";
    }
    else
    {
        this->Variabletype=std::move(variableType);
    }

    if (Type!=VALUE && !Value.empty())
    {
        std::cout<<"Value should only be used with the node type VALUE, if you want assign your node a value assign Node *A to a value node";
    }
    this->Name = std::move(ValueName);
    this->isString=IsString;
    Nodes.push_back(this);
}
Node CreateArithmeticNodes(std::vector<size_t> ALL, std::vector<size_t> Exponents, std::vector<size_t> MUL, std::vector<size_t> DIV, std::vector<size_t>ADD, std::vector<size_t>SUB)
{
    int last, next;
    for(size_t i=0;i<ALL.size();i++)
    {
        last=ALL[i==0?0:i-1];
        next=ALL[i+1==ALL.size()?i:i+1];
        for(size_t i;i<Exponents.size();i++)
        {
            //5**5/12**9
            
        }
    }
}
void CleanUp()
{
    for(Node* & node : Nodes)
    {
        delete node;
    }
}
std::vector<std::string> Keywords = {"if, else, while, for, return"};
int main()
{
    std::ifstream In("Psource/input.p");
    std::ofstream Out("Psource/Out.cpp");
    std::string CurrLine;
    if(In.is_open() and Out.is_open())
    {
        Out << "#include <iostream>\n"
               "\n"
               "int main(){\n";
        std::string CurrToken;//Current word(token)
        std::string next;
        while(std::getline(In, CurrLine)){
            bool IsString = false;
            std::istringstream CurrLineStream(CurrLine);
            std::cout<<CurrLine<<"\n";
            while (CurrLineStream>>CurrToken) {
                CurrLineStream >> next;
                /*
                Logic goes here
                 */
                std::cout << "Current Word: " << CurrToken << std::endl;
                std::cout << "Next Word: " << next << "\n";
                if (CompareStringToArr(CurrToken, VariableTypes)) {
                    std::cout << "Name: " << next << std::endl;
                    Node *node = new Node(DECLARATION, nullptr, nullptr, {0}, next, false, CurrToken);
                } else if (CompareStringToArr(CurrToken, Keywords)) {
                    /*To do*/
                } else if (CurrToken[CurrToken.length()] == '=' or
                          (sscanf(CurrToken.c_str(), "%[^=]", new char) == 1 and CurrLine.find('=')!=std::string::npos) or
                          next[0] == '=') {
                    bool Isvalid = false;
                    std::cout << "it is a definition\n";
                    std::vector<int> quotationMarkIndices = findAll(CurrLine, '"');
                    if (CurrToken[CurrToken.length()] == '=' or next[0] == '=') {

                    } else if (sscanf(CurrToken.c_str(), "%[^=]", new char) == 1) {
                        std::vector<int> IntegerString;
                        size_t equals;
                        equals = CurrLine.find('=');
                        next.clear();
                        /*Determine if string is valid*/
                        for(size_t i=0;i<CurrToken.length();i++)
                        {
                            if(CurrToken[i]=='"')
                            {
                                IsString=!IsString;//toggle
                            }
                            else if (!IsString && CurrToken[i]=='='){Isvalid=true;}
                            //sdds="world
                            //Hel=lo"
                        }
                        next=CurrLine.substr(equals+1);
                        CurrToken=CurrLine.substr(0, equals);
                        std::cout << "The input string is: " << next << "\n";
                        std::cout << "Next[0] is: " << next[0] << "\n";
                        if (next[0] == '"') {
                            if(Isvalid) {
                                for (int i = 1; i < next.length()-1; i++) {
                                    IntegerString.push_back((int) next[i]);
                                    std::cout << "Integer representation of: " << next[i] << " is " << (int) next[i]
                                              << "\n";
                                }
                                /*Create Node here*/
                                Node *node = new Node(VALUE, nullptr, nullptr, IntegerString, "", true);
                                Node *node1 = new Node(EQ, node, nullptr, {}, CurrToken, true);
                            }
                            else{std::cout<<"Input invalid\n";}

                        } else
                        {
                            std::vector<size_t> Exponents, MUL, DIV, ADD, SUB;
                            bool skip=false;
                            for(size_t i=0;i<next.length();i++)
                            {
                                if(!skip) {
                                    if (next[i] == '*') {
                                        if (next[i + 1] == '*') {
                                            Exponents.push_back(i);
                                            skip==true;
                                        } else {
                                            MUL.push_back(i);
                                        }
                                    }
                                    if (next[i] == '/') {
                                        DIV.push_back(i);
                                    }
                                    if (next[i] == '+' || next[i] == '-') {
                                        if (next[i] == '+') { ADD.push_back(i); }
                                        else { SUB.push_back(i); }
                                    }
                                }
                                else{skip=false;}
                            }
                        }
                    }
                }
                CurrToken.clear();
                next.clear();
            }
            CurrLine.clear();
        }
        for(auto & node:Nodes)
        {
            if(node->type==EQ)
            {
                if(node->isString)
                {
                    Out << node->Name << "=\"" << node->ValueToStr()<<"\";\n";
                }
            }
            else if(node->type == DECLARATION)
            {
                Out<<node->Variabletype<<" "<<node->Name<<";\n";
            }
        }
        Out << "return 0;\n"
               "}\n";
        CleanUp();
    }
}
