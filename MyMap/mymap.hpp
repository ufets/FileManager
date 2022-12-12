#include <vector>
#include <memory>
#include <iostream>
#include <functional>

#pragma once



template <typename Tkey, typename Tvalue>
struct Elem{
public:
    Tkey key;
    Tvalue value;
    std::shared_ptr<Elem> left;
    std::shared_ptr<Elem> right;
    Elem<Tkey, Tvalue>* parent;
    explicit Elem(){
        left = nullptr;
        right = nullptr;
    }
    explicit Elem(Tkey tkey, Tvalue tvalue, Elem* parent_)
    {
        key = tkey;
        value = tvalue;
        parent = parent_;
    }

    Elem(const Elem& elem){
        key = elem.key;
        value = elem.value;
    }
};



template <typename Tkey, typename Tvalue>
class mymap {
private:
    std::shared_ptr<Elem<Tkey, Tvalue>> root;

    Elem<Tkey, Tvalue>* sub_find(Tkey tkey, Elem<Tkey, Tvalue>* elem, Elem<Tkey, Tvalue>* parent)
    {
        if(tkey < elem->key)
        {
            if(elem -> left == nullptr)
                return elem;
            sub_find(tkey, elem->left.get(), elem);
        }
        else if(tkey > elem->key)
        {
            if(elem -> right == nullptr)
                return elem;
            sub_find(tkey, elem->right.get(), elem);
        }
        else return parent;
    }
    void erase_no_under_trees(Elem<Tkey, Tvalue>* ptr){
        if (ptr->parent->right.get() == ptr)
        {
            ptr->parent->right = nullptr;
        }
        else{
            ptr->parent->left = nullptr;
        }
    }
    void erase_only_right(Elem<Tkey, Tvalue>* ptr){
        if (ptr->parent->right.get() == ptr)
        {
            ptr->parent->right = ptr->right;
        }
        else{
            ptr->parent->left = ptr->right ;
        }
        ptr->right->parent = ptr->parent;
    }
    void erase_only_left(Elem<Tkey, Tvalue>* ptr){
        if (ptr->parent->right.get() == ptr)
        {
            ptr->parent->right = ptr->left;
        }
        else{
            ptr->parent->left = ptr->left;
        }
        ptr -> left->parent = ptr->parent;
    }
    void erase_both(Elem<Tkey, Tvalue>* ptr){
        Elem<Tkey, Tvalue>* tmp = ptr -> right.get();
        while(tmp -> left.get() != nullptr)
        {
            tmp = tmp -> left.get();
        }
        ptr->value = tmp -> value;
        ptr -> key = tmp -> key;
        if(tmp -> right.get() != nullptr)
        {
            erase_only_right(tmp);
        }
        else{
            erase_no_under_trees(tmp);
        }
    }
public:
    class c_iterator{
    private:
        mutable Elem<Tkey, Tvalue>* cur;
    public:
        explicit c_iterator(Elem<Tkey, Tvalue>* first): cur(first){};
        bool operator==(const c_iterator& it) const{
            return cur == it.cur;
        }
        bool operator!=(const c_iterator& it) const{
            return cur != it.cur;
        }
        ///prefix increment
        c_iterator& operator++()
        {
            if (this == nullptr || this ->cur == nullptr)
            {
                throw std::logic_error("nullptr++");
            }
            Elem<Tkey, Tvalue>* ptr = cur;
            if (ptr ->right.get() != nullptr){
                cur = ptr->right.get();
                return (*this);
            }
            while (ptr != nullptr && ptr -> parent != nullptr) {
                if (ptr->parent->left.get() == ptr) {
                    cur = ptr->parent;
                    return (*this);
                }
                ptr = ptr->parent;
            }

            cur = nullptr;
            return (*this);
        }
        ///postfix increment
        c_iterator   operator++(int value)
        {
            c_iterator tmp(*this);
            if (this == nullptr || this ->cur == nullptr)
            {
                throw std::logic_error("nullptr++");
            }
            Elem<Tkey, Tvalue>* ptr = cur;
            if (ptr ->right.get() != nullptr){
                cur = ptr->right.get();
                return tmp;
            }
            while (ptr != nullptr  && ptr -> parent != nullptr) {
                if (ptr->parent->left.get() == ptr) {
                    cur = ptr->parent;
                    return tmp;
                }
                ptr = ptr->parent;
            }

            cur = nullptr;
            return tmp;
        }
        ///prefix decrement
        c_iterator&  operator--()
        {
            if (this == nullptr || this ->cur == nullptr)
            {
                throw std::logic_error("nullptr++");
            }
            Elem<Tkey, Tvalue>* ptr = cur;
            if (ptr ->left.get() != nullptr){
                cur = ptr->left.get();
                return (*this);
            }
            if (ptr -> parent != nullptr) {
                while (ptr != nullptr) {
                    if (ptr->parent->right.get() == ptr) {
                        cur = ptr->parent;
                        return (*this);
                    }
                    ptr = ptr->parent;
                }
            }
            cur = nullptr;
            return (*this);
        }
        ///postfix decrement
        c_iterator  operator--(int value)
        {
            c_iterator tmp(*this);
            if (this == nullptr || this ->cur == nullptr)
            {
                throw std::logic_error("nullptr++");
            }
            Elem<Tkey, Tvalue>* ptr = cur;
            if (ptr ->left.get() != nullptr){
                cur = ptr->left.get();
                return tmp;
            }
            if (ptr -> parent != nullptr) {
                while (ptr != nullptr) {
                    if (ptr->parent->right.get() == ptr) {
                        cur = ptr->parent;
                        return tmp;
                    }
                    ptr = ptr->parent;
                }
            }
            cur = nullptr;
            return tmp;
        }
        ///return elem ?????
        const Elem<Tkey, Tvalue>& operator*() const
        {
            return *cur;
        }
        ///return value ?????
        const Tvalue& operator->() const
        {
            return cur->value;
        }
    };

    class myiterator{
    private:
        Elem<Tkey, Tvalue>* cur;
    public:
        explicit myiterator(Elem<Tkey, Tvalue>* first): cur(first){};
        bool operator==(const myiterator& it) const{
            return cur == it.cur;
        }
        bool operator!=(const myiterator& it) const{
            return cur != it.cur;
        }
        ///prefix increment
        myiterator&  operator++()
        {
            if (this == nullptr || this ->cur == nullptr)
            {
                throw std::logic_error("nullptr++");
            }
            Elem<Tkey, Tvalue>* ptr = cur;
            if (ptr ->right.get() != nullptr){
                cur = ptr->right.get();
                return (*this);
            }
            while (ptr != nullptr && ptr -> parent != nullptr) {
                if (ptr->parent->left.get() == ptr) {
                    cur = ptr->parent;
                    return (*this);
                }
                ptr = ptr->parent;
            }

            cur = nullptr;
            return (*this);
        }
        ///postfix increment
        myiterator  operator++(int value)
        {
            myiterator tmp(*this);
            if (this == nullptr || this ->cur == nullptr)
            {
                throw std::logic_error("nullptr++");
            }
            Elem<Tkey, Tvalue>* ptr = cur;
            if (ptr ->right.get() != nullptr){
                cur = ptr->right.get();
                return tmp;
            }
            while (ptr != nullptr  && ptr -> parent != nullptr) {
                if (ptr->parent->left.get() == ptr) {
                    cur = ptr->parent;
                    return tmp;
                }
                ptr = ptr->parent;
            }

            cur = nullptr;
            return tmp;
        }
        ///prefix decrement
        myiterator&  operator--()
        {
            if (this == nullptr || this ->cur == nullptr)
            {
                throw std::logic_error("nullptr++");
            }
            Elem<Tkey, Tvalue>* ptr = cur;
            if (ptr ->left.get() != nullptr){
                cur = ptr->left.get();
                return (*this);
            }
            if (ptr -> parent != nullptr) {
                while (ptr != nullptr) {
                    if (ptr->parent->right.get() == ptr) {
                        cur = ptr->parent;
                        return (*this);
                    }
                    ptr = ptr->parent;
                }
            }
            cur = nullptr;
            return (*this);
        }
        ///postfix decrement
        myiterator   operator--(int value)
        {
            myiterator tmp(*this);
            if (this == nullptr || this ->cur == nullptr)
            {
                throw std::logic_error("nullptr++");
            }
            Elem<Tkey, Tvalue>* ptr = cur;
            if (ptr ->left.get() != nullptr){
                cur = ptr->left.get();
                return tmp;
            }
            if (ptr -> parent != nullptr) {
                while (ptr != nullptr) {
                    if (ptr->parent->right.get() == ptr) {
                        cur = ptr->parent;
                        return tmp;
                    }
                    ptr = ptr->parent;
                }
            }
            cur = nullptr;
            return tmp;
        }
        ///return elem ?????
        Elem<Tkey, Tvalue>& operator*()
        {
            return *cur;
        }
        ///return value ?????
        Tvalue& operator->()
        {
            return cur->value;
        }
        const Tvalue& operator->() const
        {
            return cur->value;
        }
    };

    /*/////////////////////////////////////////////////////////////////////////////*/



    explicit mymap<Tkey, Tvalue> ( ):root(nullptr){};

    mymap (const mymap& Map ){
        //for(c_iterator& it: Map)
        for(const auto& it : (*const_cast<mymap<Tkey, Tvalue>*>(&Map)))
        {
            this->insert(it.key, it.value);
        }
        /*
        for(c_iterator it = Map.cbegin(); it != Map.cend(); it++)
        {
            this->insert((*it).key, (*it).value);
        }*/
    }

    mymap (mymap&& Map ) noexcept{
        this->root = Map.root;
        Map.root = nullptr;
    }

    ///begin
    myiterator begin(){
        Elem<Tkey, Tvalue>* ptr = root.get();
        while(ptr!= nullptr && ptr -> left.get() != nullptr)
        {
            ptr = ptr ->left.get();
        }
        return myiterator(ptr);
    }
    ///end
    myiterator end(){
        return myiterator(nullptr);
    }


    c_iterator cbegin() const{
        Elem<Tkey, Tvalue>* ptr = root.get();
        while(ptr!= nullptr && ptr -> left.get() != nullptr)
        {
            ptr = ptr ->left.get();
        }
        return c_iterator(ptr);
    }

    c_iterator cend() const{
        return c_iterator(nullptr);
    }





    ///find
    myiterator find(Tkey tkey){
        if (root == std::nullptr_t())
        {
            return myiterator(nullptr);
        }
        if (root -> key == tkey)
        {
            return myiterator(root.get());
        }

        Elem<Tkey, Tvalue>* ptr = sub_find(tkey, root.get(), nullptr);

        if(ptr->key > tkey)
        {
            return myiterator(ptr->left.get());
        }
        return myiterator(ptr->right.get());
    }
    ///insert
    void insert(Tkey tkey, Tvalue tvalue){
        if(root.get() == nullptr)
        {
            root.reset(new Elem<Tkey, Tvalue>(tkey, tvalue, nullptr));
            return;
        }

        if (root -> key == tkey)
        {
            throw std::invalid_argument("mymap::insert:: such element already exists");
        }

        Elem<Tkey, Tvalue>* ptr = sub_find(tkey, root.get(), nullptr);


        if(ptr -> key > tkey)
        {
            if (ptr -> left != nullptr)
                throw std::invalid_argument("mymap::insert::l:: such element already exists");
            else{
                ptr -> left.reset(new Elem<Tkey, Tvalue>(tkey, tvalue, ptr));
            }
        }
        else{
            if (ptr -> right != nullptr)
                throw std::invalid_argument("mymap:: insert::r:: such element already exists");
            else{
                (ptr -> right).reset(new Elem<Tkey, Tvalue>(tkey, tvalue, ptr));
            }
        }
    }

    void erase(Tkey tkey){
        Elem<Tkey, Tvalue>* ptr = &(*find(tkey));
        if (ptr == nullptr)
        {
            throw std::invalid_argument("mymap::erase:: no such element");
        }
        //если нет поддеревьев
        if (ptr -> right.get() == nullptr && ptr->left.get() == nullptr)
        {
            erase_no_under_trees(ptr);
            return;
        }
        //если есть только левое
        if (ptr -> right.get() == nullptr)
        {
            erase_only_left(ptr);
            return;
        }
        //только правое
        if (ptr -> left.get() == nullptr)
        {
            erase_only_right(ptr);
            return;
        }
        //оба поддерева
        erase_both(ptr);

    }

    mymap where(bool (*func)(const Elem<Tkey, Tvalue>& elem)) const
    {
        mymap<Tkey, Tvalue> Map;
        for(const auto& it : (*const_cast<mymap<Tkey, Tvalue>*>(this)))
        {
            if (func(it))
            {
                Map.insert(it.key, it.value);
            }
        }
        return Map;
        /*for(c_iterator it = Map.cbegin(); it != Map.cend(); it++)
        {
            if (func(it))
            {
                Map.insert(it.key, it.value);
            }
        }
        return Map;*/
    }
};



    template <typename Tkey, typename Tvalue>
    bool foo(const Elem<Tkey, Tvalue>& elem)
    {
        return (elem.key % 2);
    }
