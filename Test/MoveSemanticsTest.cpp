//
// Created by MORIMOTO on 2017/11/05.
//

#include <gtest/gtest.h>
#include "../Source/MoveSemantics.h"
#include <boost/timer.hpp>


TEST(MoveTest, move)
{
    move::Text tex;
    std::cout << "1" << std::endl;
    move::Text&& text = move::Text();
    std::cout << "2" << std::endl;
    const move::Text y = text;
    std::cout << "3" << std::endl;
    move::Annotation a(text);
    move::Annotation b(std::move(y));
}

TEST(MoveTest, forward)
{
    move::Widget w(1);
    
    std::cout << "log with copy" << std::endl;
    // const 参照で渡すとwの内容は保たれる
    move::logAndProcess(w);
    std::cout << w.get() << std::endl;
    std::cout << "log with move" << std::endl;
    // move でmove渡したら、もうwの内容は保たれてる保証はない。
    move::logAndProcess(std::move(w));
    std::cout << w.get() << std::endl;
}

template <typename T>
void f(T&& param) {
    std::cout << "called f(T&&)" << std::endl;
}
template <typename T>
void f(std::vector<T>&& param) {
    std::cout << "called f(vector<T>&&)" << std::endl;
}

TEST(MoveTest, UniversalReference)
{
    std::cout << "vectorをmoveで渡すと、vector<T>&& が呼ばれる" << std::endl;
    std::vector<double> vec;
    f(std::move(vec));
    
    std::cout << "それ以外はT&&の方(universal 参照)が呼ばれる" << std::endl;
    std::cout << "vector" << std::endl;
    f(vec);
    std::cout << "const vector" << std::endl;
    std::cout << "const vectorの場合vector<T>&& ではなく"
    "T&&の方が呼ばれる" << std::endl;
    const std::vector<double> cvec;
    f(std::move(cvec));
}

TEST(MoveTest, UnivesalRererenceVector)
{
    move::vector<int> v;
    int a = 0;
    v.push_back(std::move(a));
    //the following becomes error because move drops const.
//    const int b = 0;
//    v.push_back(std::move(b));
    int c = 0;
    v.emplace_back(c);
    const int d = 0;
    v.emplace_back(d);
    const int e = 0;
    v.emplace_back(std::move(e));
    //emplace_backは通るがpush_backはエラーになる。
    //push_backは右辺値参照だが、emplace_backはユニバーサル参照だから、
    //const左辺値参照が渡っている。
    //v.push_back(std::move(e));
}

TEST(MoveTest, UniversalFwd)
{
    move::Widget2 w;
    w.name();
    move::Widget2 other(std::move(w));
    other.name();
    //以下は最後のnameが不定になる。
    // name は左辺値
    std::string name = other.name();
    // set Name 内でmoveが呼ばれる
    other.setName(name);
    // nameは不定になる。
    std::cout << "name is "  << std::endl;
    std::cout << name << std::endl;
    
    //以下なら大丈夫
    const std::string name2 = other.name();
    //setName内でmoveが呼ばれるが、constなので左辺値にバインドされる。
    other.setName(name2);
    std::cout << "name2 is" << std::endl;
    std::cout << name2 << std::endl;
    
    //以下ならでも不定
    std::string name3 = "honya";
    other.setName(name3);
    std::cout << "name3 is" << std::endl;
    std::cout << name3 << std::endl;
    
    //以下ならオケー
    const std::string name4 = "hoby";
    other.setName(name4);
    std::cout << "name4 is" << std::endl;
    std::cout << name4 << std::endl;
}

TEST(MoveTest, UniversalOverload)
{
    // ユニバーサル参照を持つ関数のオーバーロードは避ける（ほとんどユニバーサル参照に吸収されるから）
    std::string p("patty dog");
    std::multiset<std::string> names;
    //move::logAndAdd(p, names);
    move::logAndAdd(22, names);
    //以下の例はユニバーサル参照のオーバーロード関数があると
//    エラーになるが、なければエラーにならない。
//    ある場合：shortはユニバーサル参照として解釈される。
//    ない場合：intの方に格上げされるて動く
//    short idx = 3;
//    move::logAndAdd(idx, names);
    for (auto s : names) {
        std::cout << s << std::endl;
    }
    
    move::Person q("nancy");
    auto cloneP(q);
    std::cout << cloneP._name << std::endl;
}

TEST(MoveTest, SolvingUniversalOverload)
{
    std::string hoge("hoge2");
    move::logAndAdd(hoge);
    
    int a = 33;
    move::logAndAdd(a);
    
}
 
    int huga(int x) {
        return x + 3;
    }
TEST(MoveTest, SolvingByEnableIf)
{
    move::SpecialPerson p("sp");
    std::cout << p._name << std::endl;
    move::SpecialPerson p2(std::move(p));
    std::cout << p2._name << std::endl;
    
    short a = 33;
    move::Person q(a);
    std::cout << q._name << std::endl;
   
    auto c = huga(a);
    std::cout << c << std::endl;
}

TEST(MoveTest, LargeVevtorTransform)
{
    boost::timer t;
    std::vector<double> x;
    for (std::size_t i = 0; i < 1; ++i) {
        x.emplace_back(i);
    }
    
    t.restart();

    move::func(x);
    std::cout << t.elapsed() << std::endl;
    
    t.restart();
    move::LargeContainer c1(x);
    std::cout << t.elapsed() << std::endl;
    c1.show();
    t.restart();
    move::LargeContainer c2(std::move(x));
    std::cout << t.elapsed() << std::endl;
    c2.show();
    
    t.restart();
    move::LargeContainer c3(c1);
    std::cout << t.elapsed() << std::endl;
    c3.show();
    
    t.restart();
    move::LargeContainer c4(std::move(c1));
    std::cout << t.elapsed() << std::endl;
    c4.show();
    
    
    
    
    
}
