#include <iostream>

using namespace std;

template <typename T>
class List {
protected:
	struct Node {
		T value;
		Node* prev = nullptr;
		Node* next = nullptr;
		Node() = default;
		Node(T nval) : value(nval) {};
		~Node() = default;
	};
	Node* Head = nullptr;
	Node* Tail = nullptr;
	int size = 0;
public:
	List() = default;
	List(const T&);
	List(T*, size_t);
	~List();
	void push_front(const T&);
	void push_back(const T&);
	T pop_back();
	T pop_front();
	bool is_empty() const;
	int size_();
	T front();
	T back();
	bool insert(const T&, unsigned int);
	void append(const List&);
	List(const List& other);
	void sort();
	class Iterator {
	protected:
		Node* curr;

	public:
		Iterator(Node* nnode);
		T& operator*() const;
		T* operator->() const;
		Iterator& operator++();
		Iterator& operator--();
		bool operator==(const Iterator& other) const;
		bool operator!=(const Iterator& other) const;
	};
	Iterator begin();
	Iterator end();
};

template <typename T>
List<T>::List(const T& nval) : Head(new Node(nval)), Tail(Head), size(1) {
}

template <typename T>
List<T>::List(T* nval, size_t sz) {
	for (size_t i = 0; i < sz; i++) {
		push_front(nval[i]);
	}
}

template <typename T>
List<T>::~List() {
	while (size > 0) {
		pop_front();
	}
}

template <typename T>
void List<T>::push_back(const T& nval) {
	Node* NNode = new Node(nval);
	if (is_empty()) {
		Head = Tail = NNode;
	}
	else {
		NNode->prev = Tail;
		Tail->next = NNode;
		Tail = NNode;
	}
	size++;
}

template <typename T>
void List<T>::push_front(const T& nval) {
	Node* NNode = new Node(nval);
	if (is_empty()) {
		Head = Tail = NNode;
	}
	else {
		NNode->next = Head;
		Head->prev = NNode;
		Head = NNode;
	}
	size++;
}

template <typename T>
T List<T>::pop_back() {
	if (is_empty()) {
		throw runtime_error("Лист пустой, удаление невозможно");
	}
	T value_ = Tail->value;
	Node* tmp = Tail;
	Tail = Tail->prev;
	if (!Tail) {
		Head = nullptr;
	}
	else {
		Tail->next = nullptr;
	}
	delete tmp;
	size--;
	return value_;
}

template <typename T>
T List<T>::pop_front() {
	if (is_empty()) {
		throw runtime_error("Лист пустой, удаление невозможно");
	}
	T value_ = Head->value;
	Node* tmp = Head;
	Head = Head->next;
	if (!Head) {
		Tail = nullptr;
	}
	else {
		Head->prev = nullptr;
	}
	delete tmp;
	size--;
	return value_;
}

template <typename T>
bool List<T>::is_empty() const {
	return size == 0;
}

template <typename T>
int List<T>::size_() {
	return size;
}

template <typename T>
T List<T>::front() {
	if (is_empty()) {
		throw runtime_error("Нельзя вывести элемент т.к. лист пуст");
	}
	return Head->value;
}

template <typename T>
T List<T>::back() {
	if (is_empty()) {
		throw runtime_error("Нельзя вывести элемент т.к. лист пуст");
	}
	return Tail->value;
}

template <typename T>
bool List<T>::insert(const T& nval, unsigned int pos) {
	if (is_empty()) {
		return false;
	}
	Node* current_pos = Head;
	for (size_t i = 0; i < pos; i++) {
		if (current_pos->next = nullptr) {
			return false;
		}
		else {
			current_pos = current_pos->next;
		}
	}
	Node* NNode = new Node(nval);
	Node* curr_back = current_pos->prev;
	if (!curr_back) {
		curr_back->next = NNode;
		NNode->prev = curr_back;
	}
	else {
		NNode->prev = nullptr;
	}
	NNode->next = current_pos;
	current_pos->prev = NNode;
	size++;
	return true;
}

template <typename T>
void List<T>::append(const List& newlist) {
	for (size_t i = 0; i < newlist.size_(); i++) {
		push_back(newlist.pop_front());
	}
	delete newlist;
}

template <typename T>
List<T>::List(const List& other) : Head(nullptr), Tail(nullptr), size(0) {
	Node* current = other.Head;
	while (current != nullptr) {
		push_back(current->value); 
		current = current->next;
	}
}

template <typename T>
void List<T>::sort() {

}

template <typename T>
List<T>::Iterator::Iterator(Node* nnode) : curr(nnode) {}

template <typename T>
T& List<T>::Iterator::operator*() const {
	return curr->value;
}

template <typename T>
T* List<T>::Iterator::operator->() const {
	return &(curr->value);
}

template <typename T>
typename List<T>::Iterator& List<T>::Iterator::operator++() {
	if (curr) {
		curr = curr->next;
	}
	return *this;
}

template <typename T>
typename List<T>::Iterator& List<T>::Iterator::operator--() {
	if (curr) {
		curr = curr->prev;
	}
	return *this;
}

template <typename T>
bool List<T>::Iterator::operator==(const Iterator& other) const {
	return curr == other.curr;
}

template <typename T>
bool List<T>::Iterator::operator!=(const Iterator& other) const {
	return curr != other.curr;
}

template <typename T>
typename List<T>::Iterator List<T>::begin() {
	return Iterator(Head);
}

template <typename T>
typename List<T>::Iterator List<T>::end() {
	return Iterator(Tail);
}
