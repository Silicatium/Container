#include <iostream>
#include <ctime>

using namespace std;

template <class AbstractClass>
class Container {
private:
	int size;
	AbstractClass** array;
public:
	Container() : size(0), array(new AbstractClass* [0]) {}
	Container(int size) : size(size), array(new AbstractClass* [size]) {
		for (int i = 0; i < size; i++) {
			array[i] = new AbstractClass();
		}
	}
	Container(const Container& с) : size(с.size), array(new AbstractClass* [с.size]) {
		for (int i = 0; i < size; i++) {
			array[i] = new AbstractClass(*(с.array[i]));
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
	AbstractClass get_object(int index) {
		//Return element in container
		if (index >= 0 && index < size) return *array[index];
		else if (index < 0 && -index <= size) return *array[size + index];
		else return *array[size - 1];
	}
	void set_object(int index, AbstractClass element) {
		//Set value by index
		int parametr = 0; //for negative index
		if (index < 0) parametr = size;
		if ((index >= 0 && index < size) || (index < 0 && -index <= size)) {
			*array[index + parametr] = element;
		}
	}
	void push_back(AbstractClass element) {
		size++;
		AbstractClass** temp_arr = new AbstractClass * [size];
		for (int i = 0; i < size - 1; i++) {
			temp_arr[i] = new AbstractClass(*array[i]);
			delete array[i];
		}
		temp_arr[size - 1] = new AbstractClass(element);
		delete[] array;
		array = new AbstractClass * [size];
		for (int i = 0; i < size; i++) {
			array[i] = new AbstractClass(*temp_arr[i]);
			delete temp_arr[i];
		}
		delete[] temp_arr;
	}
	void push_front(AbstractClass element) {
		size++;
		AbstractClass** temp_arr = new AbstractClass * [size];
		temp_arr[0] = new AbstractClass(element);
		for (int i = 1; i < size; i++) {
			temp_arr[i] = new AbstractClass(*array[i - 1]);
			delete array[i - 1];
		}
		delete[] array;
		array = new AbstractClass * [size];
		for (int i = 0; i < size; i++) {
			array[i] = new AbstractClass(*temp_arr[i]);
			delete temp_arr[i];
		}
		delete[] temp_arr;
	}
	void insert(int index, AbstractClass element) {
		int parametr = 0; //for negative index
		if (index < 0) parametr = size;
		if (index + parametr >= 0 && index + parametr < size) {
			size++;
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
			array = new AbstractClass * [size];
			for (int i = 0; i < size; i++) {
				array[i] = new AbstractClass(*temp_arr[i]);
				delete temp_arr[i];
			}
			delete[] temp_arr;
		}
		else this->push_back(element);
	}
	void remove(int index) {
		int parametr = 0; //for negative index
		if (index < 0) parametr = size;
		if (index + parametr >= 0 && index + parametr < size) {
			size--;
			AbstractClass** temp_arr = new AbstractClass * [size];
			for (int i = 0; i < index + parametr; i++) {
				temp_arr[i] = new AbstractClass(*array[i]);
				delete array[i];
			}
			delete array[index + parametr];
			for (int i = index + parametr + 1; i < size + 1; i++) {
				temp_arr[i - 1] = new AbstractClass(*array[i]);
				delete array[i];
			}
			delete[] array;
			array = new AbstractClass * [size];
			for (int i = 0; i < size; i++) {
				array[i] = new AbstractClass(*temp_arr[i]);
				delete temp_arr[i];
			}
			delete[] temp_arr;
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
	return rand() % (end - start + 1) + start;
}

void random_create_object(Container<Point>& container) {
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


int main() {

	srand(time(0));
	Container<Point> c(5);
	random_create_object(c);
	c.applyFunction([](Point l) { l.view_coords(); });
	cout << "---\n";
	random_choice_object(c).view_coords();

}