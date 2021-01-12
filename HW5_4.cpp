#ifdef __GNUC__
#include <bits/stdc++.h>
#endif // __GNUC__
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <string>
#include <queue>
#include <vector>
#include <unordered_map>
#endif // _MSC_VER

// A Tree node
struct Node
{
    char ch;
    int freq;
    Node *left, *right;
    Node(const char c = '\0', const int f = 0, Node *l = nullptr, Node *r = nullptr)
        : ch(c), freq(f), left(l), right(r) {}
    bool is_leaf() const { return !left && !right; }
}; // struct Node

class HuffmanTree
{
private:
    std::unordered_map<char, std::string> huffmanCode;
    std::string original_str;
    std::string code_str;
    std::string out_str;
    Node *root = nullptr;
    // Comparison object to be used to order the heap; rule: highest priority item has lowest frequency
    struct comp
    {
        bool operator()(Node *left, Node *right) const { return left->freq > right->freq; }
    };
    // traverse the Huffman Tree and store Huffman Codes in a map.
    void encode(Node *root, const std::string &str)
    {
        if (!root)
        {
            return;
        }
        // found a leaf node
        if (root->is_leaf())
        {
            huffmanCode[root->ch] = str;
        }
        encode(root->left, str + "0");
        encode(root->right, str + "1");
    }
    // traverse the Huffman Tree and decode the encoded string
    void decode(Node *root, int &index)
    {
        if (!root)
        {
            return;
        }
        // found a leaf node
        if (root->is_leaf())
        {
            out_str += root->ch;
            return;
        }
        index++;
        decode((code_str[index] == '0' ? root->left : root->right), index);
    }
    // Builds Huffman Tree and decode code_str
    void buildHuffmanTree()
    {
        if (original_str.empty())
        {
            std::cerr << "The string is not found. Please try again. \n";
            exit(-1);
        }
        // count frequency of appearance of each character and store it in a map
        std::unordered_map<char, int> freq;
        for (char ch : original_str)
        {
            freq[ch]++;
        }

        // Create a priority queue to store live nodes of Huffman tree
        std::priority_queue<Node *, std::vector<Node *>, comp> pq;

        // Create a leaf node for each character and add it to the priority queue.
        for (auto &pair : freq)
        {
            Node *new_node = new Node(pair.first, pair.second);
            pq.push(new_node);
        }

        // do till there is more than one node in the queue
        while (pq.size() != 1)
        {
            // Remove the two nodes of highest priority (lowest frequency) from the queue
            Node *left = pq.top();
            pq.pop();
            Node *right = pq.top();
            pq.pop();

            // Create a new internal node with these two nodes as children and with frequency equal to the sum of the two nodes' frequencies. Add the new node to the priority queue.
            Node *new_node = new Node('\0', left->freq + right->freq, left, right);
            pq.push(new_node);
        }

        // root stores pointer to root of Huffman Tree
        root = pq.top();
        pq.pop();

        // traverse the Huffman Tree and store Huffman Codes in a map. Also prints them
        encode(root, "");

        for (char &ch : original_str)
        {
            code_str += huffmanCode[ch];
        }

        // traverse the Huffman Tree again and this time decode the encoded string
        int index = -1;
        do
        {
            decode(root, index);
        } while (index < (int)code_str.size() - 1);
    }
    void delete_node(Node *&p)
    {
        if (p->left)
        {
            delete_node(p->left);
        }
        if (p->right)
        {
            delete_node(p->right);
        }
        delete p;
        p = nullptr;
    }

public:
    HuffmanTree(const std::string &t) : original_str(t) { buildHuffmanTree(); }
    ~HuffmanTree()
    {
        delete_node(root);
    }
    std::string get_code_str() const { return code_str; }
    void display()
    {
        // print input string
        std::cout << "\nOriginal string was :\n"
                  << original_str << '\n';

        // print huffman code dictionary
        std::cout << "\nHuffman Codes are :\n";
        for (auto &pair : huffmanCode)
        {
            std::cout << pair.first << " : " << pair.second << '\n';
        }

        // print encoded string
        std::cout << "\nEncoded string is :\n"
                  << code_str << '\n';

        // print decoded string
        std::cout << "\nDecoded string is : \n"
                  << out_str << '\n';

        std::cout << "\nThe original size is    : " << original_str.length() + 1 << " byte(s) \n"
                  << "The compressed size is  : " << (int)ceil(code_str.length() / 8.0) + 1 << " byte(s) \n"
                  << "The compression rate is : " << std::fixed << std::setprecision(2) << 100 * (ceil(code_str.length() / 8.0) + 1) / (original_str.length() + 1) << "% \n";
    }
}; // class HuffmanTree

int test_my_huffman_tree()
{
    std::string str;
    std::cout << "Please enter a string : \n";
    std::getline(std::cin, str);
    HuffmanTree ht(str);
    ht.display();
    return 0;
}

int main()
{
    return test_my_huffman_tree();
}
