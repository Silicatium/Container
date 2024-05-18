#include <iostream>
#include <ctime>
#include <chrono>

using namespace std;
using namespace chrono;

template <class AbstractClass>
class Container {
private:
	int size;
	int memory;
	AbstractClass** array;
	void checked_empty_container() {
		if (size == 0) throw exception("Container is empty!");
	}
	int additional_memory = 50; //memory increase
public:
	Container() : size(0), memory(0), array(new AbstractClass* [0]) {}
	Container(int size) : size(size), memory(size), array(new AbstractClass* [size]) {
		for (int i = 0; i < size; i++) {
			array[i] = new AbstractClass();
		}
	}
	Container(const Container& c) : size(c.size), memory(c.size), array(new AbstractClass* [c.memory]) {
		for (int i = 0; i < size; i++) {
			array[i] = new AbstractClass(*(c.array[i]));
		}
	}
	~Container() {
		for (int i = 0; i < size; i++) {
			delete array[i];
		}
		delete[] array;
	}
	int get_size() {
		return size;
	}
	int get_additional_memory() {
		return additional_memory;
	}
	AbstractClass get_object(int index) {
		//Return element in container
		try {
			this->checked_empty_container();
			if (index >= 0 && index < size) return *array[index];
			else if (index < 0 && -index <= size) return *array[size + index];
			else return *array[size - 1];
		}
		catch (const exception& ex) {
			cout << ex.what() << endl;
		}
	}
	void set_object(int index, AbstractClass element) {
		//Set value by index
		int parametr = 0; //for negative index
		if (index < 0) parametr = size;
		if ((index >= 0 && index < size) || (index < 0 && -index <= size)) {
			*array[index + parametr] = element;
		}
	}
	void set_additional_memory(int quantity) {
		 if (quantity >= 10 && quantity <= 10000) additional_memory = quantity;
	}
	void push_back(AbstractClass element) {
		size++;
		if (memory >= size) array[size - 1] = new AbstractClass(element);
		else {
			memory += additional_memory;
			AbstractClass** temp_arr = new AbstractClass * [size];
			for (int i = 0; i < size - 1; i++) {
				temp_arr[i] = new AbstractClass(*array[i]);
				delete array[i];
			}
			temp_arr[size - 1] = new AbstractClass(element);
			delete[] array;
			array = new AbstractClass * [memory];
			for (int i = 0; i < size; i++) {
				array[i] = new AbstractClass(*temp_arr[i]);
				delete temp_arr[i];
			}
			delete[] temp_arr;
		}
	}
	void push_front(AbstractClass element) {
		size++;
		if (memory < size) {
			memory += additional_memory;
			AbstractClass** temp_arr = new AbstractClass * [size];
			temp_arr[0] = new AbstractClass(element);
			for (int i = 1; i < size; i++) {
				temp_arr[i] = new AbstractClass(*array[i - 1]);
				delete array[i - 1];
			}
			delete[] array;
			array = new AbstractClass * [memory];
			for (int i = 0; i < size; i++) {
				array[i] = new AbstractClass(*temp_arr[i]);
				delete temp_arr[i];
			}
			delete[] temp_arr;
		}
		else {
			array[size - 1] = new AbstractClass();
			for (int i = size - 1; i > 0; i--) {
				*array[i] = *array[i - 1];
			}
			*array[0] = element;
		}
	}
	void insert(int index, AbstractClass element) {
		int parametr = 0; //for negative index
		if (index < 0) parametr = size;
		if (index + parametr >= 0 && index + parametr < size) {
			size++;
			if (memory < size) {
				memory += additional_memory;
				AbstractClass** temp_arr = new AbstractClass * [size];
				for (int i = 0; i < index + parametr; i++) {
					temp_arr[i] = new AbstractClass(*array[i]);
					delete array[i];
				}
				temp_arr[index + parametr] = new AbstractClass(element);
				for (int i = index + parametr + 1; i < size; i++) {
					temp_arr[i] = new AbstractClass(*array[i - 1]);
					delete array[i - 1];
				}
				delete[] array;
				array = new AbstractClass * [memory];
				for (int i = 0; i < size; i++) {
					array[i] = new AbstractClass(*temp_arr[i]);
					delete temp_arr[i];
				}
				delete[] temp_arr;
			}
			else {
				array[size - 1] = new AbstractClass();
				for (int i = size - 1; i > index + parametr; i--) {
					*array[i] = *array[i - 1];
				}
				*array[index + parametr] = element;
			}
		}
		else this->push_back(element);
	}
	void pop() {
		if (szie > 0) {
			size--;
			delete array[size];
		}
	}
	void remove(int index) {
		int parametr = 0; //for negative index
		if (index < 0) parametr = size;
		if (index + parametr >= 0 && index + parametr < size) {
			size--;
			for (int i = index + parametr; i < size; i++) {
				*array[i] = *array[i + 1];
			}
			delete array[size];
		}
	}
	AbstractClass removeWithGet(int index) {
		AbstractClass temp = this->get_object(index);
		this->remove(index);

		return temp;
	}
	void applyFunction(void function(AbstractClass)) {
		for (int i = 0; i < size; i++) {
			function(*array[i]);
		}

	}
};

class Point {
private:
	int x;
	int y;
public:
	Point() : x(0), y(0) {};
	Point(int x, int y) : x(x), y(y) {};
	Point(const Point& p) : x(p.x), y(p.y) {}
	~Point() { x = 0; y = 0; }
	void view_coords() {
		printf("x = %d\ny = %d\n\n", x, y);
	}
};

class ColoredPoint : public Point {
private:
	int color;
public:
	ColoredPoint() : color(0) {};
	ColoredPoint(int x, int y, int color) : Point(x, y), color(color) {};
	ColoredPoint(const ColoredPoint& cp) : Point(cp), color(cp.color) {}
	~ColoredPoint() { color = 0; }
};

int random_number(int start, int end) {
	if ((end - start + 1) + start != 0) return rand() % (end - start + 1) + start;
	else return 0;
}

void random_create_objects(Container<Point>& container) {
	int number;
	for (int i = 0; i < container.get_size(); i++) {
		number = random_number(0, 1);
		if (number == 0) { Point p(random_number(0, 100), random_number(0, 100)); container.set_object(i, p); }
		else { ColoredPoint p(random_number(0, 100), random_number(0, 100), 0); container.set_object(i, p); }
	}
}

void random_add_object(Container<Point>& container, Point object) {
	container.insert(random_number(0, container.get_size() - 1), object);
}

Point random_choice_object(Container<Point>& container) {
	return container.get_object(random_number(0, container.get_size() - 1));
}

void random_remove(Container<Point>& container) {
	container.remove(random_number(0, container.get_size() - 1));
}


int main() {
	srand(time(0)); //disabling random number storage

	Container<Point> c(10);
	Point* p; //for random create 1 object in cycle
	int countOfActions;
	int randomEvent;
	random_create_objects(c);
	cout << "Enter count of actions: ";
	cin >> countOfActions;
	system_clock::time_point startTime = system_clock::now();
	for (int i = 0; i < countOfActions; i++) {
		if (c.get_size() != 0) randomEvent = random_number(0, 2);
		else randomEvent = random_number(0, 1);
		switch (randomEvent) {
		case 0:
			p = new Point(random_number(0, 100), random_number(0, 100));
			random_add_object(c, *p);
			delete p;
			break;
		case 1:
			random_remove(c);
			break;
		case 2:
			random_choice_object(c).view_coords();
			break;
		}
	}
	system_clock::time_point endTime = system_clock::now();
	//c.applyFunction([](Point l) { l.view_coords(); });
	system("cls");
	cout << "Cycle work time: " << duration_cast<milliseconds>(endTime - startTime).count() << " milliseconds" << endl;

	return 0;
}