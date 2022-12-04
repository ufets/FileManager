#include "gtest/gtest.h"
#include "../MyMap/mymap.hpp"

TEST(MAP, constructor){
    mymap<int, double> Map;
    Map.find(123);
    std::cout<<"finished";
}

TEST(MAP, insert){
    std::cout<<"begin\n";
    mymap<int, int> Map;
    Map.insert(234, 't');
    Map.insert(1, 'e');
    Map.insert(2, 'm');
    Map.insert(333, 'k');
    std::cout<<"finished";
}

TEST(MAP, begin)
{
    mymap<int, int> Map;
    Map.insert(234, 't');
    Map.insert(1, 'e');
    auto it = Map.begin();
    std::cout<<"finished";
}

TEST(MAP, operator_plus_plus)
{

}

TEST(MAP, end)
{

}