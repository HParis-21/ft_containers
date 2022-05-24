#ifndef REDBLACKTREE_HPP
# define REDBLACKTREE_HPP

# include <iostream>


namespace ft {

	template <typename P, class Alloc = std::allocator<P> >
	class Node {
		public:
			typedef P													value;
			typedef Alloc												allocator_type;
			typedef typename allocator_type::reference 					reference;
			typedef typename allocator_type::const_reference 			const_reference;
			typedef typename allocator_type::pointer 					pointer;
			typedef typename allocator_type::const_pointer 				const_pointer;
			// typedef typename pair_value::first_type					key_type;
			// typedef typename pair_value::second_type					value_type;

		private:
			template <typename, typename ,typename> friend class RedBlackTree;
			template <typename, typename, typename> friend class RedBlackTreeSet;
			template <typename> friend class MapIterator;
			template <typename> friend class MapConstIterator;
			bool			_color;
			value			*_val;
			Node			*_left;
			Node			*_right;
			Node			*_parent;
			allocator_type	_alloc;

			void	set_nil(Node *nil) {
				this->_left = nil;
				this->_right = nil;
				this->_parent = nil;
			}

		public:
			Node(const allocator_type& alloc = allocator_type()) : _alloc(alloc) {
				this->_color = false;
				this->_left = NULL;
				this->_right = NULL;
				this->_parent = NULL;
				this->_val = this->_alloc.allocate(1);
			}

			~Node() {
				this->_alloc.destroy(this->_val);
				this->_alloc.deallocate(this->_val, 1);
			};

			Node(value val, const allocator_type& alloc = allocator_type()) : _alloc(alloc) {
				this->_color = true;

				this->_val = this->_alloc.allocate(1);
				this->_alloc.construct(this->_val, val);
				this->_left = NULL;
				this->_right = NULL;
				this->_parent = NULL;
			}

			Node(const Node &n, const allocator_type& alloc = allocator_type()) : _alloc(alloc) {
				this->_val = this->_alloc.allocate(1);
				this->_alloc.construct(this->_val, *n._val);
				*this = n;
			}

			Node &operator=(const Node &n) {
				if (this == &n)
					return *this;
				this->_color = n._color;
				this->_left = n._left;
				this->_right = n._right;
				this->_parent = n._parent;
				return (*this);
			}

			value *get_pair() {
				return this->_val;
			}

			bool color(){
				return this->_color;
			}

			Node *left(){
				return this->_left;
			}

			Node *right(){
				return this->_right;
			}

			
	};

	template<typename N, class Compare, class Alloc = std::allocator<N> >
	
	class RedBlackTree {
		
		public:
			typedef	N													node;
			typedef Compare									key_compare;
			typedef Alloc												allocator_type;
			typedef typename node::value								pair_value;
			typedef typename pair_value::first_type						key_type;
			typedef typename pair_value::second_type					value_type;
			// typedef typename node::value_type						value_type;
			typedef typename allocator_type::reference 					reference;
			typedef typename allocator_type::const_reference 			const_reference;
			typedef typename allocator_type::pointer 					pointer;
			typedef typename allocator_type::const_pointer 				const_pointer;

		private:
			template <typename, typename, typename, typename> friend class map;
			allocator_type	_alloc;
			pointer			_nil;
			pointer			_begin;
			key_compare		_comp;

			size_t max_size() const {
				return this->_alloc.max_size();
			}

			void _clear_tree(node *n) {
				if (n->_left != this->_nil) {
					this->_clear_tree(n->_left);
					this->_alloc.destroy(n->_left);
					this->_alloc.deallocate(n->_left, 1);
				}
				if (n->_right != this->_nil) {
					this->_clear_tree(n->_right);
					this->_alloc.destroy(n->_right);
					this->_alloc.deallocate(n->_right, 1);
				}
			}

			void _torn_left(node *n) {
				node *buf;
				buf = n->_right;
				if (n->_right->_left != this->_nil)
					n->_right->_left->_parent = n;
				n->_right->_parent = n->_parent;
				if (n->_parent == this->_nil)
					this->_nil->_parent = n->_right;
				n->_right = n->_right->_left;
				if (n->_parent->_left == n)
					n->_parent->_left = buf;
				else if (n->_parent->_right == n)
					n->_parent->_right = buf;
				buf->_left = n;
				n->_parent = buf;
				if (n == this->_begin)
					this->_begin = n->_parent;
			}

			void _torn_right(node *n) {
				node *buf;
				
				buf = n->_left;
				if (n->_left->_right != this->_nil)
					n->_left->_right->_parent = n;
				n->_left->_parent = n->_parent;
				if (n->_parent == this->_nil)
					this->_nil->_parent = n->_left;
				n->_left = n->_left->_right;
				if (n->_parent->_left == n)
					n->_parent->_left = buf;
				else if (n->_parent->_right == n)
					n->_parent->_right = buf;
				buf->_right = n;
				n->_parent = buf;
				if (n == this->_begin)
					this->_begin = n->_parent;
			}

			void _add_event_n3(node *n, bool left) {
				n->_parent->_color = false;
				if (left)
					n->_parent->_parent->_right->_color = false;
				else 
					n->_parent->_parent->_left->_color = false;
				if (n->_parent->_parent->_parent != this->_nil) {
					n->_parent->_parent->_color = true;
					this->_correct_add_node(n->_parent->_parent);
				}
			}

			void _add_event_n4(node *n, bool left) {
				if (left)
					this->_torn_left(n->_parent);
				else
					this->_torn_right(n->_parent);
				this->_add_event_n5(n->_left, left);
			}

			void _add_event_n5(node *n, bool left) {
				n->_parent->_color = false;
				n->_parent->_parent->_color = true;
				if (left)
					this->_torn_right(n->_parent->_parent);
				else
					this->_torn_left(n->_parent->_parent);

				
			}

			void _correct_add_node(node *n) {
				bool left = true;

				if (n->_parent->_color == false)
					return ;
				if (n->_parent != n->_parent->_parent->_left)
					left = false;
				if ((left && n->_parent->_parent->_right->_color == true) ||
					(!left && n->_parent->_parent->_left->_color == true)) {
						_add_event_n3(n, left);
				}
				else if ((left && n->_parent->_left != n) || (!left && n->_parent->_right != n))
					_add_event_n4(n, left);
				else
					_add_event_n5(n, left);
			}

			node *_search_possion(key_type key, node *begin) const {
				if (this->_begin == NULL)
					return NULL;
				if  (this->_comp(key, begin->_val->first) && begin->_left != this->_nil)
					return (this->_search_possion(key, begin->_left));
				if (key == begin->_val->first)
					return begin;
				if (this->_comp(begin->_val->first, key) && begin->_right != this->_nil)
					return (this->_search_possion(key, begin->_right));
				return begin;
			}

			node *_max_node(node *begin) const {
				if (begin->_right != this->_nil)
					return this->_max_node(begin->_right);
				return begin;
			}

			node *_min_node(node *begin) const {
				if (begin != NULL && begin->_left != this->_nil)
					return this->_min_node(begin->_left);
				return begin;
			}

			void _swap_node(node *n1, node *n2) {
				node *buf;
				bool col_buf;
				int close = 0;

				if (n2 == n1->_left)
					close = 1;
				else if (n2 == n1->_right)
					close = 2;
				if (n1->_parent == this->_nil) {
					this->_nil->_parent = n2;
					this->_begin = n2;
				}
				else {
					if (n1 == n1->_parent->_right)
						n1->_parent->_right = n2;
					else 
						n1->_parent->_left = n2;
				}
				if (n2 == n2->_parent->_right && close != 2)
						n2->_parent->_right = n1;
				else if (n2 == n2->_parent->_left && close != 1)
					n2->_parent->_left = n1;
				buf = n1->_parent;
				if (close == 0)
					n1->_parent = n2->_parent;
				else 
					n1->_parent = n2;
				n2->_parent = buf;

				if (n1->_left != this->_nil && close != 1)
					n1->_left->_parent = n2;
				if (n2->_left != this->_nil)
					n2->_left->_parent = n1;
				buf = n1->_left;
				n1->_left = n2->_left;
				if (close != 1)
					n2->_left = buf;
				else
					n2->_left = n1;

				if (n1->_right != this->_nil && close != 2)
					n1->_right->_parent = n2;
				if (n2->_right != this->_nil)
					n2->_right->_parent = n1;
				buf = n1->_right;
				n1->_right = n2->_right;
				if (close != 2)
					n2->_right = buf;
				else
					n2->_right = n1;

				col_buf = n1->_color;
				n1->_color = n2->_color;
				n2->_color = col_buf;
			}

			void _remove_event_n2(node *n, bool left) {
				n->_parent->_color = true;
				if (left) {
					n->_parent->_right->_color =false;
					this->_torn_left(n->_parent);
				}
				else {
					n->_parent->_left->_color =false;
					this->_torn_right(n->_parent);
				}
			};

			void _remove_event_n3(node *n, bool left) {
				if (left)
					n->_parent->_right->_color = true;
				else
					n->_parent->_left->_color = true;
				left = true;
				if (n->_parent->_parent->_left != n->_parent)
					left = false;
				this->_difficult_removal(n->_parent, left);
			};

			void _remove_event_n4(node *n, bool left) {
				n->_parent->_color = false;
				if (left)
					n->_parent->_right->_color =true;
				else
					n->_parent->_left->_color =true;
			};

			void _remove_event_n5(node *n, bool left) {
				if (left) {
					n->_parent->_right->_left->_color = false;
					n->_parent->_right->_color = true;
					this->_torn_right(n->_parent->_right);
				}
				else {
					n->_parent->_left->_right->_color = false;
					n->_parent->_left->_color = true;
					this->_torn_left(n->_parent->_left);
				}
			};

			void _remove_event_n6(node *n, bool left) {
				bool buf;
				if (left) {
					n->_parent->_right->_right->_color = false;
					buf = n->_parent->_color;
					n->_parent->_color = n->_parent->_right->_color;
					n->_parent->_right->_color = buf;
					this->_torn_left(n->_parent);
				}
				else {
					n->_parent->_left->_left->_color = false;
					buf = n->_parent->_color;
					n->_parent->_color = n->_parent->_left->_color;
					n->_parent->_left->_color = buf;
					this->_torn_right(n->_parent);
				}
			};


			void _difficult_removal(node *n, bool left) {
				if (n->_parent == this->_nil)
					return ;
				if ((left && n->_parent->_right->_color) || (!left && n->_parent->_left->_color) ) 
					this->_remove_event_n2(n, left);
				if ((left && !n->_parent->_color && !n->_parent->_right->_color && !n->_parent->_right->_left->_color && !n->_parent->_right->_right->_color) ||
						(!left && !n->_parent->_color && !n->_parent->_left->_color && !n->_parent->_left->_left->_color && !n->_parent->_left->_right->_color)) {
							this->_remove_event_n3(n, left);
							return ;
				}
				if ((left && n->_parent->_color && !n->_parent->_right->_color && !n->_parent->_right->_left->_color && !n->_parent->_right->_right->_color) ||
						(!left && n->_parent->_color && !n->_parent->_left->_color && !n->_parent->_left->_left->_color && !n->_parent->_left->_right->_color)) {
							this->_remove_event_n4(n, left);
							return ;
				}
				if ((left && !n->_parent->_right->_color && n->_parent->_right->_left->_color && !n->_parent->_right->_right->_color) ||
						(!left && !n->_parent->_left->_color && !n->_parent->_left->_left->_color && n->_parent->_left->_right->_color)) {
							this->_remove_event_n5(n, left);
				}
				if ((left && !n->_parent->_right->_color && !n->_parent->_right->_left->_color && n->_parent->_right->_right->_color) ||
						(!left && !n->_parent->_left->_color && n->_parent->_left->_left->_color && !n->_parent->_left->_right->_color)) {
							this->_remove_event_n6(n, left);
				}
			}

			void _clear() {
				if (this->_begin != NULL) {
					this->_clear_tree(this->_begin);
					this->_alloc.destroy(this->_begin);
					this->_alloc.deallocate(this->_begin, 1);
					this->_begin = NULL;
				}
			}

		public:
			RedBlackTree(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _comp(comp) {
				this->_nil = this->_alloc.allocate(1);
				this->_alloc.construct(this->_nil, node());
				this->_begin = NULL;
				this->_nil->set_nil(this->_nil);
			}

			~RedBlackTree() {
				if (this->_begin != NULL) {
					this->_clear_tree(this->_begin);
					this->_alloc.destroy(this->_begin);
					this->_alloc.deallocate(this->_begin, 1);
				}
				this->_alloc.destroy(this->_nil);
				this->_alloc.deallocate(this->_nil, 1);
			}

			RedBlackTree& operator= (const RedBlackTree& x) {
				this->_alloc = x._alloc;
				this->_comp = x._comp;
				if (this->_begin != NULL)
				{
					this->_clear_tree(this->_begin);
					this->_alloc.destroy(this->_begin);
					this->_alloc.deallocate(this->_begin, 1);
					this->_begin = NULL;
				}
				node *buf = x._min_node(x._begin);
				while(buf != NULL && buf != x._nil) {
				// std::cout << "RBT: "<< buf->_val->first << std::endl;
					this->add_node(*buf);
					if (buf->_right != x._nil) {
						buf = x._min_node(buf->_right);
					}
					else {
						bool left = true;
						while(left) {
							if (buf->_parent == x._nil || buf->_parent->_left == buf) {
								left = false;
							}
							buf = buf->_parent;
						}
					}
				}				
				return *this;
			}

			void swap_rbt(RedBlackTree &r) {
				pointer buf = this->_begin;
				this->_begin = r._begin;
				r._begin = buf;
				buf = this->_nil;
				this->_nil = r._nil;
				r._nil = buf;
				allocator_type	b_alloc = this->_alloc;
				this->_alloc = r._alloc;
				r._alloc = b_alloc;
				key_compare		b_comp = this->_comp;
				this->_comp = r._comp;
				r._comp = b_comp;

			}

			bool add_node(node n) {
				n.set_nil(this->_nil);
				if (this->_begin == NULL) {
					this->_begin = this->_alloc.allocate(1);
					this->_alloc.construct(this->_begin, n);
					this->_begin->_color = false;
					this->_begin->_parent->_parent = this->_begin;
				}
				else {
					node *last = this->_search_possion(n._val->first, this->_begin);
					if (last && last->_val->first == n._val->first)
						return false;
					else if (this->_comp(n._val->first, last->_val->first)) {
						last->_left = this->_alloc.allocate(1);
						this->_alloc.construct(last->_left, n);
						last->_left->_parent = last;
						_correct_add_node(last->_left);
					}
					else {
						last->_right = this->_alloc.allocate(1); 
						this->_alloc.construct(last->_right, n);
						last->_right->_parent = last;
						_correct_add_node(last->_right);
					}
				}
				return true;
			}

			pair_value *search_node(key_type k) const {
				node *last = this->_search_possion(k, this->_begin);
				if (last && last->_val->first == k)
					return last->_val;
				return NULL;
			}

			node *search_pair(key_type k) const {
				node *last = this->_search_possion(k, this->_begin);
				if (last && last->_val->first == k)
					return last;
				return NULL;
			}

			ft::pair<node*, bool> lower_bound(key_type k) const {
				node *last = this->_search_possion(k, this->_begin);
				if (last && last->_val->first == k)
					return ft::make_pair(last, false);
				if (!last)
					return ft::make_pair(this->_nil, false);
				if (this->_comp(last->_val->first, k))
					return ft::make_pair(last, true);
				return ft::make_pair(last, false);
			}

			ft::pair<node*, bool> upper_bound(key_type k) const {
				node *last = this->_search_possion(k, this->_begin);
				if (last && last->_val->first == k)
					return ft::make_pair(last, false);
				if (!last)
					return ft::make_pair(this->_nil, false);
				if (this->_comp(k, last->_val->first))
					return ft::make_pair(last, true);
				return ft::make_pair(last, false);
			}

			bool remove_node(key_type k) {
				node *last = this->_search_possion(k, this->_begin);
				if (last != NULL && last->_val->first != k)
					return false;
				
				return this->remove_node_it(last);
				
			}

			bool remove_node_it(node* rm) {

				if (rm == this->_nil || rm == NULL)
					return false;
				bool left = true;
				if(rm->_right == this->_nil && rm->_left == this->_nil && rm->_parent == this->_nil) {
					this->_begin = NULL;
					rm->_parent->_parent = rm->_parent;
					this->_alloc.destroy(rm);
					this->_alloc.deallocate(rm, 1);
					return true;
				}
				// std::cout << "REMOVE_NODE" << std::endl;
				if (rm->_right != this->_nil && rm->_left != this->_nil)
					this->_swap_node(rm, this->_min_node(rm->_right));
				if (rm->_parent == this->_nil) {
					if (rm->_right == this->_nil) 
						this->_begin = rm->_left;
					else 
						this->_begin = rm->_right;
					this->_begin->_parent = rm->_parent;
					rm->_parent->_parent = this->_begin;
					this->_begin->_color = false;
				}
				else {
					if (rm->_parent->_left != rm)
						left = false;
					if (rm->_color == true) {
						if (left)
							rm->_parent->_left = this->_nil;
						else
							rm->_parent->_right = this->_nil;
					}
					else if (rm->_left != this->_nil) {
						if (left)
							rm->_parent->_left = rm->_left;
						else
							rm->_parent->_right = rm->_left;
						rm->_left->_color = false;
						rm->_left->_parent = rm->_parent;
					}
					else if (rm->_right != this->_nil) {
						if (left)
							rm->_parent->_left = rm->_right;
						else
							rm->_parent->_right = rm->_right;
						rm->_right->_color = false;
						rm->_right->_parent = rm->_parent;
					}
					else {
						this->_difficult_removal(rm, left);
						if (rm->_parent->_left == rm)
							rm->_parent->_left = this->_nil;
						else if (rm->_parent->_right == rm)
							rm->_parent->_right = this->_nil;
						else // if (rm->_parent == this->_nil)
							this->_begin = NULL;
					}
				}
				this->_alloc.destroy(rm);
				this->_alloc.deallocate(rm, 1);
				return true;
			}

			pointer nil() const{
				return this->_nil;
			}

			pointer base() const{
				if (this->_begin != NULL)
					return this->_begin;
				return this->_nil;
			}
	};


	template<typename N, class Compare, class Alloc = std::allocator<N> >
	
	class RedBlackTreeSet {
		
		public:
			typedef	N													node;
			typedef Compare												key_compare;
			typedef Alloc												allocator_type;
			typedef typename node::value								value;
			typedef typename allocator_type::reference 					reference;
			typedef typename allocator_type::const_reference 			const_reference;
			typedef typename allocator_type::pointer 					pointer;
			typedef typename allocator_type::const_pointer 				const_pointer;

		private:
			template <typename, typename, typename> friend class set;
			allocator_type	_alloc;
			pointer			_nil;
			pointer			_begin;
			key_compare		_comp;

			void _clear_tree(node *n) {
				if (n->_left != this->_nil) {
					this->_clear_tree(n->_left);
					this->_alloc.destroy(n->_left);
					this->_alloc.deallocate(n->_left, 1);
				}
				if (n->_right != this->_nil) {
					this->_clear_tree(n->_right);
					this->_alloc.destroy(n->_right);
					this->_alloc.deallocate(n->_right, 1);
				}
			}

			void _torn_left(node *n) {
				node *buf;
				buf = n->_right;
				if (n->_right->_left != this->_nil)
					n->_right->_left->_parent = n;
				n->_right->_parent = n->_parent;
				if (n->_parent == this->_nil)
					this->_nil->_parent = n->_right;
				n->_right = n->_right->_left;
				if (n->_parent->_left == n)
					n->_parent->_left = buf;
				else if (n->_parent->_right == n)
					n->_parent->_right = buf;
				buf->_left = n;
				n->_parent = buf;
				if (n == this->_begin)
					this->_begin = n->_parent;
			}

			void _torn_right(node *n) {
				node *buf;
				
				buf = n->_left;
				if (n->_left->_right != this->_nil)
					n->_left->_right->_parent = n;
				n->_left->_parent = n->_parent;
				if (n->_parent == this->_nil)
					this->_nil->_parent = n->_left;
				n->_left = n->_left->_right;
				if (n->_parent->_left == n)
					n->_parent->_left = buf;
				else if (n->_parent->_right == n)
					n->_parent->_right = buf;
				buf->_right = n;
				n->_parent = buf;
				if (n == this->_begin)
					this->_begin = n->_parent;
			}

			void _add_event_n3(node *n, bool left) {
				n->_parent->_color = false;
				if (left)
					n->_parent->_parent->_right->_color = false;
				else 
					n->_parent->_parent->_left->_color = false;
				if (n->_parent->_parent->_parent != this->_nil) {
					n->_parent->_parent->_color = true;
					this->_correct_add_node(n->_parent->_parent);
				}
			}

			void _add_event_n4(node *n, bool left) {
				if (left)
					this->_torn_left(n->_parent);
				else
					this->_torn_right(n->_parent);
				this->_add_event_n5(n->_left, left);
			}

			void _add_event_n5(node *n, bool left) {
				n->_parent->_color = false;
				n->_parent->_parent->_color = true;
				if (left)
					this->_torn_right(n->_parent->_parent);
				else
					this->_torn_left(n->_parent->_parent);

				
			}

			void _correct_add_node(node *n) {
				bool left = true;

				if (n->_parent->_color == false)
					return ;
				if (n->_parent != n->_parent->_parent->_left)
					left = false;
				if ((left && n->_parent->_parent->_right->_color == true) ||
					(!left && n->_parent->_parent->_left->_color == true)) {
						_add_event_n3(n, left);
				}
				else if ((left && n->_parent->_left != n) || (!left && n->_parent->_right != n))
					_add_event_n4(n, left);
				else
					_add_event_n5(n, left);
			}

			node *_search_possion(value key, node *begin) const {
				if (this->_begin == NULL)
					return NULL;
				if  (this->_comp(key, *begin->_val) && begin->_left != this->_nil)
					return (this->_search_possion(key, begin->_left));
				if (key == *begin->_val)
					return begin;
				if (this->_comp(*begin->_val, key) && begin->_right != this->_nil)
					return (this->_search_possion(key, begin->_right));
				return begin;
			}

			node *_max_node(node *begin) const {
				if (begin->_right != this->_nil)
					return this->_max_node(begin->_right);
				return begin;
			}

			node *_min_node(node *begin) const {
				if (begin != NULL && begin->_left != this->_nil)
					return this->_min_node(begin->_left);
				return begin;
			}

			void _swap_node(node *n1, node *n2) {
				node *buf;
				bool col_buf;
				int close = 0;

				if (n2 == n1->_left)
					close = 1;
				else if (n2 == n1->_right)
					close = 2;
				if (n1->_parent == this->_nil) {
					this->_nil->_parent = n2;
					this->_begin = n2;
				}
				else {
					if (n1 == n1->_parent->_right)
						n1->_parent->_right = n2;
					else 
						n1->_parent->_left = n2;
				}
				if (n2 == n2->_parent->_right && close != 2)
						n2->_parent->_right = n1;
				else if (n2 == n2->_parent->_left && close != 1)
					n2->_parent->_left = n1;
				buf = n1->_parent;
				if (close == 0)
					n1->_parent = n2->_parent;
				else 
					n1->_parent = n2;
				n2->_parent = buf;

				if (n1->_left != this->_nil && close != 1)
					n1->_left->_parent = n2;
				if (n2->_left != this->_nil)
					n2->_left->_parent = n1;
				buf = n1->_left;
				n1->_left = n2->_left;
				if (close != 1)
					n2->_left = buf;
				else
					n2->_left = n1;

				if (n1->_right != this->_nil && close != 2)
					n1->_right->_parent = n2;
				if (n2->_right != this->_nil)
					n2->_right->_parent = n1;
				buf = n1->_right;
				n1->_right = n2->_right;
				if (close != 2)
					n2->_right = buf;
				else
					n2->_right = n1;

				col_buf = n1->_color;
				n1->_color = n2->_color;
				n2->_color = col_buf;
			}

			void _remove_event_n2(node *n, bool left) {
				n->_parent->_color = true;
				if (left) {
					n->_parent->_right->_color =false;
					this->_torn_left(n->_parent);
				}
				else {
					n->_parent->_left->_color =false;
					this->_torn_right(n->_parent);
				}
			};

			void _remove_event_n3(node *n, bool left) {
				if (left)
					n->_parent->_right->_color = true;
				else
					n->_parent->_left->_color = true;
				left = true;
				if (n->_parent->_parent->_left != n->_parent)
					left = false;
				this->_difficult_removal(n->_parent, left);
			};

			void _remove_event_n4(node *n, bool left) {
				n->_parent->_color = false;
				if (left)
					n->_parent->_right->_color =true;
				else
					n->_parent->_left->_color =true;
			};

			void _remove_event_n5(node *n, bool left) {
				if (left) {
					n->_parent->_right->_left->_color = false;
					n->_parent->_right->_color = true;
					this->_torn_right(n->_parent->_right);
				}
				else {
					n->_parent->_left->_right->_color = false;
					n->_parent->_left->_color = true;
					this->_torn_left(n->_parent->_left);
				}
			};

			void _remove_event_n6(node *n, bool left) {
				bool buf;
				if (left) {
					n->_parent->_right->_right->_color = false;
					buf = n->_parent->_color;
					n->_parent->_color = n->_parent->_right->_color;
					n->_parent->_right->_color = buf;
					this->_torn_left(n->_parent);
				}
				else {
					n->_parent->_left->_left->_color = false;
					buf = n->_parent->_color;
					n->_parent->_color = n->_parent->_left->_color;
					n->_parent->_left->_color = buf;
					this->_torn_right(n->_parent);
				}
			};


			void _difficult_removal(node *n, bool left) {
				if (n->_parent == this->_nil)
					return ;
				if ((left && n->_parent->_right->_color) || (!left && n->_parent->_left->_color) ) 
					this->_remove_event_n2(n, left);
				if ((left && !n->_parent->_color && !n->_parent->_right->_color && !n->_parent->_right->_left->_color && !n->_parent->_right->_right->_color) ||
						(!left && !n->_parent->_color && !n->_parent->_left->_color && !n->_parent->_left->_left->_color && !n->_parent->_left->_right->_color)) {
							this->_remove_event_n3(n, left);
							return ;
				}
				if ((left && n->_parent->_color && !n->_parent->_right->_color && !n->_parent->_right->_left->_color && !n->_parent->_right->_right->_color) ||
						(!left && n->_parent->_color && !n->_parent->_left->_color && !n->_parent->_left->_left->_color && !n->_parent->_left->_right->_color)) {
							this->_remove_event_n4(n, left);
							return ;
				}
				if ((left && !n->_parent->_right->_color && n->_parent->_right->_left->_color && !n->_parent->_right->_right->_color) ||
						(!left && !n->_parent->_left->_color && !n->_parent->_left->_left->_color && n->_parent->_left->_right->_color)) {
							this->_remove_event_n5(n, left);
				}
				if ((left && !n->_parent->_right->_color && !n->_parent->_right->_left->_color && n->_parent->_right->_right->_color) ||
						(!left && !n->_parent->_left->_color && n->_parent->_left->_left->_color && !n->_parent->_left->_right->_color)) {
							this->_remove_event_n6(n, left);
				}
			}

			void _clear() {
				if (this->_begin != NULL) {
					this->_clear_tree(this->_begin);
					this->_alloc.destroy(this->_begin);
					this->_alloc.deallocate(this->_begin, 1);
					this->_begin = NULL;
				}
			}

		public:
			RedBlackTreeSet(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _comp(comp) {
				this->_nil = this->_alloc.allocate(1);
				this->_alloc.construct(this->_nil, node());
				this->_begin = NULL;
				this->_nil->set_nil(this->_nil);
			}

			~RedBlackTreeSet() {
				if (this->_begin != NULL) {
					this->_clear_tree(this->_begin);
					this->_alloc.destroy(this->_begin);
					this->_alloc.deallocate(this->_begin, 1);
				}
				this->_alloc.destroy(this->_nil);
				this->_alloc.deallocate(this->_nil, 1);
			}

			RedBlackTreeSet& operator= (const RedBlackTreeSet& x) {
				this->_alloc = x._alloc;
				this->_comp = x._comp;
				if (this->_begin != NULL)
				{
					this->_clear_tree(this->_begin);
					this->_alloc.destroy(this->_begin);
					this->_alloc.deallocate(this->_begin, 1);
					this->_begin = NULL;
				}
				node *buf = x._min_node(x._begin);
				while(buf != NULL && buf != x._nil) {
					this->add_node(*buf);
					if (buf->_right != x._nil) {
						buf = x._min_node(buf->_right);
					}
					else {
						bool left = true;
						while(left) {
							if (buf->_parent == x._nil || buf->_parent->_left == buf) {
								left = false;
							}
							buf = buf->_parent;
						}
					}
				}				
				return *this;
			}

			size_t max_size() const {
				return this->_alloc.max_size();
			}

			void swap_rbt(RedBlackTreeSet &r) {
				pointer buf = this->_begin;
				this->_begin = r._begin;
				r._begin = buf;
				buf = this->_nil;
				this->_nil = r._nil;
				r._nil = buf;
				allocator_type	b_alloc = this->_alloc;
				this->_alloc = r._alloc;
				r._alloc = b_alloc;
				key_compare		b_comp = this->_comp;
				this->_comp = r._comp;
				r._comp = b_comp;

			}

			bool add_node(node n) {
				n.set_nil(this->_nil);
				if (this->_begin == NULL) {
					this->_begin = this->_alloc.allocate(1);
					this->_alloc.construct(this->_begin, n);
					this->_begin->_color = false;
					this->_begin->_parent->_parent = this->_begin;
				}
				else {
					node *last = this->_search_possion(*n._val, this->_begin);
					if (last && *last->_val == *n._val)
						return false;
					else if (this->_comp(*n._val, *last->_val)) {
						last->_left = this->_alloc.allocate(1);
						this->_alloc.construct(last->_left, n);
						last->_left->_parent = last;
						_correct_add_node(last->_left);
					}
					else {
						last->_right = this->_alloc.allocate(1); 
						this->_alloc.construct(last->_right, n);
						last->_right->_parent = last;
						_correct_add_node(last->_right);
					}
				}
				return true;
			}

			value *search_node(value k) const {
				node *last = this->_search_possion(k, this->_begin);
				if (last && *last->_val == k)
					return last->_val;
				return NULL;
			}

			node *search_pair(value k) const {
				node *last = this->_search_possion(k, this->_begin);
				if (last && *last->_val == k)
					return last;
				return NULL;
			}

			ft::pair<node*, bool> lower_bound(value k) const {
				node *last = this->_search_possion(k, this->_begin);
				if (last && *last->_val == k)
					return ft::make_pair(last, false);
				if (!last)
					return ft::make_pair(this->_nil, false);
				if (this->_comp(*last->_val, k))
					return ft::make_pair(last, true);
				return ft::make_pair(last, false);
			}

			ft::pair<node*, bool> upper_bound(value k) const {
				node *last = this->_search_possion(k, this->_begin);
				if (last && *last->_val == k)
					return ft::make_pair(last, false);
				if (!last)
					return ft::make_pair(this->_nil, false);
				if (this->_comp(k, *last->_val))
					return ft::make_pair(last, true);
				return ft::make_pair(last, false);
			}

			bool remove_node(value k) {
				node *last = this->_search_possion(k, this->_begin);
				if (last != NULL && *last->_val != k)
					return false;
				
				return this->remove_node_it(last);
				
			}

			bool remove_node_it(node* rm) {
				if (rm == this->_nil || rm == NULL)
					return false;
				bool left = true;
				if(rm->_right == this->_nil && rm->_left == this->_nil && rm->_parent == this->_nil) {
					this->_begin = NULL;
					rm->_parent->_parent = rm->_parent;
					this->_alloc.destroy(rm);
					this->_alloc.deallocate(rm, 1);
					return true;
				}
				if (rm->_right != this->_nil && rm->_left != this->_nil)
					this->_swap_node(rm, this->_min_node(rm->_right));
				if (rm->_parent == this->_nil) {
					if (rm->_right == this->_nil) 
						this->_begin = rm->_left;
					else 
						this->_begin = rm->_right;
					this->_begin->_parent = rm->_parent;
					rm->_parent->_parent = this->_begin;
					this->_begin->_color = false;
				}
				else {
					if (rm->_parent->_left != rm)
						left = false;
					if (rm->_color == true) {
						if (left)
							rm->_parent->_left = this->_nil;
						else
							rm->_parent->_right = this->_nil;
					}
					else if (rm->_left != this->_nil) {
						if (left)
							rm->_parent->_left = rm->_left;
						else
							rm->_parent->_right = rm->_left;
						rm->_left->_color = false;
						rm->_left->_parent = rm->_parent;
					}
					else if (rm->_right != this->_nil) {
						if (left)
							rm->_parent->_left = rm->_right;
						else
							rm->_parent->_right = rm->_right;
						rm->_right->_color = false;
						rm->_right->_parent = rm->_parent;
					}
					else {
						this->_difficult_removal(rm, left);
						if (rm->_parent->_left == rm)
							rm->_parent->_left = this->_nil;
						else if (rm->_parent->_right == rm)
							rm->_parent->_right = this->_nil;
						else // if (rm->_parent == this->_nil)
							this->_begin = NULL;
					}
				}
				this->_alloc.destroy(rm);
				this->_alloc.deallocate(rm, 1);
				return true;
			}

			pointer nil() const{
				return this->_nil;
			}

			pointer base() const{
				if (this->_begin != NULL)
					return this->_begin;
				return this->_nil;
			}
	};

}

#endif