#include<iostream>
#include <cstdlib>
#include <ctime>
#include<cmath>
#include <chrono>
#include <thread>
#include <windows.h>



using namespace std;
int counter = 0;


class node
{
	int xco;
	int yco;
	int fv;
	int gv;
	int hv;
	char symbol;
	node* next;
	bool alreadyintheheap;
	int parent_xco;
	int parent_yco;

public:
	node(int xco,int yco,int f, int g, int h,char symbol, node*next,bool already,int pxco,int pyco)
	{


		this->xco = xco;
		this -> yco = yco;

		fv = f;
		gv = g;
		hv = h;
		this->symbol = symbol;

		this->next = next;
		alreadyintheheap = already;
		parent_xco=pxco;
		parent_yco=pyco;
	}
	node()
	{
		

		symbol = '*';
		next = nullptr;
		xco = -1;
		yco = -1;
		fv, gv, hv = -1;
		alreadyintheheap = false;
		parent_xco = -1;
		parent_yco = -1;
	}

	node(const node& d)
	{
		this->fv = d.fv;
		this->hv = d.hv;
		this->gv = d.gv;
		this->symbol = d.symbol;
		this->next = d.next;
		this->xco = d.xco;
		this->yco = d.yco;
		this->alreadyintheheap = d.alreadyintheheap;
		this->parent_xco = d.parent_xco;
		this->parent_yco = d.parent_yco;
	}


	int getparentxco()
	{
		return this->parent_xco;
	}

	int getparentyco()
	{
		return this->parent_yco;
	}

	node* getnext()
	{
		return this->next;
	}

	void setnext(node* x)
	{
		this->next = x;
	}

	void setparentx(int x)
	{
		this->parent_xco = x;
	}

	void setparenty(int x)
	{
		this->parent_yco = x;
	}


	int get_fv()
	{
		return this->fv;
	}
	int get_gv()
	{
		return this->gv;
	}
	int get_hv()
	{
		return this->hv;
	}

	

	void setchar(char x)
	{
		this->symbol = x;
	}

	void setxco(int x)
	{
		this->xco = x;
	}

	void setyco(int y)
	{
		this->yco = y;
	}

	int getyco()
	{
		return this->yco;
	}

	int getxco()
	{
		return this->xco;
	}


	int computehv(int sourceind_x,int sourceind_y)
	{

		int dis = floor(sqrt((pow((sourceind_x - xco), 2)) + (pow((sourceind_y - yco), 2))));
		return dis;
	}

	char getchar()
	{
		return this->symbol;
	}

	void sethv(int hv)
	{
		this->hv = hv;
	}
	void setfv(int fv)
	{
		this->fv = fv;
	}
	void setgv(int gv)
	{
		this->gv = gv;
	}


	void operator = (const node& D) {
		fv = D.fv;
		gv = D.gv;
		hv = D.hv;
		this->next = D.next;
		symbol = D.symbol;
		xco = D.xco;
		yco = D.yco;
		this->alreadyintheheap = D.alreadyintheheap;
		this->parent_xco = D.parent_xco;
		this->parent_yco = D.parent_yco;
		//this->parent = D.parent;

	}


	void setalreadyintheheap()
	{
		this->alreadyintheheap = true;
	}

	bool getalreadyintheheap()
	{
		return this->alreadyintheheap;
	}
};


// A class for Min Heap
class MinHeap {
	node* heap_array; // pointer to array of elements in heap
	int capacity; // maximum possible size of min heap
	int heap_size; // Current number of elements in min heap

public:
	// Constructor: Initialise a capacity and heap_array;
	MinHeap(int capacity) {
		this->heap_size = 0;
		this->capacity = capacity;
		this->heap_array = new node[capacity];
	}




	// method to heapify a subtree with the root at given index i
	void MinHeapify(int i) {
		/* A recursive method to heapify 'heap_array' */
		int l = left(i);
		int r = right(i);
		
		int smallest = i;
		if (l < heap_size && heap_array[l].get_fv() < heap_array[i].get_fv())
			smallest = l;
		if (r < heap_size && heap_array[r].get_fv() < heap_array[smallest].get_fv())
			smallest = r;

		if (smallest != i) {
			swap(heap_array[i], heap_array[smallest]);
			MinHeapify(smallest);
		}
	}

	// method to get index of parent of node at index i
	int parent(int i) { return (i - 1) / 2; }

	// method to get index of left child of node at index i
	int left(int i) { return (2 * i + 1); }

	// method to get index of right child of node at index i
	int right(int i) { return (2 * i + 2); }

	// method to remove minimum element (or root) from min heap
	node* extractMin() {
		
		if (heap_size == 1) {
			heap_size--;
			return &heap_array[0];
		}

		// remove the minimum value from the heap.
		node root = heap_array[0];
		heap_array[0] = heap_array[heap_size - 1];
		heap_size--;
		MinHeapify(0);

		return &root;
	}

	// method to decrease key value of key at index i to new_val
	//void decreaseKey(int i, int new_val) {
	//	heap_array[i] = new_val;
	//	while (i != 0 && heap_array[parent(i)] > heap_array[i]) {
	//		swap(heap_array[i], heap_array[parent(i)]);
	//		i = parent(i);
	//	}
	//}

	// Returns the minimum key (key at root) from min heap
	int getMin() { return heap_array[0].get_fv(); }

	// method deletes key at index i
	// (It first reduced value to minus infinite, then calls extractMin() )
	/*void deleteKey(int i) {
		decreaseKey(i, INT_MIN);
		extractMin();
	}*/

	// method to inserts a new key 'k'
	void insertKey(node k) {
		if (heap_size == capacity) {
			cout << "\nOverflow: Could not insertKey\n";
			return;
		}

		// Inserting the new key at the end
		int i = heap_size;
		heap_array[heap_size++] = k;

		while (i != 0 && heap_array[parent(i)].get_fv() > heap_array[i].get_fv()) {
			swap(heap_array[i], heap_array[parent(i)]);
			i = parent(i);
		}
	}
};



template <typename t>
class stack
{
	node* top;
public:
	stack();
	stack(node*);
	stack(const stack&);
	bool isempty();
	bool isfull();
	void push(int, int, int, int, int, char, node*, bool, int, int);
	void pop(int&, int&,int&,int&,int&);
	int* topvalue();
	int topvaluey();
	int topvaluex();
	node* gettoppointer();
	int topvalueX();
	int topvalueY();

};

template <typename t>
stack<t>::stack()
{
	top = nullptr;
}

template <typename t>
stack<t>::stack(node* pointer)
{
	top = pointer;
}

template <typename t>
stack<t>::stack(const stack& obj)
{
	this->top = obj.top;
}

template <typename t>
bool stack<t>::isempty()
{
	if (top == nullptr)
		return true;
	else
		return false;
}

template <typename t>
bool stack<t>::isfull()
{
	return false;
}

template <typename t>
void stack<t>::push(int xco,int yco,int fv,int gv,int hv,char symbol,node* next,bool alreadyintheheap,int parent_xco,int parent_yco)
{
	node* temp = new node(xco, yco, fv, gv, hv, symbol, next, alreadyintheheap, parent_xco, parent_yco);
	if (isempty())
	{
		temp->setnext(nullptr);
		top = temp;
	}
	else if (top != nullptr)
	{
		temp->setnext(top);
		top = temp;
	}
	counter++;
}

template <typename t>
void stack<t> ::pop(int& fv, int& hv,int& gv,int &x,int& y)
{
	node* temp = top;
	top = top->getnext();
	fv = temp->get_fv();
	gv = temp->get_gv();
	hv = temp->get_hv();
	x = temp->getxco();
	y = temp->getyco();
	delete temp;
	temp = nullptr;
	counter--;
}

template <typename t>
int* stack<t>::topvalue()
{
	int* arr = new int[2];
	arr[0] = this->top->getxco();
	arr[1] = this->top->getyco();
	return arr;

}

template <typename t>
int stack<t>::topvalueX()
{
	
	if (top == nullptr)
		return -1;
	return this->top->getxco();
}

template <typename t>
int stack<t>::topvalueY()
{
	if (top == nullptr)
		return -1;
	return this->top->getyco();
}

template <typename t>
node* stack<t>::gettoppointer()
{
	return this->top;
}

template <typename t>
int stack<t>::topvaluex()
{
	return this->top->getxco();

}

template <typename t>
int stack<t>::topvaluey()
{
	return this->top->getyco();

}



void print2D(node** arr)
{
	for (int i = 0;i < 40;i++)
	{
		for (int j = 0;j < 40;j++)
		{
			cout << arr[i][j].getchar();
		}
		cout << endl;
	}
}

bool node_coordinates_unequal(int x1, int x2, int y1, int y2) {
	if (x1 != x2 || y1 != y2)
		return true;
	else
		return false;
}



void routeplannerlogic(node** arr, node* s_node, int sourceind_x, int sourceind_y, int destination_x, int destination_y)
{
	int final_cost = 0;
	int origialsource_x = sourceind_x;
	int origialsource_y = sourceind_y;
	int temp_x;
	int temp_y;
	/*int sx = sourceind_x;
	int sy = sourceind_y;
	int dx = destination_x;
	int dy = destination_y;*/
	MinHeap h(2000);
	node* tempsource = new node();
	tempsource = s_node;
	cout << endl << endl;
	for (int i = 0;i < 40;i++)
	{
		for (int j = 0;j < 40;j++)
		{
			arr[i][j].setxco(i);
			arr[i][j].setyco(j);

		}
	}

	int gn = 1;

	stack<node*> s1;
	int prexco = -1;
	int preyco = -1;
	while (sourceind_x != destination_x || sourceind_y != destination_y)
	{



		int hn;
		int* coordinates_arr = new int[2];
		coordinates_arr[0] = prexco;
		coordinates_arr[1] = preyco;

		if ((sourceind_y + 1) <= 39 && node_coordinates_unequal(coordinates_arr[0], sourceind_x, coordinates_arr[1], sourceind_y + 1))
		{
			arr[sourceind_x][sourceind_y + 1].setgv(gn);
			hn = arr[sourceind_x][sourceind_y + 1].computehv(destination_x, destination_y);   //computehv(sourceind_x,sourceind_y);

			if (arr[sourceind_x][sourceind_y + 1].getchar() == 'L')
				hn = hn + 10;
			else if (arr[sourceind_x][sourceind_y + 1].getchar() == 'H')
				hn = hn + 20;
			else if (arr[sourceind_x][sourceind_y + 1].getchar() == 'C')
				hn = INT_MAX;
			arr[sourceind_x][sourceind_y + 1].sethv(hn);
			int fn = gn + hn;
			arr[sourceind_x][sourceind_y + 1].setfv(fn);
			if (arr[sourceind_x][sourceind_y + 1].getalreadyintheheap() == false)
			{
				arr[sourceind_x][sourceind_y + 1].setparentx(sourceind_x);
				arr[sourceind_x][sourceind_y + 1].setparenty(sourceind_y);

				h.insertKey(arr[sourceind_x][sourceind_y + 1]);
				arr[sourceind_x][sourceind_y + 1].setalreadyintheheap();
				//arr[sourceind_x][sourceind_y + 1].setparent(&arr[sourceind_x][sourceind_y]);
				//cout << "the parent is " << arr[sourceind_x][sourceind_y + 1].getparent() << endl;
				cout << "inserted xco: " << sourceind_x << " inserted yco: " << sourceind_y + 1 << endl;

			}
		}
		if ((sourceind_y - 1) >= 0 && node_coordinates_unequal(coordinates_arr[0], sourceind_x, coordinates_arr[1], sourceind_y - 1))
		{

			arr[sourceind_x][sourceind_y - 1].setgv(gn);
			hn = arr[sourceind_x][sourceind_y - 1].computehv(destination_x, destination_y);

			if (arr[sourceind_x][sourceind_y - 1].getchar() == 'L')
				hn = hn + 10;
			else if (arr[sourceind_x][sourceind_y - 1].getchar() == 'H')
				hn = hn + 20;
			else if (arr[sourceind_x][sourceind_y - 1].getchar() == 'C')
				hn = INT_MAX;
			arr[sourceind_x][sourceind_y - 1].sethv(hn);
			int fn = gn + hn;
			arr[sourceind_x][sourceind_y - 1].setfv(fn);

			if (arr[sourceind_x][sourceind_y - 1].getalreadyintheheap() == false)
			{
				arr[sourceind_x][sourceind_y - 1].setparentx(sourceind_x);
				arr[sourceind_x][sourceind_y - 1].setparenty(sourceind_y);
				h.insertKey(arr[sourceind_x][sourceind_y - 1]);
				arr[sourceind_x][sourceind_y - 1].setalreadyintheheap();
				//arr[sourceind_x][sourceind_y-1].setparent(&arr[sourceind_x][sourceind_y]);
				//cout << "the parent is " << arr[sourceind_x][sourceind_y - 1].getparent() << endl;
				cout << "inserted xco: " << sourceind_x << " inserted yco: " << sourceind_y - 1 << endl;

			}
		}

		if ((sourceind_x + 1) <= 39 && node_coordinates_unequal(coordinates_arr[0], sourceind_x + 1, coordinates_arr[1], sourceind_y))
		{
			arr[sourceind_x + 1][sourceind_y].setgv(gn);
			hn = arr[sourceind_x + 1][sourceind_y].computehv(destination_x, destination_y);

			if (arr[sourceind_x + 1][sourceind_y].getchar() == 'L')
				hn = hn + 10;
			else if (arr[sourceind_x + 1][sourceind_y].getchar() == 'H')
				hn = hn + 20;
			else if (arr[sourceind_x + 1][sourceind_y].getchar() == 'C')
				hn = INT_MAX;
			arr[sourceind_x + 1][sourceind_y].sethv(hn);
			int fn = gn + hn;
			arr[sourceind_x + 1][sourceind_y].setfv(fn);

			if (arr[sourceind_x + 1][sourceind_y].getalreadyintheheap() == false)
			{

				arr[sourceind_x + 1][sourceind_y].setparentx(sourceind_x);
				arr[sourceind_x + 1][sourceind_y].setparenty(sourceind_y);
				h.insertKey(arr[sourceind_x + 1][sourceind_y]);
				arr[sourceind_x + 1][sourceind_y].setalreadyintheheap();
				//arr[sourceind_x + 1][sourceind_y].setparent(&arr[sourceind_x][sourceind_y]);
				//cout << "the parent is " << arr[sourceind_x+1][sourceind_y].getparent() << endl;
				cout << "inserted xco: " << sourceind_x + 1 << " inserted yco: " << sourceind_y << endl;


			}
		}

		if ((sourceind_x - 1) >= 0 && node_coordinates_unequal(coordinates_arr[0], sourceind_x - 1, coordinates_arr[1], sourceind_y))
		{
			arr[sourceind_x - 1][sourceind_y].setgv(gn);
			hn = arr[sourceind_x - 1][sourceind_y].computehv(destination_x, destination_y);

			if (arr[sourceind_x - 1][sourceind_y].getchar() == 'L')
				hn = hn + 10;
			else if (arr[sourceind_x - 1][sourceind_y].getchar() == 'H')
				hn = hn + 20;
			else if (arr[sourceind_x - 1][sourceind_y].getchar() == 'C')
				hn = INT_MAX;
			arr[sourceind_x - 1][sourceind_y].sethv(hn);
			int fn = gn + hn;
			arr[sourceind_x - 1][sourceind_y].setfv(fn);
			if (arr[sourceind_x - 1][sourceind_y].getalreadyintheheap() == false)
			{

				arr[sourceind_x - 1][sourceind_y].setparentx(sourceind_x);
				arr[sourceind_x - 1][sourceind_y].setparenty(sourceind_y);
				h.insertKey(arr[sourceind_x - 1][sourceind_y]);
				arr[sourceind_x - 1][sourceind_y].setalreadyintheheap();
				//arr[sourceind_x - 1][sourceind_y].setparent(&arr[sourceind_x][sourceind_y]);
				//cout << "the parent is " << arr[sourceind_x  -1][sourceind_y].getparent() << endl;
				cout << "inserted xco: " << sourceind_x - 1 << " inserted yco: " << sourceind_y << endl;

			}
		}

		node* temp = new node();
		temp = h.extractMin();
		temp->setchar('-');



		//initiasing temp varibales

		temp_x = temp->getxco();
		temp_y = temp->getyco();
		int temp_fv = temp->get_fv();
		int temp_gv = temp->get_gv();
		int temp_hv = temp->get_hv();
		int temp_char = temp->getchar();
		node* temp_next = temp->getnext();
		int temp_already = temp->getalreadyintheheap();
		int temp_pxco = temp->getparentxco();
		int temp_pyco = temp->getparentyco();
		arr[temp_x][temp_y].setchar('-');


		gn = temp->get_gv() + 1;


		int popped_hv, popped_fv, poppedval3_gv = 0;
		int popped_x, popped_y = -1;
		if (!(s1.isempty()))
		{
			if (temp->getparentxco() != s1.topvalueX() || temp->getparentyco() != s1.topvalueY())
			{
				while (!(s1.isempty()))
				{
					s1.pop(popped_fv, popped_hv, poppedval3_gv, popped_x, popped_y);
					//if(popped_x!=origialsource_x && popped_y!=origialsource_y)
					arr[popped_x][popped_y].setchar('*');
					if (popped_x == origialsource_x && popped_y == origialsource_y)
						arr[popped_x][popped_y].setchar('S');



				}
			}

		}

		prexco = arr[temp_x][temp_y].getparentxco();
		preyco = arr[temp_x][temp_y].getparentyco();
		sourceind_x = temp_x;
		sourceind_y = temp_y;



		if (s1.gettoppointer() != nullptr)
		{
			sourceind_x = s1.topvaluex();
			sourceind_y = s1.topvaluey();
		}

		
		cout << "fetched value of x from min heap: " << temp_x << "  " << " fetched value of y from min heap" << temp_y << endl << endl;


		s1.push(temp_x, temp_y, temp_fv, temp_gv, temp_hv, temp_char, temp_next, temp_already, temp_pxco, temp_pyco);
		final_cost = temp_fv;
		//this_thread::sleep_for(chrono::milliseconds(2000));
		print2D(arr);

	}
	cout << "h: " << arr[temp_x][temp_y].get_hv() << endl;
	cout << "g: " << arr[temp_x][temp_y].get_gv() << endl;
	cout << "cost: " << arr[temp_x][temp_y].get_fv() << endl;

	for (;arr[temp_x][temp_y].getparentxco() != -1 && arr[temp_x][temp_y].getparentxco() != -1 ;) /////////////////////////////
	{
		arr[temp_x][temp_y].setchar('-');
		temp_x = arr[temp_x][temp_y].getparentxco();
		temp_y = arr[temp_x][temp_y].getparentyco();


	}   /////////////////////////////////////////
	//arr[temp_x][temp_y].setchar('-');
	arr[origialsource_x][origialsource_y].setchar('S');

	arr[destination_x][destination_y].setchar('D');

	print2D(arr);




}
	






int main()
{

	

	node** arr = new node * [40];

		for (int j = 0;j < 40;j++)
		{
			arr[j]=new node[40];
		}
	

	srand(time(0));
	int start_ind1 = rand() % 40;
	int start_ind2 = rand() % 40;
	int destination_ind1 = rand() % 40;
	int destination_ind2 = rand() % 40;
	arr[start_ind1][start_ind2].setchar('S');
	arr[start_ind1][start_ind2].setparentx(-1);    /////////////////////
	arr[start_ind1][start_ind2].setparenty(-1);   //////////////////////


	//arr[start_ind1][start_ind2].setparent(nullptr);

	arr[destination_ind1][destination_ind2].setchar('D');
	

	int nooflighttraffic= rand() % 40;
	int heavytraffic = rand() % 40;
	//int noofroadsclosed= rand() % 5;
	
	for (int i = 0;i < nooflighttraffic;i++)
	{
		int randomind1= rand() % 40;
		int randomind2 = rand() % 40;
		if (arr[randomind1][randomind2].getchar() != 'S' && arr[randomind1][randomind2].getchar() != 'D')
			arr[randomind1][randomind2].setchar('L');
		else
			i--;
		
	}

	for (int i = 0;i < heavytraffic;i++)
	{

		int randomind1 = rand() % 40;
		int randomind2 = rand() % 40;
		if (arr[randomind1][randomind2].getchar() != 'S' && arr[randomind1][randomind2].getchar() != 'D')
			arr[randomind1][randomind2].setchar('H');
		else
			i--;

	}

	
	print2D(arr);
	routeplannerlogic(arr,&arr[start_ind1][start_ind2],start_ind1,start_ind2,destination_ind1,destination_ind2);

	system("pause");

}