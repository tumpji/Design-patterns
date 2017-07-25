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

// normal abstract factory implementation (without synchronization)

#include <memory>

class AbstractProductA {
public:
    virtual const char* interfaceA () = 0;
    virtual ~AbstractProductA () {}
};

class ProductA1 : public AbstractProductA { 
public:
    ProductA1 () {}
    virtual const char* interfaceA () { return &"ProductA1"[0]; }
};
class ProductA2 : public AbstractProductA { 
public:
    virtual const char* interfaceA () { return &"ProductA2"[0]; }
};


class AbstractProductB {
public:
    virtual const char* interfaceB () = 0;
    virtual ~AbstractProductB () {}
};

class ProductB1 : public AbstractProductB { 
public:
    virtual const char* interfaceB () { return &"ProductB1"[0]; }
};
class ProductB2 : public AbstractProductB { 
public:
    virtual const char* interfaceB () { return &"ProductB2"[0]; }
};




class AbstractFactory {
public:
    using AbstractProductAPTR = std::shared_ptr<AbstractProductA>;
    using AbstractProductBPTR = std::shared_ptr<AbstractProductB>;

    virtual ~AbstractFactory () {}

    virtual AbstractProductAPTR createProductA () = 0;
    virtual AbstractProductBPTR createProductB () = 0;
};

class ConcreteFactory1 : public AbstractFactory {
public:
    virtual AbstractProductAPTR createProductA () { 
        new ProductA1;
        return AbstractProductAPTR( new ProductA1 );
    }
    virtual AbstractProductBPTR createProductB () { 
        return AbstractProductBPTR( new ProductB1 );
    }
};
class ConcreteFactory2 : public AbstractFactory {
public:
    virtual AbstractProductAPTR createProductA () { 
        return AbstractProductAPTR( new ProductA2 );
    }
    virtual AbstractProductBPTR createProductB () { 
        return AbstractProductBPTR( new ProductB2 );
    }
};


//////////////////////// demo /////////////////
#include <iostream>


void function (AbstractFactory * factory) {
    AbstractFactory::AbstractProductAPTR a = factory->createProductA();
    AbstractFactory::AbstractProductBPTR b = factory->createProductB();

    std::cout << a->interfaceA() << "\t" << b->interfaceB() << std::endl;
}

int main () {

    std::cout << "ConcreteFactory1 : " << std::endl;
    AbstractFactory * factory = new ConcreteFactory1;
    function( factory );
    delete factory;

    std::cout << "ConcreteFactory2 : " << std::endl;

    factory = new ConcreteFactory2;
    function( factory );
    delete factory;
}
