#include "gtest/gtest.h"
#include "../MyMap/mymap.hpp"

TEST(MAP, constructor){
    mymap<int, char> Map;
    std::cout<<"finished";
}

TEST(MAP, copy_constructor){
    mymap<int, char> Map;
    Map.insert(234, 't');
    Map.insert(1, 'e');
    Map.insert(2, 'm');
    Map.insert(333, 'k');
    mymap<int, char> Map2(Map);
    std::cout<<"finished";
}

TEST(MAP, move_constructor){
    mymap<int, char> Map;
    Map.insert(234, 't');
    Map.insert(1, 'e');
    Map.insert(2, 'm');
    Map.insert(333, 'k');
    mymap<int, char> Map2(std::move(Map));
    std::cout<<"finished";
}

TEST(MAP, insert_normal){
    std::cout<<"begin\n";
    mymap<int, char> Map;
    Map.insert(234, 't');
    Map.insert(1, 'e');
    Map.insert(2, 'm');
    Map.insert(333, 'k');
    std::cout<<"finished";
}

TEST(MAP, insert_with_error){
    std::cout<<"begin\n";
    mymap<int, char> Map;
    Map.insert(234, 't');
    Map.insert(1, 'e');
    Map.insert(2, 'm');
    Map.insert(333, 'k');
    ASSERT_ANY_THROW(Map.insert(333, 'k'));
    std::cout<<"finished";
}

TEST(MAP, begin)
{
    mymap<int, char> Map;
    Map.insert(234, 't');
    Map.insert(1, 'e');
    Map.insert(2, 'm');
    Map.insert(333, 'k');
    auto it = Map.begin();
    EXPECT_EQ(it.operator->(), 'e');
    std::cout<<"finished";
}

TEST(MAP, begin_emty_map)
{
    mymap<int, int> Map;
    auto it = Map.begin();
    std::cout<<"finished";
}

TEST(MAP, operator_plus_plus_inf)
{
    mymap<int, int> Map;
    Map.insert(234, 't');
    Map.insert(1, 'e');
    Map.insert(3, 'm');
    Map.insert(333, 'k');

    auto it = Map.find(1);
    auto it2 = ++it;
    EXPECT_EQ(it.operator->(), 'm');
    std::cout<<"finished";
}

TEST(MAP, operator_plus_plus_post)
{
    mymap<int, int> Map;
    Map.insert(234, 't');
    Map.insert(1, 'e');
    Map.insert(3, 'm');
    Map.insert(333, 'k');

    auto it = Map.find(3);
    it++;
    EXPECT_EQ(it.operator->(), 't');
    std::cout<<"finished";
}

TEST(MAP, strelka)
{

    struct Node{
        int a;
        Node(int value):a(value){};
        /*
        friend bool operator>(const Node &node1, const Node& node2);

        friend bool operator<(const Node &node1, const Node &node2);*/
    };

/*
    bool operator>(const Node &node1, const Node& node2) {
        return node1.a > node2.a;
    }

    bool operator<(const Node &node1, const Node &node2) {
        return node1.a < node2.a;
    }
*/

    struct Node2{
        int b;
        Node2(int value):b(value){};
    };

        mymap<Node*, Node2*> Map;
        Node a(234);
        Node2 b(235);
        Map.insert(&a, &b);

        auto it = Map.find(&a);
        std::cout<<it->b;

}

TEST(MAP, erase_root)
{
    mymap<int, std::string> Map;
    Map.insert(234, "sdlg");
    Map.insert(333, "sljdgn");
    Map.insert(1, "sljdgn");
    Map.insert(3, "slgjn");
    Map.insert(222, "slgjn");
    Map.insert(12, "slgjn");
    Map.insert(42, "slgjn");
    Map.erase(234);
    auto it = Map.find(333);
    auto it2 = Map.find(1);
    EXPECT_EQ((*it).right.get(), nullptr);
    EXPECT_EQ((*it).left.get(), &(*it2));
    std::cout<<"finished";
}

TEST(MAP, erase_no_under_trees)
{
    mymap<int, std::string> Map;
    Map.insert(234, "sdlg");
    Map.insert(333, "sljdgn");
    Map.insert(1, "sljdgn");
    Map.insert(3, "slgjn");
    Map.insert(12, "slgjn");
    Map.insert(42, "slgjn");
    Map.erase(42);
    auto it = Map.find(12);
    EXPECT_EQ((*it).right.get(), nullptr);
    EXPECT_EQ((*it).left.get(), nullptr);
    std::cout<<"finished";
}

TEST(MAP, erase_leaf)
{
    mymap<int, std::string> Map;
    Map.insert(234, "sdlg");
    Map.insert(333, "sljdgn");
    Map.insert(1, "sljdgn");
    Map.insert(3, "slgjn");
    Map.insert(222, "slgjn");
    Map.insert(12, "slgjn");
    Map.insert(42, "slgjn");
    auto it = Map.find(42);
    EXPECT_EQ((*it).right.get(), nullptr);
    EXPECT_EQ((*it).left.get(), nullptr);
    std::cout<<"finished";
}


TEST(MAP, loop){
    mymap<int, std::string> Map;
    Map.insert(234, "sdlg");
    Map.insert(1, "sljdgn");
    Map.insert(3, "slgjn");
    for(auto it: Map)
    {
        std::cout<<it.value<<std::endl;
    }
}

TEST(MAP, where)
{
    mymap<int, std::string> Map;
    Map.insert(234, "11111");
    Map.insert(1, "2222");
    Map.insert(3, "33333");
    mymap<int, std::string> Map2 = Map.where(&foo);
    std::cout<<"finished";
}
