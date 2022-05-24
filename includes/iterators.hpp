#ifndef ITERATORS_HPP
# define ITERATORS_HPP

#include <cstddef>
#include <iterator>


namespace ft {
	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	class iterator {
		public:
			typedef T			value_type;
			typedef Distance	difference_type;
			typedef Pointer		pointer;
			typedef Reference	reference;
			typedef Category	iterator_category;	
	};
	
	template <class Iterator>
	class iterator_traits {
		public:
			typedef typename Iterator::difference_type		difference_type;
			typedef typename Iterator::value_type			value_type;
			typedef typename Iterator::pointer				pointer;
			typedef typename Iterator::reference			reference;
			typedef typename Iterator::iterator_category	iterator_category;
	};

	template <class T>
	class iterator_traits<T*> {
		public:
			typedef std::ptrdiff_t					difference_type;
			typedef T								value_type;
			typedef T*								pointer;
			typedef T&								reference;
			typedef std::random_access_iterator_tag	iterator_category;
			
	};

	template <class T>
	class iterator_traits<const T*> {
		public:
			typedef std::ptrdiff_t					difference_type;
			typedef T								value_type;
			typedef const T*						pointer;
			typedef const T&						reference;
			typedef std::random_access_iterator_tag	iterator_category;
	};
	

	//----------reverse_iterator-------------//
	template <class Iterator> 
	class reverse_iterator {
		public:
			typedef Iterator												iterator_type;
			typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iterator>::value_type			value_type;
			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename iterator_traits<Iterator>::pointer				pointer;
			typedef typename iterator_traits<Iterator>::reference			reference;

		private:
			iterator_type	_it;

		public:
			reverse_iterator() {
			};

			explicit reverse_iterator (iterator_type it) {
				this->_it = it;
			};
			
  			template <class Iter>
  			reverse_iterator (const reverse_iterator<Iter>& rev_it) {
				this->_it = rev_it.base();
			};

			iterator_type base () const {
				return this->_it;
			}

			reference operator*() const {
				reverse_iterator temp = *this;
				temp++;
				iterator_type it = temp._it;
				return it.operator*();
			}

			reverse_iterator operator+(difference_type n) const {
				reverse_iterator ret(this->_it - n);
				return ret;
			}

			reverse_iterator& operator++() {
				this->_it--;
				return *this;
			}

			reverse_iterator operator++(int) {
				reverse_iterator temp = *this;
				++(*this);
				return temp;
			}

			reverse_iterator& operator+= (difference_type n) {
				this->_it -= n;
				return *this;
			}

			reverse_iterator operator-(difference_type n) const {
				reverse_iterator ret(this->_it + n);
				return ret;
			}

			reverse_iterator& operator--() {
				this->_it++;
				return *this;
			}

			reverse_iterator operator--(int) {
				reverse_iterator temp = *this;
				--(*this);
				return temp;
			}

			reverse_iterator& operator-= (difference_type n) {
				this->_it += n;
				return *this;
			}

			pointer operator->() const {
  				return &(operator*());
			}

			reference operator[] (difference_type n) const {
				return *(this->_it - 1 - n);
			}
	};

	template<class Iterator>
	bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return lhs.base() == rhs.base();
	}

	template<class Iterator>
	bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return lhs.base() != rhs.base();
	}

	template<class Iterator>
	bool operator< (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return lhs.base() > rhs.base();
	}

	template<class Iterator>
	bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return lhs.base() >= rhs.base();
	}

	template<class Iterator>
	bool operator> (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return lhs.base() < rhs.base();
	}

	template<class Iterator>
	bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return lhs.base() <= rhs.base();
	}

	template<class Iterator>
	reverse_iterator<Iterator> operator+ ( typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it) {
		return (rev_it + n);
	}

	template<class Iterator>
	reverse_iterator<Iterator> operator- ( typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it) {
		return (rev_it - n);
	}
	//----------reverse_iterator-------------//
	


	//----------enable_if-------------//
	template<bool Cond, class T = void>
	struct enable_if {};
	
	template<class T>
	struct enable_if<true, T> { typedef T type; };
	//----------enable_if-------------//

	//----------is_integral-------------//
	template <typename T>
    struct is_integral : public std::integral_constant<bool, false> {};

    template <>
    struct is_integral<bool> : public std::integral_constant<bool, true> {};
        
    template <>
    struct is_integral<char> : public std::integral_constant<bool, true> {};

    template <>
    struct is_integral<short> : public std::integral_constant<bool, true> {};

    template <>
    struct is_integral<int> : public std::integral_constant<bool, true> {};

    template <>
    struct is_integral<long> : public std::integral_constant<bool, true> {};

    template <>
    struct is_integral<long long> : public std::integral_constant<bool, true> {};

    template <>
    struct is_integral<signed char> : public std::integral_constant<bool, true> {};

	template <>
    struct is_integral<wchar_t> : public std::integral_constant<bool, true> {};

	template <>
    struct is_integral<char16_t> : public std::integral_constant<bool, true> {};

	template <>
    struct is_integral<unsigned char> : public std::integral_constant<bool, true> {};

    template <>
    struct is_integral<unsigned short> : public std::integral_constant<bool, true> {};

    template <>
    struct is_integral<unsigned int> : public std::integral_constant<bool, true> {};

    template <>
    struct is_integral<unsigned long> : public std::integral_constant<bool, true> {};

    template <>
    struct is_integral<unsigned long long> : public std::integral_constant<bool, true> {};
	//----------is_integral-------------//

	//----------equal-------------//
	template <class InputIterator1, class InputIterator2>
	bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )	{
		while (first1!=last1) {
			if (!(*first1 == *first2))
				return false;
			++first1; ++first2;
		}
		return true;
	}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred) {
		while (first1!=last1) {
			if (!pred(*first1,*first2))
    			return false;
			++first1; ++first2;
		}
		return true;
	}
	//----------equal-------------//

	//----------lexicographical_compare-------------//
	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2) {
		while (first1!=last1) {
			if (first2==last2 || *first2<*first1)
				return false;
			else if (*first1<*first2)
				return true;
			++first1; ++first2;
		}
		return (first2!=last2);
	}

	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp) {
		while (first1!=last1) {
			if (first2==last2 || comp(*first2, *first1))
				return false;
			else if (comp(*first1, *first2))
				return true;
			++first1; ++first2;
		}
		return (first2!=last2);
	}
//----------lexicographical_compare-------------//

//----------pair-------------//
	template <class T1, class T2>
	class pair {
		public:
			typedef T1	first_type;
			typedef T2	second_type;

			first_type	first;
			second_type	second;
		
			pair() :first(), second() {};

			template<class U, class V>
			pair (const pair<U,V>& pr) :first(pr.first), second(pr.second) {}

			pair (const first_type& a, const second_type& b) :first(a), second(b) {}

			pair& operator= (const pair& pr) {
				if (this == &pr)
					return *this;
				this->first = pr.first;
				this->second = pr.second;
				return *this;
			}
	};

	template <class T1, class T2>
	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return lhs.first==rhs.first && lhs.second==rhs.second;
	}

	template <class T1, class T2>
	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return !(lhs==rhs);
	}

	template <class T1, class T2>
	bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second);
	}

	template <class T1, class T2>
	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return !(rhs<lhs);
	}

	template <class T1, class T2>
	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return rhs<lhs;
	}

	template <class T1, class T2>
	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return !(lhs<rhs); 
	}

	template <class T1,class T2>
	pair<T1,T2> make_pair (T1 x, T2 y) {
    	return ( pair<T1,T2>(x,y) );
	}
//----------pair-------------//

//----------VectorIterator-------------//

	template <typename T>
	class VectorIterator : public ft::iterator<std::random_access_iterator_tag, T> {
		public:
			typedef T																						value_type;
			typedef typename ft::iterator<std::random_access_iterator_tag, value_type>::pointer				pointer;
			typedef typename ft::iterator<std::random_access_iterator_tag, value_type>::difference_type		difference_type;
			typedef typename ft::iterator<std::random_access_iterator_tag, value_type>::reference			reference;
			typedef value_type																				*iterator_type;

		private:
			template <typename, typename> friend class vector;
			pointer _p;

			VectorIterator(pointer x) {
				this->_p = x;
			};

		public:

			VectorIterator() {};

			VectorIterator(const VectorIterator& vec) {
				this->_p = vec.base();
			}

			~VectorIterator() {};

			VectorIterator& operator=(const VectorIterator &vec){
				this->_p = vec.base();
				return *this;
			}

			pointer base() {
				return this->_p;
			}

			pointer base() const {
				return this->_p;
			}

			reference operator*() const {
				return *(this->_p);
			}

			VectorIterator operator+(difference_type n) const {
				VectorIterator ret(this->_p + n);
				return ret;
			}

			VectorIterator& operator++() {
				++(this->_p);
				return *this;
			};

  			VectorIterator operator++(int) {
				VectorIterator tmp(*this);
				++(*this);
				return tmp;
			}

			VectorIterator& operator+= (difference_type n) {
				this->_p += n;
				return *this;
			}

			VectorIterator operator-(difference_type n) const {
				return this->_p - n;
			}

			VectorIterator& operator--() {
				--(this->_p);
				return *this;
			};

  			VectorIterator operator--(int) {
				VectorIterator tmp(*this);
				--(*this);
				return tmp;
			}

			VectorIterator& operator-= (difference_type n) {
				this->_p -= n;
				return *this;
			}

			pointer operator->() const {
  				return &(operator*());
			}

			reference operator[] (difference_type n) const {
				return *(this->_p + n);
			}

			bool operator==(const VectorIterator& rhs) const { 
				return this->_p==rhs.base();
			}

			bool operator!=(const VectorIterator& rhs) const { 
				return !(*this==rhs);
			}

			bool operator<(const VectorIterator& rhs) const { 
				return this->_p<rhs.base();
			}

			bool operator<=(const VectorIterator& rhs) const { 
				return this->_p<=rhs.base();
			}

			bool operator>(const VectorIterator& rhs) const { 
				return this->_p>rhs.base();
			}

			bool operator>=(const VectorIterator& rhs) const { 
				return this->_p>=rhs.base();
			}

			friend VectorIterator<value_type> operator+ ( typename VectorIterator<value_type>::difference_type n, const VectorIterator<value_type>& it) {
				return (it + n);
			}

			friend typename VectorIterator<value_type>::difference_type operator- ( const VectorIterator<value_type>& it1, const VectorIterator<value_type>& it2) {
				return (it1.base() - it2.base());
			}
	};
//----------VectorIterator-------------//

//----------VectorIterator-------------//

	template <typename T>
	class VectorIteratorConst : public ft::iterator<std::random_access_iterator_tag, const T> {

		public:
			typedef T																								value_type;
			typedef typename ft::iterator<std::random_access_iterator_tag, const value_type>::pointer				pointer;
			typedef typename ft::iterator<std::random_access_iterator_tag, const value_type>::difference_type		difference_type;
			typedef typename ft::iterator<std::random_access_iterator_tag, const value_type>::reference				reference;

		private:
			template <typename, typename> friend class vector;
			pointer _p;

			VectorIteratorConst(pointer x) {
				this->_p = x;
			};

			template <typename iter>
			struct is_iter : public std::integral_constant<bool, false> {};

			template <>
			struct is_iter<VectorIterator<value_type> > : public std::integral_constant<bool, true> {};

		public:

			VectorIteratorConst() {};

			VectorIteratorConst(const VectorIteratorConst& vec) {
				this->_p = vec.base();
			}

			template <typename S>
			VectorIteratorConst(const S& vec, typename ft::enable_if<is_iter<S>::value >::type* = 0) {
				this->_p = vec.base();
			}

			~VectorIteratorConst() {};


			VectorIteratorConst& operator=(const VectorIteratorConst &vec){
				this->_p = vec.base();
				return *this;
			}

			// VectorIteratorConst& operator=(const VectorIterator &vec) {
			// 	this->_p = vec.base();
			// 	return *this;
			// }

			pointer base() {
				return this->_p;
			}

			pointer base() const {
				return this->_p;
			}

			reference operator*() const{
				return *(this->_p);
			}

			VectorIteratorConst operator+(difference_type n) const {
				return (this->_p + n);
			}

			VectorIteratorConst& operator++() {
				++(this->_p);
				return *this;
			};

  			VectorIteratorConst operator++(int) {
				VectorIteratorConst tmp(*this);
				++(*this);
				return tmp;
			}

			VectorIteratorConst& operator+= (difference_type n) {
				this->_p += n;
				return *this;
			}

			VectorIteratorConst operator-(difference_type n) const {
				return (this->_p - n);
			}

			VectorIteratorConst& operator--() {
				--(this->_p);
				return *this;
			};

  			VectorIteratorConst operator--(int) {
				VectorIteratorConst tmp(*this);
				--(*this);
				return tmp;
			}

			VectorIteratorConst& operator-= (difference_type n) {
				this->_p -= n;
				return *this;
			}

			pointer operator->() const {
  				return &(operator*());
			}

			reference operator[] (difference_type n) const {
				return *(this->_p + n);
			}

			bool operator==(const VectorIteratorConst& rhs) const { 
				return this->_p==rhs.base();
			}

			bool operator!=(const VectorIteratorConst& rhs) const { 
				return !(*this==rhs);
			}

			bool operator<(const VectorIteratorConst& rhs) const { 
				return this->_p<rhs.base();
			}

			bool operator<=(const VectorIteratorConst& rhs) const { 
				return this->_p<=rhs.base();
			}

			bool operator>(const VectorIteratorConst& rhs) const { 
				return this->_p>rhs.base();
			}

			bool operator>=(const VectorIteratorConst& rhs) const { 
				return this->_p>=rhs.base();
			}

			friend VectorIteratorConst<value_type> operator+ ( typename VectorIteratorConst<value_type>::difference_type n, const VectorIteratorConst<value_type>& it) {
				return (it + n);
			}

			friend typename VectorIteratorConst<value_type>::difference_type operator- ( const VectorIteratorConst<value_type>& it1, const VectorIteratorConst<value_type>& it2) {
				return (it1.base() - it2.base());
			}


	};

//----------VectorIterator-------------//


//----------MapIterator-------------//
	template <typename T>
	class MapIterator : public ft::iterator<std::bidirectional_iterator_tag, T> {
		public:
			typedef T																				value_type;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::pointer				pointer_node;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::difference_type		difference_type;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::reference			reference_node;
			typedef typename value_type::value													pair_value;	
			typedef pair_value 																		&reference;
			typedef pair_value 																		*pointer;

		private:
			template <typename, typename, typename, typename> friend class map;
			template <typename, typename, typename> friend class set;
			template <typename> friend class MapConstIterator;
			pointer_node _p;

			MapIterator(pointer_node x) {
				this->_p = x;
			};

		public:

			MapIterator() {};

			MapIterator(const MapIterator& vec) {
				this->_p = vec._p;
			}

			~MapIterator() {};

			MapIterator& operator=(const MapIterator &vec){
				if (this == &vec)
					return *this;
				this->_p = vec._p;
				return *this;
			}

			// pointer base() {
			// 	return this->_p;
			// }

			// pointer base() const {
			// 	return this->_p;
			// }


			MapIterator& operator++() {
				bool left = true;
				// if (this->_p == this->_p->_left){
				// 	MapIterator it;
				// 	it++;
				// }
				if (this->_p == this->_p->_right->_parent && this->_p->_right !=this->_p->_parent ) {
					this->_p =  this->_p->_right;
					while(this->_p == this->_p->_left->_parent)
						this->_p = this->_p->_left;
				}
				else {
					while (left) {
						if (this->_p != this->_p->_parent->_right)
							left = false;
						this->_p = this->_p->_parent;
					}
				}
				return *this;
			};

  			MapIterator operator++(int) {
				MapIterator tmp(*this);
				++(*this);
				return tmp;
			}

			MapIterator& operator--() {
				// std::cout << std::endl << "ITER--" << std::endl;
				bool left = true;
				if (this->_p == this->_p->_left) {
					this->_p = this->_p->_parent;
					while(this->_p == this->_p->_right->_parent && this->_p->_right !=this->_p->_parent)
						this->_p = this->_p->_right;
				}
				else if (this->_p == this->_p->_left->_parent) {
					this->_p =  this->_p->_left;
					while(this->_p == this->_p->_right->_parent)
						this->_p = this->_p->_right;
				}
				else {
					while (left) {
						if (this->_p != this->_p->_parent->_left)
							left = false;
						this->_p = this->_p->_parent;
					}
				}
				// if (this->_p == this->_p->_left){
				// 	MapIterator it;
				// 	it--;
				// }
				// std::cout << std::endl << "!!!--" << std::endl;
				return *this;
			};

  			MapIterator operator--(int) {
				MapIterator tmp(*this);
				--(*this);
				return tmp;
			}
			
			pair_value &operator*() const {
				return *(this->_p->_val);
			}

			pair_value *operator->() const {
				return (this->_p->_val);
			}

			bool operator==(const MapIterator& rhs) const { 
				return this->_p==rhs._p;
			}

			bool operator!=(const MapIterator& rhs) const { 
				return !(*this==rhs);
			}

			bool operator<(const MapIterator& rhs) const { 
				return this->_p < rhs._p;
			}

			bool operator<=(const MapIterator& rhs) const { 
				return this->_p <= rhs._p;
			}

			bool operator>(const MapIterator& rhs) const { 
				return this->_p > rhs._p;
			}

			bool operator>=(const MapIterator& rhs) const { 
				return this->_p >= rhs._p;
			}

	};
	//----------MapIterator-------------//


	//----------MapConstIterator-------------//
	template <typename T>
	class MapConstIterator : public ft::iterator<std::bidirectional_iterator_tag, const T> {
		public:
			typedef T																						value_type;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, const T>::pointer				pointer_node;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, const T>::difference_type		difference_type;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, const T>::reference				reference_node;
			typedef typename value_type::value															pair_value;	
			typedef pair_value 																				&reference;
			typedef pair_value 																				*pointer;

		private:
			template <typename, typename, typename, typename> friend class map;
			template <typename, typename, typename> friend class set;
			template <typename> friend class MapIterator;
			pointer_node _p;

			MapConstIterator(pointer_node x) {
				this->_p = x;
			};

		public:

			MapConstIterator() {};

			MapConstIterator(const MapConstIterator& vec) {
				this->_p = vec._p;
			}

			MapConstIterator(const MapIterator<value_type>& vec) {
				this->_p = vec._p;
			}

			~MapConstIterator() {};

			MapConstIterator& operator=(const MapConstIterator &vec){
				if (this == &vec)
					return *this;
				this->_p = vec._p;
				return *this;
			}

			// pointer base() {
			// 	return this->_p;
			// }

			// pointer base() const {
			// 	return this->_p;
			// }


			MapConstIterator& operator++() {
				bool left = true;
				// if (this->_p == this->_p->_left){
				// 	MapConstIterator it;
				// 	it++;
				// }
				if (this->_p == this->_p->_right->_parent) {
					this->_p =  this->_p->_right;
					while(this->_p == this->_p->_left->_parent)
						this->_p = this->_p->_left;
				}
				else {
					while (left) {
						if (this->_p != this->_p->_parent->_right)
							left = false;
						this->_p = this->_p->_parent;
					}
				}
				return *this;
			};

  			MapConstIterator operator++(int) {
				MapConstIterator tmp(*this);
				++(*this);
				return tmp;
			}

			MapConstIterator& operator--() {
				bool left = true;
				if (this->_p == this->_p->_left) {
					this->_p = this->_p->_parent;
					while(this->_p == this->_p->_right->_parent)
						this->_p = this->_p->_right;
				}
				else if (this->_p == this->_p->_left->_parent) {
					this->_p =  this->_p->_left;
					while(this->_p == this->_p->_right->_parent)
						this->_p = this->_p->_right;
				}
				else {
					while (left) {
						if (this->_p != this->_p->_parent->_left)
							left = false;
						this->_p = this->_p->_parent;
					}
				}
				// if (this->_p == this->_p->_left){
				// 	MapConstIterator it;
				// 	it--;
				// }
				return *this;
			};

  			MapConstIterator operator--(int) {
				MapConstIterator tmp(*this);
				--(*this);
				return tmp;
			}
			
			pair_value &operator*() const {
				return *(this->_p->_val);
			}

			pair_value *operator->() const {
				return (this->_p->_val);
			}

			bool operator==(const MapConstIterator& rhs) const { 
				return this->_p==rhs._p;
			}

			bool operator!=(const MapConstIterator& rhs) const { 
				return !(*this==rhs);
			}

			bool operator<(const MapConstIterator& rhs) const { 
				return this->_p < rhs._p;
			}

			bool operator<=(const MapConstIterator& rhs) const { 
				return this->_p <= rhs._p;
			}

			bool operator>(const MapConstIterator& rhs) const { 
				return this->_p > rhs._p;
			}

			bool operator>=(const MapConstIterator& rhs) const { 
				return this->_p >= rhs._p;
			}

	};
	//----------MapIterator-------------//

}

#endif