1 Question 8: Given sequence k = k1 <k2 < ... <kn of n sorted keys, with a search
probability pi for each key ki . Build the Binary 
2 search tree that has the least search cost given the access probability for each
key?
3
4
5 #include <iostream>
6 #include <vector>
7
8 using namespace std;
9
10 // Forward declaration of Node structure
11 struct Node;
12
13 // Function to build the optimal binary search tree
14 Node* buildOptimalBST(vector<int>& keys, vector<double>& probabilities);
15
16 // Function to recursively build the optimal binary search tree
17 Node* buildSubtree(vector<int>& keys, vector<vector<int>>& root, int i, int j);
18
19 // Function to search for a key in the binary search tree
20 Node* search(Node* root, int key);
21
22 // Function to delete the binary search tree
23 void deleteBinarySearchTree(Node* root);
24
25 // Binary search tree node structure
26 struct Node {
27 int key;
28 Node* left;
29 Node* right;
30
31 Node(int k) : key(k), left(nullptr), right(nullptr) {}
32 };
33
34 // Function to calculate the sum of probabilities from index i to j
35 double sum(vector<double>& probabilities, int i, int j) {
36 double s = 0.0;
37 for (int k = i; k <= j; k++) {
38 s += probabilities[k];
39 }
40 return s;
41 }
42
43 Node* buildSubtree(vector<int>& keys, vector<vector<int>>& root, int i, int j) {
44 if (i > j) {
45 return nullptr;
46 }
47
48 int r = root[i][j];
49 Node* rootNode = new Node(keys[r - 1]);
50
51 rootNode->left = buildSubtree(keys, root, i, r - 1);
52 rootNode->right = buildSubtree(keys, root, r + 1, j);
53
54 return rootNode;
55 }
56
57 Node* buildOptimalBST(vector<int>& keys, vector<double>& probabilities) {
58 int n = keys.size();
59 vector<vector<double>> cost(n + 1, vector<double>(n + 1, 0.0));
60 vector<vector<int>> root(n + 1, vector<int>(n + 1, 0));
61
62 // Initialize base cases
63 for (int i = 1; i <= n; i++) {
64 cost[i][i] = probabilities[i - 1];
File: /home/shrikant/Desktop/Shrikant/8 Page 2 of 3
65 root[i][i] = i;
66 }
67
68 // Build the cost matrix
69 for (int len = 2; len <= n; len++) {
70 for (int i = 1; i <= n - len + 1; i++) {
71 int j = i + len - 1;
72 cost[i][j] = INT_MAX;
73
74 // Calculate the optimal cost and root
75 for (int r = i; r <= j; r++) {
76 double c = ((r > i) ? cost[i][r - 1] : 0) + ((r < j) ? cost[r + 1]
[j] : 0) + sum(probabilities, i - 1, j - 1);
77 if (c < cost[i][j]) {
78 cost[i][j] = c;
79 root[i][j] = r;
80 }
81 }
82 }
83 }
84
85 // Build the optimal binary search tree
86 return buildSubtree(keys, root, 1, n);
87 }
88
89 Node* search(Node* root, int key) {
90 if (root == nullptr || root->key == key) {
91 return root;
92 }
93
94 if (key < root->key) {
95 return search(root->left, key);
96 }
97
98 return search(root->right, key);
99 }
100
101 void deleteBinarySearchTree(Node* root) {
102 if (root == nullptr) {
103 return;
104 }
105
106 // Delete the left and right subtrees
107 deleteBinarySearchTree(root->left);
108 deleteBinarySearchTree(root->right);
109
110 // Delete the current node
111 delete root;
112 }
113
114 int main() {
115 // Input sequence of keys and search probabilities
116 vector<int> keys = {1, 2, 3, 4, 5};
117 vector<double> probabilities = {0.1, 0.2, 0.15, 0.3, 0.25};
118
119 // Build the optimal binary search tree
120 Node* root = buildOptimalBST(keys, probabilities);
121
122 // Perform any desired operations on the constructed binary search tree
123 // For example, you can perform a search operation on the tree
124
125 int keyToSearch = 3;
126 Node* result = search(root, keyToSearch);
127 if (result != nullptr) {
128 cout << "Key " << keyToSearch << " found in the binary search tree." <<
endl;
File: /home/shrikant/Desktop/Shrikant/8 Page 3 of 3
129 } else {
130 cout << "Key " << keyToSearch << " not found in the binary search tree." <<
endl;
131 }
132
133 // Cleanup: Free the memory allocated for the binary search tree
134 deleteBinarySearchTree(root);
135
136 return 0;
137 }
138
139
140 ----------------------------------------------------------------------------------------------------------------------
141 