//#include <map>
//#include <stack>
//#include <vector>
//namespace ft = std;
//#else
//#include <map.hpp>
//#include <stack.hpp>
//#include <vector.hpp>
//#include <set.hpp>
//#endif
//
//#include <stdlib.h>
//
//#define MAX_RAM 4294967296
//#define BUFFER_SIZE 4096
//struct Buffer
//{
//    int idx;
//    char buff[BUFFER_SIZE];
//};
//
//
//#define COUNT (MAX_RAM / (int)sizeof(Buffer))
//
//template<typename T>
//class MutantStack : public ft::stack<T>
//{
//public:
//    MutantStack() {}
//    MutantStack(const MutantStack<T>& src) { *this = src; }
//    MutantStack<T>& operator=(const MutantStack<T>& rhs)
//    {
//        this->c = rhs.c;
//        return *this;
//    }
//    ~MutantStack() {}
//
//    typedef typename ft::stack<T>::container_type::iterator iterator;
//
//    iterator begin() { return this->c.begin(); }
//    iterator end() { return this->c.end(); }
//};
//
//int main(int argc, char** argv) {
//    if (argc != 2)
//    {
//        std::cerr << "Usage: ./test seed" << std::endl;
//        std::cerr << "Provide a seed please" << std::endl;
//        std::cerr << "Count value:" << COUNT << std::endl;
//        return 1;
//    }
//    const int seed = atoi(argv[1]);
//    srand(seed);
//
//    ft::vector<std::string> vector_str;
//    ft::vector<int> vector_int;
//    ft::stack<int> stack_int;
//    ft::vector<Buffer> vector_buffer;
//    ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
//    ft::map<int, int> map_int;
//
//    for (int i = 0; i < COUNT; i++)
//    {
//        vector_buffer.push_back(Buffer());
//    }
//
//    for (int i = 0; i < COUNT; i++)
//    {
//        const int idx = rand() % COUNT;
//        vector_buffer[idx].idx = 5;
//    }
//    ft::vector<Buffer>().swap(vector_buffer);
//
//    try
//    {
//        for (int i = 0; i < COUNT; i++)
//        {
//            const int idx = rand() % COUNT;
//            vector_buffer.at(idx);
//            std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
//        }
//    }
//    catch(const std::exception& e)
//    {
//        //NORMAL ! :P
//    }
//
//    for (int i = 0; i < COUNT; ++i)
//    {
//        map_int.insert(ft::make_pair(rand(), rand()));
//    }
//
//    int sum = 0;
//    for (int i = 0; i < 10000; i++)
//    {
//        int access = rand();
//        sum += map_int[access];
//    }
//    std::cout << "should be constant with the same seed: " << sum << std::endl;
//
//    {
//        ft::map<int, int> copy = map_int;
//    }
//    MutantStack<char> iterable_stack;
//    for (char letter = 'a'; letter <= 'z'; letter++)
//        iterable_stack.push(letter);
//    for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
//    {
//        std::cout << *it;
//    }
//    std::cout << std::endl;
//    return (0);
//}

#include <vector>
#include <map>
#include <set>
#include <iostream>
#include "vector.hpp"
#include "iterators.hpp"
#include "map.hpp"
#include "set.hpp"
#include "RedBlackTree.hpp"
#include "stack.hpp"

bool test_capacity() {
	std::vector<int>  vectSTD1;
	ft::vector<int> vectMY2;

	std::cout << "\033[36m" << "test_capacity - push_back  с нуля:" << "\033[0m" << std::endl;
	if (vectSTD1.capacity() != vectMY2.capacity()){
		std::cout << "\033[31m" << "TEST 1" << "\033[0m" << std::endl;
		return false;
	}
	if (vectSTD1.size() != vectMY2.size()){
		std::cout << "\033[31m" << "TEST 1.2 (size)" << "\033[0m" << std::endl;
		return false;
	}
	for (int i = 0; i < 2050; i++) {
		vectSTD1.push_back(i);
		vectMY2.push_back(i);
		if (vectSTD1.capacity() != vectMY2.capacity()) {
			std::cout << "\033[31m" << "TEST 2, i = " << i << "\033[0m" << std::endl;
			return false;
		}
		if (vectSTD1.size() != vectMY2.size()) {
			std::cout << "\033[31m" << "TEST 2.2 (size), i = " << i << "\033[0m" << std::endl;
			return false;
		}
	}
	std::cout << "\033[36m" << "test_capacity - max_size" << "\033[0m" << std::endl;
	if (vectSTD1.max_size() != vectMY2.max_size()) {
			std::cout << "\033[31m" << "TEST 4 (max_size) " << "\033[0m" << std::endl;
			return false;
		}

	std::cout << "\033[36m" << "test_capacity - resize" << "\033[0m" << std::endl;
	{
		std::vector<int> vectSTD11;
		ft::vector<int> vectMY22;

		for (int i=1;i<10;i++) {
			vectSTD11.push_back(i);
			vectMY22.push_back(i);
		}
		vectSTD11.resize(5);
		vectMY22.resize(5);
		if (vectSTD11[6] != vectMY22[6]) {
			std::cout << "\033[31m" << "TEST 5.1.0 (resize) " << "\033[0m" << std::endl;
			return false;
		}
		if (vectSTD11.capacity() != vectMY22.capacity() || vectSTD11.size() != vectMY22.size()) {
			std::cout << "\033[31m" << "TEST 5.1 (resize) " << "\033[0m" << std::endl;
			return false;
		}
		for (int i = 0; i < 5; i++) {
			if (vectSTD11[i] != vectMY22[i]) {
				std::cout << "\033[31m" << "TEST 5.1.2 (resize) " << "\033[0m" << std::endl;
				return false;
			}
		}
		vectSTD11.resize(8,100);
		vectMY22.resize(8,100);
		if (vectSTD11.capacity() != vectMY22.capacity() || vectSTD11.size() != vectMY22.size()) {
			std::cout << "\033[31m" << "TEST 5.2 (resize) " << "\033[0m" << std::endl;
			return false;
		}
		for (int i = 0; i < 8; i++) {
			if (vectSTD11[i] != vectMY22[i]) {
				std::cout << "\033[31m" << "TEST 5.2.2 (resize) " << "\033[0m" << std::endl;
				return false;
			}
		}
		vectSTD11.resize(12);
		vectMY22.resize(12);
		if (vectSTD11.capacity() != vectMY22.capacity() || vectSTD11.size() != vectMY22.size()) {
			std::cout << "\033[31m" << "TEST 5.3 (resize) " << "\033[0m" << std::endl;
			return false;
		}
		for (int i = 0; i < 12; i++) {
			if (vectSTD11[i] != vectMY22[i]) {
				std::cout << "\033[31m" << "TEST 5.3.2 (resize) " << "\033[0m" << std::endl;
				return false;
			}
		}
	}
	
	std::cout << "\033[36m" << "test_capacity - empty" << "\033[0m" << std::endl;
	if(vectSTD1.empty() != vectMY2.empty()) {
		std::cout << "\033[31m" << "TEST 6 (empty) " << "\033[0m" << std::endl;
			return false;
	}
	{
		std::vector<int> vectSTD11;
		ft::vector<int> vectMY22;
		if(vectSTD11.empty() != vectMY22.empty()) {
		std::cout << "\033[31m" << "TEST 6.1 (empty) " << "\033[0m" << std::endl;
			return false;
	}
	}
	
	std::cout << "\033[36m" << "test_capacity - reserve" << "\033[0m" << std::endl;
	{
		std::vector<int> vectSTD1;
		ft::vector<int> vectMY2;
		vectSTD1.reserve(100);
		vectMY2.reserve(100);
		if (vectSTD1.capacity() != vectMY2.capacity() || vectSTD1.size() != vectMY2.size()) {
			std::cout << "\033[31m" << "TEST 6.1 (reserve) " << "\033[0m" << std::endl;
			return false;
		}
		for (int i = 0; i < 100; i++) {
			vectSTD1.push_back(i);
			vectMY2.push_back(i);
			if (vectSTD1.capacity() != vectMY2.capacity() || vectSTD1.size() != vectMY2.size()) {
				std::cout << "\033[31m" << "TEST 6.2 (reserve) i = " << i << "\033[0m" << std::endl;
				return false;
			}
		}
	}
	return true;
}

bool test_push_back() {
	{
		std::vector<int> vectSTD1;
		ft::vector<int> vectMY2;

		for (int i = 0; i < 100; i++) {
			vectSTD1.push_back(i);
			vectMY2.push_back(i);
		}
		std::cout << "\033[36m" << "test_push_back - at:" << "\033[0m" << std::endl;
		for (int i = 0; i < 100; i++) {
			if (vectSTD1.at(i) != vectMY2.at(i)) {
				if (vectSTD1.capacity() != vectMY2.capacity()) {
					std::cout << "\033[31m" << "TEST 1, i = " << i << "\033[0m" << std::endl;
					return false;
				}
			}
		}
		std::cout << "\033[36m" << "test_push_back - operator[]:" << "\033[0m" << std::endl;
		for (int i = 0; i < 100; i++) {
			if (vectSTD1[i] != vectMY2[i]) {
				if (vectSTD1.capacity() != vectMY2.capacity()) {
					std::cout << "\033[31m" << "TEST 1, i = " << i << "\033[0m" << std::endl;
					return false;
				}
			}
		}
	}
	
	return true;
}

bool test_allocator() {
	{
		ft::vector<int> myvector;
		int * p;
		unsigned int i;
		
		// allocate an array with space for 5 elements using vector's allocator:
		p = myvector.get_allocator().allocate(5);
		
		// construct values in-place on the array:
		for (i=0; i<5; i++) myvector.get_allocator().construct(&p[i],i);
		
		
		for (i=0; i<5; i++) {
			if (p[i] != (int)i)
				return false;
		}

		// destroy and deallocate:
		for (i=0; i<5; i++) myvector.get_allocator().destroy(&p[i]);
		myvector.get_allocator().deallocate(p,5);
	}
	return true;
}

bool test_rever_iterator() {
	typedef std::vector<int>::iterator iter_type;
	std::cout << "\033[36m" << "construcor(1)" << "\033[0m" << std::endl;
	{
		std::reverse_iterator<iter_type> revectSTD1;
		ft::reverse_iterator<iter_type> revectMY2;
	}
	std::cout << "\033[36m" << "construcor(2)" << "\033[0m" << std::endl;
	{
		std::vector<int> v(1);
		iter_type it (v.begin());
		std::reverse_iterator<iter_type> revectSTD1(it);
		ft::reverse_iterator<iter_type> revectMY2(it);
		if (revectSTD1.base() != revectMY2.base()) {
			std::cout << "\033[31m" << "TEST 1 (base)  " << "\033[0m" << std::endl;
			return false;
		}
	}
	std::cout << "\033[36m" << "construcor(3)" << "\033[0m" << std::endl;
	{
		std::vector<int> v(10);
		for (int i=0; i<10; i++) v.push_back(i * 10);
		iter_type it (v.end());
		std::reverse_iterator<iter_type> revectSTD1(it);
		std::reverse_iterator<iter_type> r_revectSTD1(revectSTD1);
		ft::reverse_iterator<iter_type> revectMY2(it);
		ft::reverse_iterator<iter_type>r_revectMY2(revectMY2);
		(void) r_revectSTD1;
		(void) r_revectMY2;
		if (r_revectSTD1.base() != r_revectMY2.base()) {
			std::cout << "\033[31m" << "TEST 1 (base)  " << "\033[0m" << std::endl;
			return false;
		}
	}
	std::cout << "\033[36m" << "operator*" << "\033[0m" << std::endl;
	{
		std::vector<int> myvector;
		for (int i=0; i<10; i++) myvector.push_back(i * 10);
		iter_type from (myvector.begin());
		iter_type until (myvector.end());
		std::reverse_iterator<iter_type> revuSTD1 (from);	
		ft::reverse_iterator<iter_type> revuMY2 (from);
		std::reverse_iterator<iter_type> revfSTD1 (until);
		ft::reverse_iterator<iter_type> revfMY2 (until);
		if (*revuSTD1 != *revuMY2 || *revfSTD1 != *revfMY2) {
			std::cout << "\033[31m" << "TEST 1 ()  " << "\033[0m" << std::endl;
			return false;
		}

		std::cout << "\033[36m" << "operator+" << "\033[0m" << std::endl;
		{
			std::vector<int> myvector;
			for (int i=0; i<10; i++) myvector.push_back(i * 10);
			typedef std::vector<int>::iterator iter_type;
			iter_type until (myvector.end());
			std::reverse_iterator<iter_type> rev_itSTD1(until);
			ft::reverse_iterator<iter_type> rev_itMY2(until);
			if (*(rev_itSTD1 + 3) != *(rev_itMY2 + 3)) {
				std::cout << "\033[31m" << "TEST 1 ()  " << "\033[0m" << std::endl;
				return false;
			}
		}
		std::cout << "\033[36m" << "operator++" << "\033[0m" << std::endl;
		{
			std::vector<int> myvector;
			for (int i=0; i<10; i++) myvector.push_back(i * 10);
			typedef std::vector<int>::iterator iter_type;
			iter_type until (myvector.end());
			std::reverse_iterator<iter_type> rev_itSTD1(until);
			ft::reverse_iterator<iter_type> rev_itMY2(until);
			if (*(++rev_itSTD1) != *(++rev_itMY2)) {
				std::cout << "\033[31m" << "TEST 1 ()  " << "\033[0m" << std::endl;
				return false;
			}
			if (*(rev_itSTD1++) != *(rev_itMY2++)) {
				std::cout << "\033[31m" << "TEST 2 ()  " << "\033[0m" << std::endl;
				return false;
			}
		}
		std::cout << "\033[36m" << "operator+=" << "\033[0m" << std::endl;
		{
			std::vector<int> myvector;
			for (int i=0; i<10; i++) myvector.push_back(i * 10);
			typedef std::vector<int>::iterator iter_type;
			iter_type until (myvector.end());
			std::reverse_iterator<iter_type> rev_itSTD1(until);
			ft::reverse_iterator<iter_type> rev_itMY2(until);
  			rev_itSTD1 += 2;
  			rev_itMY2 += 2;
			if (*(rev_itSTD1) != *(rev_itMY2)) {
				std::cout << "\033[31m" << "TEST 1 ()  " << "\033[0m" << std::endl;
				return false;
			}
		}

		std::cout << "\033[36m" << "operator-" << "\033[0m" << std::endl;
		{
			std::vector<int> myvector;
			for (int i=0; i<10; i++) myvector.push_back(i * 10);
			typedef std::vector<int>::iterator iter_type;
			iter_type until (myvector.begin());
			std::reverse_iterator<iter_type> rev_itSTD1(until);
			ft::reverse_iterator<iter_type> rev_itMY2(until);
			if (*(rev_itSTD1 - 3) != *(rev_itMY2 - 3)) {
				std::cout << "\033[31m" << "TEST 1 ()  " << "\033[0m" << std::endl;
				return false;
			}
		}
		std::cout << "\033[36m" << "operator--" << "\033[0m" << std::endl;
		{
			std::vector<int> myvector;
			for (int i=0; i<10; i++) myvector.push_back(i * 10);	// myvector: 0 1 2 3 4 5 6 7 8 9
			typedef std::vector<int>::iterator iter_type;
			iter_type until (myvector.begin());
			std::reverse_iterator<iter_type> rev_itSTD1(until);
			ft::reverse_iterator<iter_type> rev_itMY2(until);
			if (*(--rev_itSTD1) != *(--rev_itMY2)) {
				std::cout << "\033[31m" << "TEST 1 ()  " << "\033[0m" << std::endl;
				return false;
			}
			if (*(rev_itSTD1--) != *(rev_itMY2--)) {
				std::cout << "\033[31m" << "TEST 2 ()  " << "\033[0m" << std::endl;
				return false;
			}
		}
		std::cout << "\033[36m" << "operator-=" << "\033[0m" << std::endl;
		{
			std::vector<int> myvector;
			for (int i=0; i<10; i++) myvector.push_back(i * 10);	// myvector: 0 1 2 3 4 5 6 7 8 9
			typedef std::vector<int>::iterator iter_type;
			iter_type until (myvector.begin());
			std::reverse_iterator<iter_type> rev_itSTD1(until);
			ft::reverse_iterator<iter_type> rev_itMY2(until);
  			rev_itSTD1 -= 2;
  			rev_itMY2 -= 2;
			if (*(rev_itSTD1) != *(rev_itMY2)) {
				std::cout << "\033[31m" << "TEST 1 ()  " << "\033[0m" << std::endl;
				return false;
			}
		}

		std::cout << "\033[36m" << "operator[]" << "\033[0m" << std::endl;
		{
			std::vector<int> myvector;
			for (int i=0; i<10; i++) myvector.push_back(i * 10);
			iter_type until (myvector.end());
			std::reverse_iterator<iter_type> revfSTD1 (until);
			ft::reverse_iterator<iter_type> revfMY2 (until);
			for (int i=0; i<10; i++) {
				if (revfSTD1[i] != revfMY2[i]) {
					std::cout << "\033[31m" << "TEST 1 ()  " << "\033[0m" << std::endl;
					return false;
				}
			}
			
		}
		std::cout << "\033[36m" << "operator==" << "\033[0m" << std::endl;
		{
			std::vector<int> myvector;
			for (int i=0; i<10; i++) myvector.push_back(i * 10);
			iter_type until (myvector.end());
			std::reverse_iterator<iter_type> revfSTD1 (until);
			ft::reverse_iterator<iter_type> revfMY2 (until);
			if (!(revfMY2 == revfMY2)) {
				std::cout << "\033[31m" << "TEST 1 ()  " << "\033[0m" << std::endl;
				return false;
			}
			for (int i=1; i<10; i++) {
				if (revfMY2 == revfMY2 + i) {
					std::cout << "\033[31m" << "TEST 2 ()  " << "\033[0m" << std::endl;
					return false;
				}
			}
		}
		std::cout << "\033[36m" << "operator!=" << "\033[0m" << std::endl;
		{
			std::vector<int> myvector;
			for (int i=0; i<10; i++) myvector.push_back(i * 10);
			iter_type until (myvector.end());
			std::reverse_iterator<iter_type> revfSTD1 (until);
			ft::reverse_iterator<iter_type> revfMY2 (until);
			if (revfMY2 != revfMY2) {
				std::cout << "\033[31m" << "TEST 1 ()  " << "\033[0m" << std::endl;
				return false;
			}
			for (int i=1; i<10; i++) {
				if (!(revfMY2 != revfMY2 + i)) {
					std::cout << "\033[31m" << "TEST 2 ()  " << "\033[0m" << std::endl;
					return false;
				}
			}
		}

		std::cout << "\033[36m" << "operator<" << "\033[0m" << std::endl;
		{
			std::vector<int> myvector;
			for (int i=0; i<10; i++) myvector.push_back(i * 10);
			iter_type until (myvector.end());
			std::reverse_iterator<iter_type> revfSTD1 (until);
			ft::reverse_iterator<iter_type> revfMY2 (until);
			if ((revfMY2 < revfMY2)) {
				std::cout << "\033[31m" << "TEST 1 ()  " << "\033[0m" << std::endl;
				return false;
			}
			for (int i=1; i<10; i++) {
				if (!(revfMY2 < revfMY2 + i)) {
					std::cout << "\033[31m" << "TEST 2 ()  " << "\033[0m" << std::endl;
					return false;
				}
			}
		}
		std::cout << "\033[36m" << "operator<=" << "\033[0m" << std::endl;
		{
			std::vector<int> myvector;
			for (int i=0; i<10; i++) myvector.push_back(i * 10);
			iter_type until (myvector.end());
			std::reverse_iterator<iter_type> revfSTD1 (until);
			ft::reverse_iterator<iter_type> revfMY2 (until);
			if (!(revfMY2 <= revfMY2)) {
				std::cout << "\033[31m" << "TEST 1 ()  " << "\033[0m" << std::endl;
				return false;
			}
			for (int i=0; i<10; i++) {
				if (!(revfMY2 <= revfMY2 + i)) {
					std::cout << "\033[31m" << "TEST 2 ()  " << "\033[0m" << std::endl;
					return false;
				}
			}
		}

		std::cout << "\033[36m" << "operator>" << "\033[0m" << std::endl;
		{
			std::vector<int> myvector;
			for (int i=0; i<10; i++) myvector.push_back(i * 10);
			iter_type until (myvector.end());
			std::reverse_iterator<iter_type> revfSTD1 (until);
			ft::reverse_iterator<iter_type> revfMY2 (until);
			if ((revfMY2 > revfMY2)) {
				std::cout << "\033[31m" << "TEST 1 ()  " << "\033[0m" << std::endl;
				return false;
			}
			for (int i=1; i<10; i++) {
				if (!(revfMY2  + i> revfMY2)) {
					std::cout << "\033[31m" << "TEST 2 ()  " << "\033[0m" << std::endl;
					return false;
				}
			}
		}
		std::cout << "\033[36m" << "operator>=" << "\033[0m" << std::endl;
		{
			std::vector<int> myvector;
			for (int i=0; i<10; i++) myvector.push_back(i * 10);
			iter_type until (myvector.end());
			std::reverse_iterator<iter_type> revfSTD1 (until);
			ft::reverse_iterator<iter_type> revfMY2 (until);
			if (!(revfMY2 >= revfMY2)) {
				std::cout << "\033[31m" << "TEST 1 ()  " << "\033[0m" << std::endl;
				return false;
			}
			for (int i=0; i<10; i++) {
				if (!(revfMY2 + i >= revfMY2)) {
					std::cout << "\033[31m" << "TEST 2 ()  " << "\033[0m" << std::endl;
					return false;
				}
			}
		}
		std::cout << "\033[36m" << "operator(+-)" << "\033[0m" << std::endl;
		{
			std::vector<int> myvector;
			for (int i=0; i<10; i++) myvector.push_back(i * 10);
			iter_type until (myvector.end());
			std::reverse_iterator<iter_type> revfSTD1 (until);
			ft::reverse_iterator<iter_type> revfMY2 (until);
			std::reverse_iterator<iter_type> revectSTD1;
			ft::reverse_iterator<iter_type> revectMY2;
			revectSTD1 = 3 + revfSTD1;
			revectMY2 = 3 + revfMY2;
			if (*revectSTD1 != *revectMY2) {
				std::cout << "\033[31m" << "TEST 1 ()  " << "\033[0m" << std::endl;
				return false;
			}
			if (*revfSTD1 != *revfMY2) {
				std::cout << "\033[31m" << "TEST 2 ()  " << "\033[0m" << std::endl;
				return false;
			}
			std::reverse_iterator<iter_type> revmSTD1;
			ft::reverse_iterator<iter_type> revmMY2;
			revmSTD1 = revfSTD1 - 2;
			revmMY2 = revfMY2 - 2;
			if (*revmSTD1 != *revmMY2) {
				std::cout << "\033[31m" << "TEST 2 ()  " << "\033[0m" << std::endl;
				return false;
			}
			if (*revfSTD1 != *revfMY2) {
				std::cout << "\033[31m" << "TEST 3 ()  " << "\033[0m" << std::endl;
				return false;
			}
		}
	}
	return true;
}

bool test_vector() {
	std::cout << "\033[36m" << "construcor (1)" << "\033[0m" << std::endl;
	{
		ft::vector<int> vectMY2_int;
		ft::vector<char> vectMY2_char;
		ft::vector<float> vectMY2_float;
		ft::vector<std::string> vectMY2_string;
	}
	std::cout << "\033[36m" << "construcor (2)" << "\033[0m" << std::endl;
	{
		std::string str("string");
		ft::vector<int> vectMY2_int(10, 5);
		ft::vector<char> vectMY2_char(10, 's');
		ft::vector<float> vectMY2_float(10, 15.5);
		ft::vector<std::string> vectMY2_string(10, str);
		std::vector<int> vectSTD1_int(10, 5);
		std::vector<char> vectSTD1_char(10, 's');
		std::vector<float> vectSTD1_float(10, 15.5);
		std::vector<std::string> vectSTD1_string(10, str);
		if (vectSTD1_int.capacity() != vectMY2_int.capacity() || vectSTD1_int.size() != vectMY2_int.size()) {
			std::cout << "\033[31m" << "construcor (2) Test 1.1 "  << "\033[0m" << std::endl;
			return false;
		}
		if (vectSTD1_char.capacity() != vectMY2_char.capacity() || vectSTD1_char.size() != vectMY2_char.size()) {
			std::cout << "\033[31m" << "construcor (2) Test 1.2 "  << "\033[0m" << std::endl;
			return false;
		}
		if (vectSTD1_float.capacity() != vectMY2_float.capacity() || vectSTD1_float.size() != vectMY2_float.size()) {
			std::cout << "\033[31m" << "construcor (2) Test 1.3 "  << "\033[0m" << std::endl;
			return false;
		}
		if (vectSTD1_string.capacity() != vectMY2_string.capacity() || vectSTD1_string.size() != vectMY2_string.size()) {
			std::cout << "\033[31m" << "construcor (2) Test 1.4 "  << "\033[0m" << std::endl;
			return false;
		}
		for (int i = 0; i < 10; ++i) {
			if (vectSTD1_int[i] != vectMY2_int[i] || vectSTD1_int[i] != vectMY2_int[i]) {
				std::cout << "\033[31m" << "construcor (2) Test 2.1 "  << "\033[0m" << std::endl;
				return false;
			}
			if (vectSTD1_char[i] != vectMY2_char[i] || vectSTD1_char[i] != vectMY2_char[i]) {
				std::cout << "\033[31m" << "construcor (2) Test 2.2 "  << "\033[0m" << std::endl;
				return false;
			}
			if (vectSTD1_float[i] != vectMY2_float[i] || vectSTD1_float[i] != vectMY2_float[i]) {
				std::cout << "\033[31m" << "construcor (2) Test 2.3 "  << "\033[0m" << std::endl;
				return false;
			}
			if (vectSTD1_string[i] != vectMY2_string[i] || vectSTD1_string[i] != vectMY2_string[i]) {
				std::cout << "\033[31m" << "construcor (2) Test 2.4 "  << "\033[0m" << std::endl;
				return false;
			}
		}
	}

	std::cout << "\033[36m" << "construcor (3)" << "\033[0m" << std::endl;
	{
		std::string str("string");

		std::vector<int> vectSTD1_int;
		std::vector<char> vectSTD1_char;
		std::vector<float> vectSTD1_float;
		std::vector<std::string> vectSTD1_string;
		ft::vector<int> vectMY2_int;
		ft::vector<char> vectMY2_char;
		ft::vector<float> vectMY2_float;
		ft::vector<std::string> vectMY2_string;

		for (int i = 0; i < 10; ++i) {
			vectSTD1_int.push_back(i * 10);
			vectMY2_int.push_back(i * 10);
			vectSTD1_char.push_back('A' + (i * 2));
			vectMY2_char.push_back('A' + (i * 2));
			vectSTD1_float.push_back((i * 10) + ((float)i / 10));
			vectMY2_float.push_back((i * 10) + ((float)i / 10));
			vectSTD1_string.push_back(str + std::to_string(i));
			vectMY2_string.push_back(str + std::to_string(i));
		}
		
		std::vector<int>::iterator it1_int = vectSTD1_int.begin();
		std::vector<char>::iterator it1_char(vectSTD1_char.begin());
		std::vector<float>::iterator it1_float(vectSTD1_float.begin());
		std::vector<std::string>::iterator it1_string = vectSTD1_string.begin();
		ft::vector<int>::iterator it2_int = vectMY2_int.begin();
		ft::vector<char>::iterator it2_char(vectMY2_char.begin());
		ft::vector<float>::iterator it2_float(vectMY2_float.begin());
		ft::vector<std::string>::iterator it2_string = vectMY2_string.begin();

		std::vector<int> vectSTD1_int_r(it1_int, vectSTD1_int.end());
		std::vector<char> vectSTD1_char_r(it1_char, vectSTD1_char.end());
		std::vector<float> vectSTD1_float_r(it1_float, vectSTD1_float.end());
		std::vector<std::string> vectSTD1_string_r(it1_string, vectSTD1_string.end());
		ft::vector<int> vectMY2_int_r(it2_int, vectMY2_int.end());
		ft::vector<char> vectMY2_char_r(it2_char, vectMY2_char.end());
		ft::vector<float> vectMY2_float_r(it2_float, vectMY2_float.end());
		ft::vector<std::string> vectMY2_string_r(it2_string, vectMY2_string.end());

		if (vectSTD1_int_r.capacity() != vectMY2_int_r.capacity() || vectSTD1_int_r.size() != vectMY2_int_r.size()) {
			std::cout << "\033[31m" << "construcor (3) Test 1.1 "  << "\033[0m" << std::endl;
			return false;
		}
		if (vectSTD1_char_r.capacity() != vectMY2_char_r.capacity() || vectSTD1_char_r.size() != vectMY2_char_r.size()) {
			std::cout << "\033[31m" << "construcor (3) Test 1.2 "  << "\033[0m" << std::endl;
			return false;
		}
		if (vectSTD1_float_r.capacity() != vectMY2_float_r.capacity() || vectSTD1_float_r.size() != vectMY2_float_r.size()) {
			std::cout << "\033[31m" << "construcor (3) Test 1.3 "  << "\033[0m" << std::endl;
			return false;
		}
		if (vectSTD1_string_r.capacity() != vectMY2_string_r.capacity() || vectSTD1_string_r.size() != vectMY2_string_r.size()) {
			std::cout << "\033[31m" << "construcor (3) Test 1.4 "  << "\033[0m" << std::endl;
			return false;
		}

		for (int i = 0; i < 10; ++i) {
			if (vectSTD1_int_r[i] != vectMY2_int_r[i]) {
				std::cout << "\033[31m" << "construcor (3) Test 2.1 "  << "\033[0m" << std::endl;
				return false;
			}
			if (vectSTD1_char_r[i] != vectMY2_char_r[i]) {
				std::cout << "\033[31m" << "construcor (3) Test 2.2 "  << "\033[0m" << std::endl;
				return false;
			}
			if (vectSTD1_float_r[i] != vectMY2_float_r[i]) {
				std::cout << "\033[31m" << "construcor (3) Test 2.3 "  << "\033[0m" << std::endl;
				return false;
			}
			if (vectSTD1_string_r[i] != vectMY2_string_r[i]) {
				std::cout << "\033[31m" << "construcor (3) Test 2.4 "  << "\033[0m" << std::endl;
				return false;
			}
		}
	}

	std::cout << "\033[36m" << "construcor (3.1)" << "\033[0m" << std::endl;
	{
		std::string str("string");

		std::vector<int> vectSTD1_int;
		std::vector<char> vectSTD1_char;
		std::vector<float> vectSTD1_float;
		std::vector<std::string> vectSTD1_string;

		for (int i = 0; i < 10; ++i) {
			vectSTD1_int.push_back(i * 10);
			vectSTD1_char.push_back('A' + (i * 2));
			vectSTD1_float.push_back((i * 10) + ((float)i / 10));
			vectSTD1_string.push_back(str + std::to_string(i));
		}
		
		std::vector<int>::iterator it1_int = vectSTD1_int.begin();
		std::vector<char>::iterator it1_char(vectSTD1_char.begin());
		std::vector<float>::iterator it1_float(vectSTD1_float.begin());
		std::vector<std::string>::iterator it1_string = vectSTD1_string.begin();

		std::vector<int> vectSTD1_int_r(it1_int, vectSTD1_int.end());
		std::vector<char> vectSTD1_char_r(it1_char, vectSTD1_char.end());
		std::vector<float> vectSTD1_float_r(it1_float, vectSTD1_float.end());
		std::vector<std::string> vectSTD1_string_r(it1_string, vectSTD1_string.end());
		ft::vector<int> vectMY2_int_r(it1_int, vectSTD1_int.end());
		ft::vector<char> vectMY2_char_r(it1_char, vectSTD1_char.end());
		ft::vector<float> vectMY2_float_r(it1_float, vectSTD1_float.end());
		ft::vector<std::string> vectMY2_string_r(it1_string, vectSTD1_string.end());

		if (vectSTD1_int_r.capacity() != vectMY2_int_r.capacity() || vectSTD1_int_r.size() != vectMY2_int_r.size()) {
			std::cout << "\033[31m" << "construcor (3.1) Test 1.1 "  << "\033[0m" << std::endl;
			return false;
		}
		if (vectSTD1_char_r.capacity() != vectMY2_char_r.capacity() || vectSTD1_char_r.size() != vectMY2_char_r.size()) {
			std::cout << "\033[31m" << "construcor (3.1) Test 1.2 "  << "\033[0m" << std::endl;
			return false;
		}
		if (vectSTD1_float_r.capacity() != vectMY2_float_r.capacity() || vectSTD1_float_r.size() != vectMY2_float_r.size()) {
			std::cout << "\033[31m" << "construcor (3.1) Test 1.3 "  << "\033[0m" << std::endl;
			return false;
		}
		if (vectSTD1_string_r.capacity() != vectMY2_string_r.capacity() || vectSTD1_string_r.size() != vectMY2_string_r.size()) {
			std::cout << "\033[31m" << "construcor (3.1) Test 1.4 "  << "\033[0m" << std::endl;
			return false;
		}

		for (int i = 0; i < 10; ++i) {
			if (vectSTD1_int_r[i] != vectMY2_int_r[i]) {
				std::cout << "\033[31m" << "construcor (3.1) Test 2.1 "  << "\033[0m" << std::endl;
				return false;
			}
			if (vectSTD1_char_r[i] != vectMY2_char_r[i]) {
				std::cout << "\033[31m" << "construcor (3.1) Test 2.2 "  << "\033[0m" << std::endl;
				return false;
			}
			if (vectSTD1_float_r[i] != vectMY2_float_r[i]) {
				std::cout << "\033[31m" << "construcor (3.1) Test 2.3 "  << "\033[0m" << std::endl;
				return false;
			}
			if (vectSTD1_string_r[i] != vectMY2_string_r[i]) {
				std::cout << "\033[31m" << "construcor (3.1) Test 2.4 "  << "\033[0m" << std::endl;
				return false;
			}
		}
	}

	std::cout << "\033[36m" << "construcor (4)" << "\033[0m" << std::endl;
	{
		std::string str("string");

		std::vector<int> vectSTD1_int;
		std::vector<char> vectSTD1_char;
		std::vector<float> vectSTD1_float;
		std::vector<std::string> vectSTD1_string;
		ft::vector<int> vectMY2_int;
		ft::vector<char> vectMY2_char;
		ft::vector<float> vectMY2_float;
		ft::vector<std::string> vectMY2_string;

		for (int i = 0; i < 10; ++i) {
			vectSTD1_int.push_back(i * 10);
			vectMY2_int.push_back(i * 10);
			vectSTD1_char.push_back('A' + (i * 2));
			vectMY2_char.push_back('A' + (i * 2));
			vectSTD1_float.push_back((i * 10) + ((float)i / 10));
			vectMY2_float.push_back((i * 10) + ((float)i / 10));
			vectSTD1_string.push_back(str + std::to_string(i));
			vectMY2_string.push_back(str + std::to_string(i));
		}
		
		std::vector<int> vectSTD1_int_r(vectSTD1_int);
		std::vector<char> vectSTD1_char_r(vectSTD1_char);
		std::vector<float> vectSTD1_float_r(vectSTD1_float);
		std::vector<std::string> vectSTD1_string_r(vectSTD1_string);
		ft::vector<int> vectMY2_int_r(vectMY2_int);
		ft::vector<char> vectMY2_char_r(vectMY2_char);
		ft::vector<float> vectMY2_float_r(vectMY2_float);
		ft::vector<std::string> vectMY2_string_r(vectMY2_string);

		if (vectSTD1_int_r.capacity() != vectMY2_int_r.capacity() || vectSTD1_int_r.size() != vectMY2_int_r.size()) {
			std::cout << "\033[31m" << "construcor (4) Test 1.1 "  << "\033[0m" << std::endl;
			return false;
		}
		if (vectSTD1_char_r.capacity() != vectMY2_char_r.capacity() || vectSTD1_char_r.size() != vectMY2_char_r.size()) {
			std::cout << "\033[31m" << "construcor (4) Test 1.2 "  << "\033[0m" << std::endl;
			return false;
		}
		if (vectSTD1_float_r.capacity() != vectMY2_float_r.capacity() || vectSTD1_float_r.size() != vectMY2_float_r.size()) {
			std::cout << "\033[31m" << "construcor (4) Test 1.3 "  << "\033[0m" << std::endl;
			return false;
		}
		if (vectSTD1_string_r.capacity() != vectMY2_string_r.capacity() || vectSTD1_string_r.size() != vectMY2_string_r.size()) {
			std::cout << "\033[31m" << "construcor (4) Test 1.4 "  << "\033[0m" << std::endl;
			return false;
		}
		for (int i = 0; i < 10; ++i) {
			if (vectSTD1_int_r[i] != vectMY2_int_r[i]) {
				std::cout << "\033[31m" << "construcor (4) Test 2.1 "  << "\033[0m" << std::endl;
				return false;
			}
			if (vectSTD1_char_r[i] != vectMY2_char_r[i]) {
				std::cout << "\033[31m" << "construcor (4) Test 2.2 "  << "\033[0m" << std::endl;
				return false;
			}
			if (vectSTD1_float_r[i] != vectMY2_float_r[i]) {
				std::cout << "\033[31m" << "construcor (4) Test 2.3 "  << "\033[0m" << std::endl;
				return false;
			}
			if (vectSTD1_string_r[i] != vectMY2_string_r[i]) {
				std::cout << "\033[31m" << "construcor (4) Test 2.4 "  << "\033[0m" << std::endl;
				return false;
			}
		}
	}

	std::cout << "\033[36m" << "operator=" << "\033[0m" << std::endl;
	{
		std::string str("string");

		std::vector<int> vectSTD1_int;
		std::vector<char> vectSTD1_char;
		std::vector<float> vectSTD1_float;
		std::vector<std::string> vectSTD1_string;
		ft::vector<int> vectMY2_int;
		ft::vector<char> vectMY2_char;
		ft::vector<float> vectMY2_float;
		ft::vector<std::string> vectMY2_string;

		for (int i = 0; i < 10; ++i) {
			vectSTD1_int.push_back(i * 10);
			vectMY2_int.push_back(i * 10);
			vectSTD1_char.push_back('A' + (i * 2));
			vectMY2_char.push_back('A' + (i * 2));
			vectSTD1_float.push_back((i * 10) + ((float)i / 10));
			vectMY2_float.push_back((i * 10) + ((float)i / 10));
			vectSTD1_string.push_back(str + std::to_string(i));
			vectMY2_string.push_back(str + std::to_string(i));
		}
		
		std::vector<int> vectSTD1_int_r = vectSTD1_int;
		std::vector<char> vectSTD1_char_r = vectSTD1_char;
		std::vector<float> vectSTD1_float_r = vectSTD1_float;
		std::vector<std::string> vectSTD1_string_r = vectSTD1_string ;
		ft::vector<int> vectMY2_int_r = vectMY2_int;
		ft::vector<char> vectMY2_char_r = vectMY2_char;
		ft::vector<float> vectMY2_float_r = vectMY2_float;
		ft::vector<std::string> vectMY2_string_r = vectMY2_string;

		if (vectSTD1_int_r.capacity() != vectMY2_int_r.capacity() || vectSTD1_int_r.size() != vectMY2_int_r.size()) {
			std::cout << "\033[31m" << "operator= Test 1.1 "  << "\033[0m" << std::endl;
			return false;
		}
		if (vectSTD1_char_r.capacity() != vectMY2_char_r.capacity() || vectSTD1_char_r.size() != vectMY2_char_r.size()) {
			std::cout << "\033[31m" << "operator= Test 1.2 "  << "\033[0m" << std::endl;
			return false;
		}
		if (vectSTD1_float_r.capacity() != vectMY2_float_r.capacity() || vectSTD1_float_r.size() != vectMY2_float_r.size()) {
			std::cout << "\033[31m" << "operator= Test 1.3 "  << "\033[0m" << std::endl;
			return false;
		}
		if (vectSTD1_string_r.capacity() != vectMY2_string_r.capacity() || vectSTD1_string_r.size() != vectMY2_string_r.size()) {
			std::cout << "\033[31m" << "operator= Test 1.4 "  << "\033[0m" << std::endl;
			return false;
		}
		for (int i = 0; i < 10; ++i) {
			if (vectSTD1_int_r[i] != vectMY2_int_r[i]) {
				std::cout << "\033[31m" << "operator= Test 2.1 "  << "\033[0m" << std::endl;
				return false;
			}
			if (vectSTD1_char_r[i] != vectMY2_char_r[i]) {
				std::cout << "\033[31m" << "operator=) Test 2.2 "  << "\033[0m" << std::endl;
				return false;
			}
			if (vectSTD1_float_r[i] != vectMY2_float_r[i]) {
				std::cout << "\033[31m" << "operator= Test 2.3 "  << "\033[0m" << std::endl;
				return false;
			}
			if (vectSTD1_string_r[i] != vectMY2_string_r[i]) {
				std::cout << "\033[31m" << "operator= Test 2.4 "  << "\033[0m" << std::endl;
				return false;
			}
		}
		std::string str_b("string_big");

		std::vector<int> vectSTD1_int_b;
		std::vector<char> vectSTD1_char_b;
		std::vector<float> vectSTD1_float_b;
		std::vector<std::string> vectSTD1_string_b;
		ft::vector<int> vectMY2_int_b;
		ft::vector<char> vectMY2_char_b;
		ft::vector<float> vectMY2_float_b;
		ft::vector<std::string> vectMY2_string_b;

		for (int i = 0; i < 50; ++i) {
			vectSTD1_int_b.push_back(i * 10);
			vectMY2_int_b.push_back(i * 10);
			vectSTD1_char_b.push_back('!' + i);
			vectMY2_char_b.push_back('!' + i);
			vectSTD1_float_b.push_back((i * 10) + ((float)i / 10));
			vectMY2_float_b.push_back((i * 10) + ((float)i / 10));
			vectSTD1_string_b.push_back(str_b + std::to_string(i));
			vectMY2_string_b.push_back(str_b + std::to_string(i));
		}

		vectSTD1_int_r = vectSTD1_int_b;
		vectSTD1_char_r = vectSTD1_char_b;
		vectSTD1_float_r = vectSTD1_float_b;
		vectSTD1_string_r = vectSTD1_string_b;
		vectMY2_int_r = vectMY2_int_b;
		vectMY2_char_r = vectMY2_char_b;
		vectMY2_float_r = vectMY2_float_b;
		vectMY2_string_r = vectMY2_string_b;

		if (vectSTD1_int_r.capacity() != vectMY2_int_r.capacity() || vectSTD1_int_r.size() != vectMY2_int_r.size()) {
			std::cout << "\033[31m" << "operator= Test 3.1 "  << "\033[0m" << std::endl;
			return false;
		}
		if (vectSTD1_char_r.capacity() != vectMY2_char_r.capacity() || vectSTD1_char_r.size() != vectMY2_char_r.size()) {
			std::cout << "\033[31m" << "operator= Test 3.2 "  << "\033[0m" << std::endl;
			return false;
		}
		if (vectSTD1_float_r.capacity() != vectMY2_float_r.capacity() || vectSTD1_float_r.size() != vectMY2_float_r.size()) {
			std::cout << "\033[31m" << "operator= Test 3.3 "  << "\033[0m" << std::endl;
			return false;
		}
		if (vectSTD1_string_r.capacity() != vectMY2_string_r.capacity() || vectSTD1_string_r.size() != vectMY2_string_r.size()) {
			std::cout << "\033[31m" << "operator= Test 3.4 "  << "\033[0m" << std::endl;
			return false;
		}
		for (int i = 0; i < 50; ++i) {
			if (vectSTD1_int_r[i] != vectMY2_int_r[i]) {
				std::cout << "\033[31m" << "operator= Test 4.1 "  << "\033[0m" << std::endl;
				return false;
			}
			if (vectSTD1_char_r[i] != vectMY2_char_r[i]) {
				std::cout << "\033[31m" << "operator=) Test 4.2 "  << "\033[0m" << std::endl;
				return false;
			}
			if (vectSTD1_float_r[i] != vectMY2_float_r[i]) {
				std::cout << "\033[31m" << "operator= Test 4.3 "  << "\033[0m" << std::endl;
				return false;
			}
			if (vectSTD1_string_r[i] != vectMY2_string_r[i]) {
				std::cout << "\033[31m" << "operator= Test 4.4 "  << "\033[0m" << std::endl;
				return false;
			}
		}

		std::string str_l("string_litl");

		std::vector<int> vectSTD1_int_l;
		std::vector<char> vectSTD1_char_l;
		std::vector<float> vectSTD1_float_l;
		std::vector<std::string> vectSTD1_string_l;
		ft::vector<int> vectMY2_int_l;
		ft::vector<char> vectMY2_char_l;
		ft::vector<float> vectMY2_float_l;
		ft::vector<std::string> vectMY2_string_l;

		for (int i = 0; i < 3; ++i) {
			vectSTD1_int_l.push_back(i * 10);
			vectMY2_int_l.push_back(i * 10);
			vectSTD1_char_l.push_back('!' + i * 10);
			vectMY2_char_l.push_back('!' + i * 10);
			vectSTD1_float_l.push_back((i * 10) + ((float)i / 10));
			vectMY2_float_l.push_back((i * 10) + ((float)i / 10));
			vectSTD1_string_l.push_back(str_l + std::to_string(i));
			vectMY2_string_l.push_back(str_l + std::to_string(i));
		}

		vectSTD1_int_r = vectSTD1_int_l;
		vectSTD1_char_r = vectSTD1_char_l;
		vectSTD1_float_r = vectSTD1_float_l;
		vectSTD1_string_r = vectSTD1_string_l;
		vectMY2_int_r = vectMY2_int_l;
		vectMY2_char_r = vectMY2_char_l;
		vectMY2_float_r = vectMY2_float_l;
		vectMY2_string_r = vectMY2_string_l;

		if (vectSTD1_int_r.capacity() != vectMY2_int_r.capacity() || vectSTD1_int_r.size() != vectMY2_int_r.size()) {
			std::cout << "\033[31m" << "operator= Test 5.1 "  << "\033[0m" << std::endl;
			return false;
		}
		if (vectSTD1_char_r.capacity() != vectMY2_char_r.capacity() || vectSTD1_char_r.size() != vectMY2_char_r.size()) {
			std::cout << "\033[31m" << "operator= Test 5.2 "  << "\033[0m" << std::endl;
			return false;
		}
		if (vectSTD1_float_r.capacity() != vectMY2_float_r.capacity() || vectSTD1_float_r.size() != vectMY2_float_r.size()) {
			std::cout << "\033[31m" << "operator= Test 5.3 "  << "\033[0m" << std::endl;
			return false;
		}
		if (vectSTD1_string_r.capacity() != vectMY2_string_r.capacity() || vectSTD1_string_r.size() != vectMY2_string_r.size()) {
			std::cout << "\033[31m" << "operator= Test 5.4 "  << "\033[0m" << std::endl;
			return false;
		}
		for (int i = 0; i < 3; ++i) {
			if (vectSTD1_int_r[i] != vectMY2_int_r[i]) {
				std::cout << "\033[31m" << "operator= Test 6.1 "  << "\033[0m" << std::endl;
				return false;
			}
			if (vectSTD1_char_r[i] != vectMY2_char_r[i]) {
				std::cout << "\033[31m" << "operator=) Test 6.2 "  << "\033[0m" << std::endl;
				return false;
			}
			if (vectSTD1_float_r[i] != vectMY2_float_r[i]) {
				std::cout << "\033[31m" << "operator= Test 6.3 "  << "\033[0m" << std::endl;
				return false;
			}
			if (vectSTD1_string_r[i] != vectMY2_string_r[i]) {
				std::cout << "\033[31m" << "operator= Test 6.4 "  << "\033[0m" << std::endl;
				return false;
			}
		}

		std::vector<int> vectSTD1_int_em;
		std::vector<char> vectSTD1_char_em;
		std::vector<float> vectSTD1_float_em;
		std::vector<std::string> vectSTD1_string_em;
		ft::vector<int> vectMY2_int_em;
		ft::vector<char> vectMY2_char_em;
		ft::vector<float> vectMY2_float_em;
		ft::vector<std::string> vectMY2_string_em;
	}

	std::cout << "\033[36m" << "begin" << "\033[0m" << std::endl;
	{
		std::string str("string");

		std::vector<int> vectSTD1_int;
		std::vector<char> vectSTD1_char;
		std::vector<float> vectSTD1_float;
		std::vector<std::string> vectSTD1_string;
		ft::vector<int> vectMY2_int;
		ft::vector<char> vectMY2_char;
		ft::vector<float> vectMY2_float;
		ft::vector<std::string> vectMY2_string;

		std::vector<int>::iterator it1_int;
		std::vector<char>::iterator it1_char;
		std::vector<float>::iterator it1_float;
		std::vector<std::string>::iterator it1_string;
		ft::vector<int>::iterator it2_int;
		ft::vector<char>::iterator it2_char;
		ft::vector<float>::iterator it2_float;
		ft::vector<std::string>::iterator it2_string;

		for (int i = 0; i < 10; ++i) {
			vectSTD1_int.push_back(i * 10);
			vectMY2_int.push_back(i * 10);
			vectSTD1_char.push_back('A' + (i * 2));
			vectMY2_char.push_back('A' + (i * 2));
			vectSTD1_float.push_back((i * 10) + ((float)i / 10));
			vectMY2_float.push_back((i * 10) + ((float)i / 10));
			vectSTD1_string.push_back(str + std::to_string(i));
			vectMY2_string.push_back(str + std::to_string(i));
		}

		it1_int = vectSTD1_int.begin();
		it2_int = vectMY2_int.begin();
		it1_char = vectSTD1_char.begin();
		it2_char = vectMY2_char.begin();
		it1_float = vectSTD1_float.begin();
		it2_float = vectMY2_float.begin();
		it1_string = vectSTD1_string.begin();
		it2_string = vectMY2_string.begin();

		for (int i = 0; i < 10; ++i) {
			if (it1_int[i] != it2_int[i]) {
				std::cout << "\033[31m" << "begin Test 1.1 "  << "\033[0m" << std::endl;
				return false;
			}
			if (it1_char[i] != it2_char[i]) {
				std::cout << "\033[31m" << "begin Test 1.2 "  << "\033[0m" << std::endl;
				return false;
			}
			if (it1_float[i] != it2_float[i]) {
				std::cout << "\033[31m" << "begin Test 1.3 "  << "\033[0m" << std::endl;
				return false;
			}
			if (it1_string[i] != it2_string[i]) {
				std::cout << "\033[31m" << "begin Test 1.4 "  << "\033[0m" << std::endl;
				return false;
			}
		}
	}

	std::cout << "\033[36m" << "const begin" << "\033[0m" << std::endl;
	{
		std::string str("string");

		std::vector<int> vectSTD1_int;
		ft::vector<int> vectMY2_int;

		std::vector<int>::const_iterator it1_int;
		ft::vector<int>::const_iterator it2_int;

		for (int i = 0; i < 10; ++i) {
			vectSTD1_int.push_back(i * 10);
			vectMY2_int.push_back(i * 10);
			}

		const std::vector<int> vectSTD1_int_c(vectSTD1_int);
		const ft::vector<int> vectMY2_int_c(vectMY2_int);

		it1_int = vectSTD1_int_c.begin();
		it2_int = vectMY2_int_c.begin();
		
		for (int i = 0; i < 10; ++i) {
			if (it1_int[i] != it2_int[i]) {
				std::cout << "\033[31m" << "const begin Test 1.1 "  << "\033[0m" << std::endl;
				return false;
			}
		}
	}
	
	std::cout << "\033[36m" << "end" << "\033[0m" << std::endl;
	{
		std::string str("string");

		std::vector<int> vectSTD1_int;
		std::vector<char> vectSTD1_char;
		std::vector<float> vectSTD1_float;
		std::vector<std::string> vectSTD1_string;
		ft::vector<int> vectMY2_int;
		ft::vector<char> vectMY2_char;
		ft::vector<float> vectMY2_float;
		ft::vector<std::string> vectMY2_string;

		std::vector<int>::iterator it1_int;
		std::vector<char>::iterator it1_char;
		std::vector<float>::iterator it1_float;
		std::vector<std::string>::iterator it1_string;
		ft::vector<int>::iterator it2_int;
		ft::vector<char>::iterator it2_char;
		ft::vector<float>::iterator it2_float;
		ft::vector<std::string>::iterator it2_string;

		for (int i = 0; i < 10; ++i) {
			vectSTD1_int.push_back(i * 10);
			vectMY2_int.push_back(i * 10);
			vectSTD1_char.push_back('A' + (i * 2));
			vectMY2_char.push_back('A' + (i * 2));
			vectSTD1_float.push_back((i * 10) + ((float)i / 10));
			vectMY2_float.push_back((i * 10) + ((float)i / 10));
			vectSTD1_string.push_back(str + std::to_string(i));
			vectMY2_string.push_back(str + std::to_string(i));
		}

		it1_int = vectSTD1_int.end();
		it2_int = vectMY2_int.end();
		it1_char = vectSTD1_char.end();
		it2_char = vectMY2_char.end();
		it1_float = vectSTD1_float.end();
		it2_float = vectMY2_float.end();
		it1_string = vectSTD1_string.end();
		it2_string = vectMY2_string.end();

		if (*(it1_int - 1) != *(it2_int - 1)) {
			std::cout << "\033[31m" << "end Test 1.1 "  << "\033[0m" << std::endl;
			return false;
		}
		if (*(it1_char - 1) != *(it2_char - 1)) {
			std::cout << "\033[31m" << "end Test 1.2 "  << "\033[0m" << std::endl;
			return false;
		}
		if (*(it1_float - 1) != *(it2_float - 1)) {
			std::cout << "\033[31m" << "end Test 1.3 "  << "\033[0m" << std::endl;
			return false;
		}
		if (*(it1_string - 1) != *(it2_string - 1)) {
			std::cout << "\033[31m" << "end Test 1.4 "  << "\033[0m" << std::endl;
			return false;
		}
	}
	std::cout << "\033[36m" << "const end" << "\033[0m" << std::endl;
	{
		std::string str("string");

		std::vector<int> vectSTD1_int;
		std::vector<char> vectSTD1_char;
		std::vector<float> vectSTD1_float;
		std::vector<std::string> vectSTD1_string;
		ft::vector<int> vectMY2_int;
		ft::vector<char> vectMY2_char;
		ft::vector<float> vectMY2_float;
		ft::vector<std::string> vectMY2_string;

		std::vector<int>::const_iterator it1_int;
		std::vector<char>::const_iterator it1_char;
		std::vector<float>::const_iterator it1_float;
		std::vector<std::string>::const_iterator it1_string;
		ft::vector<int>::const_iterator it2_int;
		ft::vector<char>::const_iterator it2_char;
		ft::vector<float>::const_iterator it2_float;
		ft::vector<std::string>::const_iterator it2_string;

		for (int i = 0; i < 10; ++i) {
			vectSTD1_int.push_back(i * 10);
			vectMY2_int.push_back(i * 10);
			vectSTD1_char.push_back('A' + (i * 2));
			vectMY2_char.push_back('A' + (i * 2));
			vectSTD1_float.push_back((i * 10) + ((float)i / 10));
			vectMY2_float.push_back((i * 10) + ((float)i / 10));
			vectSTD1_string.push_back(str + std::to_string(i));
			vectMY2_string.push_back(str + std::to_string(i));
		}

		const std::vector<int> vectSTD1_int_c(vectSTD1_int);
		const std::vector<char> vectSTD1_char_c(vectSTD1_char);
		const std::vector<float> vectSTD1_float_c(vectSTD1_float);
		const std::vector<std::string> vectSTD1_string_c(vectSTD1_string);
		const ft::vector<int> vectMY2_int_c(vectMY2_int);
		const ft::vector<char> vectMY2_char_c(vectMY2_char);
		const ft::vector<float> vectMY2_float_c(vectMY2_float);
		const ft::vector<std::string> vectMY2_string_c(vectMY2_string);

		it1_int = vectSTD1_int_c.end();
		it2_int = vectMY2_int_c.end();
		it1_char = vectSTD1_char_c.end();
		it2_char = vectMY2_char_c.end();
		it1_float = vectSTD1_float_c.end();
		it2_float = vectMY2_float_c.end();
		it1_string = vectSTD1_string_c.end();
		it2_string = vectMY2_string_c.end();

		if (*(it1_int - 1) != *(it2_int - 1)) {
			std::cout << "\033[31m" << "end Test 1.1 "  << "\033[0m" << std::endl;
			return false;
		}
		if (*(it1_char - 1) != *(it2_char - 1)) {
			std::cout << "\033[31m" << "end Test 1.2 "  << "\033[0m" << std::endl;
			return false;
		}
		if (*(it1_float - 1) != *(it2_float - 1)) {
			std::cout << "\033[31m" << "end Test 1.3 "  << "\033[0m" << std::endl;
			return false;
		}
		if (*(it1_string - 1) != *(it2_string - 1)) {
			std::cout << "\033[31m" << "end Test 1.4 "  << "\033[0m" << std::endl;
			return false;
		}
	}

	std::cout << "\033[36m" << "rend" << "\033[0m" << std::endl;
	{
		std::string str("string");

		std::vector<int> vectSTD1_int;
		std::vector<char> vectSTD1_char;
		std::vector<float> vectSTD1_float;
		std::vector<std::string> vectSTD1_string;
		ft::vector<int> vectMY2_int;
		ft::vector<char> vectMY2_char;
		ft::vector<float> vectMY2_float;
		ft::vector<std::string> vectMY2_string;

		std::vector<int>::reverse_iterator it1_int;
		std::vector<char>::reverse_iterator it1_char;
		std::vector<float>::reverse_iterator it1_float;
		std::vector<std::string>::reverse_iterator it1_string;
		ft::vector<int>::reverse_iterator it2_int;
		ft::vector<char>::reverse_iterator it2_char;
		ft::vector<float>::reverse_iterator it2_float;
		ft::vector<std::string>::reverse_iterator it2_string;

		for (int i = 0; i < 10; ++i) {
			vectSTD1_int.push_back(i * 10);
			vectMY2_int.push_back(i * 10);
			vectSTD1_char.push_back('A' + (i * 2));
			vectMY2_char.push_back('A' + (i * 2));
			vectSTD1_float.push_back((i * 10) + ((float)i / 10));
			vectMY2_float.push_back((i * 10) + ((float)i / 10));
			vectSTD1_string.push_back(str + std::to_string(i));
			vectMY2_string.push_back(str + std::to_string(i));
		}

		it1_int = vectSTD1_int.rend();
		it2_int = vectMY2_int.rend();
		it1_char = vectSTD1_char.rend();
		it2_char = vectMY2_char.rend();
		it1_float = vectSTD1_float.rend();
		it2_float = vectMY2_float.rend();
		it1_string = vectSTD1_string.rend();
		it2_string = vectMY2_string.rend();

		for (int i = 1; i < 11; ++i) {
			if (*(it1_int - i) != *(it2_int - i)) {
				std::cout << "\033[31m" << "rend Test 1.1 "  << "\033[0m" << std::endl;
				return false;
			}
			if (*(it1_char - i) != *(it2_char - i)) {
				std::cout << "\033[31m" << "rend Test 1.2 "  << "\033[0m" << std::endl;
				return false;
			}
			if (*(it1_float - i) != *(it2_float - i)) {
				std::cout << "\033[31m" << "rend Test 1.3 "  << "\033[0m" << std::endl;
				return false;
			}
			if (*(it1_string - i) != *(it2_string - i)) {
				std::cout << "\033[31m" << "rend Test 1.4 "  << "\033[0m" << std::endl;
				return false;
			}
		}
	}

	std::cout << "\033[36m" << "const rend" << "\033[0m" << std::endl;
	{
		std::string str("string");

		std::vector<int> vectSTD1_int;
		ft::vector<int> vectMY2_int;

		std::vector<int>::const_reverse_iterator it1_int;
		ft::vector<int>::const_reverse_iterator it2_int;

		for (int i = 0; i < 10; ++i) {
			vectSTD1_int.push_back(i * 10);
			vectMY2_int.push_back(i * 10);
		}

		const std::vector<int> vectSTD1_int_c(vectSTD1_int);
		const ft::vector<int> vectMY2_int_c(vectMY2_int);

		it1_int = vectSTD1_int_c.rend();
		it2_int = vectMY2_int_c.rend();
		
		for (int i = 1; i < 11; ++i) {
			if (*(it1_int - i) != *(it2_int - i)) {
				std::cout << "\033[31m" << "const rend Test 1.1 "  << "\033[0m" << std::endl;
				return false;
			}
		}
	}
	
	std::cout << "\033[36m" << "rbegin" << "\033[0m" << std::endl;
	{
		std::string str("string");

		std::vector<int> vectSTD1_int;
		std::vector<char> vectSTD1_char;
		std::vector<float> vectSTD1_float;
		std::vector<std::string> vectSTD1_string;
		ft::vector<int> vectMY2_int;
		ft::vector<char> vectMY2_char;
		ft::vector<float> vectMY2_float;
		ft::vector<std::string> vectMY2_string;

		std::vector<int>::reverse_iterator it1_int;
		std::vector<char>::reverse_iterator it1_char;
		std::vector<float>::reverse_iterator it1_float;
		std::vector<std::string>::reverse_iterator it1_string;
		ft::vector<int>::reverse_iterator it2_int;
		ft::vector<char>::reverse_iterator it2_char;
		ft::vector<float>::reverse_iterator it2_float;
		ft::vector<std::string>::reverse_iterator it2_string;

		for (int i = 0; i < 10; ++i) {
			vectSTD1_int.push_back(i * 10);
			vectMY2_int.push_back(i * 10);
			vectSTD1_char.push_back('A' + (i * 2));
			vectMY2_char.push_back('A' + (i * 2));
			vectSTD1_float.push_back((i * 10) + ((float)i / 10));
			vectMY2_float.push_back((i * 10) + ((float)i / 10));
			vectSTD1_string.push_back(str + std::to_string(i));
			vectMY2_string.push_back(str + std::to_string(i));
		}

		it1_int = vectSTD1_int.rbegin();
		it2_int = vectMY2_int.rbegin();
		it1_char = vectSTD1_char.rbegin();
		it2_char = vectMY2_char.rbegin();
		it1_float = vectSTD1_float.rbegin();
		it2_float = vectMY2_float.rbegin();
		it1_string = vectSTD1_string.rbegin();
		it2_string = vectMY2_string.rbegin();

		if (*(it1_int) != *(it2_int)) {
			std::cout << "\033[31m" << "rbegin Test 1.1 "  << "\033[0m" << std::endl;
			return false;
		}
		if (*(it1_char) != *(it2_char)) {
			std::cout << "\033[31m" << "rbegin Test 1.2 "  << "\033[0m" << std::endl;
			return false;
		}
		if (*(it1_float) != *(it2_float)) {
			std::cout << "\033[31m" << "rbegin Test 1.3 "  << "\033[0m" << std::endl;
			return false;
		}
		if (*(it1_string) != *(it2_string)) {
			std::cout << "\033[31m" << "rbegin Test 1.4 "  << "\033[0m" << std::endl;
			return false;
		}
	}
	std::cout << "\033[36m" << "const rbegin" << "\033[0m" << std::endl;
	{
		std::string str("string");

		std::vector<int> vectSTD1_int;
		std::vector<char> vectSTD1_char;
		std::vector<float> vectSTD1_float;
		std::vector<std::string> vectSTD1_string;
		ft::vector<int> vectMY2_int;
		ft::vector<char> vectMY2_char;
		ft::vector<float> vectMY2_float;
		ft::vector<std::string> vectMY2_string;

		std::vector<int>::const_reverse_iterator it1_int;
		std::vector<char>::const_reverse_iterator it1_char;
		std::vector<float>::const_reverse_iterator it1_float;
		std::vector<std::string>::const_reverse_iterator it1_string;
		ft::vector<int>::const_reverse_iterator it2_int;
		ft::vector<char>::const_reverse_iterator it2_char;
		ft::vector<float>::const_reverse_iterator it2_float;
		ft::vector<std::string>::const_reverse_iterator it2_string;

		for (int i = 0; i < 10; ++i) {
			vectSTD1_int.push_back(i * 10);
			vectMY2_int.push_back(i * 10);
			vectSTD1_char.push_back('A' + (i * 2));
			vectMY2_char.push_back('A' + (i * 2));
			vectSTD1_float.push_back((i * 10) + ((float)i / 10));
			vectMY2_float.push_back((i * 10) + ((float)i / 10));
			vectSTD1_string.push_back(str + std::to_string(i));
			vectMY2_string.push_back(str + std::to_string(i));
		}

		const std::vector<int> vectSTD1_int_c(vectSTD1_int);
		const std::vector<char> vectSTD1_char_c(vectSTD1_char);
		const std::vector<float> vectSTD1_float_c(vectSTD1_float);
		const std::vector<std::string> vectSTD1_string_c(vectSTD1_string);
		const ft::vector<int> vectMY2_int_c(vectMY2_int);
		const ft::vector<char> vectMY2_char_c(vectMY2_char);
		const ft::vector<float> vectMY2_float_c(vectMY2_float);
		const ft::vector<std::string> vectMY2_string_c(vectMY2_string);

		it1_int = vectSTD1_int_c.rbegin();
		it2_int = vectMY2_int_c.rbegin();
		it1_char = vectSTD1_char_c.rbegin();
		it2_char = vectMY2_char_c.rbegin();
		it1_float = vectSTD1_float_c.rbegin();
		it2_float = vectMY2_float_c.rbegin();
		it1_string = vectSTD1_string_c.rbegin();
		it2_string = vectMY2_string_c.rbegin();

		if (*(it1_int) != *(it2_int)) {
			std::cout << "\033[31m" << "rbegin Test 1.1 "  << "\033[0m" << std::endl;
			return false;
		}
		if (*(it1_char) != *(it2_char)) {
			std::cout << "\033[31m" << "rbegin Test 1.2 "  << "\033[0m" << std::endl;
			return false;
		}
		if (*(it1_float) != *(it2_float)) {
			std::cout << "\033[31m" << "rbegin Test 1.3 "  << "\033[0m" << std::endl;
			return false;
		}
		if (*(it1_string) != *(it2_string)) {
			std::cout << "\033[31m" << "rbegin Test 1.4 "  << "\033[0m" << std::endl;
			return false;
		}
	}

	std::cout << "\033[36m" << "back:" << "\033[0m" << std::endl;
	{
		std::vector<int> vectSTD1;
		ft::vector<int> vectMY2;
		for (int i = 0; i < 100; i++) {
			vectSTD1.push_back(i);
			vectMY2.push_back(i);
			if (vectSTD1.back() != vectMY2.back()) {
				std::cout << "\033[31m" << "TEST 1 (back) i = " << i << "\033[0m" << std::endl;
				return false;
			}
		}
		std::cout << "\033[36m" << "front:" << "\033[0m" << std::endl;
		if (vectSTD1.front() != vectMY2.front()) {
			std::cout << "\033[31m" << "TEST 1 (front)" << "\033[0m" << std::endl;
			return false;
		}
	}

	std::cout << "\033[36m" << "assign:" << "\033[0m" << std::endl;
	{
		std::vector<int> vectSTD1;
		ft::vector<int> vectMY2;
		std::vector<int> vectSTD1_c;
		ft::vector<int> vectMY2_c;
		vectSTD1.assign(7, 100);
		vectMY2.assign(7, 100);
		if (vectSTD1.capacity() != vectMY2.capacity() || vectSTD1.size() != vectMY2.size()) {
			std::cout << "\033[31m" << "TEST 1.1 (assign) " << "\033[0m" << std::endl;
			return false;
		}
		for (int i = 0; i < 7; ++i) {
			if (vectSTD1[i] != vectMY2[i]) {
				std::cout << "\033[31m" << "TEST 1.2 (assign) i =  " << i << "\033[0m" << std::endl;
				return false;
			}
		}
		vectSTD1_c.assign(vectSTD1.begin(), vectSTD1.end());
		vectMY2_c.assign(vectSTD1.begin(), vectSTD1.end());
		if (vectSTD1_c.capacity() != vectMY2_c.capacity() || vectSTD1_c.size() != vectMY2_c.size()) {
			std::cout << "\033[31m" << "TEST 2.1 (assign) " << "\033[0m" << std::endl;
			return false;
		}
		for (int i = 0; i < 7; ++i) {
			if (vectSTD1_c[i] != vectMY2_c[i]) {
				std::cout << "\033[31m" << "TEST 2.2 (assign) i =  " << i << "\033[0m" << std::endl;
				return false;
			}
		}
		
		vectSTD1.assign(10, 5);
		vectMY2.assign(10, 5);
		if (vectSTD1.capacity() != vectMY2.capacity() || vectSTD1.size() != vectMY2.size()) {
			std::cout << "\033[31m" << "TEST 3 (assign) " << "\033[0m" << std::endl;
			return false;
		}
		for (int i = 0; i < 10; ++i) {
			if (vectSTD1[i] != vectMY2[i]) {
				std::cout << "\033[31m" << "TEST 4 (assign) i =  " << i << "\033[0m" << std::endl;
				return false;
			}
		}

		vectSTD1_c.assign(vectSTD1.begin(), vectSTD1.end());
		vectMY2_c.assign(vectSTD1.begin(), vectSTD1.end());
		if (vectSTD1_c.capacity() != vectMY2_c.capacity() || vectSTD1_c.size() != vectMY2_c.size()) {
			std::cout << "\033[31m" << "TEST 2.3 (assign) " << "\033[0m" << std::endl;
			return false;
		}
		for (int i = 0; i < 10; ++i) {
			if (vectSTD1_c[i] != vectMY2_c[i]) {
				std::cout << "\033[31m" << "TEST 2.4 (assign) i =  " << i << "\033[0m" << std::endl;
				return false;
			}
		}

		vectSTD1.assign(3, 0);
		vectMY2.assign(3, 0);
		if (vectSTD1.capacity() != vectMY2.capacity() || vectSTD1.size() != vectMY2.size()) {
			std::cout << "\033[31m" << "TEST 5 (assign) " << "\033[0m" << std::endl;
			return false;
		}
		for (int i = 0; i < 3; ++i) {
			if (vectSTD1[i] != vectMY2[i]) {
				std::cout << "\033[31m" << "TEST 6 (assign) i =  " << i << "\033[0m" << std::endl;
				return false;
			}
		}

		vectSTD1_c.assign(vectSTD1.begin(), vectSTD1.end());
		vectMY2_c.assign(vectSTD1.begin(), vectSTD1.end());
		if (vectSTD1_c.capacity() != vectMY2_c.capacity() || vectSTD1_c.size() != vectMY2_c.size()) {
			std::cout << "\033[31m" << "TEST 2.5 (assign) " << "\033[0m" << std::endl;
			return false;
		}
		for (int i = 0; i < 3; ++i) {
			if (vectSTD1_c[i] != vectMY2_c[i]) {
				std::cout << "\033[31m" << "TEST 2.6 (assign) i =  " << i << "\033[0m" << std::endl;
				return false;
			}
		}
	}

	std::cout << "\033[36m" << "pop_back:" << "\033[0m" << std::endl;
	{
		std::vector<int> vectSTD1;
		ft::vector<int> vectMY2;
		for (int i = 0; i < 100; ++i) {
			vectSTD1.push_back(i);
			vectMY2.push_back(i);
		}
		for (int i = 0; i < 100; ++i) {
			vectSTD1.pop_back();
			vectMY2.pop_back();
			if (vectSTD1.capacity() != vectMY2.capacity() || vectSTD1.size() != vectMY2.size()) {
				std::cout << "\033[31m" << "TEST 7 (pop_back) " << "\033[0m" << std::endl;
				return false;
			}
		}
	}
	std::cout << "\033[36m" << "clear:" << "\033[0m" << std::endl;
	{
		std::vector<int> vectSTD1;
		ft::vector<int> vectMY2;
		for (int i = 0; i < 100; ++i) {
			vectSTD1.push_back(i);
			vectMY2.push_back(i);
		}
		vectSTD1.clear();
		vectMY2.clear();
		if (vectSTD1.capacity() != vectMY2.capacity() || vectSTD1.size() != vectMY2.size()) {
			std::cout << "\033[31m" << "TEST 1 (clear) " << "\033[0m" << std::endl;
			return false;
		}
	}
	std::cout << "\033[36m" << "insert (1):" << "\033[0m" << std::endl;
	{
		std::vector<int> vectSTD1;
		ft::vector<int> vectMY2;

		std::vector<int>::iterator it1;
		ft::vector<int>::iterator it2;

		for (int i = 0; i < 10; ++i) {
			vectSTD1.push_back(i * 10);
			vectMY2.push_back(i * 10);
		}

		it1 = vectSTD1.insert(vectSTD1.begin() + 5, 55);
		it2 = vectMY2.insert(vectMY2.begin() + 5, 55);

		if (vectSTD1.capacity() != vectMY2.capacity() || vectSTD1.size() != vectMY2.size()) {
			std::cout << "\033[31m" << "insert TEST 1.1 " << "\033[0m" << std::endl;
			return false;
		}
		for (int i = 0; i < 11; ++i) {
			if (vectSTD1[i] != vectMY2[i]) {
				std::cout << "\033[31m" << "insert TEST 1.2 " << "\033[0m" << std::endl;
				return false;
			}
		}
		if (*it1 != *it2) {
			std::cout << "\033[31m" << "insert TEST 1.3 " << "\033[0m" << std::endl;
			return false;
		}

	}
	{
		std::vector<int> vectSTD1;
		ft::vector<int> vectMY2;

		std::vector<int>::iterator it1;
		ft::vector<int>::iterator it2;

		for (int i = 0; i < 8; ++i) {
			vectSTD1.push_back(i * 10);
			vectMY2.push_back(i * 10);
		}

		it1 = vectSTD1.insert(vectSTD1.begin() + 5, 55);
		it2 = vectMY2.insert(vectMY2.begin() + 5, 55);

		if (vectSTD1.capacity() != vectMY2.capacity() || vectSTD1.size() != vectMY2.size()) {
			std::cout << "\033[31m" << "insert TEST 2.1 " << "\033[0m" << std::endl;
			return false;
		}
		for (int i = 0; i < 9; ++i) {
			if (vectSTD1[i] != vectMY2[i]) {
				std::cout << "\033[31m" << "insert TEST 2.2 " << "\033[0m" << std::endl;
				return false;
			}
		}
		if (*it1 != *it2) {
			std::cout << "\033[31m" << "insert TEST 2.3 " << "\033[0m" << std::endl;
			return false;
		}
	}

	std::cout << "\033[36m" << "insert (2):" << "\033[0m" << std::endl;
	{
		std::vector<int> vectSTD1;
		ft::vector<int> vectMY2;

		for (int i = 0; i < 10; ++i) {
			vectSTD1.push_back(i * 10);
			vectMY2.push_back(i * 10);
		}

		vectSTD1.insert(vectSTD1.begin() + 5, 5, 55);
		vectMY2.insert(vectMY2.begin() + 5, 5, 55);

		if (vectSTD1.capacity() != vectMY2.capacity() || vectSTD1.size() != vectMY2.size()) {
			std::cout << "\033[31m" << "insert TEST 1.1 " << "\033[0m" << std::endl;
			return false;
		}
		for (int i = 0; i < 15; ++i) {
			if (vectSTD1[i] != vectMY2[i]) {
				std::cout << "\033[31m" << "insert TEST 1.2 " << "\033[0m" << std::endl;
				return false;
			}
		}
	}

	std::cout << "\033[36m" << "insert (3):" << "\033[0m" << std::endl;
	{

		std::vector<int> vec;
		std::vector<int> vectSTD1;
		ft::vector<int> vectMY2;

		for (int i = 0; i < 5; ++i) {
			vec.push_back(i * 100);
		}

		for (int i = 0; i < 10; ++i) {
			vectSTD1.push_back(i * 10);
			vectMY2.push_back(i * 10);
		}

		vectSTD1.insert(vectSTD1.begin() + 3, vec.begin(), vec.end());
		vectMY2.insert(vectMY2.begin() + 3, vec.begin(), vec.end());

		if (vectSTD1.capacity() != vectMY2.capacity() || vectSTD1.size() != vectMY2.size()) {
			std::cout << "\033[31m" << "insert TEST 1.1 " << "\033[0m" << std::endl;
			return false;
		}
		for (int i = 0; i < 15; ++i) {
			if (vectSTD1[i] != vectMY2[i]) {
				std::cout << "\033[31m" << "insert TEST 1.2 " << "\033[0m" << std::endl;
				return false;
			}
		}

	}
	{
		std::vector<int> vectSTD1;
		ft::vector<int> vectMY2;

		for (int i = 0; i < 8; ++i) {
			vectSTD1.push_back(i * 10);
			vectMY2.push_back(i * 10);
		}

		vectSTD1.insert(vectSTD1.begin() + 5, 55);
		vectMY2.insert(vectMY2.begin() + 5, 55);

		if (vectSTD1.capacity() != vectMY2.capacity() || vectSTD1.size() != vectMY2.size()) {
			std::cout << "\033[31m" << "insert TEST 2.1 " << "\033[0m" << std::endl;
			return false;
		}
		for (int i = 0; i < 9; ++i) {
			if (vectSTD1[i] != vectMY2[i]) {
				std::cout << "\033[31m" << "insert TEST 2.2 " << "\033[0m" << std::endl;
				return false;
			}
		}
	}
	{

		std::vector<int> vectSTD1;
		std::vector<int> vectSTD1_c;

		ft::vector<int> vectMY2;
		ft::vector<int> vectMY2_c;

		vectSTD1.assign(26, 1);
		vectMY2.assign(26, 1);

		vectSTD1_c.assign(22, 1);
		vectMY2_c.assign(22, 1);

		vectSTD1_c.insert(vectSTD1_c.end() - 14, vectSTD1.begin(), vectSTD1.end());

		vectMY2_c.insert(vectMY2_c.end() - 14, vectMY2.begin(), vectMY2.end());

		if (vectSTD1_c.capacity() != vectMY2_c.capacity() || vectSTD1_c.size() != vectMY2_c.size()) {
			std::cout << "\033[31m" << "insert TEST 3.1 " << "\033[0m" << std::endl;
			return false;
		}
		for (int i = 0; i < 22 + 26; ++i) {
			if (vectSTD1_c[i] != vectMY2_c[i]) {
				std::cout << "\033[31m" << "insert TEST 3.2 " << "\033[0m" << std::endl;
				return false;
			}
		}
	}
	{

		std::vector<int> vectSTD1;
		std::vector<int> vectSTD1_c;

		ft::vector<int> vectMY2;
		ft::vector<int> vectMY2_c;

		vectSTD1.assign(26, 1);
		vectMY2.assign(26, 1);

		vectSTD1_c.assign(48, 1);
		vectMY2_c.assign(48, 1);

		vectSTD1_c.insert(vectSTD1_c.end() - 10, vectSTD1.begin(), vectSTD1.end());

		vectMY2_c.insert(vectMY2_c.end() - 10, vectMY2.begin(), vectMY2.end());

		if (vectSTD1_c.capacity() != vectMY2_c.capacity() || vectSTD1_c.size() != vectMY2_c.size()) {
			std::cout << "\033[31m" << "insert TEST 4.1 " << "\033[0m" << std::endl;
			return false;
		}
		for (int i = 0; i < 22 + 48; ++i) {
			if (vectSTD1_c[i] != vectMY2_c[i]) {
				std::cout << "\033[31m" << "insert TEST 4.2 " << "\033[0m" << std::endl;
				return false;
			}
		}
	}

	std::cout << "\033[36m" << "erase (1):" << "\033[0m" << std::endl;
	{
		std::vector<int> vectSTD1;
		ft::vector<int> vectMY2;

		std::vector<int>::iterator it1;
		ft::vector<int>::iterator it2;

		for (int i = 0; i < 10; ++i) {
			vectSTD1.push_back(i * 10);
			vectMY2.push_back(i * 10);
		}

		it1 = vectSTD1.erase(vectSTD1.begin() + 5);
		it2 = vectMY2.erase(vectMY2.begin() + 5);

		if (vectSTD1.capacity() != vectMY2.capacity() || vectSTD1.size() != vectMY2.size()) {
			std::cout << "\033[31m" << "erase TEST 1.1 " << "\033[0m" << std::endl;
			return false;
		}
		for (int i = 0; i < 9; ++i) {
			if (vectSTD1[i] != vectMY2[i]) {
				std::cout << "\033[31m" << "erase TEST 1.2 " << "\033[0m" << std::endl;
				return false;
			}
		}
		if (*it1 != *it2) {
			std::cout << "\033[31m" << "erase TEST 1.3 " << "\033[0m" << std::endl;
			return false;
		}

	}
	{
		std::vector<int> vectSTD1;
		ft::vector<int> vectMY2;

		std::vector<int>::iterator it1;
		ft::vector<int>::iterator it2;

		for (int i = 0; i < 8; ++i) {
			vectSTD1.push_back(i * 10);
			vectMY2.push_back(i * 10);
		}

		it1 = vectSTD1.erase(vectSTD1.begin() + 5);
		it2 = vectMY2.erase(vectMY2.begin() + 5);

		if (vectSTD1.capacity() != vectMY2.capacity() || vectSTD1.size() != vectMY2.size()) {
			std::cout << "\033[31m" << "erase TEST 2.1 " << "\033[0m" << std::endl;
			return false;
		}
		for (int i = 0; i < 7; ++i) {
			if (vectSTD1[i] != vectMY2[i]) {
				std::cout << "\033[31m" << "erase TEST 2.2 " << "\033[0m" << std::endl;
				return false;
			}
		}
		if (*it1 != *it2) {
			std::cout << "\033[31m" << "erase TEST 2.3 " << "\033[0m" << std::endl;
			return false;
		}
	}

	std::cout << "\033[36m" << "erase (2):" << "\033[0m" << std::endl;
	{
		std::vector<int> vectSTD1;
		ft::vector<int> vectMY2;

		std::vector<int>::iterator it1;
		ft::vector<int>::iterator it2;

		for (int i = 0; i < 10; ++i) {
			vectSTD1.push_back(i * 10);
			vectMY2.push_back(i * 10);
		}

		it1 = vectSTD1.erase(vectSTD1.begin() + 3, vectSTD1.begin() + 5);
		it2 = vectMY2.erase(vectMY2.begin() + 3, vectMY2.begin() + 5);

		if (vectSTD1.capacity() != vectMY2.capacity() || vectSTD1.size() != vectMY2.size()) {
			std::cout << "\033[31m" << "erase TEST 1.1 " << "\033[0m" << std::endl;
			return false;
		}
		for (int i = 0; i < 8; ++i) {
			if (vectSTD1[i] != vectMY2[i]) {
				std::cout << "\033[31m" << "erase TEST 1.2 " << "\033[0m" << std::endl;
				return false;
			}
		}
		if (*it1 != *it2) {
			std::cout << "\033[31m" << "erase TEST 1.3 " << "\033[0m" << std::endl;
			return false;
		}

	}
	{
		std::vector<int> vectSTD1;
		ft::vector<int> vectMY2;

		std::vector<int>::iterator it1;
		ft::vector<int>::iterator it2;

		for (int i = 0; i < 8; ++i) {
			vectSTD1.push_back(i * 10);
			vectMY2.push_back(i * 10);
		}

		it1 = vectSTD1.erase(vectSTD1.begin() + 5, vectSTD1.begin() + 8);
		it2 = vectMY2.erase(vectMY2.begin() + 5, vectMY2.begin() + 8);

		if (vectSTD1.capacity() != vectMY2.capacity() || vectSTD1.size() != vectMY2.size()) {
			std::cout << "\033[31m" << "erase TEST 2.1 " << "\033[0m" << std::endl;
			return false;
		}
		for (int i = 0; i < 5; ++i) {
			if (vectSTD1[i] != vectMY2[i]) {
				std::cout << "\033[31m" << "erase TEST 2.2 " << "\033[0m" << std::endl;
				return false;
			}
		}
		if (*it1 != *it2) {
			std::cout << "\033[31m" << "erase TEST 2.3 " << "\033[0m" << std::endl;
			return false;
		}
	}
	std::cout << "\033[36m" << "swap:" << "\033[0m" << std::endl;
	{
		std::vector<int> vectSTD1(5, 5);
		std::vector<int> vectSTD1_c(10, 10);
		ft::vector<int> vectMY2(5, 5);
		ft::vector<int> vectMY2_c(10, 10);

		std::vector<int>::iterator it1 = vectSTD1.begin();
		ft::vector<int>::iterator it2 = vectMY2.begin();

		vectSTD1.swap(vectSTD1_c);
		vectMY2.swap(vectMY2_c);

		std::vector<int>::iterator it1_c  = vectSTD1.begin();
		ft::vector<int>::iterator it2_c = vectMY2.begin();

		if((it1 == it1_c) != (it2 == it2_c)) {
			std::cout << "\033[31m" << "swap TEST 0.1 " << "\033[0m" << std::endl;
			return false;
		}

		if (vectSTD1.capacity() != vectMY2.capacity() || vectSTD1.size() != vectMY2.size()) {
			std::cout << "\033[31m" << "swap TEST 1.1 " << "\033[0m" << std::endl;
			return false;
		}
		for (int i = 0; i < 10; ++i) {
			if (vectSTD1[i] != vectMY2[i]) {
				std::cout << "\033[31m" << "swap TEST 2.2 " << "\033[0m" << std::endl;
				return false;
			}
		}
		if (vectSTD1_c.capacity() != vectMY2_c.capacity() || vectSTD1_c.size() != vectMY2_c.size()) {
			std::cout << "\033[31m" << "swap TEST 1.3 " << "\033[0m" << std::endl;
			return false;
		}
		for (int i = 0; i < 5; ++i) {
			if (vectSTD1_c[i] != vectMY2_c[i]) {
				std::cout << "\033[31m" << "swap TEST 2.4 " << "\033[0m" << std::endl;
				return false;
			}
		}

	}
	std::cout << "\033[36m" << "operators:" << "\033[0m" << std::endl;
	{
		std::vector<int> vectSTD1(5, 5);
		std::vector<int> vectSTD1_c(5, 5);
		ft::vector<int> vectMY2(5, 5);
		ft::vector<int> vectMY2_c(5, 5);
		
		if ((vectSTD1 == vectSTD1_c) != (vectMY2 == vectMY2_c)){
			std::cout << "\033[31m" << "operator== TEST 1 " << "\033[0m" << std::endl;
			return false;
		}
		if ((vectSTD1 != vectSTD1_c) != (vectMY2 != vectMY2_c)){
			std::cout << "\033[31m" << "operator!= TEST 1 " << "\033[0m" << std::endl;
			return false;
		}
		if ((vectSTD1 < vectSTD1_c) != (vectMY2 < vectMY2_c)){
			std::cout << "\033[31m" << "operator< TEST 1.1 " << "\033[0m" << std::endl;
			return false;
		}
		if ((vectSTD1_c < vectSTD1) != (vectMY2_c < vectMY2)){
			std::cout << "\033[31m" << "operator< TEST 1.2 " << "\033[0m" << std::endl;
			return false;
		}
		if ((vectSTD1 <= vectSTD1_c) != (vectMY2 <= vectMY2_c)){
			std::cout << "\033[31m" << "operator<= TEST 1.1 " << "\033[0m" << std::endl;
			return false;
		}
		if ((vectSTD1_c <= vectSTD1) != (vectMY2_c <= vectMY2)){
			std::cout << "\033[31m" << "operator<= TEST 1.2 " << "\033[0m" << std::endl;
			return false;
		}
		if ((vectSTD1 > vectSTD1_c) != (vectMY2 > vectMY2_c)){
			std::cout << "\033[31m" << "operator> TEST 1.1 " << "\033[0m" << std::endl;
			return false;
		}
		if ((vectSTD1_c > vectSTD1) != (vectMY2_c > vectMY2)){
			std::cout << "\033[31m" << "operator> TEST 1.2 " << "\033[0m" << std::endl;
			return false;
		}
		if ((vectSTD1 >= vectSTD1_c) != (vectMY2 >= vectMY2_c)){
			std::cout << "\033[31m" << "operator>= TEST 1.1 " << "\033[0m" << std::endl;
			return false;
		}
		if ((vectSTD1_c >= vectSTD1) != (vectMY2_c >= vectMY2)){
			std::cout << "\033[31m" << "operator>= TEST 1.2 " << "\033[0m" << std::endl;
			return false;
		}
		
	}
	{
		std::vector<int> vectSTD1(6, 5);
		std::vector<int> vectSTD1_c(5, 5);
		ft::vector<int> vectMY2(6, 5);
		ft::vector<int> vectMY2_c(5, 5);
		
		if ((vectSTD1 == vectSTD1_c) != (vectMY2 == vectMY2_c)){
			std::cout << "\033[31m" << "operator== TEST 2 " << "\033[0m" << std::endl;
			return false;
		}
		if ((vectSTD1 != vectSTD1_c) != (vectMY2 != vectMY2_c)){
			std::cout << "\033[31m" << "operator!= TEST 2 " << "\033[0m" << std::endl;
			return false;
		}
		if ((vectSTD1 < vectSTD1_c) != (vectMY2 < vectMY2_c)){
			std::cout << "\033[31m" << "operator< TEST 2.1 " << "\033[0m" << std::endl;
			return false;
		}
		if ((vectSTD1_c < vectSTD1) != (vectMY2_c < vectMY2)){
			std::cout << "\033[31m" << "operator< TEST 2.2 " << "\033[0m" << std::endl;
			return false;
		}
		if ((vectSTD1 <= vectSTD1_c) != (vectMY2 <= vectMY2_c)){
			std::cout << "\033[31m" << "operator<= TEST 2.1 " << "\033[0m" << std::endl;
			return false;
		}
		if ((vectSTD1_c <= vectSTD1) != (vectMY2_c <= vectMY2)){
			std::cout << "\033[31m" << "operator<= TEST 2.2 " << "\033[0m" << std::endl;
			return false;
		}
		if ((vectSTD1 > vectSTD1_c) != (vectMY2 > vectMY2_c)){
			std::cout << "\033[31m" << "operator> TEST 2.1 " << "\033[0m" << std::endl;
			return false;
		}
		if ((vectSTD1_c > vectSTD1) != (vectMY2_c > vectMY2)){
			std::cout << "\033[31m" << "operator> TEST 2.2 " << "\033[0m" << std::endl;
			return false;
		}
		if ((vectSTD1 >= vectSTD1_c) != (vectMY2 >= vectMY2_c)){
			std::cout << "\033[31m" << "operator>= TEST 2.1 " << "\033[0m" << std::endl;
			return false;
		}
		if ((vectSTD1_c >= vectSTD1) != (vectMY2_c >= vectMY2)){
			std::cout << "\033[31m" << "operator>= TEST 2.2 " << "\033[0m" << std::endl;
			return false;
		}
		

	}
	{
		std::vector<int> vectSTD1(5, 5);
		std::vector<int> vectSTD1_c(5, 6);
		ft::vector<int> vectMY2(5, 5);
		ft::vector<int> vectMY2_c(5, 6);
		
		if ((vectSTD1 == vectSTD1_c) != (vectMY2 == vectMY2_c)){
			std::cout << "\033[31m" << "operator== TEST 3 " << "\033[0m" << std::endl;
			return false;
		}
		if ((vectSTD1 != vectSTD1_c) != (vectMY2 != vectMY2_c)){
			std::cout << "\033[31m" << "operator!= TEST 3 " << "\033[0m" << std::endl;
			return false;
		}
		if ((vectSTD1 < vectSTD1_c) != (vectMY2 < vectMY2_c)){
			std::cout << "\033[31m" << "operator< TEST 3.1 " << "\033[0m" << std::endl;
			return false;
		}
		if ((vectSTD1_c < vectSTD1) != (vectMY2_c < vectMY2)){
			std::cout << "\033[31m" << "operator< TEST 3.2 " << "\033[0m" << std::endl;
			return false;
		}
		if ((vectSTD1 <= vectSTD1_c) != (vectMY2 <= vectMY2_c)){
			std::cout << "\033[31m" << "operator<= TEST 3.1 " << "\033[0m" << std::endl;
			return false;
		}
		if ((vectSTD1_c <= vectSTD1) != (vectMY2_c <= vectMY2)){
			std::cout << "\033[31m" << "operator<= TEST 3.2 " << "\033[0m" << std::endl;
			return false;
		}
		if ((vectSTD1 > vectSTD1_c) != (vectMY2 > vectMY2_c)){
			std::cout << "\033[31m" << "operator> TEST 3.1 " << "\033[0m" << std::endl;
			return false;
		}
		if ((vectSTD1_c > vectSTD1) != (vectMY2_c > vectMY2)){
			std::cout << "\033[31m" << "operator> TEST 3.2 " << "\033[0m" << std::endl;
			return false;
		}
		if ((vectSTD1 >= vectSTD1_c) != (vectMY2 >= vectMY2_c)){
			std::cout << "\033[31m" << "operator>= TEST 3.1 " << "\033[0m" << std::endl;
			return false;
		}
		if ((vectSTD1_c >= vectSTD1) != (vectMY2_c >= vectMY2)){
			std::cout << "\033[31m" << "operator>= TEST 3.2 " << "\033[0m" << std::endl;
			return false;
		}
	}
	std::cout << "\033[36m" << "Non-member swap:" << "\033[0m" << std::endl;
	{
		std::vector<int> vectSTD1(5, 5);
		std::vector<int> vectSTD1_c(10, 10);
		ft::vector<int> vectMY2(5, 5);
		ft::vector<int> vectMY2_c(10, 10);

		std::vector<int>::iterator it1 = vectSTD1.begin();
		ft::vector<int>::iterator it2 = vectMY2.begin();

		vectSTD1.swap(vectSTD1_c);
		vectMY2.swap(vectMY2_c);
		std::vector<int>::iterator it1_c  = vectSTD1.begin();
		ft::vector<int>::iterator it2_c = vectMY2.begin();

		if((it1 == it1_c) != (it2 == it2_c)) {
			std::cout << "\033[31m" << "Non-member swap TEST 0.1 " << "\033[0m" << std::endl;
			return false;
		}

		if (vectSTD1.capacity() != vectMY2.capacity() || vectSTD1.size() != vectMY2.size()) {
			std::cout << "\033[31m" << "Non-member swap TEST 1.1 " << "\033[0m" << std::endl;
			return false;
		}
		for (int i = 0; i < 10; ++i) {
			if (vectSTD1[i] != vectMY2[i]) {
				std::cout << "\033[31m" << "Non-member swap TEST 2.2 " << "\033[0m" << std::endl;
				return false;
			}
		}
		if (vectSTD1_c.capacity() != vectMY2_c.capacity() || vectSTD1_c.size() != vectMY2_c.size()) {
			std::cout << "\033[31m" << "Non-member swap TEST 1.3 " << "\033[0m" << std::endl;
			return false;
		}
		for (int i = 0; i < 5; ++i) {
			if (vectSTD1_c[i] != vectMY2_c[i]) {
				std::cout << "\033[31m" << "Non-member swap TEST 2.4 " << "\033[0m" << std::endl;
				return false;
			}
		}

	}
	return true;

}

bool test_VectorIterator() {
	std::cout << "\033[36m" << "iterator_traits" << "\033[0m" << std::endl;
	{
		typedef std::vector<int>::iterator itt;
		typedef ft::iterator_traits<itt> traits;
		if (typeid(traits::iterator_category)!=typeid(std::random_access_iterator_tag)) {
			std::cout << "\033[31m" << "TEST 1  " << "\033[0m" << std::endl;
			return false;
		}
		typedef ft::iterator_traits<int *> traits_i;
		if (typeid(traits_i::iterator_category)!=typeid(std::random_access_iterator_tag)) {
			std::cout << "\033[31m" << "TEST 1  " << "\033[0m" << std::endl;
			return false;
		}
		typedef ft::iterator_traits<const int *> traits_ci;
		if (typeid(traits_ci::iterator_category)!=typeid(std::random_access_iterator_tag)) {
			std::cout << "\033[31m" << "TEST 1  " << "\033[0m" << std::endl;
			return false;
		}
	}
	std::cout << "\033[36m" << "constuctor (1)" << "\033[0m" << std::endl;
	{
		ft::vector<int>::iterator it2;
		ft::vector<int>::const_iterator c_it2;
	}
	std::cout << "\033[36m" << "constuctor (private)" << "\033[0m" << std::endl;
//	{
//		std::cout << "\033[31m" << "uncomment private constructor " << "\033[0m" << std::endl;
//	}
	std::cout << "\033[36m" << "constuctor (1)" << "\033[0m" << std::endl;
	{
		std::vector<int> vectSTD1(10, 10);
		const std::vector<int> vectSTD1_c(10, 10);
		ft::vector<int> vectMY2(10, 10);
		const ft::vector<int> vectMY2_c(10, 10);

		std::vector<int>::iterator it1(vectSTD1.begin());
		std::vector<int>::const_iterator c_it1(vectSTD1_c.begin());
		ft::vector<int>::iterator it2(vectMY2.begin());
		ft::vector<int>::const_iterator c_it2(vectMY2_c.begin());

		std::vector<int>::iterator it1_c(it1);
		std::vector<int>::const_iterator c_it1_c(c_it1);
		ft::vector<int>::iterator it2_c(it2);
		ft::vector<int>::const_iterator c_it2_c(c_it2);

		if (*it1_c != *it2_c || *c_it1_c != *c_it2_c) {
			std::cout << "\033[31m" << "TEST 1  " << "\033[0m" << std::endl;
			return false;
		}
	}

	std::cout << "\033[36m" << "operator=(*)" << "\033[0m" << std::endl;
	{
		std::vector<int> vectSTD1(10, 10);
		const std::vector<int> vectSTD1_c(10, 10);
		ft::vector<int> vectMY2(10, 10);
		const ft::vector<int> vectMY2_c(10, 10);

		std::vector<int>::iterator it1(vectSTD1.begin());
		std::vector<int>::const_iterator c_it1(vectSTD1_c.begin());
		ft::vector<int>::iterator it2(vectMY2.begin());
		ft::vector<int>::const_iterator c_it2(vectMY2_c.begin());

		std::vector<int>::iterator it1_c = it1;
		std::vector<int>::const_iterator c_it1_c = c_it1;
		ft::vector<int>::iterator it2_c = it2;
		ft::vector<int>::const_iterator c_it2_c = c_it2;

		if (*it1_c != *it2_c || *c_it1_c != *c_it2_c) {
			std::cout << "\033[31m" << "TEST 1  " << "\033[0m" << std::endl;
			return false;
		}
		ft::vector<int>::const_iterator c_it2_cp(it2);
		(void)c_it2_cp;
	}

	std::cout << "\033[36m" << "base" << "\033[0m" << std::endl;
	{
		std::vector<int> vectSTD1(10, 10);
		const std::vector<int> vectSTD1_c(10, 10);
		ft::vector<int> vectMY2(10, 10);
		const ft::vector<int> vectMY2_c(10, 10);

		std::vector<int>::iterator it1(vectSTD1.begin());
		std::vector<int>::const_iterator c_it1(vectSTD1_c.begin());
		ft::vector<int>::iterator it2(vectMY2.begin());
		ft::vector<int>::const_iterator c_it2(vectMY2_c.begin());

		if (*it1.base() != *it2.base() || *c_it1.base() != *c_it2.base()) {
			std::cout << "\033[31m" << "TEST 1  " << "\033[0m" << std::endl;
			return false;
		}
	}

	std::cout << "\033[36m" << "operator+" << "\033[0m" << std::endl;
	{
		std::vector<int> vectSTD1;
		ft::vector<int> vectMY2;

		for (int i = 0; i < 10; ++i) {
			vectSTD1.push_back(i * 10);
			vectMY2.push_back(i * 10);
		}
		const std::vector<int> vectSTD1_c(vectSTD1);
		const ft::vector<int> vectMY2_c(vectMY2);

		std::vector<int>::iterator it1(vectSTD1.begin());
		std::vector<int>::const_iterator c_it1(vectSTD1_c.begin());
		ft::vector<int>::iterator it2(vectMY2.begin());
		ft::vector<int>::const_iterator c_it2(vectMY2_c.begin());


		if (*(it1 + 5) != *(it2 + 5) || *(c_it1 + 5) != *(c_it2 + 5)) {
			std::cout << "\033[31m" << "TEST 1  " << "\033[0m" << std::endl;
			return false;
		}
	}

	std::cout << "\033[36m" << "operator++" << "\033[0m" << std::endl;
	{
		std::vector<int> vectSTD1;
		ft::vector<int> vectMY2;

		for (int i = 0; i < 10; ++i) {
			vectSTD1.push_back(i * 10);
			vectMY2.push_back(i * 10);
		}
		const std::vector<int> vectSTD1_c(vectSTD1);
		const ft::vector<int> vectMY2_c(vectMY2);

		std::vector<int>::iterator it1(vectSTD1.begin());
		std::vector<int>::const_iterator c_it1(vectSTD1_c.begin());
		ft::vector<int>::iterator it2(vectMY2.begin());
		ft::vector<int>::const_iterator c_it2(vectMY2_c.begin());


		if (*(it1++) != *(it2++) || *(c_it1++) != *(c_it2++)) {
			std::cout << "\033[31m" << "TEST 1  " << "\033[0m" << std::endl;
			return false;
		}
		if (*(it1) != *(it2) || *(c_it1) != *(c_it2)) {
			std::cout << "\033[31m" << "TEST 2  " << "\033[0m" << std::endl;
			return false;
		}
		if (*(++it1) != *(++it2) || *(++c_it1) != *(++c_it2)) {
			std::cout << "\033[31m" << "TEST 3  " << "\033[0m" << std::endl;
			return false;
		}
		if (*(it1) != *(it2) || *(c_it1) != *(c_it2)) {
			std::cout << "\033[31m" << "TEST 4  " << "\033[0m" << std::endl;
			return false;
		}
	}
	std::cout << "\033[36m" << "operator+=" << "\033[0m" << std::endl;
	{
		std::vector<int> vectSTD1;
		ft::vector<int> vectMY2;

		for (int i = 0; i < 10; ++i) {
			vectSTD1.push_back(i * 10);
			vectMY2.push_back(i * 10);
		}
		const std::vector<int> vectSTD1_c(vectSTD1);
		const ft::vector<int> vectMY2_c(vectMY2);

		std::vector<int>::iterator it1(vectSTD1.begin());
		std::vector<int>::const_iterator c_it1(vectSTD1_c.begin());
		ft::vector<int>::iterator it2(vectMY2.begin());
		ft::vector<int>::const_iterator c_it2(vectMY2_c.begin());

		it1 += 5;
		c_it1 += 5;
		it2 += 5;
		c_it2 += 5;

		if (*(it1) != *(it2) || *(c_it1) != *(c_it2)) {
			std::cout << "\033[31m" << "TEST 1  " << "\033[0m" << std::endl;
			return false;
		}
	}

	std::cout << "\033[36m" << "operator-" << "\033[0m" << std::endl;
	{
		std::vector<int> vectSTD1;
		ft::vector<int> vectMY2;

		for (int i = 0; i < 10; ++i) {
			vectSTD1.push_back(i * 10);
			vectMY2.push_back(i * 10);
		}
		const std::vector<int> vectSTD1_c(vectSTD1);
		const ft::vector<int> vectMY2_c(vectMY2);

		std::vector<int>::iterator it1(vectSTD1.end());
		std::vector<int>::const_iterator c_it1(vectSTD1_c.end());
		ft::vector<int>::iterator it2(vectMY2.end());
		ft::vector<int>::const_iterator c_it2(vectMY2_c.end());


		if (*(it1 - 5) != *(it2 - 5) || *(c_it1 - 5) != *(c_it2 - 5)) {
			std::cout << "\033[31m" << "TEST 1  " << "\033[0m" << std::endl;
			return false;
		}
	}

	std::cout << "\033[36m" << "operator--" << "\033[0m" << std::endl;
	{
		std::vector<int> vectSTD1;
		ft::vector<int> vectMY2;

		for (int i = 0; i < 10; ++i) {
			vectSTD1.push_back(i * 10);
			vectMY2.push_back(i * 10);
		}
		const std::vector<int> vectSTD1_c(vectSTD1);
		const ft::vector<int> vectMY2_c(vectMY2);

		std::vector<int>::iterator it1(vectSTD1.end() - 1);
		std::vector<int>::const_iterator c_it1(vectSTD1_c.end() - 1);
		ft::vector<int>::iterator it2(vectMY2.end() - 1);
		ft::vector<int>::const_iterator c_it2(vectMY2_c.end() - 1);


		if (*(it1--) != *(it2--) || *(c_it1--) != *(c_it2--)) {
			std::cout << "\033[31m" << "TEST 1  " << "\033[0m" << std::endl;
			return false;
		}
		if (*(it1) != *(it2) || *(c_it1) != *(c_it2)) {
			std::cout << "\033[31m" << "TEST 2  " << "\033[0m" << std::endl;
			return false;
		}
		if (*(--it1) != *(--it2) || *(--c_it1) != *(--c_it2)) {
			std::cout << "\033[31m" << "TEST 3  " << "\033[0m" << std::endl;
			return false;
		}
		if (*(it1) != *(it2) || *(c_it1) != *(c_it2)) {
			std::cout << "\033[31m" << "TEST 4  " << "\033[0m" << std::endl;
			return false;
		}
	}
	std::cout << "\033[36m" << "operator-=" << "\033[0m" << std::endl;
	{
		std::vector<int> vectSTD1;
		ft::vector<int> vectMY2;

		for (int i = 0; i < 10; ++i) {
			vectSTD1.push_back(i * 10);
			vectMY2.push_back(i * 10);
		}
		const std::vector<int> vectSTD1_c(vectSTD1);
		const ft::vector<int> vectMY2_c(vectMY2);

		std::vector<int>::iterator it1(vectSTD1.end());
		std::vector<int>::const_iterator c_it1(vectSTD1_c.end());
		ft::vector<int>::iterator it2(vectMY2.end());
		ft::vector<int>::const_iterator c_it2(vectMY2_c.end());

		it1 -= 5;
		c_it1 -= 5;
		it2 -= 5;
		c_it2 -= 5;

		if (*(it1) != *(it2) || *(c_it1) != *(c_it2)) {
			std::cout << "\033[31m" << "TEST 1  " << "\033[0m" << std::endl;
			return false;
		}
	}

	std::cout << "\033[36m" << "operator[]" << "\033[0m" << std::endl;
	{
		std::vector<int> vectSTD1;
		ft::vector<int> vectMY2;

		for (int i = 0; i < 10; ++i) {
			vectSTD1.push_back(i * 10);
			vectMY2.push_back(i * 10);
		}
		const std::vector<int> vectSTD1_c(vectSTD1);
		const ft::vector<int> vectMY2_c(vectMY2);

		std::vector<int>::iterator it1(vectSTD1.begin());
		std::vector<int>::const_iterator c_it1(vectSTD1_c.begin());
		ft::vector<int>::iterator it2(vectMY2.begin());
		ft::vector<int>::const_iterator c_it2(vectMY2_c.begin());

		for (int i = 0; i < 10; ++i) {
			if (it1[i] != it2[i] || c_it1[i] != c_it2[i]) {
				std::cout << "\033[31m" << "TEST 1  " << "\033[0m" << std::endl;
				return false;
			}
		}
	}
	std::cout << "\033[36m" << "relational operators" << "\033[0m" << std::endl;
	{
		std::vector<int> vectSTD1;
		ft::vector<int> vectMY2;

		for (int i = 0; i < 10; ++i) {
			vectSTD1.push_back(i * 10);
			vectMY2.push_back(i * 10);
		}
		const std::vector<int> vectSTD1_c(vectSTD1);
		const ft::vector<int> vectMY2_c(vectMY2);

		std::vector<int>::iterator it1(vectSTD1.begin());
		std::vector<int>::const_iterator c_it1(vectSTD1_c.begin());
		ft::vector<int>::iterator it2(vectMY2.begin());
		ft::vector<int>::const_iterator c_it2(vectMY2_c.begin());

		std::vector<int>::iterator it1_e(vectSTD1.end());
		std::vector<int>::const_iterator c_it1_e(vectSTD1_c.end());
		ft::vector<int>::iterator it2_e(vectMY2.end());
		ft::vector<int>::const_iterator c_it2_e(vectMY2_c.end());

		if ((it1 == it1_e) != (it2 == it2_e)) {
			std::cout << "\033[31m" << "non-const operator== TEST 1.1  " << "\033[0m" << std::endl;
			return false;
		}
		if ((c_it1 == c_it1_e) != (c_it2 == c_it2_e)) {
			std::cout << "\033[31m" << "const operator== TEST 1.1  " << "\033[0m" << std::endl;
			return false;
		}
		if ((it1 != it1_e) != (it2 != it2_e)) {
			std::cout << "\033[31m" << "non-const operator!= TEST 1.1  " << "\033[0m" << std::endl;
			return false;
		}
		if ((c_it1 != c_it1_e) != (c_it2 != c_it2_e)) {
			std::cout << "\033[31m" << "const operator!= TEST 1.1  " << "\033[0m" << std::endl;
			return false;
		}
		if ((it1 < it1_e) != (it2 < it2_e)) {
			std::cout << "\033[31m" << "non-const operator< TEST 1.1  " << "\033[0m" << std::endl;
			return false;
		}
		if ((c_it1 < c_it1_e) != (c_it2 < c_it2_e)) {
			std::cout << "\033[31m" << "const operator< TEST 1.1  " << "\033[0m" << std::endl;
			return false;
		}
		if ((it1 <= it1_e) != (it2 <= it2_e)) {
			std::cout << "\033[31m" << "non-const operator<= TEST 1.1  " << "\033[0m" << std::endl;
			return false;
		}
		if ((c_it1 <= c_it1_e) != (c_it2 <= c_it2_e)) {
			std::cout << "\033[31m" << "const operator<= TEST 1.1  " << "\033[0m" << std::endl;
			return false;
		}
		if ((it1 > it1_e) != (it2 > it2_e)) {
			std::cout << "\033[31m" << "non-const operator> TEST 1.1  " << "\033[0m" << std::endl;
			return false;
		}
		if ((c_it1 > c_it1_e) != (c_it2 > c_it2_e)) {
			std::cout << "\033[31m" << "const operator> TEST 1.1  " << "\033[0m" << std::endl;
			return false;
		}
		if ((it1 >= it1_e) != (it2 >= it2_e)) {
			std::cout << "\033[31m" << "non-const operator>= TEST 1.1  " << "\033[0m" << std::endl;
			return false;
		}
		if ((c_it1 >= c_it1_e) != (c_it2 >= c_it2_e)) {
			std::cout << "\033[31m" << "const operator>= TEST 1.1  " << "\033[0m" << std::endl;
			return false;
		}
	}
	{
		std::vector<int> vectSTD1;
		ft::vector<int> vectMY2;

		for (int i = 0; i < 10; ++i) {
			vectSTD1.push_back(i * 10);
			vectMY2.push_back(i * 10);
		}
		const std::vector<int> vectSTD1_c(vectSTD1);
		const ft::vector<int> vectMY2_c(vectMY2);

		std::vector<int>::iterator it1(vectSTD1.begin());
		std::vector<int>::const_iterator c_it1(vectSTD1_c.begin());
		ft::vector<int>::iterator it2(vectMY2.begin());
		ft::vector<int>::const_iterator c_it2(vectMY2_c.begin());

		std::vector<int>::iterator it1_e(vectSTD1.begin());
		std::vector<int>::const_iterator c_it1_e(vectSTD1_c.begin());
		ft::vector<int>::iterator it2_e(vectMY2.begin());
		ft::vector<int>::const_iterator c_it2_e(vectMY2_c.begin());

		if ((it1 == it1_e) != (it2 == it2_e)) {
			std::cout << "\033[31m" << "non-const operator== TEST 2.1  " << "\033[0m" << std::endl;
			return false;
		}
		if ((c_it1 == c_it1_e) != (c_it2 == c_it2_e)) {
			std::cout << "\033[31m" << "const operator== TEST 2.1  " << "\033[0m" << std::endl;
			return false;
		}
		if ((it1 != it1_e) != (it2 != it2_e)) {
			std::cout << "\033[31m" << "non-const operator!= TEST 2.1  " << "\033[0m" << std::endl;
			return false;
		}
		if ((c_it1 != c_it1_e) != (c_it2 != c_it2_e)) {
			std::cout << "\033[31m" << "const operator!= TEST 2.1  " << "\033[0m" << std::endl;
			return false;
		}
		if ((it1 < it1_e) != (it2 < it2_e)) {
			std::cout << "\033[31m" << "non-const operator< TEST 2.1  " << "\033[0m" << std::endl;
			return false;
		}
		if ((c_it1 < c_it1_e) != (c_it2 < c_it2_e)) {
			std::cout << "\033[31m" << "const operator< TEST 2.1  " << "\033[0m" << std::endl;
			return false;
		}
		if ((it1 <= it1_e) != (it2 <= it2_e)) {
			std::cout << "\033[31m" << "non-const operator<= TEST 2.1  " << "\033[0m" << std::endl;
			return false;
		}
		if ((c_it1 <= c_it1_e) != (c_it2 <= c_it2_e)) {
			std::cout << "\033[31m" << "const operator<= TEST 2.1  " << "\033[0m" << std::endl;
			return false;
		}
		if ((it1 > it1_e) != (it2 > it2_e)) {
			std::cout << "\033[31m" << "non-const operator> TEST 2.1  " << "\033[0m" << std::endl;
			return false;
		}
		if ((c_it1 > c_it1_e) != (c_it2 > c_it2_e)) {
			std::cout << "\033[31m" << "const operator> TEST 2.1  " << "\033[0m" << std::endl;
			return false;
		}
		if ((it1 >= it1_e) != (it2 >= it2_e)) {
			std::cout << "\033[31m" << "non-const operator>= TEST 2.1  " << "\033[0m" << std::endl;
			return false;
		}
		if ((c_it1 >= c_it1_e) != (c_it2 >= c_it2_e)) {
			std::cout << "\033[31m" << "const operator>= TEST 2.1  " << "\033[0m" << std::endl;
			return false;
		}
	}
	{
		std::vector<int> vectSTD1;
		ft::vector<int> vectMY2;

		for (int i = 0; i < 10; ++i) {
			vectSTD1.push_back(i * 10);
			vectMY2.push_back(i * 10);
		}
		const std::vector<int> vectSTD1_c(vectSTD1);
		const ft::vector<int> vectMY2_c(vectMY2);

		std::vector<int>::iterator it1(vectSTD1.end());
		std::vector<int>::const_iterator c_it1(vectSTD1_c.end());
		ft::vector<int>::iterator it2(vectMY2.end());
		ft::vector<int>::const_iterator c_it2(vectMY2_c.end());

		std::vector<int>::iterator it1_e(vectSTD1.begin());
		std::vector<int>::const_iterator c_it1_e(vectSTD1_c.begin());
		ft::vector<int>::iterator it2_e(vectMY2.begin());
		ft::vector<int>::const_iterator c_it2_e(vectMY2_c.begin());

		if ((it1 == it1_e) != (it2 == it2_e)) {
			std::cout << "\033[31m" << "non-const operator== TEST 3.1  " << "\033[0m" << std::endl;
			return false;
		}
		if ((c_it1 == c_it1_e) != (c_it2 == c_it2_e)) {
			std::cout << "\033[31m" << "const operator== TEST 3.1  " << "\033[0m" << std::endl;
			return false;
		}
		if ((it1 != it1_e) != (it2 != it2_e)) {
			std::cout << "\033[31m" << "non-const operator!= TEST 3.1  " << "\033[0m" << std::endl;
			return false;
		}
		if ((c_it1 != c_it1_e) != (c_it2 != c_it2_e)) {
			std::cout << "\033[31m" << "const operator!= TEST 3.1  " << "\033[0m" << std::endl;
			return false;
		}
		if ((it1 < it1_e) != (it2 < it2_e)) {
			std::cout << "\033[31m" << "non-const operator< TEST 3.1  " << "\033[0m" << std::endl;
			return false;
		}
		if ((c_it1 < c_it1_e) != (c_it2 < c_it2_e)) {
			std::cout << "\033[31m" << "const operator< TEST 3.1  " << "\033[0m" << std::endl;
			return false;
		}
		if ((it1 <= it1_e) != (it2 <= it2_e)) {
			std::cout << "\033[31m" << "non-const operator<= TEST 3.1  " << "\033[0m" << std::endl;
			return false;
		}
		if ((c_it1 <= c_it1_e) != (c_it2 <= c_it2_e)) {
			std::cout << "\033[31m" << "const operator<= TEST 3.1  " << "\033[0m" << std::endl;
			return false;
		}
		if ((it1 > it1_e) != (it2 > it2_e)) {
			std::cout << "\033[31m" << "non-const operator> TEST 3.1  " << "\033[0m" << std::endl;
			return false;
		}
		if ((c_it1 > c_it1_e) != (c_it2 > c_it2_e)) {
			std::cout << "\033[31m" << "const operator> TEST 3.1  " << "\033[0m" << std::endl;
			return false;
		}
		if ((it1 >= it1_e) != (it2 >= it2_e)) {
			std::cout << "\033[31m" << "non-const operator>= TEST 3.1  " << "\033[0m" << std::endl;
			return false;
		}
		if ((c_it1 >= c_it1_e) != (c_it2 >= c_it2_e)) {
			std::cout << "\033[31m" << "const operator>= TEST 3.1  " << "\033[0m" << std::endl;
			return false;
		}
	}
	std::cout << "\033[36m" << "non_meber operators+" << "\033[0m" << std::endl;
	{
		std::vector<int> vectSTD1;
		ft::vector<int> vectMY2;

		for (int i = 0; i < 10; ++i) {
			vectSTD1.push_back(i * 10);
			vectMY2.push_back(i * 10);
		}
		const std::vector<int> vectSTD1_c(vectSTD1);
		const ft::vector<int> vectMY2_c(vectMY2);

		std::vector<int>::iterator it1_c(vectSTD1.begin());
		std::vector<int>::const_iterator c_it1_c(vectSTD1_c.begin());
		ft::vector<int>::iterator it2_c(vectMY2.begin());
		ft::vector<int>::const_iterator c_it2_c(vectMY2_c.begin());

		std::vector<int>::iterator it1 = it1_c + 5;
		std::vector<int>::const_iterator c_it1 = c_it1_c + 5;
		ft::vector<int>::iterator it2 = it2_c + 5;
		ft::vector<int>::const_iterator c_it2 = c_it2_c + 5;

		if (*(it1) != *(it2) || *(c_it1) != *(c_it2)) {
			std::cout << "\033[31m" << "TEST 1  " << "\033[0m" << std::endl;
			return false;
		}
	}
	std::cout << "\033[36m" << "non_meber operators-" << "\033[0m" << std::endl;
	{
		std::vector<int> vectSTD1;
		ft::vector<int> vectMY2;

		for (int i = 0; i < 10; ++i) {
			vectSTD1.push_back(i * 10);
			vectMY2.push_back(i * 10);
		}
		const std::vector<int> vectSTD1_c(vectSTD1);
		const ft::vector<int> vectMY2_c(vectMY2);

		std::vector<int>::iterator it1_c(vectSTD1.end());
		std::vector<int>::const_iterator c_it1_c(vectSTD1_c.end());
		ft::vector<int>::iterator it2_c(vectMY2.end());
		ft::vector<int>::const_iterator c_it2_c(vectMY2_c.end());

		std::vector<int>::iterator it1 = it1_c - 5;
		std::vector<int>::const_iterator c_it1 = c_it1_c - 5;
		ft::vector<int>::iterator it2 = it2_c - 5;
		ft::vector<int>::const_iterator c_it2 = c_it2_c - 5;

		if (*(it1) != *(it2) || *(c_it1) != *(c_it2)) {
			std::cout << "\033[31m" << "TEST 1  " << "\033[0m" << std::endl;
			return false;
		}
	}

	return true;
}

bool test_RBT() {

    return true;
}


bool test_map_iterator() {
	std::cout << "\033[36m" << "constructor(1) " << "\033[0m" << std::endl;
	{
		ft::map<int, int>::iterator it;		
	}
	std::cout << "\033[36m" << "constructor(copy) " << "\033[0m" << std::endl;
	{
		std::map<int, int> mSTD1;
		ft::map<int, int> mMY2;
		mSTD1.insert(std::make_pair(100, 100));
		mMY2.insert(ft::make_pair(100, 100));
		std::map<int, int>::iterator it1(mSTD1.begin());
		ft::map<int, int>::iterator it2(mMY2.begin());
		if ((*it1).second != (*it2).second) {
			std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
			return false;
		}
	}
	std::cout << "\033[36m" << "operator++(--) " << "\033[0m" << std::endl;
	{
		
		std::map<int, int> mSTD1;
		ft::map<int, int> mMY2;
		mSTD1.insert(std::make_pair(10, 10));
		mMY2.insert(ft::make_pair(10, 10));
		mSTD1.insert(std::make_pair(20, 20));
		mMY2.insert(ft::make_pair(20, 20));
		mSTD1.insert(std::make_pair(30, 30));
		mMY2.insert(ft::make_pair(30, 30));
		mSTD1.insert(std::make_pair(40, 40));
		mMY2.insert(ft::make_pair(40, 40));
		mSTD1.insert(std::make_pair(50, 50));
		mMY2.insert(ft::make_pair(50, 50));
		mSTD1.insert(std::make_pair(60, 60));
		mMY2.insert(ft::make_pair(60, 60));
		mSTD1.insert(std::make_pair(70, 70));
		mMY2.insert(ft::make_pair(70, 70));
		mSTD1.insert(std::make_pair(80, 80));
		mMY2.insert(ft::make_pair(80, 80));
		mSTD1.insert(std::make_pair(90, 90));
		mMY2.insert(ft::make_pair(90, 90));
		mSTD1.insert(std::make_pair(100, 100));
		mMY2.insert(ft::make_pair(100, 100));
		

		std::map<int, int>::iterator it1(mSTD1.begin());
		ft::map<int, int>::iterator it2(mMY2.begin());
		for (int i = 0; i < 10; i++) {
			if ((*it1).second != (*it2).second) {
				std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
				return false;
			}
			it1++;
			it2++;

		}
		for (int i = 0; i < 10; i++) {
			it1--;
			it2--;
			if ((*it1).second != (*it2).second) {
				std::cout << "\033[31m" << "TEST 2 " << "\033[0m" << std::endl;
				return false;
			}
		}
	}
	std::cout << "\033[36m" << "operator==(!=)" << "\033[0m" << std::endl;
	{
		std::map<int, int> mSTD1;
		ft::map<int, int> mMY2;

		for (int i = 0; i < 10; ++i) {
			mSTD1.insert(std::make_pair(i * 10, i * 10));
			mMY2.insert(ft::make_pair(i * 10, i * 10));
		}


	
		std::map<int, int>::iterator it1(mSTD1.begin());
		ft::map<int, int>::iterator it2(mMY2.begin());
		std::map<int, int>::iterator it1_e(mSTD1.end());
		ft::map<int, int>::iterator it2_e(mMY2.end());
		for (int i = 0; i < 10; i++) {
			if ((it1 == it1_e) != (it2 == it2_e)) {
				std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
				return false;
			}
			it1++;
			it2++;
		}
		if ((it1 != it1_e) != (it2 != it2_e)) {
			std::cout << "\033[31m" << "TEST 2 " << "\033[0m" << std::endl;
			return false;
		}
	}
	return true;
}

bool test_map() {
	std::cout << "\033[36m" << "constructor (1)" << "\033[0m" << std::endl;
	{
		std::map<int, int> mSTD1;
		ft::map<int, int> mMY2;
	}
	std::cout << "\033[36m" << "constructor (2)" << "\033[0m" << std::endl;
	{
		std::map<int, int> mSTD1;
		ft::map<int, int> mMY2;

		for (int i = 0; i < 10; ++i) {
			mSTD1.insert(std::make_pair(i * 10, i * 10));
			mMY2.insert(ft::make_pair(i * 10, i * 10));
		}
		std::map<int, int> mSTD1_c(mSTD1.begin(), mSTD1.end());
		ft::map<int, int> mMY2_c(mMY2.begin(), mMY2.end());
		
		std::map<int, int>::iterator it1(mSTD1_c.begin());
		ft::map<int, int>::iterator it2(mMY2_c.begin());
		for (int i = 0; i < 10; i++) {
			if ((*it1).second != (*it2).second) {
				std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
				return false;
			}
			it1++;
			it2++;
		}
	}

	std::cout << "\033[36m" << "constructor (3)" << "\033[0m" << std::endl;
	{
		ft::map<int, int> mMY2;

		for (int i = 0; i < 10; ++i) {
			mMY2.insert(ft::make_pair(i * 10, i * 10));
		}
		ft::map<int, int> mMY2_c(mMY2);

		ft::map<int, int>::iterator it2(mMY2.begin());
		ft::map<int, int>::iterator it2_c(mMY2_c.begin());

		for (int i = 0; i < 10; ++i) {
			if ((*it2_c).second != (*it2).second) {
				std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
				return false;
			}
			it2_c++;
			it2++;
		}
	}
	std::cout << "\033[36m" << "operator=" << "\033[0m" << std::endl;
	{
		ft::map<int, int> mMY2;

		for (int i = 0; i < 10; ++i) {
			mMY2.insert(ft::make_pair(i * 10, i * 10));
		}
		ft::map<int, int> mMY2_c = mMY2;

		ft::map<int, int>::iterator it2(mMY2.begin());
		ft::map<int, int>::iterator it2_c(mMY2_c.begin());

		for (int i = 0; i < 10; ++i) {
			if ((*it2_c).second != (*it2).second) {
				std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
				return false;
			}
			it2_c++;
			it2++;
		}
		if (mMY2.size() != mMY2_c.size()) {
			std::cout << "\033[31m" << "TEST 2 " << "\033[0m" << std::endl;
			return false;
		}
	}

	std::cout << "\033[36m" << "empty" << "\033[0m" << std::endl;
	{
		std::map<int, int> mSTD1;
		ft::map<int, int> mMY2;

		if (mSTD1.empty() != mMY2.empty()) {
			std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
			return false;
		}
		for (int i = 0; i < 10; ++i) {
			mSTD1.insert(std::make_pair(i * 10, i * 10));
			mMY2.insert(ft::make_pair(i * 10, i * 10));
		}
		if (mSTD1.empty() != mMY2.empty()) {
			std::cout << "\033[31m" << "TEST 2 " << "\033[0m" << std::endl;
			return false;
		}
	}
	std::cout << "\033[36m" << "size" << "\033[0m" << std::endl;
	{
		std::map<int, int> mSTD1;
		ft::map<int, int> mMY2;

		if (mSTD1.size() != mMY2.size()) {
			std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
			return false;
		}
		for (int i = 0; i < 10; ++i) {
			mSTD1.insert(std::make_pair(i * 10, i * 10));
			mMY2.insert(ft::make_pair(i * 10, i * 10));
			if (mSTD1.size() != mMY2.size()) {
				std::cout << "\033[31m" << "TEST 2 " << "\033[0m" << std::endl;
				return false;
			}
		}
	}
	std::cout << "\033[36m" << "operator[]" << "\033[0m" << std::endl;
	{
		std::map<int, int> mSTD1;
		ft::map<int, int> mMY2;

		for (int i = 0; i < 10; ++i) {
			mSTD1.insert(std::make_pair(i * 10, i * 10));
			mMY2.insert(ft::make_pair(i * 10, i * 10));
		}
		if (mSTD1[80] != mMY2[80]) {
			std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
			return false;
		}
		mSTD1[500] = 500;
		mMY2[500] = 500;
	}
	{
		ft::map<int, int> mMY2;
		mMY2[500] = 500;
	}
	std::cout << "\033[36m" << "insert(1)" << "\033[0m" << std::endl;
	{
		std::map<int, int> mSTD1;
		ft::map<int, int> mMY2;
		for (int i = 0; i < 10; ++i) {
			mSTD1.insert(std::make_pair(i * 10, i * 10));
			mMY2.insert(ft::make_pair(i * 10, i * 10));
		}
		std::pair<std::map<int,int>::iterator, bool > p1;
		ft::pair<ft::map<int,int>::iterator, bool > p2;

		p1 = mSTD1.insert(std::make_pair(50, 50));
		p2 = mMY2.insert(ft::make_pair(50, 50));
		if (mSTD1.size()!= mMY2.size()) {
			std::cout << "\033[31m" << "TEST 2.1 " << "\033[0m" << std::endl;
			return false;
		}
		if (p1.second != p2.second) {
			std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
			return false;
		}
		if (p1.first->second != p2.first->second) {
			std::cout << "\033[31m" << "TEST 2 " << "\033[0m" << std::endl;
			return false;
		}
		p1 = mSTD1.insert(std::make_pair(500, 500));
		p2 = mMY2.insert(ft::make_pair(500, 500));
		if (mSTD1.size()!= mMY2.size()) {
			std::cout << "\033[31m" << "TEST 2.2 " << "\033[0m" << std::endl;
			return false;
		}
		if (p1.second != p2.second) {
			std::cout << "\033[31m" << "TEST 3 " << "\033[0m" << std::endl;
			return false;
		}
		if (p1.first->second != p2.first->second) {
			std::cout << "\033[31m" << "TEST 4 " << "\033[0m" << std::endl;
			return false;
		}

	}
	std::cout << "\033[36m" << "insert(2)" << "\033[0m" << std::endl;
	{
		std::map<int, int> mSTD1;
		ft::map<int, int> mMY2;
		for (int i = 0; i < 10; ++i) {
			mSTD1.insert(std::make_pair(i * 10, i * 10));
			mMY2.insert(ft::make_pair(i * 10, i * 10));
		}
		if (mSTD1.size()!= mMY2.size()) {
			std::cout << "\033[31m" << "TEST 1.1 " << "\033[0m" << std::endl;
			return false;
		}
		std::map<int,int>::iterator it1 = mSTD1.begin();
		ft::map<int,int>::iterator it2 = mMY2.begin();

		it1 = mSTD1.insert(it1, std::make_pair(50, 50));
		it2 = mMY2.insert(it2, ft::make_pair(50, 50));
		if (it1->second != it2->second) {
			std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
			return false;
		}
		if (mSTD1.size()!= mMY2.size()) {
			std::cout << "\033[31m" << "TEST 2.2 " << "\033[0m" << std::endl;
			return false;
		}
	}
	std::cout << "\033[36m" << "insert(3)" << "\033[0m" << std::endl;
	{
		std::map<int, int> mSTD1;
		ft::map<int, int> mMY2;
		for (int i = 0; i < 10; ++i) {
			mSTD1.insert(std::make_pair(i * 10, i * 10));
			mMY2.insert(ft::make_pair(i * 10, i * 10));
		}
		std::map<int, int> mSTD1_c;
		ft::map<int, int> mMY2_c;

		mSTD1_c.insert(mSTD1.begin(), mSTD1.end()); 
		mMY2_c.insert(mMY2.begin(), mMY2.end());

		std::map<int,int>::iterator it1 = mSTD1_c.begin();
		ft::map<int,int>::iterator it2 = mMY2_c.begin();
		for(int i =0; i < 10; i++) {
			if (it1->second != it2->second) {
				std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
				return false;
			}
			it1++;
			it2++;
		}
		if (mSTD1_c.size()!= mMY2_c.size()) {
			std::cout << "\033[31m" << "TEST 2.1 " << "\033[0m" << std::endl;
			return false;
		}
	}
	std::cout << "\033[36m" << "erase(1)" << "\033[0m" << std::endl;
	{
		std::map<int, int> mSTD1;
		ft::map<int, int> mMY2;
		for (int i = 0; i < 10; ++i) {
			mSTD1.insert(std::make_pair(i * 10, i * 10));
			mMY2.insert(ft::make_pair(i * 10, i * 10));
		}

		mSTD1.erase(mSTD1.begin());
		mMY2.erase(mMY2.begin());

		std::map<int,int>::iterator it1 = mSTD1.begin();
		ft::map<int,int>::iterator it2 = mMY2.begin();
		for(int i =0; i < 9; i++) {
			if (it1->second != it2->second) {
				std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
				return false;
			}
			it1++;
			it2++;
		}
		if (mSTD1.size()!= mMY2.size()) {
			std::cout << "\033[31m" << "TEST 2.1 " << "\033[0m" << std::endl;
			return false;
		}
	}
	std::cout << "\033[36m" << "erase(2)" << "\033[0m" << std::endl;
	{
		std::map<int, int> mSTD1;
		ft::map<int, int> mMY2;
		for (int i = 0; i < 10; ++i) {
			mSTD1.insert(std::make_pair(i * 10, i * 10));
			mMY2.insert(ft::make_pair(i * 10, i * 10));
		}
		size_t s1 = mSTD1.erase(50);
		size_t s2 = mMY2.erase(50);
		if (s1 != s2) {
			std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
			return false;
		}
		s1 = mSTD1.erase(500);
		s2 = mMY2.erase(500);
		if (s1 != s2) {
			std::cout << "\033[31m" << "TEST 2 " << "\033[0m" << std::endl;
			return false;
		}
		
		
		std::map<int,int>::iterator it1 = mSTD1.begin();
		ft::map<int,int>::iterator it2 = mMY2.begin();
		for(int i =0; i < 9; i++) {
			if (it1->second != it2->second) {
				std::cout << "\033[31m" << "TEST 3 " << "\033[0m" << std::endl;
				return false;
			}
			it1++;
			it2++;
		}
		if (mSTD1.size()!= mMY2.size()) {
			std::cout << "\033[31m" << "TEST 4 " << "\033[0m" << std::endl;
			return false;
		}
	}
	std::cout << "\033[36m" << "erase(3)" << "\033[0m" << std::endl;
	{
		std::map<int, int> mSTD1;
		ft::map<int, int> mMY2;
		for (int i = 0; i < 10; ++i) {
			mSTD1.insert(std::make_pair(i * 10, i * 10));
			mMY2.insert(ft::make_pair(i * 10, i * 10));
		}
		mSTD1.erase(mSTD1.begin(), mSTD1.end());
		mMY2.erase(mMY2.begin(), mMY2.end());
		if (mSTD1.size()!= mMY2.size()) {
			std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
			return false;
		}
		
		if (mSTD1.empty()!= mMY2.empty()) {
			std::cout << "\033[31m" << "TEST 2 " << "\033[0m" << std::endl;
			return false;
		}
		
	}
	std::cout << "\033[36m" << "swap" << "\033[0m" << std::endl;
	{
		std::map<int, int> mSTD1;
		ft::map<int, int> mMY2;
		for (int i = 0; i < 10; ++i) {
			mSTD1.insert(std::make_pair(i * 10, i * 10));
			mMY2.insert(ft::make_pair(i * 10, i * 10));
		}
		std::map<int, int> mSTD1_c;
		ft::map<int, int> mMY2_c;
		for (int i = 10; i < 15; ++i) {
			mSTD1_c.insert(std::make_pair(i * 10, i * 10));
			mMY2_c.insert(ft::make_pair(i * 10, i * 10));
		}
		mSTD1.swap(mSTD1_c);
		mMY2.swap(mMY2_c);
		if (mSTD1.size()!= mMY2.size()) {
			std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
			return false;
		}
		if (mSTD1_c.size()!= mMY2_c.size()) {
			std::cout << "\033[31m" << "TEST 2 " << "\033[0m" << std::endl;
			return false;
		}
		std::map<int,int>::iterator it1 = mSTD1.begin();
		ft::map<int,int>::iterator it2 = mMY2.begin();

		for (int i = 0; i < 5; ++i)
		{
			if (it1->second != it2->second) {
				std::cout << "\033[31m" << "TEST 3 " << "\033[0m" << std::endl;
				return false;
			}
			it1++;
			it2++;
		}
		it1 = mSTD1_c.begin();
		it2 = mMY2_c.begin();
		for (int i = 0; i < 10; ++i)
		{
			if (it1->second != it2->second) {
				std::cout << "\033[31m" << "TEST 4 " << "\033[0m" << std::endl;
				return false;
			}
			it1++;
			it2++;
		}
	}
	std::cout << "\033[36m" << "clear" << "\033[0m" << std::endl;
	{
		std::map<int, int> mSTD1;
		ft::map<int, int> mMY2;
		for (int i = 0; i < 10; ++i) {
			mSTD1.insert(std::make_pair(i * 10, i * 10));
			mMY2.insert(ft::make_pair(i * 10, i * 10));
		}
		mSTD1.clear();
		mMY2.clear();
		if (mSTD1.size()!= mMY2.size()) {
			std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
			return false;
		}
		
		if (mSTD1.empty()!= mMY2.empty()) {
			std::cout << "\033[31m" << "TEST 2 " << "\033[0m" << std::endl;
			return false;
		}
		for (int i = 0; i < 10; ++i) {
			mSTD1.insert(std::make_pair(i * 10, i * 10));
			mMY2.insert(ft::make_pair(i * 10, i * 10));
		}
		if (mSTD1.size()!= mMY2.size()) {
			std::cout << "\033[31m" << "TEST 3 " << "\033[0m" << std::endl;
			return false;
		}
		
		if (mSTD1.empty()!= mMY2.empty()) {
			std::cout << "\033[31m" << "TEST 4 " << "\033[0m" << std::endl;
			return false;
		}
		mSTD1.clear();
		mMY2.clear();
		
	}
	std::cout << "\033[36m" << "key_comp" << "\033[0m" << std::endl;
	{
		ft::map<char,int> mymap;

		ft::map<char,int>::key_compare mycomp = mymap.key_comp();
		(void)mycomp;

	}
	std::cout << "\033[36m" << "value _comp" << "\033[0m" << std::endl;
	std::cout << "\033[36m" << "find" << "\033[0m" << std::endl;
	{
		std::map<int, int> mSTD1;
		ft::map<int, int> mMY2;
		for (int i = 0; i < 10; ++i) {
			mSTD1.insert(std::make_pair(i * 10, i * 10));
			mMY2.insert(ft::make_pair(i * 10, i * 10));
		}
		if (mSTD1.find(50)->second != mMY2.find(50)->second) {
			std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
			return false;
		}
		if ((mSTD1.find(500) == mSTD1.end()) != (mMY2.find(500) == mMY2.end())) {
			std::cout << "\033[31m" << "TEST 2 " << "\033[0m" << std::endl;
			return false;
		}
	}
	std::cout << "\033[36m" << "count" << "\033[0m" << std::endl;
	{
		std::map<int, int> mSTD1;
		ft::map<int, int> mMY2;
		for (int i = 0; i < 10; ++i) {
			mSTD1.insert(std::make_pair(i * 10, i * 10));
			mMY2.insert(ft::make_pair(i * 10, i * 10));
		}
		if (mSTD1.count(50) != mMY2.count(50)) {
			std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
			return false;
		}
		if (mSTD1.count(500) != mMY2.count(500)) {
			std::cout << "\033[31m" << "TEST 2 " << "\033[0m" << std::endl;
			return false;
		}
	}
	std::cout << "\033[36m" << "lower_bound 0" << "\033[0m" << std::endl;
	{
		std::map<int, int> mSTD1;
		ft::map<int, int> mMY2;
		for (int i = 0; i < 10; ++i) {
			mSTD1.insert(std::make_pair(i * 10, i * 10));
			mMY2.insert(ft::make_pair(i * 10, i * 10));
		}
		if (mSTD1.lower_bound(50)->second != mMY2.lower_bound(50)->second) {
			std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
			return false;
		}
		if (mSTD1.lower_bound(15)->second != mMY2.lower_bound(15)->second) {
			std::cout << "\033[31m" << "TEST 2 " << "\033[0m" << std::endl;
			return false;
		}
		
	}
	std::cout << "\033[36m" << "lower_bound" << "\033[0m" << std::endl;
	{
		std::map<int, int> mSTD1;
		ft::map<int, int> mMY2;
		for (int i = 0; i < 10; ++i) {
			mSTD1.insert(std::make_pair(i * 10, i * 10));
			mMY2.insert(ft::make_pair(i * 10, i * 10));
		}
		if (mSTD1.lower_bound(50)->second != mMY2.lower_bound(50)->second) {
			std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
			return false;
		}
		if (mSTD1.lower_bound(15)->second != mMY2.lower_bound(15)->second) {
			std::cout << "\033[31m" << "TEST 2 " << "\033[0m" << std::endl;
			return false;
		}
	}
	std::cout << "\033[36m" << "lower_bound 1" << "\033[0m" << std::endl;
	{
		std::map<char, int> mSTD1;
		ft::map<char, int> mMY2;

			mSTD1['a']=10;
 			mSTD1['c']=20;
 			mSTD1['e']=30;

			mMY2['a']=10;
 			mMY2['c']=20;
 			mMY2['e']=30;
		
		if (mSTD1.lower_bound('a')->second != mMY2.lower_bound('a')->second) {
			std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
			return false;
		}
		if (mSTD1.lower_bound('b')->second != mMY2.lower_bound('b')->second) {
			std::cout << "\033[31m" << "TEST 2 " << "\033[0m" << std::endl;
			return false;
		}
	}

	std::cout << "\033[36m" << "upper_bound 0" << "\033[0m" << std::endl;
	{
		std::map<int, int> mSTD1;
		ft::map<int, int> mMY2;
		for (int i = 0; i < 10; ++i) {
			mSTD1.insert(std::make_pair(i * 10, i * 10));
			mMY2.insert(ft::make_pair(i * 10, i * 10));
		}
		if (mSTD1.upper_bound(50)->second != mMY2.upper_bound(50)->second) {
			std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
			return false;
		}
		if (mSTD1.upper_bound(15)->second != mMY2.upper_bound(15)->second) {
			std::cout << "\033[31m" << "TEST 2 " << "\033[0m" << std::endl;
			return false;
		}
	}
	std::cout << "\033[36m" << "upper_bound" << "\033[0m" << std::endl;
	{
		std::map<int, int> mSTD1;
		ft::map<int, int> mMY2;
		for (int i = 0; i < 10; ++i) {
			mSTD1.insert(std::make_pair(i * 10, i * 10));
			mMY2.insert(ft::make_pair(i * 10, i * 10));
		}
		if (mSTD1.upper_bound(50)->second != mMY2.upper_bound(50)->second) {
			std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
			return false;
		}
		if (mSTD1.upper_bound(15)->second != mMY2.upper_bound(15)->second) {
			std::cout << "\033[31m" << "TEST 2 " << "\033[0m" << std::endl;
			return false;
		}
		
	}
	std::cout << "\033[36m" << "upper_bound 1" << "\033[0m" << std::endl;
	{
		std::map<char, int> mSTD1;
		ft::map<char, int> mMY2;

			mSTD1['a']=10;
 			mSTD1['c']=20;
 			mSTD1['e']=30;

			mMY2['a']=10;
 			mMY2['c']=20;
 			mMY2['e']=30;
		
		if (mSTD1.upper_bound('a')->second != mMY2.upper_bound('a')->second) {
			std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
			return false;
		}
		if (mSTD1.upper_bound('b')->second != mMY2.upper_bound('b')->second) {
			std::cout << "\033[31m" << "TEST 2 " << "\033[0m" << std::endl;
			return false;
		}
	}
	std::cout << "\033[36m" << "equal_range 1" << "\033[0m" << std::endl;
	{
		std::map<char,int> mymap1;
		ft::map<char,int> mymap2;

 	mymap1['a']=10;
 	mymap1['b']=20;
 	mymap1['c']=30;

	mymap2['a']=10;
 	mymap2['b']=20;
 	mymap2['c']=30;

 	std::pair<std::map<char,int>::iterator,std::map<char,int>::iterator> ret1;
 	ft::pair<ft::map<char,int>::iterator,ft::map<char,int>::iterator> ret2;
 	ret1 = mymap1.equal_range('b');
 	ret2 = mymap2.equal_range('b');

	if (ret1.first->first != ret2.first->first) {
		std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
		return false;
	}
	if (ret1.first->second != ret2.first->second) {
		std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
		return false;
	}
	if (ret1.second->first != ret2.second->first) {
		std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
		return false;
	}
	if (ret1.second->second != ret2.second->second) {
		std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
		return false;
	}
 	
	}
	std::cout << "\033[36m" << "equal_range 2" << "\033[0m" << std::endl;
	{
		std::map<char,int> mymap1;
		ft::map<char,int> mymap2;

		mymap1['a']=10;
		mymap1['c']=20;
		mymap1['e']=30;

		mymap2['a']=10;
		mymap2['c']=20;
		mymap2['e']=30;

		std::pair<std::map<char,int>::iterator,std::map<char,int>::iterator> ret1;
		ft::pair<ft::map<char,int>::iterator,ft::map<char,int>::iterator> ret2;
		ret1 = mymap1.equal_range('b');
		ret2 = mymap2.equal_range('b');

		if (ret1.first->first != ret2.first->first) {
		std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
		return false;
		}
		if (ret1.first->second != ret2.first->second) {
			std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
			return false;
		}
		if (ret1.second->first != ret2.second->first) {
			std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
			return false;
		}
		if (ret1.second->second != ret2.second->second) {
			std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
			return false;
		}
	}
	std::cout << "\033[36m" << "operators" << "\033[0m" << std::endl;
	{
		ft::map<int,int> mSTD1;
		ft::map<int,int> mMY2;
		std::map<int,int> s1;
		std::map<int,int> s2;
		for (int i = 0; i < 10; ++i) {
			mSTD1.insert(ft::make_pair(i * 10, i * 10));
			s1.insert(std::make_pair(i * 10, i * 10));

			mMY2.insert(ft::make_pair(i * 10, i * 10));
			s2.insert(std::make_pair(i * 10, i * 10));
		}
		// std::cout << (mSTD1 == mMY2) << " " << (s1 == s2) << std::endl;
		if ((mSTD1 == mMY2) != (s1 == s2)) {
			std::cout << "\033[31m" << "TEST 1.1 " << "\033[0m" << std::endl;
			return false;
		}
		if ((mSTD1 != mMY2) != (s1 != s2)) {
			std::cout << "\033[31m" << "TEST 1.2 " << "\033[0m" << std::endl;
			return false;
		}
		if ((mSTD1 < mMY2) != (s1 < s2)) {
			std::cout << "\033[31m" << "TEST 1.3 " << "\033[0m" << std::endl;
			return false;
		}
		if ((mSTD1 > mMY2) != (s1 > s2)) {
			std::cout << "\033[31m" << "TEST 1.4 " << "\033[0m" << std::endl;
			return false;
		}
		if ((mSTD1 >= mMY2) != (s1 >= s2)) {
			std::cout << "\033[31m" << "TEST 1.5 " << "\033[0m" << std::endl;
			return false;
		}
		if ((mSTD1 <= mMY2) != (s1 <= s2)) {
			std::cout << "\033[31m" << "TEST 1.6 " << "\033[0m" << std::endl;
			return false;
		}
	}
	{
		ft::map<int,int> mSTD1;
		ft::map<int,int> mMY2;
		std::map<int,int> s1;
		std::map<int,int> s2;
		for (int i = 0; i < 10; ++i) {
			mSTD1.insert(ft::make_pair(i * 100, i * 10));
			s1.insert(std::make_pair(i * 10, i * 10));

			mMY2.insert(ft::make_pair(i * 100, i * 10));
			s2.insert(std::make_pair(i * 10, i * 10));
		}
		if ((mSTD1 == mMY2) != (s1 == s2)) {
			std::cout << "\033[31m" << "TEST 2.1 " << "\033[0m" << std::endl;
			return false;
		}
		if ((mSTD1 != mMY2) != (s1 != s2)) {
			std::cout << "\033[31m" << "TEST 2.2 " << "\033[0m" << std::endl;
			return false;
		}
		if ((mSTD1 < mMY2) != (s1 < s2)) {
			std::cout << "\033[31m" << "TEST 2.3 " << "\033[0m" << std::endl;
			return false;
		}
		if ((mSTD1 > mMY2) != (s1 > s2)) {
			std::cout << "\033[31m" << "TEST 2.4 " << "\033[0m" << std::endl;
			return false;
		}
		if ((mSTD1 >= mMY2) != (s1 >= s2)) {
			std::cout << "\033[31m" << "TEST 2.5 " << "\033[0m" << std::endl;
			return false;
		}
		if ((mSTD1 <= mMY2) != (s1 <= s2)) {
			std::cout << "\033[31m" << "TEST 2.6 " << "\033[0m" << std::endl;
			return false;
		}
	}
	{
		ft::map<int,int> mSTD1;
		ft::map<int,int> mMY2;
		std::map<int,int> s1;
		std::map<int,int> s2;
		for (int i = 0; i < 10; ++i) {
			mSTD1.insert(ft::make_pair(i * 10, i * 100));
			s1.insert(std::make_pair(i * 10, i * 10));

			mMY2.insert(ft::make_pair(i * 10, i * 100));
			s2.insert(std::make_pair(i * 10, i * 10));
		}
		if ((mSTD1 == mMY2) != (s1 == s2)) {
			std::cout << "\033[31m" << "TEST 3.1 " << "\033[0m" << std::endl;
			return false;
		}
		if ((mSTD1 != mMY2) != (s1 != s2)) {
			std::cout << "\033[31m" << "TEST 3.2 " << "\033[0m" << std::endl;
			return false;
		}
		if ((mSTD1 < mMY2) != (s1 < s2)) {
			std::cout << "\033[31m" << "TEST 3.3 " << "\033[0m" << std::endl;
			return false;
		}
		if ((mSTD1 > mMY2) != (s1 > s2)) {
			std::cout << "\033[31m" << "TEST 3.4 " << "\033[0m" << std::endl;
			return false;
		}
		if ((mSTD1 >= mMY2) != (s1 >= s2)) {
			std::cout << "\033[31m" << "TEST 3.5 " << "\033[0m" << std::endl;
			return false;
		}
		if ((mSTD1 <= mMY2) != (s1 <= s2)) {
			std::cout << "\033[31m" << "TEST 3.6 " << "\033[0m" << std::endl;
			return false;
		}
	}
	{
		ft::map<int,int> mSTD1;
		ft::map<int,int> mMY2;
		std::map<int,int> s1;
		std::map<int,int> s2;
		for (int i = 0; i < 10; ++i) {
			mSTD1.insert(ft::make_pair(i * 10, i * 10));
			s1.insert(std::make_pair(i * 100, i * 10));

			mMY2.insert(ft::make_pair(i * 10, i * 10));
			s2.insert(std::make_pair(i * 100, i * 10));
		}
		if ((mSTD1 == mMY2) != (s1 == s2)) {
			std::cout << "\033[31m" << "TEST 4.1 " << "\033[0m" << std::endl;
			return false;
		}
		if ((mSTD1 != mMY2) != (s1 != s2)) {
			std::cout << "\033[31m" << "TEST 4.2 " << "\033[0m" << std::endl;
			return false;
		}
		if ((mSTD1 < mMY2) != (s1 < s2)) {
			std::cout << "\033[31m" << "TEST 4.3 " << "\033[0m" << std::endl;
			return false;
		}
		if ((mSTD1 > mMY2) != (s1 > s2)) {
			std::cout << "\033[31m" << "TEST 4.4 " << "\033[0m" << std::endl;
			return false;
		}
		if ((mSTD1 >= mMY2) != (s1 >= s2)) {
			std::cout << "\033[31m" << "TEST 4.5 " << "\033[0m" << std::endl;
			return false;
		}
		if ((mSTD1 <= mMY2) != (s1 <= s2)) {
			std::cout << "\033[31m" << "TEST 4.6 " << "\033[0m" << std::endl;
			return false;
		}
	}
	{
		ft::map<int,int> mSTD1;
		ft::map<int,int> mMY2;
		std::map<int,int> s1;
		std::map<int,int> s2;
		for (int i = 0; i < 10; ++i) {
			mSTD1.insert(ft::make_pair(i * 10, i * 10));
			s1.insert(std::make_pair(i * 10, i * 100));

			mMY2.insert(ft::make_pair(i * 10, i * 10));
			s2.insert(std::make_pair(i * 10, i * 100));
		}
		if ((mSTD1 == mMY2) != (s1 == s2)) {
			std::cout << "\033[31m" << "TEST 5.1 " << "\033[0m" << std::endl;
			return false;
		}
		if ((mSTD1 != mMY2) != (s1 != s2)) {
			std::cout << "\033[31m" << "TEST 5.2 " << "\033[0m" << std::endl;
			return false;
		}
		if ((mSTD1 < mMY2) != (s1 < s2)) {
			std::cout << "\033[31m" << "TEST 5.3 " << "\033[0m" << std::endl;
			return false;
		}
		if ((mSTD1 > mMY2) != (s1 > s2)) {
			std::cout << "\033[31m" << "TEST 5.4 " << "\033[0m" << std::endl;
			return false;
		}
		if ((mSTD1 >= mMY2) != (s1 >= s2)) {
			std::cout << "\033[31m" << "TEST 5.5 " << "\033[0m" << std::endl;
			return false;
		}
		if ((mSTD1 <= mMY2) != (s1 <= s2)) {
			std::cout << "\033[31m" << "TEST 5.6 " << "\033[0m" << std::endl;
			return false;
		}
	}
	{
		ft::map<int,int> mSTD1;
		ft::map<int,int> mMY2;
		std::map<int,int> s1;
		std::map<int,int> s2;
		for (int i = 0; i < 10; ++i) {
			mSTD1.insert(ft::make_pair(i * 100, i * 10));
			s1.insert(std::make_pair(i * 10, i * 100));

			mMY2.insert(ft::make_pair(i * 100, i * 10));
			s2.insert(std::make_pair(i * 10, i * 100));
		}
		if ((mSTD1 == mMY2) != (s1 == s2)) {
			std::cout << "\033[31m" << "TEST 6.1 " << "\033[0m" << std::endl;
			return false;
		}
		if ((mSTD1 != mMY2) != (s1 != s2)) {
			std::cout << "\033[31m" << "TEST 6.2 " << "\033[0m" << std::endl;
			return false;
		}
		if ((mSTD1 < mMY2) != (s1 < s2)) {
			std::cout << "\033[31m" << "TEST 6.3 " << "\033[0m" << std::endl;
			return false;
		}
		if ((mSTD1 > mMY2) != (s1 > s2)) {
			std::cout << "\033[31m" << "TEST 6.4 " << "\033[0m" << std::endl;
			return false;
		}
		if ((mSTD1 >= mMY2) != (s1 >= s2)) {
			std::cout << "\033[31m" << "TEST 6.5 " << "\033[0m" << std::endl;
			return false;
		}
		if ((mSTD1 <= mMY2) != (s1 <= s2)) {
			std::cout << "\033[31m" << "TEST 6.6 " << "\033[0m" << std::endl;
			return false;
		}
	}
	{
		ft::map<int,int> mSTD1;
		ft::map<int,int> mMY2;
		std::map<int,int> s1;
		std::map<int,int> s2;
		for (int i = 0; i < 10; ++i) {
			mSTD1.insert(ft::make_pair(i * 10, i * 100));
			s1.insert(std::make_pair(i * 100, i * 10));

			mMY2.insert(ft::make_pair(i * 10, i * 100));
			s2.insert(std::make_pair(i * 100, i * 10));
		}
		if ((mSTD1 == mMY2) != (s1 == s2)) {
			std::cout << "\033[31m" << "TEST 7.1 " << "\033[0m" << std::endl;
			return false;
		}
		if ((mSTD1 != mMY2) != (s1 != s2)) {
			std::cout << "\033[31m" << "TEST 7.2 " << "\033[0m" << std::endl;
			return false;
		}
		if ((mSTD1 < mMY2) != (s1 < s2)) {
			std::cout << "\033[31m" << "TEST 7.3 " << "\033[0m" << std::endl;
			return false;
		}
		if ((mSTD1 > mMY2) != (s1 > s2)) {
			std::cout << "\033[31m" << "TEST 7.4 " << "\033[0m" << std::endl;
			return false;
		}
		if ((mSTD1 >= mMY2) != (s1 >= s2)) {
			std::cout << "\033[31m" << "TEST 7.5 " << "\033[0m" << std::endl;
			return false;
		}
		if ((mSTD1 <= mMY2) != (s1 <= s2)) {
			std::cout << "\033[31m" << "TEST 7.6 " << "\033[0m" << std::endl;
			return false;
		}
	}
	{
		ft::map<int,int> mSTD1;
		ft::map<int,int> mMY2;
		std::map<int,int> s1;
		std::map<int,int> s2;
		for (int i = 0; i < 11; ++i) {
			mSTD1.insert(ft::make_pair(i * 10, i * 10));
			s1.insert(std::make_pair(i * 10, i * 10));
		}
		for (int i = 0; i < 10; ++i) {
			mMY2.insert(ft::make_pair(i * 10, i * 10));
			s2.insert(std::make_pair(i * 10, i * 10));
		}
		if ((mSTD1 == mMY2) != (s1 == s2)) {
			std::cout << "\033[31m" << "TEST 8.1 " << "\033[0m" << std::endl;
			return false;
		}
		if ((mSTD1 != mMY2) != (s1 != s2)) {
			std::cout << "\033[31m" << "TEST 8.2 " << "\033[0m" << std::endl;
			return false;
		}
		if ((mSTD1 < mMY2) != (s1 < s2)) {
			std::cout << "\033[31m" << "TEST 8.3 " << "\033[0m" << std::endl;
			return false;
		}
		if ((mSTD1 > mMY2) != (s1 > s2)) {
			std::cout << "\033[31m" << "TEST 8.4 " << "\033[0m" << std::endl;
			return false;
		}
		if ((mSTD1 >= mMY2) != (s1 >= s2)) {
			std::cout << "\033[31m" << "TEST 8.5 " << "\033[0m" << std::endl;
			return false;
		}
		if ((mSTD1 <= mMY2) != (s1 <= s2)) {
			std::cout << "\033[31m" << "TEST 8.6 " << "\033[0m" << std::endl;
			return false;
		}
	}
	{
		ft::map<int,int> mSTD1;
		ft::map<int,int> mMY2;
		std::map<int,int> s1;
		std::map<int,int> s2;
		for (int i = 0; i < 10; ++i) {
			mSTD1.insert(ft::make_pair(i * 10, i * 10));
			s1.insert(std::make_pair(i * 10, i * 10));
		}
		for (int i = 0; i < 11; ++i) {
			mMY2.insert(ft::make_pair(i * 10, i * 10));
			s2.insert(std::make_pair(i * 10, i * 10));
		}
		if ((mSTD1 == mMY2) != (s1 == s2)) {
			std::cout << "\033[31m" << "TEST 9.1 " << "\033[0m" << std::endl;
			return false;
		}
		if ((mSTD1 != mMY2) != (s1 != s2)) {
			std::cout << "\033[31m" << "TEST 9.2 " << "\033[0m" << std::endl;
			return false;
		}
		if ((mSTD1 < mMY2) != (s1 < s2)) {
			std::cout << "\033[31m" << "TEST 9.3 " << "\033[0m" << std::endl;
			return false;
		}
		if ((mSTD1 > mMY2) != (s1 > s2)) {
			std::cout << "\033[31m" << "TEST 9.4 " << "\033[0m" << std::endl;
			return false;
		}
		if ((mSTD1 >= mMY2) != (s1 >= s2)) {
			std::cout << "\033[31m" << "TEST 9.5 " << "\033[0m" << std::endl;
			return false;
		}
		if ((mSTD1 <= mMY2) != (s1 <= s2)) {
			std::cout << "\033[31m" << "TEST 9.6 " << "\033[0m" << std::endl;
			return false;
		}
	}
	std::cout << "\033[36m" << "const begin" << "\033[0m" << std::endl;
	{
		std::map<int,int> mSTD1;
		ft::map<int,int> mMY2;

		for (int i = 0; i < 10; ++i) {
			mSTD1.insert(std::make_pair(i * 10, i * 10));
			mMY2.insert(ft::make_pair(i * 10, i * 10));
		}

		const std::map<int,int> mSTD1_c(mSTD1);
		const ft::map<int,int> mMY2_c(mMY2);

		std::map<int, int>::const_iterator it1 = mSTD1_c.begin();
		ft::map<int, int>::const_iterator it2 = mMY2_c.begin();
		for (int i = 0; i < 10; ++i) {
			if (it1->second != it2->second) {
				std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
				return false;
			}
			it1++;
			it2++;
		}
	}
	std::cout << "\033[36m" << "const rbegin" << "\033[0m" << std::endl;
	{
		std::map<int,int> mSTD1;
		ft::map<int,int> mMY2;

		for (int i = 0; i < 10; ++i) {
			mSTD1.insert(std::make_pair(i * 10, i * 10));
			mMY2.insert(ft::make_pair(i * 10, i * 10));
		}

		std::map<int, int>::reverse_iterator it1 = mSTD1.rbegin();
		ft::map<int, int>::reverse_iterator it2 = mMY2.rbegin();
		for (int i = 0; i < 9; ++i) {
			it1++;
			it2++;
			if (it1->second != it2->second) {
				std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
				return false;
			}
		}
	}
	std::cout << "\033[36m" << "const rend" << "\033[0m" << std::endl;
	{
		std::map<int,int> mSTD1;
		ft::map<int,int> mMY2;

		for (int i = 0; i < 10; ++i) {
			mSTD1.insert(std::make_pair(i * 10, i * 10));
			mMY2.insert(ft::make_pair(i * 10, i * 10));
		}

		std::map<int, int>::reverse_iterator it1 = mSTD1.rend();
		ft::map<int, int>::reverse_iterator it2 = mMY2.rend();
		for (int i = 0; i < 9; ++i) {
			it1--;
			it2--;
			if (it1->second != it2->second) {
				std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
				return false;
			}
		}
	}
	return true;
}

bool test_stack() {


    return true;
}

bool test_RBTS() {

    return true;
}

bool test_set() {
	std::cout << "\033[36m" << "constructor (1)" << "\033[0m" << std::endl;
	{
		std::set<int> setSTD1;
		ft::set<int> setMY2;
	}
	std::cout << "\033[36m" << "constructor (2)" << "\033[0m" << std::endl;
	{
		std::set<int> setSTD1;

		for (int i = 0; i < 10; ++i) {
			setSTD1.insert(i * 10);
					}
		std::set<int> setSTD1_c(setSTD1.begin(), setSTD1.end());
		ft::set<int> setMY2_c(setSTD1.begin(), setSTD1.end());
		
		std::set<int> ::iterator it1(setSTD1_c.begin());
		ft::set<int> ::iterator it2(setMY2_c.begin());
		for (int i = 0; i < 10; i++) {
			if ((*it1) != (*it2)) {
				std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
				return false;
			}
			it1++;
			it2++;
		}
	}

	std::cout << "\033[36m" << "constructor (3)" << "\033[0m" << std::endl;
	{
		ft::set<int> setMY2;

		for (int i = 0; i < 10; ++i) {
			setMY2.insert(i * 10);
		}
		ft::set<int> setMY2_c(setMY2);

		ft::set<int>::iterator it2(setMY2.begin());
		ft::set<int>::iterator it2_c(setMY2_c.begin());

		for (int i = 0; i < 10; ++i) {
			if ((*it2_c) != (*it2)) {
				std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
				return false;
			}
			it2_c++;
			it2++;
		}
	}
	{
		ft::set<int> setMY2;
		ft::set<int> setMY2_c(setMY2);
	}
	std::cout << "\033[36m" << "operator=" << "\033[0m" << std::endl;
	{
		ft::set<int> setMY2;

		for (int i = 0; i < 10; ++i) {
			setMY2.insert(i * 10);
		}
		ft::set<int> setMY2_c = setMY2;

		ft::set<int>::iterator it2(setMY2.begin());
		ft::set<int>::iterator it2_c(setMY2_c.begin());

		for (int i = 0; i < 10; ++i) {
			if ((*it2_c) != (*it2)) {
				std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
				return false;
			}
			it2_c++;
			it2++;
		}
		if (setMY2.size() != setMY2_c.size()) {
			std::cout << "\033[31m" << "TEST 2 " << "\033[0m" << std::endl;
			return false;
		}
	}

	std::cout << "\033[36m" << "empty" << "\033[0m" << std::endl;
	{
		std::set<int> setSTD1;
		ft::set<int> setMY2;

		if (setSTD1.empty() != setMY2.empty()) {
			std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
			return false;
		}
		for (int i = 0; i < 10; ++i) {
			setSTD1.insert(i * 10);
			setMY2.insert(i * 10);
		}
		if (setSTD1.empty() != setMY2.empty()) {
			std::cout << "\033[31m" << "TEST 2 " << "\033[0m" << std::endl;
			return false;
		}
	}
	std::cout << "\033[36m" << "size" << "\033[0m" << std::endl;
	{
		std::set<int> setSTD1;
		ft::set<int> setMY2;

		if (setSTD1.size() != setMY2.size()) {
			std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
			return false;
		}
		for (int i = 0; i < 10; ++i) {
			setSTD1.insert(i * 10);
			setMY2.insert(i * 10);
			if (setSTD1.size() != setMY2.size()) {
				std::cout << "\033[31m" << "TEST 2 " << "\033[0m" << std::endl;
				return false;
			}
		}
	}
	std::cout << "\033[36m" << "insert(1)" << "\033[0m" << std::endl;
	{
		std::set<int> setSTD1;
		ft::set<int> setMY2;
		for (int i = 0; i < 10; ++i) {
			setSTD1.insert(i * 10);
			setMY2.insert(i * 10);
		}
		std::pair<std::set<int>::iterator, bool > p1;
		ft::pair<ft::set<int>::iterator, bool > p2;

		p1 = setSTD1.insert(50);
		p2 = setMY2.insert(50);
		if (setSTD1.size()!= setMY2.size()) {
			std::cout << "\033[31m" << "TEST 2.1 " << "\033[0m" << std::endl;
			return false;
		}
		if (p1.second != p2.second) {
			std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
			return false;
		}
		if (*p1.first != *p2.first) {
			std::cout << "\033[31m" << "TEST 2 " << "\033[0m" << std::endl;
			return false;
		}
		p1 = setSTD1.insert(500);
		p2 = setMY2.insert(500);
		if (setSTD1.size()!= setMY2.size()) {
			std::cout << "\033[31m" << "TEST 2.2 " << "\033[0m" << std::endl;
			return false;
		}
		if (p1.second != p2.second) {
			std::cout << "\033[31m" << "TEST 3 " << "\033[0m" << std::endl;
			return false;
		}
		if (*p1.first != *p2.first) {
			std::cout << "\033[31m" << "TEST 4 " << "\033[0m" << std::endl;
			return false;
		}

	}
	std::cout << "\033[36m" << "insert(2)" << "\033[0m" << std::endl;
	{
		std::set<int> setSTD1;
		ft::set<int> setMY2;
		for (int i = 0; i < 10; ++i) {
			setSTD1.insert(i * 10);
			setMY2.insert(i * 10);
		}
		if (setSTD1.size()!= setMY2.size()) {
			std::cout << "\033[31m" << "TEST 1.1 " << "\033[0m" << std::endl;
			return false;
		}
		std::set<int>::iterator it1 = setSTD1.begin();
		ft::set<int>::iterator it2 = setMY2.begin();

		it1 = setSTD1.insert(it1, 50);
		it2 = setMY2.insert(it2, 50);
		if (*it1 != *it2) {
			std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
			return false;
		}
		if (setSTD1.size()!= setMY2.size()) {
			std::cout << "\033[31m" << "TEST 2.2 " << "\033[0m" << std::endl;
			return false;
		}
	}
	std::cout << "\033[36m" << "insert(3)" << "\033[0m" << std::endl;
	{
		std::set<int> setSTD1;
		ft::set<int> setMY2;
		for (int i = 0; i < 10; ++i) {
			setSTD1.insert(i * 10);
			setMY2.insert(i * 10);
		}
		std::set<int> setSTD1_c;
		ft::set<int> setMY2_c;

		setSTD1_c.insert(setSTD1.begin(), setSTD1.end());
		setMY2_c.insert(setMY2.begin(), setMY2.end());

		std::set<int>::iterator it1 = setSTD1_c.begin();
		ft::set<int>::iterator it2 = setMY2_c.begin();
		for(int i =0; i < 10; i++) {
			if (*it1!= *it2) {
				std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
				return false;
			}
			it1++;
			it2++;
		}
		if (setSTD1_c.size()!= setMY2_c.size()) {
			std::cout << "\033[31m" << "TEST 2.1 " << "\033[0m" << std::endl;
			return false;
		}
	}
	std::cout << "\033[36m" << "erase(1)" << "\033[0m" << std::endl;
	{
		std::set<int> setSTD1;
		ft::set<int> setMY2;
		for (int i = 0; i < 10; ++i) {
			setSTD1.insert(i * 10);
			setMY2.insert(i * 10);
		}

		setSTD1.erase(setSTD1.begin());
		setMY2.erase(setMY2.begin());

		std::set<int>::iterator it1 = setSTD1.begin();
		ft::set<int>::iterator it2 = setMY2.begin();
		for(int i =0; i < 9; i++) {
			if (*it1 != *it2) {
				std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
				return false;
			}
			it1++;
			it2++;
		}
		if (setSTD1.size()!= setMY2.size()) {
			std::cout << "\033[31m" << "TEST 2.1 " << "\033[0m" << std::endl;
			return false;
		}
	}
	std::cout << "\033[36m" << "erase(2)" << "\033[0m" << std::endl;
	{
		std::set<int> setSTD1;
		ft::set<int> setMY2;
		for (int i = 0; i < 10; ++i) {
			setSTD1.insert(i * 10);
			setMY2.insert(i * 10);
		}
		size_t s1 = setSTD1.erase(50);
		size_t s2 = setMY2.erase(50);
		if (s1 != s2) {
			std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
			return false;
		}
		s1 = setSTD1.erase(500);
		s2 = setMY2.erase(500);
		if (s1 != s2) {
			std::cout << "\033[31m" << "TEST 2 " << "\033[0m" << std::endl;
			return false;
		}

		std::set<int>::iterator it1 = setSTD1.begin();
		ft::set<int>::iterator it2 = setMY2.begin();
		for(int i =0; i < 9; i++) {
			if (*it1 != *it2) {
				std::cout << "\033[31m" << "TEST 3 " << "\033[0m" << std::endl;
				return false;
			}
			it1++;
			it2++;
		}
		if (setSTD1.size()!= setMY2.size()) {
			std::cout << "\033[31m" << "TEST 4 " << "\033[0m" << std::endl;
			return false;
		}
	}
	std::cout << "\033[36m" << "erase(3)" << "\033[0m" << std::endl;
	{
		std::set<int> setSTD1;
		ft::set<int> setMY2;
		for (int i = 0; i < 10; ++i) {
			setSTD1.insert(i * 10);
			setMY2.insert(i * 10);
		}
		setSTD1.erase(setSTD1.begin(), setSTD1.end());
		setMY2.erase(setMY2.begin(), setMY2.end());
		if (setSTD1.size()!= setMY2.size()) {
			std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
			return false;
		}
		
		if (setSTD1.empty()!= setMY2.empty()) {
			std::cout << "\033[31m" << "TEST 2 " << "\033[0m" << std::endl;
			return false;
		}
		
	}
	std::cout << "\033[36m" << "swap" << "\033[0m" << std::endl;
	{
		std::set<int> setSTD1;
		ft::set<int> setMY2;
		for (int i = 0; i < 10; ++i) {
			setSTD1.insert(i * 10);
			setMY2.insert(i * 10);
		}
		std::set<int> setSTD1_c;
		ft::set<int> setMY2_c;
		for (int i = 10; i < 15; ++i) {
			setSTD1_c.insert(i * 10);
			setMY2_c.insert(i * 10);
		}
		setSTD1.swap(setSTD1_c);
		setMY2.swap(setMY2_c);
		if (setSTD1.size()!= setMY2.size()) {
			std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
			return false;
		}
		if (setSTD1_c.size()!= setMY2_c.size()) {
			std::cout << "\033[31m" << "TEST 2 " << "\033[0m" << std::endl;
			return false;
		}
		std::set<int>::iterator it1 = setSTD1.begin();
		ft::set<int>::iterator it2 = setMY2.begin();

		for (int i = 0; i < 5; ++i)
		{
			if (*it1 != *it2) {
				std::cout << "\033[31m" << "TEST 3 " << "\033[0m" << std::endl;
				return false;
			}
			it1++;
			it2++;
		}
		it1 = setSTD1_c.begin();
		it2 = setMY2_c.begin();
		for (int i = 0; i < 10; ++i)
		{
			if (*it1 != *it2) {
				std::cout << "\033[31m" << "TEST 4 " << "\033[0m" << std::endl;
				return false;
			}
			it1++;
			it2++;
		}
	}
	std::cout << "\033[36m" << "clear" << "\033[0m" << std::endl;
	{
		std::set<int> setSTD1;
		ft::set<int> setMY2;
		for (int i = 0; i < 10; ++i) {
			setSTD1.insert(i * 10);
			setMY2.insert(i * 10);
		}
		setSTD1.clear();
		setMY2.clear();
		if (setSTD1.size()!= setMY2.size()) {
			std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
			return false;
		}
		
		if (setSTD1.empty()!= setMY2.empty()) {
			std::cout << "\033[31m" << "TEST 2 " << "\033[0m" << std::endl;
			return false;
		}
		for (int i = 0; i < 10; ++i) {
			setSTD1.insert(i * 10);
			setMY2.insert(i * 10);
		}
		if (setSTD1.size()!= setMY2.size()) {
			std::cout << "\033[31m" << "TEST 3 " << "\033[0m" << std::endl;
			return false;
		}
		
		if (setSTD1.empty()!= setMY2.empty()) {
			std::cout << "\033[31m" << "TEST 4 " << "\033[0m" << std::endl;
			return false;
		}
		setSTD1.clear();
		setMY2.clear();
		
	}
	std::cout << "\033[36m" << "key_comp" << "\033[0m" << std::endl;
	{
		ft::set<char> mymap;

		ft::set<char>::key_compare mycomp = mymap.key_comp();
		(void)mycomp;

	}
	std::cout << "\033[36m" << "value _comp" << "\033[0m" << std::endl;
	{
	}
	std::cout << "\033[36m" << "find" << "\033[0m" << std::endl;
	{
		std::set<int> setSTD1;
		ft::set<int> setMY2;
		for (int i = 0; i < 10; ++i) {
			setSTD1.insert(i * 10);
			setMY2.insert(i * 10);
		}
		if (*setSTD1.find(50)!= *setMY2.find(50)) {
			std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
			return false;
		}
		if ((setSTD1.find(500) == setSTD1.end()) != (setMY2.find(500) == setMY2.end())) {
			std::cout << "\033[31m" << "TEST 2 " << "\033[0m" << std::endl;
			return false;
		}
	}
	std::cout << "\033[36m" << "count" << "\033[0m" << std::endl;
	{
		std::set<int> setSTD1;
		ft::set<int> setMY2;
		for (int i = 0; i < 10; ++i) {
			setSTD1.insert(i * 10);
			setMY2.insert(i * 10);
		}
		if (setSTD1.count(50) != setMY2.count(50)) {
			std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
			return false;
		}
		if (setSTD1.count(500) != setMY2.count(500)) {
			std::cout << "\033[31m" << "TEST 2 " << "\033[0m" << std::endl;
			return false;
		}
	}
	std::cout << "\033[36m" << "lower_bound 0" << "\033[0m" << std::endl;
	{
		std::set<int> setSTD1;
		ft::set<int> setMY2;
		for (int i = 0; i < 10; ++i) {
			setSTD1.insert(i * 10);
			setMY2.insert(i * 10);
		}
		if (*setSTD1.lower_bound(50) != *setMY2.lower_bound(50)) {
			std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
			return false;
		}
		if (*setSTD1.lower_bound(15) != *setMY2.lower_bound(15)) {
			std::cout << "\033[31m" << "TEST 2 " << "\033[0m" << std::endl;
			return false;
		}
	}
	std::cout << "\033[36m" << "lower_bound" << "\033[0m" << std::endl;
	{
		std::set<int> setSTD1;
		ft::set<int> setMY2;
		for (int i = 0; i < 10; ++i) {
			setSTD1.insert(i * 10);
			setMY2.insert(i * 10);
		}
		if (*setSTD1.lower_bound(50) != *setMY2.lower_bound(50)) {
			std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
			return false;
		}
		if (*setSTD1.lower_bound(15) != *setMY2.lower_bound(15)) {
			std::cout << "\033[31m" << "TEST 2 " << "\033[0m" << std::endl;
			return false;
		}
	}
	std::cout << "\033[36m" << "lower_bound 1" << "\033[0m" << std::endl;
	{
		std::set<char> setSTD1;
		ft::set<char> setMY2;

		setSTD1.insert('a');
		setMY2.insert('a');
		setSTD1.insert('c');
		setMY2.insert('c');
		setSTD1.insert('e');
		setMY2.insert('e');
		
		if (*setSTD1.lower_bound('a')!= *setMY2.lower_bound('a')) {
			std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
			return false;
		}
		if (*setSTD1.lower_bound('b') != *setMY2.lower_bound('b')) {
			std::cout << "\033[31m" << "TEST 2 " << "\033[0m" << std::endl;
			return false;
		}
	}

	std::cout << "\033[36m" << "upper_bound 0" << "\033[0m" << std::endl;
	{
		std::set<int> setSTD1;
		ft::set<int> setMY2;
		for (int i = 0; i < 10; ++i) {
			setSTD1.insert(i * 10);
			setMY2.insert(i * 10);
		}
		if (*setSTD1.upper_bound(50) != *setMY2.upper_bound(50)) {
			std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
			return false;
		}
		if (*setSTD1.upper_bound(15) != *setMY2.upper_bound(15)) {
			std::cout << "\033[31m" << "TEST 2 " << "\033[0m" << std::endl;
			return false;
		}
	}
	std::cout << "\033[36m" << "upper_bound 0" << "\033[0m" << std::endl;
	{
		std::set<int> setSTD1;
		ft::set<int> setMY2;
		for (int i = 0; i < 10; ++i) {
			setSTD1.insert(i * 10);
			setMY2.insert(i * 10);
		}
		if (*setSTD1.upper_bound(50) != *setMY2.upper_bound(50)) {
			std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
			return false;
		}
		if (*setSTD1.upper_bound(15) != *setMY2.upper_bound(15)) {
			std::cout << "\033[31m" << "TEST 2 " << "\033[0m" << std::endl;
			return false;
		}
	}
	std::cout << "\033[36m" << "upper_bound 1" << "\033[0m" << std::endl;
	{
		std::set<char> setSTD1;
		ft::set<char> setMY2;

		setSTD1.insert('a');
		setMY2.insert('a');
		setSTD1.insert('c');
		setMY2.insert('c');
		setSTD1.insert('e');
		setMY2.insert('e');
		
		if (*setSTD1.upper_bound('a')!= *setMY2.upper_bound('a')) {
			std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
			return false;
		}
		if (*setSTD1.upper_bound('b') != *setMY2.upper_bound('b')) {
			std::cout << "\033[31m" << "TEST 2 " << "\033[0m" << std::endl;
			return false;
		}
	}
	std::cout << "\033[36m" << "equal_range 1" << "\033[0m" << std::endl;
	{
		std::set<char> mymap1;
		ft::set<char> mymap2;

 	mymap1.insert('a');
 	mymap1.insert('b');
 	mymap1.insert('c');
	mymap2.insert('a');
 	mymap2.insert('b');
 	mymap2.insert('c');

 	std::pair<std::set<char>::iterator,std::set<char>::iterator> ret1;
 	ft::pair<ft::set<char>::iterator,ft::set<char>::iterator> ret2;
 	ret1 = mymap1.equal_range('b');
 	ret2 = mymap2.equal_range('b');

	if (*ret1.first != *ret2.first) {
		std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
		return false;
	}
	if (*ret1.second != *ret2.second) {
		std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
		return false;
	}
 	
	}
	std::cout << "\033[36m" << "equal_range 2" << "\033[0m" << std::endl;
	{
			std::set<char> mymap1;
		ft::set<char> mymap2;

 	mymap1.insert('a');
 	mymap1.insert('c');
 	mymap1.insert('e');
	mymap2.insert('a');
 	mymap2.insert('c');
 	mymap2.insert('e');

 	std::pair<std::set<char>::iterator,std::set<char>::iterator> ret1;
 	ft::pair<ft::set<char>::iterator,ft::set<char>::iterator> ret2;
 	ret1 = mymap1.equal_range('b');
 	ret2 = mymap2.equal_range('b');

	if (*ret1.first != *ret2.first) {
		std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
		return false;
	}
	if (*ret1.second != *ret2.second) {
		std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
		return false;
	}
	}
	std::cout << "\033[36m" << "operators" << "\033[0m" << std::endl;
	{
		ft::set<int> setSTD1;
		ft::set<int> setMY2;
		std::set<int> s1;
		std::set<int> s2;
		for (int i = 0; i < 10; ++i) {
			setSTD1.insert(i * 10);
			s1.insert(i * 10);

			setMY2.insert(i * 10);
			s2.insert(i * 10);
		}
		if ((setSTD1 == setMY2) != (s1 == s2)) {
			std::cout << "\033[31m" << "TEST 1.1 " << "\033[0m" << std::endl;
			return false;
		}
		if ((setSTD1 != setMY2) != (s1 != s2)) {
			std::cout << "\033[31m" << "TEST 1.2 " << "\033[0m" << std::endl;
			return false;
		}
		if ((setSTD1 < setMY2) != (s1 < s2)) {
			std::cout << "\033[31m" << "TEST 1.3 " << "\033[0m" << std::endl;
			return false;
		}
		if ((setSTD1 > setMY2) != (s1 > s2)) {
			std::cout << "\033[31m" << "TEST 1.4 " << "\033[0m" << std::endl;
			return false;
		}
		if ((setSTD1 >= setMY2) != (s1 >= s2)) {
			std::cout << "\033[31m" << "TEST 1.5 " << "\033[0m" << std::endl;
			return false;
		}
		if ((setSTD1 <= setMY2) != (s1 <= s2)) {
			std::cout << "\033[31m" << "TEST 1.6 " << "\033[0m" << std::endl;
			return false;
		}
	}
	{
		ft::set<int> setSTD1;
		ft::set<int> setMY2;
		std::set<int> s1;
		std::set<int> s2;
		for (int i = 0; i < 10; ++i) {
			setSTD1.insert(i * 100);
			s1.insert(i * 100);

			setMY2.insert(i * 10);
			s2.insert(i * 10);
		}
		if ((setSTD1 == setMY2) != (s1 == s2)) {
			std::cout << "\033[31m" << "TEST 2.1 " << "\033[0m" << std::endl;
			return false;
		}
		if ((setSTD1 != setMY2) != (s1 != s2)) {
			std::cout << "\033[31m" << "TEST 2.2 " << "\033[0m" << std::endl;
			return false;
		}
		if ((setSTD1 < setMY2) != (s1 < s2)) {
			std::cout << "\033[31m" << "TEST 2.3 " << "\033[0m" << std::endl;
			return false;
		}
		if ((setSTD1 > setMY2) != (s1 > s2)) {
			std::cout << "\033[31m" << "TEST 2.4 " << "\033[0m" << std::endl;
			return false;
		}
		if ((setSTD1 >= setMY2) != (s1 >= s2)) {
			std::cout << "\033[31m" << "TEST 2.5 " << "\033[0m" << std::endl;
			return false;
		}
		if ((setSTD1 <= setMY2) != (s1 <= s2)) {
			std::cout << "\033[31m" << "TEST 2.6 " << "\033[0m" << std::endl;
			return false;
		}
	}
	{
		ft::set<int> setSTD1;
		ft::set<int> setMY2;
		std::set<int> s1;
		std::set<int> s2;
		for (int i = 0; i < 10; ++i) {
			setSTD1.insert(i * 10);
			s1.insert(i * 10);

			setMY2.insert(i * 100);
			s2.insert(i * 100);
		}
		if ((setSTD1 == setMY2) != (s1 == s2)) {
			std::cout << "\033[31m" << "TEST 3.1 " << "\033[0m" << std::endl;
			return false;
		}
		if ((setSTD1 != setMY2) != (s1 != s2)) {
			std::cout << "\033[31m" << "TEST 3.2 " << "\033[0m" << std::endl;
			return false;
		}
		if ((setSTD1 < setMY2) != (s1 < s2)) {
			std::cout << "\033[31m" << "TEST 3.3 " << "\033[0m" << std::endl;
			return false;
		}
		if ((setSTD1 > setMY2) != (s1 > s2)) {
			std::cout << "\033[31m" << "TEST 3.4 " << "\033[0m" << std::endl;
			return false;
		}
		if ((setSTD1 >= setMY2) != (s1 >= s2)) {
			std::cout << "\033[31m" << "TEST 3.5 " << "\033[0m" << std::endl;
			return false;
		}
		if ((setSTD1 <= setMY2) != (s1 <= s2)) {
			std::cout << "\033[31m" << "TEST 3.6 " << "\033[0m" << std::endl;
			return false;
		}
	}
	{
		ft::set<int> setSTD1;
		ft::set<int> setMY2;
		std::set<int> s1;
		std::set<int> s2;
		for (int i = 0; i < 10; ++i) {
			setSTD1.insert(i * 10);
			s1.insert(i * 10);
		}

		for (int i = 0; i < 5; ++i) {
			setMY2.insert(i * 100);
			s2.insert(i * 100);
		}
		if ((setSTD1 == setMY2) != (s1 == s2)) {
			std::cout << "\033[31m" << "TEST 4.1 " << "\033[0m" << std::endl;
			return false;
		}
		if ((setSTD1 != setMY2) != (s1 != s2)) {
			std::cout << "\033[31m" << "TEST 4.2 " << "\033[0m" << std::endl;
			return false;
		}
		if ((setSTD1 < setMY2) != (s1 < s2)) {
			std::cout << "\033[31m" << "TEST 4.3 " << "\033[0m" << std::endl;
			return false;
		}
		if ((setSTD1 > setMY2) != (s1 > s2)) {
			std::cout << "\033[31m" << "TEST 4.4 " << "\033[0m" << std::endl;
			return false;
		}
		if ((setSTD1 >= setMY2) != (s1 >= s2)) {
			std::cout << "\033[31m" << "TEST 4.5 " << "\033[0m" << std::endl;
			return false;
		}
		if ((setSTD1 <= setMY2) != (s1 <= s2)) {
			std::cout << "\033[31m" << "TEST 4.6 " << "\033[0m" << std::endl;
			return false;
		}
	}
	{
		ft::set<int> setSTD1;
		ft::set<int> setMY2;
		std::set<int> s1;
		std::set<int> s2;
		for (int i = 0; i < 10; ++i) {
			setSTD1.insert(i * 10);
			s1.insert(i * 10);
		}

		for (int i = 0; i < 15; ++i) {
			setMY2.insert(i * 100);
			s2.insert(i * 100);
		}
		if ((setSTD1 == setMY2) != (s1 == s2)) {
			std::cout << "\033[31m" << "TEST 5.1 " << "\033[0m" << std::endl;
			return false;
		}
		if ((setSTD1 != setMY2) != (s1 != s2)) {
			std::cout << "\033[31m" << "TEST 5.2 " << "\033[0m" << std::endl;
			return false;
		}
		if ((setSTD1 < setMY2) != (s1 < s2)) {
			std::cout << "\033[31m" << "TEST 5.3 " << "\033[0m" << std::endl;
			return false;
		}
		if ((setSTD1 > setMY2) != (s1 > s2)) {
			std::cout << "\033[31m" << "TEST 5.4 " << "\033[0m" << std::endl;
			return false;
		}
		if ((setSTD1 >= setMY2) != (s1 >= s2)) {
			std::cout << "\033[31m" << "TEST 5.5 " << "\033[0m" << std::endl;
			return false;
		}
		if ((setSTD1 <= setMY2) != (s1 <= s2)) {
			std::cout << "\033[31m" << "TEST 5.6 " << "\033[0m" << std::endl;
			return false;
		}
	}
	std::cout << "\033[36m" << "const begin" << "\033[0m" << std::endl;
	{
		std::set<int> setSTD1;
		ft::set<int> setMY2;

		for (int i = 0; i < 10; ++i) {
			setSTD1.insert(i * 10);
			setMY2.insert(i * 10);
		}

		const std::set<int> setSTD1_c(setSTD1);
		const ft::set<int> setMY2_c(setMY2);

		std::set<int>::const_iterator it1 = setSTD1_c.begin();
		ft::set<int>::const_iterator it2 = setMY2_c.begin();
		for (int i = 0; i < 10; ++i) {
			if (*it1 != *it2) {
				std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
				return false;
			}
			it1++;
			it2++;
		}
	}
	std::cout << "\033[36m" << "const rbegin" << "\033[0m" << std::endl;
	{
		std::set<int> setSTD1;
		ft::set<int> setMY2;

		for (int i = 0; i < 10; ++i) {
			setSTD1.insert(i * 10);
			setMY2.insert(i * 10);
		}

		std::set<int>::reverse_iterator it1 = setSTD1.rbegin();
		ft::set<int>::reverse_iterator it2 = setMY2.rbegin();
		for (int i = 0; i < 9; ++i) {
			it1++;
			it2++;
			if (*it1 != *it2) {
				std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
				return false;
			}
		}
	}
	std::cout << "\033[36m" << "const rend" << "\033[0m" << std::endl;
	{
		std::set<int> setSTD1;
		ft::set<int> setMY2;

		for (int i = 0; i < 10; ++i) {
			setSTD1.insert(i * 10);
			setMY2.insert(i * 10);
		}

		std::set<int>::reverse_iterator it1 = setSTD1.rend();
		ft::set<int>::reverse_iterator it2 = setMY2.rend();
		for (int i = 0; i < 9; ++i) {
			it1--;
			it2--;
			if (*it1 != *it2) {
				std::cout << "\033[31m" << "TEST 1 " << "\033[0m" << std::endl;
				return false;
			}
		}
	}
	return true;
}


int main(void) {
	time_t t = clock();

	///////////////////////////////////////////////////////////////////////////////
	std::cout << "\033[33m" << "TEST CAPACITY: " << "\033[0m" << std::endl;
	if (test_capacity())
		std::cout << "\033[32m" << "TEST CAPACITY: OK" << "\033[0m" << std::endl;
	else{
		std::cout << "\033[31m" << "TEST CAPACITY: KO" << "\033[0m" << std::endl;
		return 1;}
	///////////////////////////////////////////////////////////////////////////////
	std::cout << "\033[33m" << "TEST PUSH_BACK: " << "\033[0m" << std::endl;
	if (test_push_back())
		std::cout << "\033[32m" << "TEST PUSH_BACK: OK" << "\033[0m" << std::endl;
	else{
		std::cout << "\033[31m" << "TEST PUSH_BACK: KO" << "\033[0m" << std::endl;return 1;}
	///////////////////////////////////////////////////////////////////////////////
	std::cout << "\033[33m" << "TEST REVER_ITERATOR: " << "\033[0m" << std::endl;
	if (test_rever_iterator())
		std::cout << "\033[32m" << "TEST REVER_ITERATOR: OK" << "\033[0m" << std::endl;
	else{
		std::cout << "\033[31m" << "TEST REVER_ITERATOR: KO" << "\033[0m" << std::endl;return 1;}
	///////////////////////////////////////////////////////////////////////////////
	std::cout << "\033[33m" << "TEST Allocator: " << "\033[0m" << std::endl;
	if (test_allocator())
		std::cout << "\033[32m" << "TEST Allocator: OK" << "\033[0m" << std::endl;
	else{
		std::cout << "\033[31m" << "TEST Allocator: KO" << "\033[0m" << std::endl; return 1;}
	///////////////////////////////////////////////////////////////////////////////
	std::cout << "\033[33m" << "TEST VECTOR: " << "\033[0m" << std::endl;
	if (test_vector())
		std::cout << "\033[32m" << "TEST VECTOR: OK" << "\033[0m" << std::endl;
	else{
		std::cout << "\033[31m" << "TEST VECTOR: KO" << "\033[0m" << std::endl;return 1;}
	///////////////////////////////////////////////////////////////////////////////
	std::cout << "\033[33m" << "TEST VectorIterator: " << "\033[0m" << std::endl;
	if (test_VectorIterator())
		std::cout << "\033[32m" << "TEST VectorIterator: OK" << "\033[0m" << std::endl;
	else{
		std::cout << "\033[31m" << "TEST VectorIterator: KO" << "\033[0m" << std::endl;return 1;}
	///////////////////////////////////////////////////////////////////////////////
		std::cout << "\033[33m" << "TEST RBT: " << "\033[0m" << std::endl;
	if (test_RBT())
		std::cout << "\033[32m" << "TEST RBT: OK" << "\033[0m" << std::endl;
	else{
		std::cout << "\033[31m" << "TEST RBT: KO" << "\033[0m" << std::endl;return 1;}
	///////////////////////////////////////////////////////////////////////////////
		std::cout << "\033[33m" << "TEST map_iterator: " << "\033[0m" << std::endl;
	if (test_map_iterator())
		std::cout << "\033[32m" << "TEST map_iterator: OK" << "\033[0m" << std::endl;
	else{
		std::cout << "\033[31m" << "TEST map_iterator: KO" << "\033[0m" << std::endl;return 1;}
	///////////////////////////////////////////////////////////////////////////////
	std::cout << "\033[33m" << "TEST map: " << "\033[0m" << std::endl;
	if (test_map())
		std::cout << "\033[32m" << "TEST map: OK" << "\033[0m" << std::endl;
	else{
		std::cout << "\033[31m" << "TEST map: KO" << "\033[0m" << std::endl;return 1;}
	///////////////////////////////////////////////////////////////////////////////
	std::cout << "\033[33m" << "TEST map: " << "\033[0m" << std::endl;
	if (test_stack())
		std::cout << "\033[32m" << "TEST map: OK" << "\033[0m" << std::endl;
	else{
		std::cout << "\033[31m" << "TEST map: KO" << "\033[0m" << std::endl;return 1;}
	///////////////////////////////////////////////////////////////////////////////
		std::cout << "\033[33m" << "TEST RBTS: " << "\033[0m" << std::endl;
	if (test_RBTS())
		std::cout << "\033[32m" << "TEST RBTS: OK" << "\033[0m" << std::endl;
	else{
		std::cout << "\033[31m" << "TEST RBTS: KO" << "\033[0m" << std::endl;return 1;}
	///////////////////////////////////////////////////////////////////////////////
	std::cout << "\033[33m" << "TEST map: " << "\033[0m" << std::endl;
	if (test_set())
		std::cout << "\033[32m" << "TEST map: OK" << "\033[0m" << std::endl;
	else{
		std::cout << "\033[31m" << "TEST map: KO" << "\033[0m" << std::endl;return 1;}
	///////////////////////////////////////////////////////////////////////////////
	
	
	std::cout << "\033[35m" << clock() - t << "\033[0m" << std::endl;
//	while(1);
	return (0);
}