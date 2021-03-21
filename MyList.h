#pragma once

template <typename T>
class MyList
{
	// Объявляем структуру Node, для того, чтобы итератор видел его.
	struct Node;
public:
	// Объявляем класс итератор в начале.
	class iterator;
	class const_iterator;

	// Конструктор по умолчанию.
	// Результат: будет инициализирован барьерный элемент.
	MyList()
	{
		m_barrier.data = 0;

		m_barrier.next = &m_barrier;
		m_barrier.prev = &m_barrier;
	}


	// Конструктор копирования.
	// Входные параметры: other - копируемый список.
	// Результат: будет создан список - копия other.
	MyList(const MyList& other)
	{
		m_barrier.data = 0;

		m_barrier.next = &m_barrier;
		m_barrier.prev = &m_barrier;

		for (auto& it : other) {
			pushBack(it);
		}
	}


	// Оператор присваивания.
	// Входные параметры: other - вектор, который будет присваиваиться.
	// Результат: будет скопирован список other.
	MyList& operator=(const MyList& other)
	{
		clear();
		for (auto& it : other) {
			pushBack(it);
		}
		return *this;
	}


	// Деструктор.
	// Если в списке хранились указатели, то удаляются только эти указатели, не информация
	// на которую они указывают.
	// Результат: будут удалены все узлы в списке, кроме барьерного.
	~MyList()
	{
		clear();
	}


	// Очистить.
	// Если в списке хранились указатели, то удаляются только эти указатели, не информация
	// на которую они указывают.
	// Результат: будут удалены все узлы в списке, кроме барьерного.
	void clear()
	{
		if (m_barrier.next == &m_barrier) {
			return;
		}

		for (auto it = ++begin(); it != end(); it++) {
			delete it.m_node->prev;
		}
		delete m_barrier.prev;

		m_barrier.next = &m_barrier;
		m_barrier.prev = &m_barrier;
	}


	// Вставить в начало.
	// Входные параметры: newElement - вставляемый элемент.
	// Результат: первым элементом станет newElement.
	void pushFront(const T& newElement)
	{
		Node* newFrontNode = new Node;
		newFrontNode->data = newElement;
		newFrontNode->next = m_barrier.next;
		newFrontNode->prev = &m_barrier;

		m_barrier.next->prev = newFrontNode;
		m_barrier.next = newFrontNode;
	}


	// Вставить в конец.
	// Входные параметры: newElement - вставляемый элемент.
	// Результат: последним элементом станет newElement.
	void pushBack(const T& newElement)
	{
		Node* newBackNode = new Node;
		newBackNode->data = newElement;
		newBackNode->next = &m_barrier;
		newBackNode->prev = m_barrier.prev;

		m_barrier.prev->next = newBackNode;
		m_barrier.prev = newBackNode;
	}


	// Функция начать.
	// Возвращает: итератор на первый элемент в списке.
	iterator begin()
	{
		iterator it;
		it.m_node = m_barrier.next;

		return it;
	}


	// Функция начать.
	// Возвращает: итератор на первый элемент в списке.
	const_iterator begin() const
	{
		const_iterator it(m_barrier.next);

		return it;
	}


	// Функция конец.
	// Возвращает: итератор на элемент после последнего в списке.
	iterator end()
	{
		iterator it;
		it.m_node = &m_barrier;

		return it;
	}


	// Функция конец.
	// Возвращает: итератор на элемент после последнего в списке.
	const_iterator end() const
	{
		const_iterator it(&m_barrier);

		return it;
	}


	// Вставить. Элемент, на место которого идет вставка, будет смещен вправо
	// относительно старого.
	// Входные параметры: it - итератор на элемент, на место которого
	// будет вставлен вставляемый элемент.
	// element - вставляемый элемент.
	// Возвращает: итератор на вставленный элемент.
	iterator insert(iterator it, const T& element)
	{
		Node* newNode = new Node;
		newNode->data = element;
		newNode->next = it.m_node;
		newNode->prev = it.m_node->prev;

		newNode->prev->next = newNode;
		newNode->next->prev = newNode;


		iterator newIt;
		newIt.m_node = newNode;
		return newIt;
	}


	// Удалить первый элемент.
	// Возвращает: удаленный элемент.
	T popFront()
	{
		T buf = m_barrier.next->data;
		Node* newFrontNode = m_barrier.next->next;

		delete m_barrier.next;

		m_barrier.next = newFrontNode;
		newFrontNode->prev = &m_barrier;

		return buf;
	}


	// Удалить последний элемент.
	// Возвращает: удаленный элемент.
	T popBack()
	{
		T buf = m_barrier.prev->data;
		Node* newBackNode = m_barrier.prev->prev;

		delete m_barrier.prev;

		m_barrier.prev = newBackNode;
		newBackNode->next = &m_barrier;

		return buf;
	}


	// Первый элемент.
	// Возвращает: ссылку на первый элемент.
	T& front()
	{
		return m_barrier.next->data;
	}


	// Последний элемент.
	// Возвращает: ссылку на последний элемент.
	T& back()
	{
		return m_barrier.prev->data;
	}


	class iterator
	{
		// Для доступа MyList к приватным полям iterator.
		friend class MyList;
	public:
		// Конструктор по умолчанию. 
		// Результат: указатель становится nullptr.
		iterator()
		{
			m_node = nullptr;
		}


		// Конструктор копирования. 
		// Результат: указатель будет скопирован.
		iterator(const iterator& other)
		{
			m_node = other.m_node;
		}


		// Оператор присваивания.
		// Результат: указатель будет скопирован.
		iterator& operator=(const iterator& other)
		{
			if (*this == other) {
				return *this;
			}

			m_node = other.m_node;

			return *this;
		}


		// Оператор разыменования.
		// Результат: ссылка на элемент на который указывает итератор.
		T& operator*()
		{
			return m_node->data;
		}


		// Префиксный инкремент.
		// Результат: ссылка на новый элемент.
		iterator& operator++()
		{
			m_node = m_node->next;
			return *this;
		}


		// Постфиксный инкремент.
		// Результат: копия старого элемента.
		iterator operator++(int)
		{
			iterator old = *this;
			operator++();
			return old;
		}


		// Префиксный декремент.
		// Результат: ссылка на новый элемент.
		iterator& operator--()
		{
			m_node = m_node->prev;
			return *this;
		}


		// Постфиксный декремент.
		// Результат: копия старого элемента.
		iterator operator--(int)
		{
			iterator old = *this;
			operator--();
			return old;
		}

		
		// Оператор "равно". Если указатели одинаковые, то истина.
		// Входные параметры: other - итератор, с которым идет сравнение.
		bool operator==(iterator other)
		{
			if (m_node == other.m_node) {
				return true;
			}

			return false;
		}


		// Оператор "не равно". Если указатели разные, то истина.
		// Входные параметры: other - итератор, с которым идет сравнение.
		bool operator!=(iterator other)
		{
			return !(*this == other);
		}


	private:

		// Указатель на узел в векторе.
		Node* m_node;
	};

	class const_iterator
	{
	public:
		// Конструктор по умолчанию. 
		// Результат: указатель становится nullptr.
		const_iterator()
		{
			m_node = nullptr;
		}


		// Конструктор. 
		// Результат: указатель становится nullptr.
		const_iterator(const Node* node)
		{
			m_node = node;
		}


		// Оператор разыменования.
		// Результат: const ссылка на элемент на который указывает итератор.
		const T& operator*()
		{
			return m_node->data;
		}


		// Префиксный инкремент.
		// Результат: ссылка на новый элемент.
		const_iterator& operator++()
		{
			m_node = m_node->next;
			return *this;
		}


		// Постфиксный инкремент.
		// Результат: копия старого элемента.
		const_iterator operator++(int)
		{
			const_iterator old = *this;
			operator++();
			return old;
		}


		// Префиксный декремент.
		// Результат: ссылка на новый элемент.
		const_iterator& operator--()
		{
			m_node = m_node->prev;
			return *this;
		}


		// Постфиксный декремент.
		// Результат: копия старого элемента.
		const_iterator operator--(int)
		{
			const_iterator old = *this;
			operator--();
			return old;
		}


		// Оператор "равно". Если указатели одинаковые, то истина.
		// Входные параметры: other - итератор, с которым идет сравнение.
		bool operator==(const_iterator other)
		{
			if (m_node == other.m_node) {
				return true;
			}

			return false;
		}


		// Оператор "не равно". Если указатели разные, то истина.
		// Входные параметры: other - итератор, с которым идет сравнение.
		bool operator!=(const_iterator other)
		{
			return !(*this == other);
		}


	private:

		// Указатель на узел в векторе.
		const Node* m_node;
	};

private:

	struct Node
	{
		// Информация хранящаяся в узле.
		T data;

		// Указатель на следующий узел.
		Node* next;

		// Указатель на предыдущий узел.
		Node* prev;
	};


	// Барьерный элемент.
	Node m_barrier;
};
