#include <iostream>
#include <cstdlib>
using namespace std;

#define MAX 100

// este bloque define nuestra clase Stack
class Stack {
private:
	struct nodeStack {
		int val;
		nodeStack* next;
	};
	typedef struct nodeStack nodoS;

	nodoS *S;	// puntero al frente de la pila
	int nItems;	// alacena la cantidad de elementos de la pila

public:
	Stack();
	Stack(int num);
	~Stack();

	void push(int);
	int pop();
	int top();
	int size();
	bool isEmpty();
	void display();
};

// constructor de la clase.. crea la pila vacia
Stack::Stack(){
	cout << "Creando stack vacio..." << endl;
	S = NULL;
	nItems = 0;
}

// constructor de la clase.. crea la pila con un elemento
Stack::Stack(int num){
	cout << "Creando stack con un nodo..." << endl;
	S = new nodoS;
	S->val = num;
	S->next = NULL;
	nItems = 1;
}

// destructor de la clase, libera la memoria de todos los nodos
Stack::~Stack() {
	nodoS *p;
	cout << "Destruyendo stack..." << endl;
	while(S != nullptr){
		p = S;
		S = S->next;
		delete p;
	}
}

// inserta un elemento al frente de la pila
void Stack::push(int elem) {
	nodoS *p = new nodoS;
	p->val = elem;
	p->next = S;
	S = p;
	nItems++;
}

// Elimina el elemento que esta al frente de la pila y retorna su valor
int Stack::pop(){
	if (S==nullptr){
		cout<<"pop(): WARNING!!. Stack vacio!"<<endl;
		return -1;
	}

	nodoS *p = S;
	int k = p->val;
	S = S->next;
	delete p;
	nItems--;

	return k;
}

// retorna el valor que esta al tope de la pila
int Stack::top(){
	if (S==nullptr){
		cout<<"Stack vacio!"<<endl;
		return -1;
	}

	return S->val;
}

// retorna la cantidad de elementos que hay en la pila, en O(1) time
int Stack::size(){
	return this->nItems;
}

bool Stack::isEmpty(){
	if (S==nullptr)
		return true;
	return false;
}
// lista la pila
void Stack::display(){
	if (S==nullptr){
		cout<<"Stack vacio!";
		return;
	}

	cout << "Pila con " << nItems << " elementos: ";
	nodoS *p = S;
	while (p != nullptr){
		cout << p->val << " ";
		p = p->next;
	}
	cout << endl;
}

// este bloque define nuestra clase Queue
class Queue {
private:
	struct nodeQueue {
		int val;
		nodeQueue* next;
	};
	typedef struct nodeQueue nodoQ;

	nodoQ *Q;	// puntero AL FRENTE de la cola, por donde entran los elementos (enqueue)
	int nItems;	// almacena la cantidad de elementos de la cola

public:
    Queue();
    Queue(int num);
    ~Queue();

    void enqueue(int);
    int dequeue();
    int front();
    int last();
    int size();
    bool isEmpty();
    void display();
};

// constructor de la clase.. crea la cola vacia
Queue::Queue(){
	cout << "Creando Cola vacia..." << endl;
	Q = NULL;
	nItems = 0;
}

// constructor de la clase.. crea la cola con un elemento
Queue::Queue(int num){
	cout << "Creando Cola con un elemento..." << endl;
    Q = new nodoQ;
    Q->val = num;
    Q->next = NULL;
	 nItems = 1;
}

// destructor de la clase, libera la memoria de todos los nodoQ
Queue::~Queue() {
	nodoQ *p;
	cout << "Destruyendo Queue..." << endl;

	while(Q != nullptr){
 		p = Q;
 		Q = Q->next;
		delete p;
	}
}

// inserta un elemento al final(back) de la cola en tiempo O(n): la recorre desde el front al rear y lo pone al final
void Queue::enqueue(int elem) {
	nodoQ *p, *nuevo;

	nuevo = new nodoQ;
	nuevo->val = elem;
	nuevo->next = NULL;

	if (Q == nullptr)
		Q = nuevo;
	else{
		p = Q;
		while (p->next != nullptr)
			p = p->next;

		p->next = nuevo;
	}
	nItems++;
}

// Elimina el elemento que esta al frente de la cola y retorna su valo, en tiempo O(1)
int Queue::dequeue(){
    if (Q==nullptr){
        cout<<"dequeue(): ERROR!!. Cola vacia!"<<endl;
        return -1;
    }

    nodoQ *q = Q;
    int k= q->val;
    Q = Q->next;
    delete q;
	 nItems--;

    return k;
}

// retorna el elemento que esta al frente de la cola, corre en O(1)
int Queue::front(){
	if (Q==nullptr){
		cout<<"front():Cola vacia!"<<endl;
		return -1;
	}

	return Q->val;
}

// retorna el elemento que esta al final de la cola (el último que se inserto), corre en O(n)
int Queue::last(){
	if (Q==nullptr){
		cout<<"last():Cola vacia!"<<endl;
		return -1;
	}
	nodoQ *p = Q;
	while (p->next != nullptr)
		p = p->next;

	return p->val;
}

// retorna la cantidad de elementos que hay en la cola, en O(1) time
int Queue::size(){
	return this->nItems;
}

// lista la cola
void Queue::display(){
	if (Q==nullptr)
		cout<<"Cola vacia!";

	cout << "Cola con " << nItems << " elementos: ";
	nodoQ *p = Q;
	while (p != nullptr){
		cout << p->val << " ";
		p = p->next;
	}
	cout << endl;
}


int main(int argc, char **argv) {
	if(argc != 2){
		cout << "Error. Debe ejecutarse como ./sgteMayor n" << endl;
		exit(EXIT_FAILURE);
	}

	int i, x, n=atoi(argv[1]);
	Stack pila;
	Queue cola;
	// llenamos la cola
	for(i=0; i<n; i++){
		x=rand()%MAX;
		cola.enqueue(x);
	}
	cout << endl;
	cola.display();

	// paso 1
	pila.push(cola.dequeue());

	// paso 2
	for (i=1; i<n; i++){
		x = cola.dequeue(); // se extrae de la cola...
		
		// paso 2.a
		while(!pila.isEmpty() && x>pila.top())
			cout << " * El sgte mayor a " << pila.pop() << " es " << x << endl;

		// paso 2.b
		pila.push(x);	
	}

	// paso 3
	while(!pila.isEmpty())
		cout << " * El sgte mayor a " <<pila.pop()<< " es -1" << endl;

	return EXIT_SUCCESS;
}
