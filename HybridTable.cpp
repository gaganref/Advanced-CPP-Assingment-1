#include "HybridTable.h"
#include "iostream"
#include "cmath"

using namespace std;

Node::Node(int index, int val) {
    index_ = index;
    val_ = val;
    next_ = nullptr;
}

Node::Node(int index, int val, Node* next) {
    index_ = index;
    val_ = val;
    next_ = next;
}

Node::~Node() {
	// IMPLEMENT ME
}

HybridTable::HybridTable() {
    total_array_size = INITIAL_ARRAY_SIZE;
    array_ = new int[total_array_size] {0};   // Initializes array_ with all values as 0
//    used_array_size = total_array_size;
    list_ = nullptr;
}

HybridTable::HybridTable(const int *p, int n) {
    total_array_size = n;
    array_ = new int[total_array_size];
    for (int itr = 0; itr < total_array_size; itr++) {
        array_[itr] = p[itr];
    }

    list_ = nullptr;
}

HybridTable::~HybridTable() {
    // Destructor to be implemented

    delete [] array_;
    deleteAllNodes();
}

HybridTable::HybridTable(const HybridTable& other) {
    total_array_size = other.total_array_size;
//    used_array_size = other.used_array_size;
    array_ = new int[total_array_size];   // initialize a new array with the other array size

    for (int itr = 0; itr < total_array_size; itr++) {
        array_[itr] = other.array_[itr];  // copy the values of other array
    }

    list_ = nullptr;
    if(other.list_ != nullptr){
        Node* other_current = other.list_;
        list_ = new Node(other_current->index_, other_current->val_);
        Node* this_current = list_;
        other_current = other.list_->next_;

        while(other_current != nullptr){
            Node* temp_node = new Node(other_current->index_, other_current->val_);
            this_current->next_ = temp_node;
            other_current = other_current->next_;
            this_current = temp_node;
        }
    }
}

HybridTable& HybridTable::operator=(const HybridTable& other) {
	if(this != &other){ //To make sure the object is assigning to itself (ex: x=x)
        //delete previous values
        delete [] array_;
        deleteAllNodes();

        total_array_size = other.total_array_size;
//        used_array_size = other.used_array_size;
        array_ = new int[total_array_size];   // initialize a new array with the other array size

        for (int itr = 0; itr < total_array_size; itr++) {
            array_[itr] = other.array_[itr];  // copy the values of other array
        }

        list_ = nullptr;
        if(other.list_ != nullptr){
            Node* other_current = other.list_;
            list_ = new Node(other_current->index_, other_current->val_);
            Node* this_current = list_;
            other_current = other.list_->next_;

            while(other_current != nullptr){
                Node* temp_node = new Node(other_current->index_, other_current->val_);
                this_current->next_ = temp_node;
                other_current = other_current->next_;
                this_current = temp_node;
            }
        }
    }

	return *this;
}

int HybridTable::get(int i) const {
	if((i < total_array_size) && (i >= 0)){
        return array_[i];
    }

    Node* node = getNode(i);
    if(node != nullptr){
        return node->val_;
    }

	return 0;
}

void HybridTable::set(int i, int val) {
    if(findAndReplace(i, val)){
        return;
    }


    /* @TODO
     * array size should in powers of 2, For example: 2pow(3) = 8 means range from [0-7]
     * Check if the array size can be increased
     * if can be increased increase and set the value
     * if cannot be introduce it in the linked list but the list index should be in increasing order
     * */

    // introduce the new value into the list and then check for the resizing of array
    insertNodeAtIndex(i, val);

    int new_array_size = calcNewArraySize();
    if(new_array_size > total_array_size){
        resizeArray(new_array_size);
    }
//    cout << "array size: " << endl << this->toString() << endl;
}

string HybridTable::toString() const {
	string out_string;

    for(int itr=0; itr < total_array_size; itr++){
        out_string += to_string(itr) + " : " + to_string(array_[itr]);
        if(itr < total_array_size-1){
            out_string += "\n";
        }
    }
    if(list_ != nullptr){
        out_string = out_string + "\n---\n" + listAsString();
    }

	return out_string;
}

int HybridTable::getArraySize() const {
//    cout << "array size: " << endl << this->toString() << endl;
	return total_array_size;
}

int HybridTable::getTotalSize() const {
//    cout << "Total array size: " << endl << this->toString() << endl;
    return total_array_size + getListLength();
}

bool HybridTable::findAndReplace(const int index, const int val) {
    if((index < total_array_size) & (index >= 0)){
        array_[index] = val;
        return true;
    }

    Node* node = getNode(index);
    if(node != nullptr){
        node->val_ = val;
        return true;
    }

    return false;
}


int HybridTable::possibleArraySize(int index) {
    // Finding log of index base 2
    int lg = log(index) / log(2);

    // Calculating the two possible
    // nearest values
    int a = pow(2, lg);
    int b = pow(2, lg + 1);

    // Find the closest one
    if ((index - a) < (b - index)) {
        if (a > index) {
            return a;
        }
    }
    return b;
}

int HybridTable::getListLength() const {
    int list_length = 0;
    Node* current_node = list_;
    while(current_node != nullptr){
        list_length += 1;
        current_node = current_node->next_;
    }
    return list_length;
}

Node *HybridTable::getNode(int index) const {
    Node* current_node = list_;
    while(current_node != nullptr){
        if(current_node->index_ == index){
            return current_node;
        }
        current_node = current_node->next_;
    }
    return nullptr;
}

void HybridTable::setNode(int index, int val) {
    Node* node = getNode(index);
    if(node != nullptr){
        node->val_ = val;
    }
}

void HybridTable::insertNodeAfter(Node* location, int index, int val) {
    if(location == nullptr){
        return;
    }
    Node* new_node = new Node(index, val);
    if(location->next_ != nullptr){
        new_node->next_ = location->next_;
    }
    location->next_ = new_node;
}

void HybridTable::removeNodeAfter(Node* node) {
    if(node == nullptr){
        return;
    }
    Node* temp_node = node->next_;
    node->next_ = node->next_->next_;
    delete temp_node;
}

void HybridTable::removeNode(Node* node) {
    if(node == nullptr){
        return;
    }

    if(node == list_){
        removeHeadNode();
        return;
    }

    Node* previous_node = findPreviousNode(node);

    removeNodeAfter(previous_node);
}

void HybridTable::removeHeadNode() {
    if(list_ == nullptr){
        return;
    }

    Node* temp_node = list_->next_;
    delete list_;
    list_ = temp_node;
}

Node *HybridTable::findPreviousNode(Node *node) {
    Node* previous_node = list_;
    Node* current_node = list_;

    while(current_node != nullptr){
        if(node == current_node){
            break;
        }
        previous_node = current_node;
        current_node = current_node->next_;
    }

    return previous_node;
}

void HybridTable::deleteAllNodes() {
    while(list_ != nullptr){
        Node* temp_node = list_;
        list_ = temp_node->next_;
        delete temp_node;
    }
}

void HybridTable::insertHead(int index, int val) {
    Node* new_node = new Node(index, val, list_);
    list_ = new_node;
}

void HybridTable::insertNodeAtIndex(int index, int val) {
    if(list_ == nullptr){
        insertHead(index, val);
        return;
    }
    if(index < list_->index_){
        insertHead(index, val);
        return;
    }

    Node* current_node = list_;
    Node* possible_location = current_node;
    while(current_node != nullptr){
        if(current_node->index_ <= index){
            possible_location = current_node;
        }
        else{
            break;
        }
        current_node = current_node->next_;
    }
    insertNodeAfter(possible_location, index, val);
}

string HybridTable::listAsString() const {
    string out_string;
    Node* current_head = list_;
    int itr =0;
    while(current_head != nullptr){
        if(itr != 0){
            out_string += " --> ";
        }
        out_string += to_string(current_head->index_) + " : " + to_string(current_head->val_);
        current_head = current_head->next_;
        itr++;
    }
    return out_string;
}

int HybridTable::calcNewArraySize() {
    int out_size = total_array_size;
    int used_size = total_array_size;
    int new_size = nextPossibleArraySize(out_size);

    Node* current_node = list_;
    while(current_node != nullptr){
        int current_node_index = current_node->index_;
        if((current_node_index < new_size) && (current_node_index >= 0)){
            used_size ++;
        }

        float calc_percent = calcPercent(used_size, new_size);
        if(calc_percent >= 75.0f){
            out_size = new_size;
            used_size = out_size;
        }

        if(current_node_index >= new_size){
            new_size = nextPossibleArraySize(new_size);
        }
        current_node = current_node->next_;
    }

    return out_size;
}

int HybridTable::nextPossibleArraySize(int size) {
    int current_power = ceil(sqrt(size));
    if(pow(2, current_power) <= size){
        current_power += 1;
    }

    return pow(2, current_power);
}

float HybridTable::calcPercent(const int num1, const int num2) {
    return (((float)num1 / (float)num2) * 100.0f);
}

void HybridTable::resizeArray(int size) {
    int old_size = total_array_size;
    total_array_size = size;
    int* temp_array = new int[total_array_size]{0};
    for(int itr=0; itr<old_size; itr++){
        temp_array[itr] = array_[itr];
    }
    delete [] array_;
    array_ = temp_array;


    Node* current_node = list_;
    while(current_node != nullptr){
        Node* next_node = current_node->next_;
        int current_node_index = current_node->index_;
        if(current_node_index > size){
            break;
        }
        if((current_node_index < size) && (current_node_index >= 0)){
            array_[current_node_index] = current_node->val_;
            removeNode(current_node);
        }
        current_node = next_node;
    }

}
