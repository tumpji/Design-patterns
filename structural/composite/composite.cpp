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

// normal composite implementation 

#include <set>
#include <memory>
#include <stdexcept>


class Composite;
class Leaf;

class Component {
public:
    using ComponentPtr = std::shared_ptr<Component>;
    using CompositePtr = std::shared_ptr<Composite>;
    using LeafPtr      = std::shared_ptr<Leaf>;

    Component () {}
    virtual ~Component () {};

    virtual void Operation () = 0;

    virtual void Add ( ComponentPtr );
    virtual void Remove ( ComponentPtr );
};

class Leaf : public Component {
public:
    virtual void Operation ();
};

class Composite : public Component {
public:
    virtual void Operation ();

    virtual void Add ( ComponentPtr );
    virtual void Remove ( ComponentPtr );
private:
    std::set< ComponentPtr > set;
};


//////// Component 

void Component::Add ( ComponentPtr com ) {
    (void)com;
    throw std::runtime_error("Add is not implemented");
}
void Component::Remove ( ComponentPtr com ) {
    (void)com;
    throw std::runtime_error("Add is not implemented");
}

//////// Composite

void Composite::Operation () {
    for ( auto& t : set ) {
        t->Operation();
    }
}

void Composite::Add ( ComponentPtr com ) {
    set.insert( com );
}

void Composite::Remove ( ComponentPtr com ) {
    set.erase( com );
}

//////// Leaf

#include <iostream>
void Leaf::Operation() {
    std::cout << "Operation" << std::endl;
}

////////////////////////// demo //////////////////////////////

int main () { 
    Component::ComponentPtr composite = std::make_shared<Composite>();
    Component::ComponentPtr leaf      = std::make_shared<Leaf>();

    composite->Add( std::make_shared<Leaf>() );
    composite->Add( std::make_shared<Leaf>() );

    leaf->Operation();
    composite->Operation();

    return 0;
}


