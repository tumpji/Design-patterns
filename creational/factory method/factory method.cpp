//This file is part of Design-patterns.
//
//    Design-patterns is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Lesser General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    Design-patterns is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU Lesser General Public License for more details.
//
//    You should have received a copy of the GNU Lesser General Public License
//    along with Design-patterns.  If not, see <http://www.gnu.org/licenses/>.

// normal factory method implementation (without synchronization)
// threre isn't need for it

struct Product { };
struct ConcreteProductA : public Product { };
struct ConcreteProductB : public Product { };

class Creator {
public:
    virtual Product* FactoryMethod () = 0;
    virtual ~Creator () {}

    /*
    virtual void operation () = 0;
    ...
    */
};



class ConcreteCreator1 : public Creator {
public:
    ConcreteCreator1 () {}
    virtual Product* FactoryMethod ();
};
class ConcreteCreator2 : public Creator {
public:
    ConcreteCreator2 () {}
    virtual Product* FactoryMethod ();
};

////////////// demo ////////////////
//
#include <iostream>

Product* ConcreteCreator1::FactoryMethod() {
    std::cout << "Creating A" << std::endl;
    return new ConcreteProductA;
}
Product* ConcreteCreator2::FactoryMethod() {
    std::cout << "Creating B" << std::endl;
    return new ConcreteProductB;
}

#include <iostream>

int main () {
    Creator* a = new ConcreteCreator1;

    for ( int i = 0 ; i < 3; ++i ) {
        auto t = a->FactoryMethod();
        delete t;
    }
    delete a;
    a = nullptr;

    a = new ConcreteCreator2;

    for ( int i = 0 ; i < 3; ++i ) {
        auto t = a->FactoryMethod();
        delete t;
    }
    delete a;
    a = nullptr;
}
