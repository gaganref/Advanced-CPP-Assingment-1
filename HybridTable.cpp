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
    used_array_size = total_array_size;
    list_ = nullptr;
}

HybridTable::HybridTable(const int *p, int n) {
    total_array_size = n;
    array_ = new int[total_array_size];
    for (int itr = 0; itr < total_array_size; itr++) {
        array_[itr] = p[itr];
        used_array_size += 1;
    }

    list_ = nullptr;
}

HybridTable::~HybridTable() {
    // Destructor to be implemented

    delete[] array_;
    deleteAllNodes();
}

HybridTable::HybridTable(const HybridTable& other) {
    total_array_size = other.total_array_size;
    used_array_size = other.used_array_size;
    array_ = new int[total_array_size];   // initialize a new array with the other array size

    for (int itr = 0; itr < used_array_size; itr++) {
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
        delete []array_;
        deleteAllNodes();

        total_array_size = other.total_array_size;
        used_array_size = other.used_array_size;
        array_ = new int[total_array_size];   // initialize a new array with the other array size

        for (int itr = 0; itr < used_array_size; itr++) {
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
	if((i < used_array_size) && (i >= 0)){
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

    //Debug
//    float test = calcPercent(19, 27);
//    cout << test << endl;


    /* @TODO
     * array size should in powers of 2, For example: 2pow(3) = 8 means range from [0-7]
     * Check if the array size can be increased
     * if can be increased increase and set the value
     * if cannot be introduce it in the linked list but the list index should be in increasing order
     * */

    // introduce the new value into the list and then check for the resizing of array
    insertNodeAtIndex(i, val);

}

string HybridTable::toString() const {
	string out_string;

    for(int itr=0; itr < used_array_size; itr++){
        out_string += to_string(itr) + " : " + to_string(array_[itr]);
        if(itr < used_array_size-1){
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

float HybridTable::calcPercent(const int num1, const int num2) {
    return (((float)num1 / (float)num2) * 100.0f);
}
