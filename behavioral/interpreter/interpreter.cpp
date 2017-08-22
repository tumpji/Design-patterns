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

// example of interpreter implementation 

#include <iostream>
#include <memory>
#include <string>
#include <map>


class Context {
public:
    // copy
    Context () = default;
    Context ( const Context& ) = default;

    void addVar ( std::string name, bool value ) {
        map[name] = value;
    }

    bool getVar ( std::string name ) {
        return map[name];
    }

private:
    std::map< std::string, bool > map;
};







class Exp {
    public:
        Exp () { }
        virtual ~Exp () {}

        using ExpPtr = std::shared_ptr<Exp>;

        using InterRet = bool;
        virtual InterRet Interpret (Context) = 0;

};

class UnaryExp : public Exp {
    public:
        UnaryExp ( ExpPtr a ) : Exp(), a(a) { }
        ExpPtr a;
};

class BinaryExp : public Exp {
    public:
        BinaryExp ( ExpPtr a, ExpPtr b ) :
            Exp(), a(a), b(b) 
        {}
        ExpPtr a;
        ExpPtr b;
};

class OrExp: public BinaryExp {
    public:
        OrExp ( ExpPtr a, ExpPtr b ) :
            BinaryExp(a,b) {}

        virtual InterRet Interpret (Context context) {
            return a->Interpret(context) or b->Interpret(context);
        }
};

class AndExp : public BinaryExp {
    public:
        AndExp ( ExpPtr a, ExpPtr b ) : 
            BinaryExp(a,b) {}

        virtual bool Interpret (Context context) {
            return a->Interpret(context) and b->Interpret(context);
        }
};

class NotExp : public UnaryExp {
    public:
        NotExp( ExpPtr a ) : UnaryExp(a) {}

        virtual bool Interpret (Context context) {
            return not a->Interpret(context);
        }
};

class Variable : public Exp {
    public:
        Variable ( std::string name ) : Exp(), name(name) { }

        virtual bool Interpret (Context context) {
            return context.getVar(name);
        }
    private:
        std::string name;
};

//////////////////////////// demo //////////////////

int main () {


    Exp::ExpPtr exp [7] = { 
        std::make_shared<Variable>("a"),
        std::make_shared<Variable>("b"),
        std::make_shared<Variable>("c"),
        std::make_shared<NotExp>( exp[0] ),
        std::make_shared<AndExp>( exp[0], exp[1] ),
        std::make_shared<AndExp>( exp[2], exp[3] ),
        std::make_shared<OrExp> ( exp[4], exp[5] )
    };

    // exp[6] = (a and b) or ( c and not a )




    for ( unsigned a = 0; a < 2 ; ++a )
    for ( unsigned b = 0; b < 2 ; ++b )
    for ( unsigned c = 0; c < 2 ; ++c )
    {
        Context o;
        o.addVar("a", a % 2 );
        o.addVar("b", b % 2 );
        o.addVar("c", c % 2 );
    
        std::cout << a << " " << b << " " << c << " : " << exp[6]->Interpret(o) << std::endl;
    }

    return 0;
}
