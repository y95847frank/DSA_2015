#include <utility>
#include <list>

struct EmptyHeap: public std::exception {};

template<class T>
class BinomialHeap {
	private:
		/* inner class: binomial tree */
		struct BinomialTree {
			int _size;
			T element;
			std::list<BinomialTree*> children;

			BinomialTree(T _ele): _size(1), element(_ele) {
				children.clear();
			}

			/* return the size of BinomialTree
			* #note that nullptr->size() == 0
			* (nullptr is a null pointer (like NULL in C))
			*/
			int size() {
				return (this!=nullptr)?this->_size:0;
			}
		};
		/* some definition for convinience
		*/
		typedef BinomialTree BT;
		typedef BinomialHeap<T> BH;
		typedef std::pair<BT*, BT*> CarrySum;
		typedef std::pair<T, BH> MaxRemainder;

		/* Merge three binomial trees which have the same sizes
		*
		* INPUT:   a: operand a, b: operand b, c: carry in
		*          (each of them are either nullptr or a pointer of BinomialTree with size 2^n)
		*
		* OUTPUT:  a pair consist of two variables.
		*          first: carry out (nullptr or a pointer of BinomialTree with size 2^(n+1))
		*          second: sum (nullptr or a pointer of BinomialTree with size 2^n)
		*
		* (just as a full adder: http://en.wikipedia.org/wiki/Adder_%28electronics%29#Full_adder )
		*/
		CarrySum merge_tree(BT *a, BT *b, BT *c) {
			CarrySum two;
			if(a == nullptr && b == nullptr && c == nullptr) {
			  two.first = a;
			  two.second = a;
			}
			if(a == nullptr && b == nullptr && c != nullptr) {
			  two.first = nullptr;
			  two.second = c;
			}
			if(a == nullptr && b != nullptr && c == nullptr) {
			  two.first = nullptr;
			  two.second = b;
			}
			if(a != nullptr && b == nullptr && c == nullptr) {
			  two.first = nullptr;
			  two.second = a;
			}
			if(a == nullptr && b != nullptr && c != nullptr) {
			  
			  two.second == nullptr;
			  if(b->element > c->element) {
			    b->children.push_back(c);
				b->_size *= 2;
				two.first = b;
			  }
			  else {
			    c->children.push_back(b);
				c->_size *= 2;
				two.first = c;
			  }
			}
			if(a != nullptr && b == nullptr && c != nullptr) {
			  
			  two.second = nullptr;
			  if(a->element > c->element) {
			    a->children.push_back(c);
				a->_size *= 2;
				two.first = a;
			  }
			  else {
			    c->children.push_back(a);
				c->_size *= 2;
				two.first = c;
			  }
			}
			if(a != nullptr && b != nullptr && c == nullptr) {
			  
			  two.second == nullptr;
			  if(a->element > b->element) {
			    a->children.push_back(b);
				a->_size *= 2;
				two.first = a;
			  }
			  else {
			    b->children.push_back(a);
				b->_size *= 2;
				two.first = b;
			  }
			}
			if(a != nullptr && b != nullptr && c != nullptr) {
			  two.second = a;
			  
			  if(b->element > c->element) {
			    b->children.push_back(c);
				b->_size *= 2;
				two.first = b;
			  }
			  else {
			    c->children.push_back(b);
				c->_size *= 2;
				two.first = c;
			  }
			}
			return two;
			};

		/* Pop the maximum element of a binomial tree and make other elements a binomial heap.
		*
		* INPUT:   a: a pointer of BinomialTree
		*
		* OUTPUT:  a pair consist of two variables.
		*          first: the maximum element
		*          second: a binomial heap consists of other elements
		*/
		MaxRemainder pop_max(BT *a) {
			MaxRemainder two;
			two.first = a->element;
			int numtree = 1;
			int numsum = 0;
			if(a->_size == 1) {
				for(int i = 0; i < 32; i++)
					two.second.trees[i] = nullptr;
				}
			else {
				while(numtree != a->_size){
					numtree *= 2;
					numsum++;
					}
				for(int i = 0; i < numsum ; i++){
					two.second.trees[i] = a->children.front();
					a->children.pop_front();
					}
				for(int j = numsum; j < 32; j++)
					two.second.trees[j] = nullptr;
				}
			two.second.size = a->_size - 1;
			return two;
		}

		BT* trees[32]; //binomial trees of the binomial heap, where trees[i] is a tree with size 2^i.

	public:
		int size;
		BinomialHeap(): size(0) {
			for(int i=0; i<32; ++i) trees[i] = nullptr;
		}
		BinomialHeap(T element): size(1) {
			for(int i=0; i<32; ++i) trees[i] = nullptr;
			trees[0] = new BT(element);
		}
		/* merge all elements in the binomial heap b into *this, and clear the binomial heap b.
		*
		* INPUT:   b: a reference of BinomialHeap
		*/
		void merge(BH &b) {
			BinomialTree *newtree = nullptr;
			CarrySum two;
			this->size += b.size;
			for(int i = 0; i < 32; i++) {
				two = merge_tree(this->trees[i], b.trees[i], newtree);
				this->trees[i] = two.second;   //sum(remain)
				newtree = two.first;   //carry out
				b.trees[i] = nullptr;
				}
			b.size = 0;
			}

		void insert(const T &element) {
			BH tmp = BH(element);
			merge(tmp);
		}
		
		T pop() {
			if(size==0) throw EmptyHeap();
			else {
				//find the tree contains maximum element
				int max_tree = -1;
				for(int i=0; i<32; ++i)
					if(trees[i]->size() > 0 && (max_tree == -1 || trees[i]->element > trees[max_tree]->element))
						max_tree = i;

				MaxRemainder m_r = pop_max(trees[max_tree]);
				T &max_element = m_r.first;
				BH &remainder = m_r.second;

				size -= trees[max_tree]->size();
				trees[max_tree] = nullptr;
				merge(remainder);
				return max_element;
			}
		}
};
