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

// example of facade implementation 

#include <iostream>


namespace Internal {
    class A {
        public: 
            void Operation (int a) {(void)a;}
    };
    
    class B {
        public:
            void Operation1 ( A& src ) { (void)src; }
            void Operation2 () {};
    };

}

class Facade {
    public:
        static void Operation1 () {
            Internal::A g;
            g.Operation(1);
            g.Operation(2);
        }

        static void Operation2 () {
            // abstraction 
            Internal::A a;
            Internal::B b;
            b.Operation1( a );
            b.Operation2();
            a.Operation(10);
        }
};
