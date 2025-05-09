#include <iostream>
#include <fstream>
#include <algorithm>
#include "BST.h"


using namespace std;


BST::BST() {
	root = NULL;
	count = 0;
}


bool BST::empty() {
	if (count == 0) return true;
	return false;
}


int BST::size() {
	return count;
}


void BST::preOrderPrint() {
	if (root == NULL) return;// handle special case
	else preOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::preOrderPrint2(BTNode *cur) {

	if (cur == NULL) return;
	cur->item.print(cout);
	preOrderPrint2(cur->left);
	preOrderPrint2(cur->right);
}


void BST::inOrderPrint() {
	if (root == NULL) return;// handle special case
	else inOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::inOrderPrint2(BTNode *cur) {

	if (cur == NULL) return;

	inOrderPrint2(cur->left);
	cur->item.print(cout);
	inOrderPrint2(cur->right);
}


void BST::postOrderPrint() {
	if (root == NULL) return;// handle special case
	else postOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::postOrderPrint2(BTNode *cur) {
	if (cur == NULL) return;
	postOrderPrint2(cur->left);
	postOrderPrint2(cur->right);
	cur->item.print(cout);
}



int BST::countNode() {
	int	counter = 0;
	if (root == NULL) return 0;
	countNode2(root, counter);
	return counter;
}


void BST::countNode2(BTNode *cur, int &count) {
	if (cur == NULL) return;
	countNode2(cur->left, count);
	countNode2(cur->right, count);
	count++;
}


bool BST::findGrandsons(type grandFather) {
	if (root == NULL) return false;
	return (fGS2(grandFather, root));
}


bool BST::fGS2(type grandFather, BTNode *cur) {
	if (cur == NULL) return false;
	//if (cur->item == grandFather) {
	if (cur->item.compare2(grandFather)){

		fGS3(cur, 0);// do another TT to find grandsons
		return true;
	}
	if (fGS2(grandFather, cur->left)) return true;
	return fGS2(grandFather, cur->right);
}


void BST::fGS3(BTNode *cur, int level) {
	if (cur == NULL) return;
	if (level == 2) {
		cur->item.print(cout);
		return;  // No need to search downward
	}
	fGS3(cur->left, level + 1);
	fGS3(cur->right, level + 1);
}



void BST::topDownLevelTraversal() {
	BTNode			*cur;
	Queue		    q;


	if (empty()) return; 	// special case
	q.enqueue(root);	// Step 1: enqueue the first node
	while (!q.empty()) { 	// Step 2: do 2 operations inside
		q.dequeue(cur);
		if (cur != NULL) {
			cur->item.print(cout);

			if (cur->left != NULL)
				q.enqueue(cur->left);

			if (cur->right != NULL)
				q.enqueue(cur->right);
		}
	}
}

//insert for BST
bool BST::insert(type newItem) {
	BTNode	*cur = new BTNode(newItem);
	if (!cur) return false;		// special case 1
	if (root == NULL) {
		root = cur;
		count++;
		return true; 			// special case 2
	}
	insert2(root, cur);			// normal
	count++;
	return true;
}


void BST::insert2(BTNode *cur, BTNode *newNode) {
	//if (cur->item > newNode->item) {
	if (cur->item.compare1(newNode->item)){
		if (cur->left == NULL)
			cur->left = newNode;
		else
			insert2(cur->left, newNode);
	}
	else {
		if (cur->right == NULL)
			cur->right = newNode;
		else
			insert2(cur->right, newNode);
	}
}



bool BST::remove(type item) {
	if (root == NULL) return false; 		// special case 1: tree is empty
	return remove2(root, root, item); 		// normal case
}

bool BST::remove2(BTNode *pre, BTNode *cur, type item) {

	// Turn back when the search reaches the end of an external path
	if (cur == NULL) return false;

	// normal case: manage to find the item to be removed
	//if (cur->item == item) {
	if (cur->item.compare2(item)){
		if (cur->left == NULL || cur->right == NULL)
			case2(pre, cur);	// case 2 and case 1: cur has less than 2 sons
		else
			case3(cur);		// case 3, cur has 2 sons
		count--;				// update the counter
		return true;
	}

	// Current node does NOT store the current item -> ask left sub-tree to check
	//if (cur->item > item)
	if (cur->item.compare1(item))
		return remove2(cur, cur->left, item);

	// Item is not in the left subtree, try the right sub-tree instead
	return remove2(cur, cur->right, item);
}


void BST::case2(BTNode *pre, BTNode *cur) {

	// special case: delete root node
	if (pre == cur) {
		if (cur->left != NULL)	// has left son?
			root = cur->left;
		else
			root = cur->right;

		free(cur);
		return;
	}

	if (pre->right == cur) {		// father is right son of grandfather? 
		if (cur->left == NULL)			// father has no left son?
			pre->right = cur->right;			// connect gfather/gson
		else
			pre->right = cur->left;
	}
	else {						// father is left son of grandfather?
		if (cur->left == NULL)			// father has no left son? 
			pre->left = cur->right;				// connect gfather/gson
		else
			pre->left = cur->left;
	}

	free(cur);					// remove item
}


void BST::case3(BTNode *cur) {
	BTNode		*is, *isFather;

	// get the IS and IS_parent of current node
	is = isFather = cur->right;
	while (is->left != NULL) {
		isFather = is;
		is = is->left;
	}

	// copy IS node into current node
	cur->item = is->item;

	// Point IS_Father (grandfather) to IS_Child (grandson)
	if (is == isFather)
		cur->right = is->right;		// case 1: There is no IS_Father    
	else
		isFather->left = is->right;	// case 2: There is IS_Father

	// remove IS Node
	free(is);
}

bool BST::deepestNodes() {
	BTNode* cur;
	if (empty()) return false;
	Queue cur_level;
	Queue next_level; // 
	cur_level.enqueue(root);
	while (!cur_level.empty())
	{
		for (int i = 0; i < cur_level.count; i++)
		{
			cur_level.dequeue(cur);
			if (cur->left != NULL)
				next_level.enqueue(cur->left);
			if (cur->right != NULL)
				next_level.enqueue(cur->right);
			cur_level.enqueue(cur);
		}
		if (next_level.empty()) { // no more child
			for (int i = 1; !cur_level.empty();i++) //print
			{
				cur_level.dequeue(cur);
				cout << "student"<<i <<":";
				cout << "\nName: " << cur->item.name;
				cout << "\nID: " << cur->item.id;
				cout << "\nAddress: " << cur->item.address;
				cout << "\nDate of Birth: " << cur->item.DOB;
				cout << "\nPhone No: " << cur->item.phone_no;
				cout << "\nCourse: " << cur->item.course;
				cout << "\nCGPA: " << cur->item.cgpa;
				cout << "\n";
			}
			return true;
		}
		else {
			while (!cur_level.empty()) // clear list
				cur_level.dequeue(cur);
			while (!next_level.empty()) { // move next level to cur level
				next_level.dequeue(cur);
				cur_level.enqueue(cur);
			}
		}
	}
	
	
	
}


bool BST::display(int order, int source) {

	if (empty())
		return false;
	ofstream output("student-info.txt"); // open file if file is not exist will create a new file

	display2(root, order, source , output);
	output.close();
	return true;
}

void BST::display2(BTNode* cur, int order, int source , ofstream& filename) {
	if (cur == NULL) return;

	if (order == 1) { // ascending order

		if (cur->left != NULL)
			display2(cur->left, order, source, filename);
		display3(cur, source,filename);
		if (cur->right != NULL)
			display2(cur->right, order, source, filename);
	}
	else { // descending order

		if (cur->right != NULL)
			display2(cur->right, order, source, filename);
		display3(cur, source,filename);
		if (cur->left != NULL)
			display2(cur->left, order, source, filename);
		
	
	}
	return;
}


void BST::display3(BTNode* cur,int source,ofstream& filename) {

	if (source == 1) {
		cout << "\nName: " << cur->item.name;
		cout << "\nID: " << cur->item.id;
		cout << "\nAddress: " << cur->item.address;
		cout << "\nDate of Birth: " << cur->item.DOB;
		cout << "\nPhone No: " << cur->item.phone_no;
		cout << "\nCourse: " << cur->item.course;
		cout << "\nCGPA: " << cur->item.cgpa;
		cout << "\n";
	}
	else {
		cur->item.print(filename);
	}
	return;
}


BTNode* BST::finditem(BTNode* cur, type item) {//find item address and return
	if (cur == NULL) return NULL;
	if (cur->item.compare2(item))  return cur;
	if (cur->item.compare1(item))finditem(cur->left, item);
	else finditem(cur->right, item);

}

bool BST::CloneSubtree2(BTNode* cur, BTNode*& root) { 
	if (cur == NULL) return true;

	root = new BTNode(cur->item);//copy the item to the tree
	return CloneSubtree2(cur->left, root->left) && CloneSubtree2(cur->right, root->right);
}

bool BST::CloneSubtree(BST t1, type item) {
	if (!empty()) return false;
	if (t1.empty()) return false;//check condition 


	BTNode* cur = t1.finditem(t1.root, item);
	if (cur == NULL) return false;//if the item cannot find return false

	CloneSubtree2(cur, root);//clone the subtree

	cout << "T1:" << endl;//display t1
	t1.preOrderPrint();
	cout << "T2:" << endl;//display t2
	preOrderPrint();

	return true;
}



bool BST::printLevelNodes() {//print level nodes
	BTNode* cur;
	Queue		    q;
	int level = 1, size = 0;

	if (empty()) return false;
	q.enqueue(root);


	while (!q.empty()) {
		size = q.count;//get the length of the level
		cout << "Level " << level << " nodes: ";//print level

		for (int i = 0;i < size;i++) {//print nodes of each level
			q.dequeue(cur);
			if (cur != NULL) {
				cout << cur->item.id << "\t";

				if (cur->left != NULL)
					q.enqueue(cur->left);

				if (cur->right != NULL)
					q.enqueue(cur->right);
			}
		}


		cout << endl;
		level++;
	}

	return true;
}


bool BST::printPath3(BTNode* cur) {//read  and print external paths
	if (cur == NULL) return true;


	printPath3(cur->left);//print external path
	cout << cur->item.id << "\t";
}

bool BST::printPath2(BTNode* cur, BTNode* path) {
	if (cur == NULL) return true;

	BTNode* temp = new BTNode(cur->item);//insert the node to one side tree
	temp->left = path;
	path = temp;

	if (cur->left == NULL && cur->right == NULL) {//if the node is leaf, print the path
		printPath3(path);
		cout << endl;
	}

	printPath2(cur->left, path);
	printPath2(cur->right, path);
}

bool BST::printPath() {//start print path
	BTNode* cur = root;
	BST path;
	if (root == NULL) return false;

	cout << "Below are all the external paths for the tree : " << endl;
	printPath2(root, path.root);
	return true;
}

