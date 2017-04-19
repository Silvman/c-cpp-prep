#include <iostream>
#include "set.hpp"

using namespace std;

// вызывается только при ::insert, так что нет случая с отсутствием а

tree_node<T>::tree_node(T a)
  : key(a), count(0),
    l(nullptr), r(nullptr) { }

tree_node::tree_node(tree_node& from)
    : key(from.key), count(from.count),
      l(nullptr), r(nullptr) {
  // cout << "CConstr" << endl;
  if (from.l) {
    l = new tree_node(*from.l);
  }

  if (from.r) {
    r = new tree_node(*from.r);
  }
}

tree_node& tree_node::operator = (tree_node& from) {
  // cout << "operator = node" << endl;
  key = from.key;
  count = from.count;
  l = from.l;
  r = from.r;

  return *this;
}

tree_node::~tree_node() {
  // cout << "Destr" << endl;
  if (l) {
    delete l;
  }

  if (r) {
    delete r;
  }
}


tree_node* tree_node::seekByKey(int a) {
  tree_node* buf = this;

  while (1) {
    if (buf->key == a) break;
    if (buf->key < a) {
      if (buf->r) {
        buf = buf->r;
      } else {
        break;
      }
    } else {
      if (buf->l) {
        buf = buf->l;
      } else {
        break;
      }
    }
  }

  return buf;
}

tree_node* tree_node::search(int a) {
  tree_node* closest = this->seekByKey(a);

  if (closest->key == a) {
    return closest;
  } else {
    return nullptr;
  }
}

tree_node* tree_node::insert(int a) {
  tree_node* buf = this->seekByKey(a);
  if (buf->key == a) {
    buf->count++;
  } else {
    if(buf->key < a) {
      buf->r = new tree_node(a);
      return buf->r;
    } else {
      buf->l = new tree_node(a);
      return buf->l;
    }
  }
  return nullptr;
}

tree_node* tree_node::amputee(int a) {
  tree_node* target = nullptr;

  // cout << "a = " << a << endl;
  // cout << "key = " << key << endl;

  if (a > key && r)	{
		target = r->amputee(a);
		if (target == r)
			r = nullptr;
	}

	if (a < key && l)	{
		target = l->amputee(a);
		if (target == l)
			l = nullptr;
	}

	if (key == a) {
		if (!l && !r)
       target = this;

		if (l && !r) {
			target = l;
			*this = *l;
		}

		if (!l && r) {
			target = r;
			*this = *r;
		}

		if (l && r)	{
      tree_node* max_node_l = l->getMaxNode();
      tree_node* min_node_r = r->getMinNode();

			if ( (key - max_node_l->key) < (min_node_r->key - key)) {
				target = l->amputee(max_node_l->key);

    		if (target == l)
    			l = nullptr;

				key = max_node_l->key;
        count = max_node_l->count;
			} else {
				target = r->amputee(min_node_r->key);

    		if (target == r)
    			r = nullptr;

				key = min_node_r->key;
        count = min_node_r->count;
			}
		}
	}

	if (target) {
	  target->l = nullptr;
		target->r = nullptr;
	}

	return target;
}

tree_node* tree_node::getMaxNode() {
  tree_node* current = this;

  while (current->r)
    current = current->r;

  return current;
}

tree_node* tree_node::getMinNode() {
  tree_node* current = this;

  while (current->l)
    current = current->l;

  return current;
}


void tree_node::print() {
  for (int i = 0; i <= count; i++)
    cout << key << " ";

  return;
}

void tree_node::printTreeAsc() {
    if (l) l->printTreeAsc();

    this->print();

    if (r) r->printTreeAsc();

    return;
}

void tree_node::printTreeLeaves() {
    if (l) l->printTreeLeaves();

    if (r) r->printTreeLeaves();

    if(!l && !r) {
      this->print();
    }

    return;
}

// bin_tree

bin_tree::bin_tree() : head(nullptr) { }

bin_tree::bin_tree(bin_tree& from) {
  head = new tree_node(*from.head);
  // cout << "CCbintree" << endl;
}

bin_tree::~bin_tree() {
  delete head;
}


const tree_node* bin_tree::add(int a) {
  if (head) {
    return head->insert(a);
  } else {
    head = new tree_node(a);
    return head;
  }
}

const tree_node* bin_tree::search(int a) {
  if (head) {
    return head->search(a);
  }

  return nullptr;
}

int bin_tree::drop(int a) {
  if (head) {
    if(tree_node* target = head->amputee(a)) {
      delete target;
      if (target == head)
        head = nullptr;

      return 1;
    }
  }
  return 0;
}


void bin_tree::printAsc() {
  if (head)
    head->printTreeAsc();

  cout << endl;
  return;
}

void bin_tree::printLeaves() {
  if (head)
    head->printTreeLeaves();

  cout << endl;
  return;
}
