# Red-black-Tree


**Implementation of priority queue using 2-3-4 Tree.**

Priority queue can be implemented with Red-Black Trees which are represented by 2-3-4 Trees. Elements of queue are actions represented by string (maximum length is 256 chars) and their integer priority. If there are actions with same priority, they are sorted lexicographically. Priority of actions can be changed individually. Actions are structured by their priority and smaller numbers represent higher priority.

Implemented operations:
- Creating empty tree and deleting the Tree
- Searching for an action based on its priority and inserting a new action
- Deleting action from the Tree (1. option: deleting action with given priority, 2. option: deleting action with highest priority)
- Printing a tree with overloaded operator << (1. option: printing Tree as 2-3-4 Tree, 2.option: printing Tree as Red-Black tree)
-  Changing the priority of action
-  Finding all actions with given priority
-  Main program which communicates with user
-  Reading and printing through console
-  Reading and writing in a file

This prohect was my work as help tp my colleague. It was homework project and he included me in.


Ps. If working with files: when writing from a file, every line needs to be formated as follows:
One line contains name of action(maximum 256 chars) and its priority
