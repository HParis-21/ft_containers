#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include "iterators.hpp"

namespace ft {

	template <typename T, class Alloc = std::allocator<T> >
	class vector {
		
		public:
			typedef T											value_type;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::size_type			size_type;
			typedef typename allocator_type::difference_type	difference_type;
			typedef typename allocator_type::reference 			reference;
			typedef typename allocator_type::const_reference 	const_reference;
			typedef typename allocator_type::pointer 			pointer;
			typedef typename allocator_type::const_pointer 		const_pointer;
			typedef ft::VectorIterator<value_type>				iterator;
			typedef ft::VectorIteratorConst<value_type>         const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;


		private:
			allocator_type				_alloc;
			pointer						_begin;
			size_type					_capacity;
			size_type					_size;

			void	_clear(pointer begin, size_type siz, size_type capacity) {
				for (size_type i = 0; i < siz; ++i) {
					this->_alloc.destroy(begin + i);
				}
				this->_alloc.deallocate(begin, capacity);
			}

		public:
    //////////////////////////////
    // Constructors
    //////////////////////////////
			explicit vector(const allocator_type& alloc = allocator_type()) {
                this->_alloc = alloc;
				this->_begin = NULL;
				this->_capacity = 0;
				this->_size = 0;

			};

			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) {
                this->_alloc = alloc;
                if (n < 1) {
					this->_begin = NULL;
					this->_capacity = 0;
					this->_size = 0;
				}
				else {
					this->_begin = this->_alloc.allocate(n);
					this->_capacity = n;
					this->_size = n;
					for (size_type i = 0; i < n; ++i) {
						this->_alloc.construct(this->_begin + i, val);
					}
				}
			}

//			 template <class InputIterator, class = typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type>
			template <class InputIterator>
         	vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),  typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0) {
                this->_alloc = alloc;
                difference_type range = last - first;
					try {
						this->_begin = this->_alloc.allocate(range);
						this->_capacity = range;
						this->_size = 0;
						while (first != last) {
							this->_alloc.construct(this->_begin + this->_size, *first);
							++this->_size;
							++first;
						}
					} catch (...) {
						this->~vector();
						throw ;
					}
					
			}

			vector (const vector& x) {
                this->_alloc = x._alloc;
                this->_begin = NULL;
                this->_capacity = 0;
                this->_size = 0;
				if (x._capacity != 0)
					insert(this->begin(), x.begin(), x.end());
			}

    //////////////////////////////
    // Destructors
    //////////////////////////////

			~vector() {
				if (this->_begin != NULL)
					this->_clear(this->_begin, this->_size, this->_capacity);
			};

    //////////////////////////////
    // Assignment operator
    //////////////////////////////

			vector& operator=(const vector& x) {
//				 if (this == &x)
//				 	return *this;
//				 this->_clear(this->_begin, this->_size, this->_capacity);
//				 this->_begin =  this->_alloc.allocate(x._capacity);
//				 for (size_type i = 0; i < x._size; ++i) {
//				 	this->_alloc.construct(this->_begin + i, x[i]);
//				 }
//				 this->_size = x._size;
//				 this->_capacity = x._capacity;
				this->clear();		
				if (x._capacity != 0)		
					insert(this->begin(), x.begin(), x.end());

				return *this;
			}

    //////////////////////////////
    // Iterators
    //////////////////////////////

			iterator begin() {  return iterator(this->_begin);  }

			const_iterator begin() const {  return const_iterator(this->_begin);    }

			iterator end() {    return iterator(this->_begin + this->_size);    }

			const_iterator end() const {    return const_iterator(this->_begin + this->_size);  }

    //////////////////////////////
    // Reverse iterators
    //////////////////////////////

			reverse_iterator rbegin() { return reverse_iterator(this->end());   }

			const_reverse_iterator rbegin() const { return const_reverse_iterator(this->end()); }

			reverse_iterator rend() {   return reverse_iterator(this->begin()); }

			const_reverse_iterator rend() const {   return const_reverse_iterator(this->begin());   }

    //////////////////////////////
    // Capacity
    //////////////////////////////

			size_type size() const { return this->_size; }

			size_type max_size() {  return _alloc.max_size();   }
	
			void resize(size_type n, value_type val = value_type()) {
				if (n == this->_size)
					return ;
				if (n < this->_size) {
					this->_size = n;
					return ;
				}
				this->insert(end(), n - _size, val);

				// for (size_type i = this->_size; i < n; ++i) {
				// 	this->push_back(val);
				// }
			}
	
			size_type capacity(void) {  return this->_capacity; }

			bool empty () const {   return (!this->_size);  }

			void reserve (size_type n) {
				if (n <= this->_capacity)
					return ;
				pointer buf = this->_begin;
				this->_begin = this->_alloc.allocate(n);
				for (size_type i = 0; i < this->_size; ++i) {
					this->_alloc.construct(this->_begin + i, buf[i]);
					// *(this->_begin + i) = *(buf + i);
				}
				// delete buf;
				this->_clear(buf, this->_size, this->_capacity);
				this->_capacity = n;
			}

    //////////////////////////////
    //Element access
    //////////////////////////////

			reference &at(size_type n) {
				if (n >= this->_size)
					throw std::out_of_range("vector");
				return *(this->_begin + n);
			}
			
			const_reference at (size_type n) const {
				if (n >= this->_size)
					throw std::out_of_range("vector");
				return *(this->_begin + n);
			}

			reference &operator[](size_type n) {
				return *(this->_begin + n);
			}

			const_reference operator[] (size_type n) const {
				return *(this->_begin + n);
			}

			reference front() {
				return *this->_begin;
			}

			const_reference front() const {
				return *this->_begin;
			}

			reference back() {
				return *(this->_begin + this->_size - 1);
			}

			const_reference back() const {
				return *(this->_begin + this->_size - 1);
			}

    //////////////////////////////
    // Assignment modifiers
    //////////////////////////////

			void assign (size_type n, const value_type &val) {
				if (n > this->_capacity) {
					this->_clear(this->_begin, this->_size, this->_capacity);
					this->_capacity = n;
					this->_begin = this->_alloc.allocate(n);
				}
				else {
					for (size_type i = 0; i < _size; ++i) {
						this->_alloc.destroy(this->_begin + i);
					}
				}
				this->_size = 0;
				for (size_type i = 0; i < n; ++i) {
					this->push_back(val);
				}
			}

			template <class InputIterator>
			void assign (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0) {
				size_type range = last - first;
				if (range > this->_capacity) {
					this->_clear(this->_begin, this->_size, this->_capacity);
					this->_capacity = range;
					this->_begin = this->_alloc.allocate(range);
				}
				else {
					for (size_type i = 0; i < _size; ++i) {
						this->_alloc.destroy(this->_begin + i);
					}
				}
				this->_size = 0;
				for (size_type i = 0; i < range; ++i, ++first) {
					this->push_back(*first);
				}
			}

			void	push_back(const value_type &value) {
				if (this->_size == this->_capacity) {
					if (this->_capacity == 0) {
						this->_capacity = 1;
						this->_begin = this->_alloc.allocate(this->_capacity);
					}
					else {
						this->_capacity *= 2;
						pointer buf = this->_begin;
						this->_begin = this->_alloc.allocate(this->_capacity);
						for (size_type i = 0; i < this->_size; ++i) {
							this->_alloc.construct(this->_begin + i, buf[i]);
						}
						this->_clear(buf, this->_size, this->_size);
					}
				}
				this->_alloc.construct(this->_begin + this->_size, value);
				this->_size += 1;
			};

			void pop_back() {
				if (this->_size == 0)
					return ;
				this->_alloc.destroy(this->_begin + this->_size);
				this->_size -= 1;
			}

			iterator insert(iterator position, const value_type& val) {
				if (this->_begin == NULL) {
					push_back(val);
					return begin();
				}
				if (position == end())
				{
					push_back(val);
					return end() - 1;
				}
				size_type pos = position - this->begin();
				value_type buf = (*this)[pos];
				value_type buf2 = (*this)[pos];

				(*this)[pos] = val;
				for (size_type i = pos + 1; i < this->_size; ++i) {
					buf2 = (*this)[i];
					(*this)[i] = buf;
					buf = buf2;
				}
				this->push_back(buf);
				
				return this->begin() + pos;
			}


			void insert (iterator position, size_type n, const value_type& val){
				// if (n < 1)
				// 	return ;
				// size_type pos = position - this->begin();
				// size_type n_buf = n;
				// if (pos + n > this->_size)
				// 	n_buf = this->_size - pos;
				// vector buf(position , position + n_buf);
				// this->_size = pos;
				// for (size_type i = 0; i < n; ++i) {
				// 	this->push_back(val);
				// }
				// for (size_type i = 0; i < n_buf; ++i) {
				// 	this->push_back(buf[i]);
				// }
				size_type pos = 0;
				if (this->_begin != NULL)
					pos = position - this->begin();
				size_type rang = this->_size + n;
				rang = this->_capacity < rang ? this->_capacity * 2 < rang ? rang : this->_capacity * 2 : this->_capacity;
				pointer buf;
				buf = this->_alloc.allocate(rang);
				size_type i = 0;
				for (; i < pos; ++i) {
					this->_alloc.construct(buf + i, (*this)[i]);
				}
				for (size_type n_val = i + n; i < n_val; ++i) {
					this->_alloc.construct(buf + i, val);
				}
				if (this->_begin != NULL) {
					for(; position != this->end(); ++position, ++i) {
						this->_alloc.construct(buf + i, (*position));
					}
					this->_clear(this->_begin, this->_size, this->_capacity);
				}
				this->_begin = buf;
				this->_size = i;
				if (this->_capacity < rang)
					this->_capacity = rang;
			}


			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0) {
				size_type pos = 0;
				if (this->_begin != NULL)
					pos = position - this->begin();
				size_type rang = this->_size + (last - first);
				rang = this->_capacity < rang ? this->_capacity * 2 < rang ? rang : this->_capacity * 2 : this->_capacity;
				pointer buf;
				buf = this->_alloc.allocate(rang);
				size_type i = 0;
				for (; i < pos; ++i) {
					this->_alloc.construct(buf + i, (*this)[i]);
				}

				try {
					for (; first != last; ++i, ++first) {
						this->_alloc.construct(buf + i, (*first));
					}
				} catch(...) {
					for (size_type j = 0; j < i; ++j) {
						this->_alloc.destroy(buf + j);
					}
					this->_alloc.deallocate(buf, rang);
					throw ;
				}

				if (this->_begin != NULL) {
					for(; position != this->end(); ++position, ++i) {
						this->_alloc.construct(buf + i, (*position));
					}
					this->_clear(this->_begin, this->_size, this->_capacity);
				}
				this->_begin = buf;
				this->_size = i;
				if (this->_capacity < rang)
					this->_capacity = rang;

			}

    //////////////////////////////
    // Erasure modifiers
    //////////////////////////////

			iterator erase (iterator position) {
				size_type pos = position - this->begin();

				size_type size_move = static_cast<size_type>((end() - (this->_begin + pos) - 1) * sizeof(value_type));
				_alloc.destroy(this->_begin + pos);
				if (position != end() - 1) 
					std::memmove(this->_begin + pos, this->_begin + pos + 1, size_move);
				--_size;
				return this->begin() + pos;
			}


			iterator erase (iterator first, iterator last) {
				size_type pos = first - this->begin();
				size_type dist = last - first;

				this->_size -= dist;
				for (size_type i = pos; i < this->_size; ++i) {
					this->_alloc.construct(this->_begin + i, *(this->_begin + i + dist));
				}
				
				return this->begin() + pos;
			}

			void swap (vector& x) {
				if (this == &x)
					return ;
				pointer buf = this->_begin;
				this->_begin = x._begin;
				x._begin = buf;
				size_type buf_s = this->_size;
				this->_size = x._size;
				x._size = buf_s;
				buf_s = this->_capacity;
				this->_capacity = x._capacity;
				x._capacity = buf_s;
			}

			void clear () {
				for (size_type i = 0; i < _size; ++i) {
					this->_alloc.destroy(this->_begin + i);
				}
				this->_size = 0;
			}

    //////////////////////////////
    // Allocator
    //////////////////////////////

			allocator_type get_allocator() const {  return this->_alloc;    }
	};

    //////////////////////////////
    // Relational operators
    //////////////////////////////

	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return (lhs.size() != rhs.size() ? false : ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Alloc> 
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return !(lhs == rhs);
	}

	template <class T, class Alloc> 
	bool operator< (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class T, class Alloc> 
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return !(rhs < lhs);
	}

	template <class T, class Alloc> 
	bool operator> (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return !(lhs <= rhs);
	}

	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return !(lhs < rhs);
	}

	template <class T, class Alloc>
  	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)  {
		x.swap(y);
	}
  }

#endif