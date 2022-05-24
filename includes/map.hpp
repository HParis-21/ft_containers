#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include "iterators.hpp"
# include "RedBlackTree.hpp"

namespace ft {

	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key,T> > >
	class map {
		public:
			typedef Key													key_type;
			typedef T													mapped_type;
			typedef ft::pair<const key_type,mapped_type>				value_type;
			typedef Compare												key_compare;
			typedef Alloc												allocator_type;
			typedef typename allocator_type::reference 					reference;
			typedef typename allocator_type::const_reference 			const_reference;
			typedef typename allocator_type::pointer 					pointer;
			typedef typename allocator_type::const_pointer 				const_pointer;
			typedef ft::Node<value_type, allocator_type>				node;
			typedef ft::MapIterator<node>								iterator;
			typedef ft::MapConstIterator<node>							const_iterator;
			typedef ft::reverse_iterator<iterator>						reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;
			typedef typename iterator_traits<iterator>::difference_type	difference_type;
			typedef size_t												size_type;
			typedef typename ft::RedBlackTree<node, key_compare>		RBT;



			class value_compare {
				friend class map;
				protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {}
				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator() (const value_type& x, const value_type& y) const {
						return comp(x.first, y.first);
					}
			};

		private:
			allocator_type			_alloc;
			key_compare				_comp;
			RBT						_rbt;
			size_type				_size;

		public:

    //////////////////////////////
    // Constructors
    //////////////////////////////

			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _comp(comp), _size(0) {
			};


			template <class InputIterator>
  			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0) : _alloc(alloc), _comp(comp) , _rbt(comp){
				this->insert(first, last);
			}

			
			map (const map& x) {    *this = x;  }
    //////////////////////////////
    // Destructors
    //////////////////////////////

			~map() {};

    //////////////////////////////
    // Assignment operator
    //////////////////////////////

			map& operator= (const map& x) {
				if (this == &x) {
					return *this;
				}
				this->_alloc = x._alloc;
				this->_comp = x._comp;
				this->_size = 0;
				this->_rbt._clear();
				iterator first(x.begin());
				iterator second(x.end());
				for(;first != second; ++first) {
					this->insert(*first);
				}
				return *this;
			

			}
			
		//construct -END

    //////////////////////////////
    // Iterators
    //////////////////////////////

			iterator begin() {
				return this->_rbt._min_node(this->_rbt.base());
			}

			iterator begin() const {
				return this->_rbt._min_node(this->_rbt.base());
			}

			iterator end() {
				return (this->_rbt.nil());
			}

			iterator end() const{
				return (this->_rbt.nil());
			}

    //////////////////////////////
    // Reverse iterators
    //////////////////////////////

			reverse_iterator rbegin() {
				return reverse_iterator(this->end());
			}

			const_reverse_iterator rbegin() const{
				return reverse_iterator(this->end());
			}

			reverse_iterator rend() {
				return reverse_iterator(this->begin());
			}

			const_reverse_iterator rend() const{
				return reverse_iterator(this->begin());
			}


    //////////////////////////////
    // Capacity
    //////////////////////////////

			bool empty () const {
				return !this->_size;
			}

			size_type size() const {
				return this->_size;
			}

			size_type max_size() const {
				return this->_rbt.max_size();
			}


		//Element access:

			mapped_type& operator[] (const key_type& k) {
			// 	value_type *p = this->_rbt.search_node(k);
			// 	if (p)
			// 		return p->second;
			// 	this->insert(value_type(k, key_type()));
			// 	return this->_rbt.search_node(k)->second;
				return (*insert(ft::make_pair(k, mapped_type())).first).second;
			}

			

    //////////////////////////////
    //Modifiers:
    //////////////////////////////

			pair<iterator,bool> insert (const value_type& val) {
				bool ret = false;
				if (this->_rbt.add_node(val)) {
					this->_size++;
					ret = true;
				}
				return(ft::make_pair(iterator(this->_rbt._search_possion(val.first, this->_rbt.base())),ret));
			}

			iterator insert (iterator position, const value_type& val) {
				position = this->insert(val).first;
				return position;
			}

			template <class InputIterator>
			void insert (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0) {
				for (;first != last; ++first) {
					this->insert(*first);
				}
			}

			void erase (iterator position) {
				if (this->_rbt.remove_node_it(position._p))
					this->_size--;
			}

			size_type erase (const key_type& k) {
				if (this->_rbt.remove_node(k)) {
					this->_size--;
					return 1;
				}
				return 0;
			}

			void erase (iterator first, iterator last) {
				iterator buf(first);
				++first;
				while (first != last) {
					this->erase(first);
					first = buf;
					++first;
				}
				this->erase(buf);
				// this->erase(last);
			}

			void swap (map& x) {
				if (this == &x)
					return ;
				key_compare	buf_c;
				size_type buf_s;
				buf_c = this->_comp;
				buf_s = this->_size;
				this->_comp = x._comp;
				this->_size = x._size;
				x._comp = buf_c;
				x._size = buf_s;
				this->_rbt.swap_rbt(x._rbt);
			}

			void clear() {
				this->_rbt._clear();
				this->_size = 0;
			}


    //////////////////////////////
    // Observers
    //////////////////////////////

		key_compare key_comp() const {
			return this->_comp;
		}

		value_compare value_comp() const {
			return value_compare(_comp);
		}

    //////////////////////////////
	//Operations:
    //////////////////////////////

		iterator find (const key_type& k) {
			node *p = this->_rbt.search_pair(k);
			if (p)
				return p;
			return this->end();
		}

		const_iterator find (const key_type& k) const {
			node *p = this->_rbt.search_pair(k);
			if (p)
				return p;
			return this->end();
		}

		size_type count (const key_type& k) const {
			if (this->_rbt.search_node(k))
				return 1;
			return 0;
		}

    //////////////////////////////
    // Bound operations
    //////////////////////////////

		iterator lower_bound (const key_type& k) {
			pair<node*, bool> p = this->_rbt.lower_bound(k);
			iterator it(p.first);
			if (p.second)
				++it;
			return it;
		}

		const_iterator lower_bound (const key_type& k) const {
			return this->_rbt.lower_bound(k);
		}

		iterator upper_bound (const key_type& k) {
			pair<node*, bool> p = this->_rbt.upper_bound(k);
			iterator it(p.first);
			if (p.second == false)
				++it;
			return it;
		}

		const_iterator upper_bound (const key_type& k) const {
			iterator it(this->_rbt.lower_bound(k));
			if (this->_rbt.search_pair(k) != NULL)
				it++;
			return it;
		}

		pair<const_iterator,const_iterator> equal_range (const key_type& k) const {
			iterator it_l(this->lower_bound(k));
			iterator it_u(this->upper_bound(k));
				
			return(ft::make_pair(it_l, it_u));
		}

		pair<iterator,iterator>	equal_range (const key_type& k) {
			iterator it_l(this->lower_bound(k));
			iterator it_u(this->upper_bound(k));
				
			return(ft::make_pair(it_l, it_u));
		}

    //////////////////////////////
    // Allocator
    //////////////////////////////

		allocator_type get_allocator() const {
			return this->_alloc;
		}
			
	};

    //////////////////////////////
    // Relational operators
    //////////////////////////////

	template< class Key, class T, class Compare, class Alloc >
	bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
		if (lhs.size() != rhs.size())
			return false;
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
		return !(lhs == rhs);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
		return !(rhs < lhs);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
		return !(lhs <= rhs);
	}


	template< class Key, class T, class Compare, class Alloc >
	bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
		return !(lhs < rhs);
	}

	}

#endif