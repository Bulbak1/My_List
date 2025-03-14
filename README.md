# My_List
## Методы
### Конструкторы
- List();
- List(const T&);
- List(T*, size_t);
- List(const List& other);
### Деструктор
- ~List();
### Iterators
- Iterator begin();
- Iterator end();
### element access methods
- T front();
- T back();
### Capacity
- bool is_empty() const;
-	int size_();
### Modifiers
- void push_front(const T&);
- void push_back(const T&);
- T pop_back();
- T pop_front();
- bool insert(const T&, unsigned int);
- void append(const List&);
