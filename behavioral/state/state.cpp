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

// example of state design pattern

#include <memory>
#include <iostream>


class Context;

class State {
    // interface for bahavior associated with state of context
    public:
        // two 
        virtual void HandleA ( Context& )  = 0;
        virtual void HandleB ( Context& ) {}

    protected:
        // interface for changing states
        void changeState (Context& c, State& );
};


class ConcreteState1 : public State {
    // state dependent bahavior - state 1
    public:
        virtual void HandleA ( Context& c );
        virtual void HandleB ( Context& c ) {
            std::cout << "S1 b" << std::endl;
            (void)c;
        }

        static ConcreteState1& Instance () { return singleton; }
    private:
        ConcreteState1 () {}
        static ConcreteState1 singleton;
};

class ConcreteState2 : public State {
    // state dependent bahavior - state 2
    public:
        virtual void HandleA ( Context& c ) {
            std::cout << "S2 a" << std::endl;
            changeState(c, ConcreteState1::Instance());

        }
        virtual void HandleB ( Context& c ) {
            std::cout << "S2 b" << std::endl;
            (void)c;
        }

        static ConcreteState2& Instance () { return singleton; }
    private:
        ConcreteState2 () {}
        static ConcreteState2 singleton;
};

ConcreteState1 ConcreteState1::singleton = ConcreteState1();
ConcreteState2 ConcreteState2::singleton = ConcreteState2();

void ConcreteState1::HandleA ( Context& c ) {
    std::cout << "S1 a" << std::endl;
    changeState(c, ConcreteState2::Instance());
}


class Context {
    // Context for states & common bahavior ...
    public:
        Context () : state(&ConcreteState1::Instance()) {}

        void RequestA () { state->HandleA(*this); }
        void RequestB () { state->HandleB(*this); }

    private:
    // interface for changing state
        friend class State;
        void changeState (State& a) { state = &a; }
    private:
        State* state;
};

void State::changeState (Context& c, State& state) {
    c.changeState(state);
}

///////////// demo ////////////////////

int main () {
    Context c;
    c.RequestA();
    c.RequestB();
    c.RequestA();
    c.RequestB();

    return 0;
}
