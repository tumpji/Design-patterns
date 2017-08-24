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

// example of Mememto

#include <memory>
#include <iostream>

class Memento;


class Originator {
    public:
        Originator () : state_int(0), state_bool(false) {}

        std::shared_ptr<Memento> CreateMememnto ();
        void SetMemento (std::shared_ptr<const Memento>);


        void change () { state_bool = state_int = 13; }
    private:
        int state_int;
        bool state_bool;

        friend std::ostream& operator<< (std::ostream&, const Originator& );
};

std::ostream& operator<< (std::ostream& in, const Originator& orig ) {
    in << "Object : " << orig.state_int << " " << orig.state_bool << std::endl;
    return in;
}

class Memento {
    public:
        ~Memento () {}

    private:
        Memento () {};
        friend class Originator;

        // member state_int
        void SetStateInt ( int a ) { state_int = a; }
        int GetStateInt () const { return state_int; }

        // member state_bool
        void SetStateBool ( bool a ) { state_bool = a; }
        bool GetStateBool () const { return state_bool; }

    private:
        int state_int;
        bool state_bool;
};

std::shared_ptr<Memento> Originator::CreateMememnto() {
    auto ret = std::shared_ptr<Memento>(new Memento);
    ret->SetStateInt( state_int );
    ret->SetStateBool( state_bool );
    return ret;
}

void Originator::SetMemento ( std::shared_ptr<const Memento> mem ) {
    state_int = mem->GetStateInt();
    state_bool = mem->GetStateBool();
}


///////////////// demo /////////////////////


int main ( ) {
    Originator orig;
    std::cout << orig;

    auto memento = orig.CreateMememnto();
    orig.change();

    std::cout << orig;

    orig.SetMemento( memento );
    std::cout << orig;

    return 0;
}
