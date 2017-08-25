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

// example of Observer

#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

class Observer {
    // defines updating interface
    public:
        virtual void Update () = 0;
};

class Subject {
    // manages list of observers ( attach, detach )
    // provides notify - to inform observers
    public:
        void Attach ( std::weak_ptr<Observer> obs ) { observers.push_back( obs ); }
        void Detach ( std::weak_ptr<Observer> obs ) { 
//            std::remove( observers.begin(), observers.end(), obs );
        }
        void Notify ();

    private:
        std::vector< std::weak_ptr<Observer> >  observers;
};

// Notify with expired cleening
void Subject::Notify () {
    std::vector< std::weak_ptr<Observer> > expir;

    for ( auto wp : observers ) {
        std::shared_ptr<Observer> sp ( wp );

        if ( sp.use_count() ) 
            sp->Update();
        else {
            std::cout << "Expired" << std::endl;
            expir.push_back( sp );
        }
    }

    for ( auto a : expir ) Detach( a );
}

class ConcreteSubject : public Subject {
    // manages state and it's getters/setters
    // sends Notify on change/posible change (depends on implementation)
    public:
        ~ConcreteSubject () { 
            std::cout << "ConcreteSubject deleted" << std::endl;
        }
        int GetState () { return state; }
        void SetState (int newstate) { state = newstate; Notify(); }
    private:
        int state;
};

class ConcreteObserver : public Observer {
    // bounded with one/many others subject (concrete type usualy)
    // it's state can be subset or other morphism
    public:
        ConcreteObserver ( std::shared_ptr<ConcreteSubject> sub ) : subject(sub) {
            Update();
        }
        ~ConcreteObserver () {
            std::cout << "ConcreteObserver deleted" << std::endl;
        }

        virtual void Update () {
            state = subject->GetState();
            print();
        }

        void print () {
            std::cout << "Observer " << this << "\t" << state << std::endl;
        }

    private:
        int state;
        std::shared_ptr<ConcreteSubject> subject;
};


///////////////////////// demo ////////////////////////////

std::shared_ptr<ConcreteObserver> a () {
    auto a = std::make_shared<ConcreteSubject>();

    auto obs1 = std::make_shared<ConcreteObserver>(a);
    auto obs2 = std::make_shared<ConcreteObserver>(a);
    a->Attach(obs1);
    a->Attach(obs2);

    a->SetState(11);

    a->SetState(22);

    return obs1;
}

void b () {
    std::cout << "Pred a" << std::endl;
    auto g = a();
    std::cout << "Po a" << std::endl;
}

int main () {
 
    std::cout << "Pred b" << std::endl;   

    b ();

    std::cout << "Po b" << std::endl;


    return 0;
}
