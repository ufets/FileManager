#include <vector>
#include <memory>
#include <iostream>

#pragma once



template <typename Tkey, typename Tvalue>
struct Elem{
public:
    Tkey key;
    Tvalue value;
    std::shared_ptr<Elem> left;
    std::shared_ptr<Elem> right;
    explicit Elem(){
        left = nullptr;
        right = nullptr;
    }
    explicit Elem(Tkey tkey, Tvalue tvalue)
    {
        key = tkey;
        value = tvalue;
    }

    Elem(const Elem& elem){
        key = elem.key;
        value = elem.value;
    }
};

template <typename T3>
class myiterator{
private:
    T3* cur;
public:
    explicit myiterator(T3* first): cur(first){};
    bool operator==(const myiterator<T3> it) const{
        return cur == it.cur;
    }
    bool operator!=(const myiterator<T3> it) const{
        return cur != it.cur;
    }
    T3& operator*()
    {
        return *cur;
    }
};


template <typename Tkey, typename Tvalue>
class mymap {
private:
    std::shared_ptr<Elem<Tkey, Tvalue>> root;

    Elem<Tkey, Tvalue>* sub_find(Tkey tkey, Elem<Tkey, Tvalue>* elem, Elem<Tkey, Tvalue>* parent)
    {
        std::cout<<tkey<<":SUBFIND:111\n";
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
    //void sub_insert(Tkey tkey, Tvalue& tvalue, Elem<Tkey, Tvalue>& elem);
    //void sub_erase(Tkey tkey, Elem<Tkey, Tvalue>& elem);
public:
    explicit mymap<Tkey, Tvalue> ( ):root(nullptr){};
    ///begin
    myiterator<Elem<Tkey, Tvalue>> begin(){
        Elem<Tkey, Tvalue>* ptr = root.get();
        while(ptr!= nullptr && ptr -> left.get() != nullptr)
        {
            ptr = ptr ->left.get();
        }
        return myiterator<Elem<Tkey, Tvalue>>(ptr);
    }

    ///end
    myiterator<Elem<Tkey, Tvalue>> end(){
        return myiterator<Elem<Tkey, Tvalue>>(nullptr);
    }

    ///find
    myiterator<Elem<Tkey, Tvalue>> find(Tkey tkey){
        if (root == std::nullptr_t())
        {
            return myiterator<Elem<Tkey, Tvalue>>(nullptr);
        }
        if (root -> key == tkey)
        {
            return myiterator<Elem<Tkey, Tvalue>>(root.get());
        }

        Elem<Tkey, Tvalue>* ptr = sub_find(tkey, root.get(), nullptr);

        if(ptr->key < tkey)
        {
            return myiterator(ptr->left.get());
        }
        return myiterator<Elem<Tkey, Tvalue>>(ptr->right.get());
    }

    ///insert
    void insert(Tkey tkey, Tvalue tvalue){
        std::cout<<tkey<<":INSERT:111\n";
        if(root.get() == nullptr)
        {
            root.reset(new Elem<Tkey, Tvalue>(tkey, tvalue));
            return;
        }

        if (root -> key == tkey)
        {
            throw std::invalid_argument("mymap::insert:: such element already exists");
        }

        std::cout<<tkey<<":INSERT:222\n";
        Elem<Tkey, Tvalue>* ptr = sub_find(tkey, root.get(), nullptr);
        std::cout<<tkey<<":INSERT:333\n";

        if(ptr -> key > tkey)
        {
            if (ptr -> left != nullptr)
                throw std::invalid_argument("mymap::insert::l:: such element already exists");
            else{
                ptr -> left.reset(new Elem<Tkey, Tvalue>(tkey, tvalue));
            }
        }
        else{
            if (ptr -> right != nullptr)
                throw std::invalid_argument("mymap:: insert::r:: such element already exists");
            else{
                (ptr -> right).reset(new Elem<Tkey, Tvalue>(tkey, tvalue));
            }
        }
        std::cout<<tkey<<":INSERT:444\n";
    }

    //void erase(Tkey tkey);
};
