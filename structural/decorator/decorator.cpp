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

// normal decorator implementation 

#include <memory>
#include <iostream> // for demo


class Component {
    // interface 
public:
    virtual void Operation () = 0;
    virtual ~Component () {}

};

using ComponentPtr = std::shared_ptr<Component>;

class ConcreteComponent : public Component {
    // implements main behaviour
public:
    virtual void Operation () {
        std::cout << "ConcreteComponent" << std::endl;
    }
};


class Decorator : public Component {
public:
    Decorator ( ComponentPtr comp ) : component(comp) {}

    virtual void Operation () {
        component->Operation();
    };
protected:
    ComponentPtr component;
};




class ConcreteDecoratorA : public Decorator {
public:
    ConcreteDecoratorA ( ComponentPtr com ) : Decorator(com), added_state(0) {}

    virtual void Operation () { 
        std::cout << "Called " << ++added_state << " times" << std::endl; 
        component->Operation();
    }
protected:
    int added_state;
};

class ConcreteDecoratorB : public Decorator {
public:
    ConcreteDecoratorB ( ComponentPtr com ) : Decorator(com) {}

    virtual void Operation () { 
        std::cout << "Added behaviour" << std::endl;
        component->Operation();
    }
};

/////////////////////////////////// demo ///////////////////////

int main () {
    ComponentPtr zajem = std::make_shared<ConcreteComponent>();

    std::cout << "Not decorated: " << std::endl;
    zajem->Operation();

    std::cout << "\nConcreteDecoratorA " << std::endl;
    zajem = std::make_shared<ConcreteDecoratorA>(zajem);
    zajem->Operation();

    std::cout << "\nConcreteDecoratorB " << std::endl;
    zajem = std::make_shared<ConcreteDecoratorB>(zajem);
    zajem->Operation();

    std::cout << "\nConcreteDecoratorB (secod time)" << std::endl;
    zajem = std::make_shared<ConcreteDecoratorB>(zajem);
    zajem->Operation();
}

