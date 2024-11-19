This repository contains functions and utilities to process, analyze, and manipulate suffix trees. The main operations include building a suffix tree from a set of input strings, checking the existence of suffixes, calculating properties of the tree, and compressing the tree for more efficient storage.








You can use the main functionality of the program by running it with one of the following commands, specifying the required arguments.

--build: Build a suffix tree from a set of input strings.


--properties: Calculate specific properties of the suffix tree such as the number of leaves, K-dimensional suffixes, and the maximum number of children for any node.


--check: Check if certain suffixes exist in the suffix tree.



--compress: Compress the suffix tree to reduce its size and print the compressed tree.

Example:

./main --build <input_file> <output_file>

./main --properties <input_file> <output_file> <K>

./main --check <input_file> <output_file>

./main --compress <input_file> <output_file>


processTree():
This function is responsible for reading the input file, building the suffix tree, and printing its level-order representation to the output file.

calculateTreeProperties():
This function calculates and prints:

The number of leaves in the suffix tree.
The number of K-dimensional suffixes.
The maximum number of children for any node in the tree.
checkSuffixExistence():
This function checks whether the given suffixes exist in the suffix tree. It prints 1 if the suffix exists, or 0 otherwise.

compressSuffixTree():
This function compresses the suffix tree and prints the compressed version in level-order to the output file.