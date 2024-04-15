#include <iostream>

using namespace std;

template <class AbstractClass>
class Container {
private:
	int size;
	AbstractClass** array;
public:
	Container() : size(0), array(new AbstractClass * []) {}
	Container(int size) : size(size), array(new AbstractClass * [size]) {
		for (int i = 0; i < size; i++) {
			array[i] = new AbstractClass();
		}
	}
	Container(const Container& с) : size(с.size), array(new AbstractClass * [с.size]) {
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
		size += 1;
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
		size += 1;
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
};


int main() {

	Container<int> c(4);
	c.push_front(1);
	for (int i = 0; i < c.get_size(); i++) {
		cout << c.get_object(i) << endl;
	}
	c.set_object(2, 4);
	cout << c.get_object(2);

	return 0;
}