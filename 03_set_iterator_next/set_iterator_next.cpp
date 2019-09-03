#include "test_runner.h"
#include <cassert>
#include <deque>
#include <iostream>

using namespace std;


struct Node {
	Node(int v, Node* p)
			: value(v)
			, parent(p)
	{}

	int value;
	Node* left = nullptr;
	Node* right = nullptr;
	Node* parent;
};


class NodeBuilder {
public:
	Node* CreateRoot(int value) {
		nodes.emplace_back(value, nullptr);
		return &nodes.back();
	}

	Node* CreateLeftSon(Node* me, int value) {
		assert( me->left == nullptr );
		nodes.emplace_back(value, me);
		me->left = &nodes.back();
		return me->left;
	}

	Node* CreateRightSon(Node* me, int value) {
		assert( me->right == nullptr );
		nodes.emplace_back(value, me);
		me->right = &nodes.back();
		return me->right;
	}

private:
	deque<Node> nodes;
};

Node* FindSubTreeMin(Node *tree)
{
	while (tree->left) {
		tree = tree->left;
	}
	return tree;
}

Node* Next(Node* me) {
	Node *ret = me;

	if (!me->parent) {
		return me->right ? FindSubTreeMin(me->right) : nullptr;
	}
	if (me->right) {
		return FindSubTreeMin(me->right);
	}
	if (me->parent->value > me->value)
		return me->parent;
	while (ret->parent && ret->parent->value < me->value) {
		ret = ret->parent;
	}
	if (!ret->parent) {
		return ret->value > me->value ? ret : nullptr;
	}
	return ret->parent;
}


void Test1() {
	NodeBuilder nb;


	Node* n1;
	Node* n2;
	Node* n3;
	Node* n4;
	Node* n5;
	Node* n50;
	Node* n89;
	Node* n90;
	Node* n91;
	Node* n100;
	Node* n101;


	Node* root = nb.CreateRoot(50);
	n50 = root;
	ASSERT_EQUAL( root->value, 50 );

	Node* l = nb.CreateLeftSon(root, 2);
	n2 = l;
	Node* min = nb.CreateLeftSon(l, 1);
	n1 = min;
	Node* r = nb.CreateRightSon(l, 4);
	n4 = r;
	ASSERT_EQUAL( min->value, 1);
	ASSERT_EQUAL( r->parent->value, 2 );

	n3 = nb.CreateLeftSon(r, 3);
	n5 = nb.CreateRightSon(r, 5);

	r = nb.CreateRightSon(root, 100);
	n100 = r;
	l = nb.CreateLeftSon(r, 90);
	n90 = l;
	n101 = nb.CreateRightSon(r, 101);

	n89 = nb.CreateLeftSon(l, 89);
	r = nb.CreateRightSon(l, 91);
	n91 = r;


	ASSERT_EQUAL( Next(n1)->value, 2 );
	ASSERT_EQUAL( Next(n2)->value, 3 );
	ASSERT_EQUAL( Next(n3)->value, 4 );
	ASSERT_EQUAL( Next(n4)->value, 5 );
	ASSERT_EQUAL( Next(n5)->value, 50 );
	ASSERT_EQUAL( Next(n50)->value, 89 );
	ASSERT_EQUAL( Next(n89)->value, 90 );
	ASSERT_EQUAL( Next(n90)->value, 91 );
	ASSERT_EQUAL( Next(n91)->value, 100 );
	ASSERT_EQUAL( Next(n100)->value, 101 );
	ASSERT_EQUAL((size_t)Next(n101), (size_t)nullptr );


	ASSERT_EQUAL( Next(min)->value, 2 );
	ASSERT_EQUAL( Next(l)->value, 91);
	ASSERT_EQUAL( Next(root)->value, 89 );
	ASSERT_EQUAL( Next(r)->value, 100);

	while (min) {
		cout << min->value << "\n";
		min = Next(min);
	}
}

void TestRootOnly() {
	NodeBuilder nb;
	Node* root = nb.CreateRoot(42);
	ASSERT( Next(root) == nullptr);
};


int main() {
	TestRunner tr;
	RUN_TEST(tr, Test1);
	RUN_TEST(tr, TestRootOnly);
	return 0;
}