#include "HybridTable.h"
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

}

HybridTable::HybridTable() {
    total_array_size = INITIAL_ARRAY_SIZE;
    array_ = new int[total_array_size] {0};   // Initializes array_ with all values as 0
    list_ = nullptr;
}

HybridTable::HybridTable(const int* p, int n) {
    createAndCopyArray(p, n);
    list_ = nullptr;
}

HybridTable::~HybridTable() {
    delete [] array_;
    deleteAllNodes();
}

HybridTable::HybridTable(const HybridTable& other) {
    // Copy new values
    createAndCopyArray(other.array_, other.total_array_size);
    list_ = nullptr;
    copyWholeList(other.list_);
}

HybridTable& HybridTable::operator=(const HybridTable& other) {
	if(this != &other){ //To make sure the object is assigning to itself (ex: x=x)

        //delete previous values
        delete [] array_;
        deleteAllNodes();

        //copy new values
        createAndCopyArray(other.array_, other.total_array_size);
        list_ = nullptr;
        copyWholeList(other.list_);
    }

	return *this;
}

int HybridTable::get(int i) const {
	if((i < total_array_size) && (i >= 0)){  //Check if the index is valid array_ index
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

    // introduce the new value into the list and then check for the resizing of array
    insertNodeAtIndex(i, val);

    int new_array_size = calcNewArraySize();
    if(new_array_size > total_array_size){
        resizeArray(new_array_size);
    }
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
	return total_array_size;
}

int HybridTable::getTotalSize() const {
    return total_array_size + getListLength();
}

bool HybridTable::findAndReplace(const int index, const int val) {
    if((index < total_array_size) & (index >= 0)){  // checks if the index is between 0 and total array size
        array_[index] = val;
        return true;
    }

    // checks if the node is available and changes
    Node* node = getNode(index);
    if(node != nullptr){
        node->val_ = val;
        return true;
    }

    return false;
}

int HybridTable::calcNewArraySize() {
    int out_size = total_array_size;
    int used_size = total_array_size;
    int next_size = nextPossibleArraySize(out_size);

    Node* current_node = list_;
    while(current_node != nullptr){
        int current_node_index = current_node->index_;

        // increment used size if the current index is valid in new size
        if((current_node_index < next_size) && (current_node_index >= 0)){
            used_size ++;
        }

        // if the used size percent is greater than or equal to 75 change out_size to new_size
        if(calcPercent(used_size, next_size) >= 75.0f){
            out_size = next_size;
        }

        if(current_node_index >= next_size){
            next_size = nextPossibleArraySize(next_size);
            used_size++;
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

void HybridTable::resizeArray(int size) {
    int old_size = total_array_size;
    total_array_size = size;

    int* temp_array = new int[total_array_size]{0}; // create an array with new size
    for(int itr=0; itr<old_size; itr++){
        temp_array[itr] = array_[itr];  // copy values from previous array
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

        // if the list index is a valid new array index copy the value to array and remove it from the list
        if((current_node_index < size) && (current_node_index >= 0)){
            array_[current_node_index] = current_node->val_;
            removeNode(current_node);
        }

        current_node = next_node;
    }

}

void HybridTable::createAndCopyArray(const int* otherArray, int otherArraySize) {
    total_array_size = otherArraySize;
    array_ = new int[total_array_size]; // initialize a new array with the other array size
    for (int itr = 0; itr < total_array_size; itr++) {
        array_[itr] = otherArray[itr]; //copy the values of other array
    }
}

void HybridTable::copyWholeList(Node* otherList) {
    if(otherList == list_){
        return;
    }
    // first copy the head node and then loop through the remaining nodes
    if(otherList != nullptr){
        Node* other_current = otherList;
        list_ = new Node(other_current->index_, other_current->val_);
        Node* this_current = list_;
        other_current = otherList->next_;

        while(other_current != nullptr){
            Node* temp_node = new Node(other_current->index_, other_current->val_);
            this_current->next_ = temp_node;
            other_current = other_current->next_;
            this_current = temp_node;
        }
    }
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

void HybridTable::insertHead(int index, int val) {
    Node* new_node = new Node(index, val, list_);
    list_ = new_node;
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

void HybridTable::insertNodeAtIndex(int index, int val) {
    if((list_ == nullptr) || (index < list_->index_)){   // insert into the head node if it null or the current index is less than head
        insertHead(index, val);
        return;
    }

    // find the possible insert location such that the list should be in increasing order
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

Node *HybridTable::findPreviousNode(Node* node) {
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

float HybridTable::calcPercent(const int num1, const int num2) {
    return (((float)num1 / (float)num2) * 100.0f);
}