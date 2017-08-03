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

// normal factory method implementation 

#include <memory>

struct Product { virtual void who () = 0; };
struct ConcreteProductA : public Product { void who ();};
struct ConcreteProductB : public Product { void who ();};



class Creator {
public:
    virtual std::shared_ptr<Product> makeProduct () = 0;
    virtual ~Creator () {}
};

class ConcreteCreator1 : public Creator {
public:
    ConcreteCreator1 () {}
    virtual std::shared_ptr<Product> makeProduct () {
        return std::make_shared<ConcreteProductA>(); 
        // or any other construction of object + init
    }
};
class ConcreteCreator2 : public Creator {
public:
    ConcreteCreator2 () {}
    virtual std::shared_ptr<Product> makeProduct () {
        return std::make_shared<ConcreteProductB>(); 
    }
};


////////////// demo ////////////////
//
#include <iostream>

void ConcreteProductA::who() {
    std::cout << "Creating A" << std::endl;
}
void ConcreteProductB::who() {
    std::cout << "Creating B" << std::endl;
}

#include <iostream>

int main () {
    std::unique_ptr< Creator > creator = std::make_unique<ConcreteCreator1>();

    for ( int i = 0 ; i < 3; ++i ) {
        auto t = creator->makeProduct();
        t->who();
    }

    creator = std::make_unique<ConcreteCreator2>();

    for ( int i = 0 ; i < 3; ++i ) {
        auto t = creator->makeProduct();
        t->who();
    }
}
