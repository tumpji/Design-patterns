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

// normal brigde implementation 


#include <memory>


class Implementation {
public:
    virtual ~Implementation () {}
    virtual void dev_draw_text () = 0;
    virtual void dev_draw_line () = 0;
};

class Implementation_platformA : public Implementation {
public:
    Implementation_platformA () {}
    virtual void dev_draw_text () { };
    virtual void dev_draw_line () { };
};

// class Implementation_platformB : public Implementation { }
// ...







//// abstraction tree

class Abstraction {
public:
    Abstraction () {
        imp = std::make_unique<Implementation_platformA> ();
    }

    void draw_text () { imp->dev_draw_text(); };
    void draw_line () { imp->dev_draw_line(); };
protected:
    std::shared_ptr<Implementation> imp;
};

class Abstraction_specific : public Abstraction {
public:
    void draw_rect () { 
        draw_line(); draw_line();
        draw_line(); draw_line();
    }
    // ...
};

//class Abstraction_specific2 : public Abstraction { }
//...


//////////////// demo

int main  () {
    Abstraction_specific g;
    g.draw_rect();
    g.draw_line();
}
