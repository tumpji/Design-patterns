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

// example of Mediator

#include <iostream>
#include <memory>
#include <vector>

class Colleague;

class Mediator {
    public:
        virtual void CreateColleagues () = 0;
        virtual void ColleagueChanged (Colleague*) = 0;
};


class Colleague {
    public:
        Colleague ( Mediator* med ) : mediator(med) { };
        virtual ~Colleague () {}

        virtual void Changed () { mediator->ColleagueChanged(this); }
    protected:
        Mediator* mediator;
};


class ConcreteColleague : public Colleague {
    public:
        ConcreteColleague ( Mediator* med, std::string id ) : Colleague(med), state(0), id(id) {}

        void setState (int s) { 
            state = s;
            std::cout << id << " state changed to " << state << std::endl;
            Changed();
        }

        int getState () { return state; }
        
    private:
        int state;
        std::string id;
};




class ConcreteMediator : public Mediator {
    public:
        ConcreteMediator () : a(nullptr), b(nullptr) {}

        virtual void CreateColleagues () {
            a = new ConcreteColleague(dynamic_cast<Mediator*>(this), "A");
            b = new ConcreteColleague(dynamic_cast<Mediator*>(this), "B");
            c = new ConcreteColleague(dynamic_cast<Mediator*>(this), "C");
            d = new ConcreteColleague(dynamic_cast<Mediator*>(this), "D");
        }
        virtual void ColleagueChanged (Colleague* ptr) {
            // a;
            // b; 
            // c = a + b; // every time
            // d = c - 2*a // every time
            if ( ptr == a ) {
                c->setState( a->getState() + b->getState() );
                d->setState( c->getState() - 2 * a->getState() );
            }
            else if ( ptr == b ) {
                c->setState( a->getState() + b->getState() );
            }
            else if ( ptr == c ) {
                d->setState( c->getState() - 2 * a->getState() );
            }
            else {}
        }

        ConcreteColleague* getColleague (int i) { 
            switch( i ) { 
                case 0: return a; 
                case 1: return b; 
                //case 2: return c; 
                //case 3: return d; 
                default: return nullptr; 
            }
        }
    private:
        ConcreteColleague* a;
        ConcreteColleague* b;
        ConcreteColleague* c;
        ConcreteColleague* d;
};


///////////////////////////  demo /////////////////////

int main () {
    ConcreteMediator m;
    m.CreateColleagues();


    std::cout << "\t change A to 10" << std::endl;
    m.getColleague(0)->setState(10);

    std::cout << "\t change B to 20" << std::endl;
    m.getColleague(1)->setState(20);
    



    return 0;
}


