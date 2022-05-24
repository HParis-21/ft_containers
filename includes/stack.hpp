#ifndef STACK_HPP
# define STACK_HPP

#include <deque>
#include "vector.hpp"

namespace ft {

	template <class T, class Container = vector<T> >
	class stack {
		public:
			typedef T									value_type;
			typedef Container							container_type;
			typedef typename container_type::size_type	size_type;

		private:
			container_type	_ctnr;

		public:

    //////////////////////////////
    // Member functions
    //////////////////////////////

			explicit stack (const container_type& ctnr = container_type()) { this->_ctnr = ctnr;}

			bool empty() const {return _ctnr.empty();}

			size_type size() const {return _ctnr.size();}

			value_type& top() {return _ctnr.back();}

			const value_type& top() const {return _ctnr.back();}

			void push (const value_type& val) {_ctnr.push_back(val);}

			void pop() {_ctnr.pop_back();}


//	template <class value_type, class container_type>
// 	friend bool operator== (const stack<value_type,container_type>& lhs, const stack<value_type,container_type>& rhs);
//
//	template <class value_type, class container_type>
// 	friend bool operator!= (const stack<value_type,container_type>& lhs, const stack<value_type,container_type>& rhs);
//
//	template <class value_type, class container_type>
// 	friend bool operator< (const stack<value_type,container_type>& lhs, const stack<value_type,container_type>& rhs);
//
//	template <class value_type, class container_type>
// 	friend bool operator> (const stack<value_type,container_type>& lhs, const stack<value_type,container_type>& rhs);
//
//	template <class value_type, class container_type>
// 	friend bool operator<= (const stack<value_type,container_type>& lhs, const stack<value_type,container_type>& rhs);
//
//	template <class value_type, class container_type>
// 	friend bool operator>= (const stack<value_type,container_type>& lhs, const stack<value_type,container_type>& rhs);

	};
    //////////////////////////////
    // Relational operators
    //////////////////////////////

	template <class T, class Container>
 	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		 return lhs._ctnr == rhs._ctnr;
	}

	template <class T, class Container>
 	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		 return lhs._ctnr != rhs._ctnr;
	}

	template <class T, class Container>
 	bool operator< (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		 return lhs._ctnr < rhs._ctnr;
	}

	template <class T, class Container>
 	bool operator> (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		 return lhs._ctnr > rhs._ctnr;
	}

	template <class T, class Container>
 	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		 return lhs._ctnr <= rhs._ctnr;
	}

	template <class T, class Container>
 	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		 return lhs._ctnr >= rhs._ctnr;
	}

}

#endif