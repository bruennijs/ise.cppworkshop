
#include <cassert>
#include <initializer_list>
#include <utility>
#include <algorithm>

template <typename C>
struct reverse_order_range {
	reverse_order_range( C &r ) : c(&r) {}
	
	typedef typename C::reverse_iterator iterator;
	iterator begin() { return c->rbegin(); }
	iterator end() { return c->rend(); }
private:
	C *c;
};

template <typename C>
reverse_order_range<C> reverse_order( C &r )
{
	return reverse_order_range<C>(r);
}

template <typename E>
struct Node
{
	Node( const E &e ) : element(e), prev(nullptr), next(nullptr) {}
	E element;
	Node *prev;
	Node *next;
};

template <typename E>
class ListIterator
{
public:
	ListIterator( Node<E> *vn = nullptr ) : n(vn) {}
	
	E& operator*() const { return n->element; }
	ListIterator& operator++() { n = n->next; return *this; }
	ListIterator operator++(int) { ListIterator tmp(*this); n = n->next; return tmp; }
	bool operator==( const ListIterator &i ) const { return n == i.n; }
	bool operator!=( const ListIterator &i ) const { return n != i.n; }
private:
	Node<E> *n;
};

template <typename E>
class ReverseListIterator
{
public:
	ReverseListIterator( Node<E> *vn = nullptr ) : n(vn) {}
	
	E& operator*() const { return n->element; }
	ReverseListIterator& operator++() { n = n->prev; return *this; }
	ReverseListIterator operator++(int) { ReverseListIterator tmp(*this); n = n->prev; return tmp; }
	bool operator==( const ReverseListIterator &i ) const { return n == i.n; }
	bool operator!=( const ReverseListIterator &i ) const { return n != i.n; }
private:
	Node<E> *n;
};

template <typename E>
class List
{
public:
	List() {}
	List( const List& l ) {
		for( auto &e : l )
			push_back( e );
	}
	List( List &&l ) : first(l.first), last(l.last) {
		l.first = nullptr;
		l.last = nullptr;
	}
	List( std::initializer_list<E> l ) {
		for( auto &e : l )
			push_back( e );
	}
	~List() {
		while( !empty() )
			pop_back();
	}
	List& operator=( const List& l ) {
		if( this != &l ) {
			while( !empty() )
				pop_back();
			
			first = nullptr;
			last = nullptr;
			
			for( auto &e : l )
				push_back( e );
		}
		return *this;
	}
	List& operator=( List&& l ) {
		if( this != &l ) {
			while( !empty() )
				pop_back();
			
			first = l.first;
			last = l.last;
			
			l.first = nullptr;
			l.last = nullptr;
		}
		return *this;
	}
	
	bool empty() const { return first == nullptr; }
	void pop_front() {
		assert( !empty() );
		Node<E> *n  = first->next;
		delete first;
		first = n;
		if( first )
			first->prev = nullptr;
		else
			last = nullptr;
	}
	void pop_back() {
		assert( !empty() );
		Node<E> *n  = last->prev;
		delete last;
		last = n;
		if( last )
			last->next = nullptr;
		else
			first = nullptr;
	}
	
	void push_back( const E& e ) {
		Node<E> *p = new Node<E>( e );
		if( last )
		{
			last->next = p;
			p->prev = last;
		}
		else
		{
			first = p;
		}
		last = p;
	}
	
	typedef ListIterator<E> iterator;
	typedef ReverseListIterator<E> reverse_iterator;
	iterator begin() { return iterator(first); }
	iterator end() { return iterator(0); }
	reverse_iterator rbegin() { return reverse_iterator(last); }
	reverse_iterator rend() { return reverse_iterator(0); }
	
private:
	Node<E> *first = nullptr;
	Node<E> *last  = nullptr;
};

#include <iostream>

template<typename E>
using MyList = List<E>;

int main()
{
	MyList<int> c1{ 44, 11, 33, 77 };

	for( auto &e : reverse_order(c1) )
		std::cout << e << std::endl;
	for( auto i = c1.rbegin(); i != c1.rend(); ++i )
		std::cout << *i << std::endl;
}

