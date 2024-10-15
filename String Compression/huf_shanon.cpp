#include <bits/stdc++.h>
using namespace std;

void read_data(string file , vector<pair<char,double>>&symbols ,int &n){
    ifstream infile(file);
    if (!infile) {
        cerr << "Error opening file!" << endl;
        return ;
    }
    infile >> n;

    if (n <= 0) {
        cerr << "Invalid number of symbols" << endl;
        return ;
    }

    for (int i = 0; i < n; ++i) {
        char symbol;
        double probability;
        infile >> symbol >> probability;

        if (infile.fail()) {
            cerr << "Error reading data from file" << endl;
            return ;
        }

        symbols.push_back(make_pair(symbol, probability));
    }

    if (!validInput(n, symbols)) {
        return ;
    }
}


// Node structure for Huffman Tree
struct Node {
    char symbol;
    double prob;
    Node* left;
    Node* right;

    Node(char sym, double prob) : symbol(sym), prob(prob), left(nullptr), right(nullptr) {}
};

// Comparator for priority queue
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->prob > b->prob;
    }
};

// Printing the Huffman codes
void printEncoding(const map<char, string>& encoding) {
    for (auto& pair : encoding) {
        cout << pair.first << ": " << pair.second << endl;
    }
}

// Generate Huffman codes recursively
void genHuffman(Node* root, string code, map<char, string>& huffmanCodes) {
    if (!root) return;
    if (!root->left && !root->right) { 
        huffmanCodes[root->symbol] = code;
    }
    genHuffman(root->left, code + "0", huffmanCodes); // On moving left, add 0
    genHuffman(root->right, code + "1", huffmanCodes); // On moving right, add 1
}

// Huffman encoding function
void huffmanEncoding(const vector<pair<char, double>>& symbols) {
    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (auto& sym : symbols) {
        pq.push(new Node(sym.first, sym.second));
    }

    while (pq.size() > 1) {
        Node* left = pq.top(); 
        pq.pop();
        Node* right = pq.top(); 
        pq.pop();

        Node* combined = new Node('\0', left->prob + right->prob);
        combined->left = left;
        combined->right = right;

        pq.push(combined);
    }

    Node* root = pq.top();
    map<char, string> huffmanCodes;
    genHuffman(root, "", huffmanCodes);
    printEncoding(huffmanCodes);
}

// Shannon-Fano encoding function
void SF_encoder(vector<pair<char, double>>& symbols, int start, int end, map<char, string>& codes, string code) {
    if (start == end) {
        codes[symbols[start].first] = code;
        return;
    }

    double totalProb = 0;
    for (int i = start; i <= end; ++i) {
        totalProb += symbols[i].second;
    }

    double cumulativeProb = 0;
    int splitIndex = start;
    while (splitIndex <= end && cumulativeProb + symbols[splitIndex].second <= totalProb / 2) {
        cumulativeProb += symbols[splitIndex].second;
        ++splitIndex;
    }

    if (splitIndex == start) ++splitIndex;

    SF_encoder(symbols, start, splitIndex - 1, codes, code + "0");
    SF_encoder(symbols, splitIndex, end, codes, code + "1");
}

// Wrapper for Shannon-Fano encoding
void SFencoding(vector<pair<char, double>>& symbols) {
    sort(symbols.begin(), symbols.end(), [](const pair<char, double>& a, const pair<char, double>& b) {
        return a.second > b.second;
    });

    map<char, string> codes;
    SF_encoder(symbols, 0, symbols.size() - 1, codes, "");
    printEncoding(codes);
}

bool validInput(int n, vector<pair<char,double>>&symbols){
    double totalProb = 0;
    for (auto& sym : symbols) {
        if (sym.second <= 0 || sym.second > 1) {
            cerr << "Invalid probability for symbol " << sym.first << endl;
            return false;
        }
        totalProb += sym.second;
    }
    if (totalProb > 1) {
        cerr << "Total probability exceeds 1" << endl;
        return false;
    }
    return true;
}


int main() {
    // Your code goes here
    string file = "prob.dat";
    vector<pair<char,double>> symbols;
    int n;
    read_data(file,symbols,n);
    cout<<"Huffman Encoding : "<<endl;
    huffmanEncoding(symbols);

    cout<<"Shanon Fano Encoding : "<<endl;
    SFencoding(symbols);
    return 0;
}