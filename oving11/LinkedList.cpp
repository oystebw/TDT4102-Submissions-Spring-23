#include "LinkedList.h"

namespace LinkedList{

std::ostream& operator<<(std::ostream& os, const Node& node){
    os << node.value << '\n';
    return os;
}

Node* LinkedList::insert(Node* pos, const std::string& value){
    if(pos == head.get()){
        head = std::make_unique<Node>(value, std::move(head->next), nullptr);
        head->next->prev = head.get();
        return pos;
    }
    if(pos == tail){
        pos->getPrev()->next = std::make_unique<Node>(value, std::make_unique<Node>(tail), pos->getPrev());
        return pos;
    }

    Node* prev = pos->getPrev();
    prev->next = std::make_unique<Node>(value, std::move(prev->next), prev);
    pos->prev = prev->getNext();
    return prev->getNext();
}

Node* LinkedList::remove(Node* pos){
    if(pos == head.get()){
        head = std::move(head.get()->next);
    }

    Node* tempPrev = pos->getPrev();
    Node* tempNext = pos->getNext();
    tempPrev->next = std::move(pos->next);
    tempNext->prev = tempPrev;

    return tempNext;
}

Node* LinkedList::find(const std::string& value){
    Node* current = head.get();

    while(current != tail){
        if(current->getValue() == value){
            return current;
        }
        current = current->getNext();
    }
    return tail;
}

void LinkedList::remove(const std::string& value){
    Node* current = head.get();
    while(current != tail){
        if(current->getValue() == value){
            remove(current);
            return;
        }
        current = current->getNext();
    }
}

std::ostream& operator<<(std::ostream& os, const LinkedList& list){
    int x{1};
    Node* current = list.head.get();
    while(current != list.tail){
        os << "Node " << x << ": " << current->getValue() << '\n';
        x++;
        current = current->getNext();
    }
    return os;
}

}

void testLinkedList(){
    LinkedList::LinkedList ll;
}