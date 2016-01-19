#ifndef RUBIK_H
#define RUBIK_H


#include <iostream>
#include <assert.h>
#include <array>
#include <cstdio>
#include <string>
#include <vector>
#include <typeinfo>

typedef std::array< std::array< std::array< char, 3>, 3>, 6> cube_type;

struct turn {
    turn(int a, bool b) : side(a), clockwise(b) {}
    int side;
    bool clockwise;
};

struct sequence {

    std::string to_str() {
        std::string str;
        for (int i = 0; i < seq.size(); i++) {
            std::string a;

            switch (seq[i].side) {
                case 0:
                    a = "F";
                    break;
                case 1:
                    a = "L";
                    break;
                case 2:
                    a = "U";
                    break;
                case 3:
                    a = "R";
                    break;
                case 4:
                    a = "D";
                    break;
                case 5:
                    a = "B";
                    break;
            }

            str.append(a).append(seq[i].clockwise ? "" : "p");
            if (i != seq.size() - 1) {
                str.append(",");
            }
        }
        return str;
    }

    turn operator[](const int nIndex) {
        return seq[nIndex];
    }


    void push_back (const turn& val){
        seq.push_back(val);
    };

    void pop_back () {
        seq.pop_back();
    }

    int size() {
        return seq.size();
    }

private:
    std::vector<turn> seq;

};


class Rubik {
    cube_type startcube = {{
                                   {{ {{'w','w','w'}},{{'w','w','w'}},{{'w','w','w'}} }},
                                   {{ {{'r','r','r'}},{{'r','r','r'}},{{'r','r','r'}} }},
                                   {{ {{'g','g','g'}},{{'g','g','g'}},{{'g','g','g'}} }},
                                   {{ {{'o','o','o'}},{{'o','o','o'}},{{'o','o','o'}} }},
                                   {{ {{'b','b','b'}},{{'b','b','b'}},{{'b','b','b'}} }},
                                   {{ {{'y','y','y'}},{{'y','y','y'}},{{'y','y','y'}} }}
                           }};
    cube_type cube = startcube;


public:
    void scramble() {
        for (int i = 0; i < 50; i++) {
            move(std::rand() % 6,std::rand() % 2 == 0);
        }
    };

    void move(int side, bool clockwise = true) {
        //{F, L, U, R, D, B} = {0, 1, 2, 3, 4, 5}
        //Up orientations from front perspective {F, L, U, R, D, B} = {Up, In, In, In, In, Up}

        assert(side >= 0 && side < 6);

        std::array< std::array< std::array< char, 3>, 3>, 6> original = cube;

        if (clockwise) {
            cube[side][0][0] = original[side][2][0];
            cube[side][0][1] = original[side][1][0];
            cube[side][0][2] = original[side][0][0];
            cube[side][1][0] = original[side][2][1];
            cube[side][1][2] = original[side][0][1];
            cube[side][2][0] = original[side][2][2];
            cube[side][2][1] = original[side][1][2];
            cube[side][2][2] = original[side][0][2];
        } else {
            cube[side][2][0] = original[side][0][0];
            cube[side][1][0] = original[side][0][1];
            cube[side][0][0] = original[side][0][2];
            cube[side][2][1] = original[side][1][0];
            cube[side][0][1] = original[side][1][2];
            cube[side][2][2] = original[side][2][0];
            cube[side][1][2] = original[side][2][1];
            cube[side][0][2] = original[side][2][2];
        }

        if (side == 0) {
            if (clockwise) {
                cube[1][2][0] = original[4][2][0];
                cube[1][2][1] = original[4][2][1];
                cube[1][2][2] = original[4][2][2];

                cube[2][2][0] = original[1][2][0];
                cube[2][2][1] = original[1][2][1];
                cube[2][2][2] = original[1][2][2];

                cube[3][2][0] = original[2][2][0];
                cube[3][2][1] = original[2][2][1];
                cube[3][2][2] = original[2][2][2];

                cube[4][2][0] = original[3][2][0];
                cube[4][2][1] = original[3][2][1];
                cube[4][2][2] = original[3][2][2];
            } else {
                cube[4][2][0] = original[1][2][0];
                cube[4][2][1] = original[1][2][1];
                cube[4][2][2] = original[1][2][2];

                cube[1][2][0] = original[2][2][0];
                cube[1][2][1] = original[2][2][1];
                cube[1][2][2] = original[2][2][2];

                cube[2][2][0] = original[3][2][0];
                cube[2][2][1] = original[3][2][1];
                cube[2][2][2] = original[3][2][2];

                cube[3][2][0] = original[4][2][0];
                cube[3][2][1] = original[4][2][1];
                cube[3][2][2] = original[4][2][2];
            }
        } else if (side == 1) {
            if (clockwise) {
                cube[2][0][0] = original[5][2][2];
                cube[2][1][0] = original[5][1][2];
                cube[2][2][0] = original[5][0][2];

                cube[0][0][0] = original[2][0][0];
                cube[0][1][0] = original[2][1][0];
                cube[0][2][0] = original[2][2][0];

                cube[4][2][2] = original[0][0][0];
                cube[4][1][2] = original[0][1][0];
                cube[4][0][2] = original[0][2][0];

                cube[5][2][2] = original[4][2][2];
                cube[5][1][2] = original[4][1][2];
                cube[5][0][2] = original[4][0][2];
            } else {
                cube[5][2][2] = original[2][0][0];
                cube[5][1][2] = original[2][1][0];
                cube[5][0][2] = original[2][2][0];

                cube[2][0][0] = original[0][0][0];
                cube[2][1][0] = original[0][1][0];
                cube[2][2][0] = original[0][2][0];

                cube[0][0][0] = original[4][2][2];
                cube[0][1][0] = original[4][1][2];
                cube[0][2][0] = original[4][0][2];

                cube[4][2][2] = original[5][2][2];
                cube[4][1][2] = original[5][1][2];
                cube[4][0][2] = original[5][0][2];
            }
        } else if (side == 2) {
            if (clockwise) {
                cube[0][0][0] = original[3][2][0];
                cube[0][0][1] = original[3][1][0];
                cube[0][0][2] = original[3][0][0];

                cube[1][0][2] = original[0][0][0];
                cube[1][1][2] = original[0][0][1];
                cube[1][2][2] = original[0][0][2];

                cube[5][0][0] = original[1][0][2];
                cube[5][0][1] = original[1][1][2];
                cube[5][0][2] = original[1][2][2];

                cube[3][2][0] = original[5][0][0];
                cube[3][1][0] = original[5][0][1];
                cube[3][0][0] = original[5][0][2];
            } else {
                cube[3][2][0] = original[0][0][0];
                cube[3][1][0] = original[0][0][1];
                cube[3][0][0] = original[0][0][2];

                cube[0][0][0] = original[1][0][2];
                cube[0][0][1] = original[1][1][2];
                cube[0][0][2] = original[1][2][2];

                cube[1][0][2] = original[5][0][0];
                cube[1][1][2] = original[5][0][1];
                cube[1][2][2] = original[5][0][2];

                cube[5][0][0] = original[3][2][0];
                cube[5][0][1] = original[3][1][0];
                cube[5][0][2] = original[3][0][0];
            }
        } else if (side == 3) {
            if (clockwise) {
                cube[0][0][2] = original[4][2][0];
                cube[0][1][2] = original[4][1][0];
                cube[0][2][2] = original[4][0][0];

                cube[2][0][2] = original[0][0][2];
                cube[2][1][2] = original[0][1][2];
                cube[2][2][2] = original[0][2][2];

                cube[5][2][0] = original[2][0][2];
                cube[5][1][0] = original[2][1][2];
                cube[5][0][0] = original[2][2][2];

                cube[4][2][0] = original[5][2][0];
                cube[4][1][0] = original[5][1][0];
                cube[4][0][0] = original[5][0][0];
            } else {
                cube[4][2][0] = original[0][0][2];
                cube[4][1][0] = original[0][1][2];
                cube[4][0][0] = original[0][2][2];

                cube[0][0][2] = original[2][0][2];
                cube[0][1][2] = original[2][1][2];
                cube[0][2][2] = original[2][2][2];

                cube[2][0][2] = original[5][2][0];
                cube[2][1][2] = original[5][1][0];
                cube[2][2][2] = original[5][0][0];

                cube[5][2][0] = original[4][2][0];
                cube[5][1][0] = original[4][1][0];
                cube[5][0][0] = original[4][0][0];
            }
        } else if (side == 4) {
            if (clockwise) {
                cube[0][2][0] = original[1][0][0];
                cube[0][2][1] = original[1][1][0];
                cube[0][2][2] = original[1][2][0];

                cube[1][0][0] = original[5][2][0];
                cube[1][1][0] = original[5][2][1];
                cube[1][2][0] = original[5][2][2];

                cube[5][2][0] = original[3][2][2];
                cube[5][2][1] = original[3][1][2];
                cube[5][2][2] = original[3][0][2];

                cube[3][2][2] = original[0][2][0];
                cube[3][1][2] = original[0][2][1];
                cube[3][0][2] = original[0][2][2];
            } else {
                cube[1][0][0] = original[0][2][0];
                cube[1][1][0] = original[0][2][1];
                cube[1][2][0] = original[0][2][2];

                cube[5][2][0] = original[1][0][0];
                cube[5][2][1] = original[1][1][0];
                cube[5][2][2] = original[1][2][0];

                cube[3][2][2] = original[5][2][0];
                cube[3][1][2] = original[5][2][1];
                cube[3][0][2] = original[5][2][2];

                cube[0][2][0] = original[3][2][2];
                cube[0][2][1] = original[3][1][2];
                cube[0][2][2] = original[3][0][2];
            }
        } else if (side == 5) {
            if (clockwise) {
                cube[1][0][0] = original[2][0][0];
                cube[1][0][1] = original[2][0][1];
                cube[1][0][2] = original[2][0][2];

                cube[2][0][0] = original[3][0][0];
                cube[2][0][1] = original[3][0][1];
                cube[2][0][2] = original[3][0][2];

                cube[3][0][0] = original[4][0][0];
                cube[3][0][1] = original[4][0][1];
                cube[3][0][2] = original[4][0][2];

                cube[4][0][0] = original[1][0][0];
                cube[4][0][1] = original[1][0][1];
                cube[4][0][2] = original[1][0][2];
            } else {
                cube[2][0][0] = original[1][0][0];
                cube[2][0][1] = original[1][0][1];
                cube[2][0][2] = original[1][0][2];

                cube[3][0][0] = original[2][0][0];
                cube[3][0][1] = original[2][0][1];
                cube[3][0][2] = original[2][0][2];

                cube[4][0][0] = original[3][0][0];
                cube[4][0][1] = original[3][0][1];
                cube[4][0][2] = original[3][0][2];

                cube[1][0][0] = original[4][0][0];
                cube[1][0][1] = original[4][0][1];
                cube[1][0][2] = original[4][0][2];
            }
        }
    };

    void print() {
        printf("            *-----------*            \n");
        printf("            | %c | %c | %c |            \n",
                            cube[2][0][0], cube[2][0][1], cube[2][0][2]);
        printf("            *-----------*            \n");
        printf("            | %c | %c | %c |            \n",
                            cube[2][1][0], cube[2][1][1], cube[2][1][2]);
        printf("            *-----------*            \n");
        printf("            | %c | %c | %c |            \n",
                            cube[2][2][0], cube[2][2][1], cube[2][2][2]);
        printf("*-----------*-----------*-----------*-----------*\n");
        printf("| %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |\n",
                            cube[1][0][2], cube[1][1][2], cube[1][2][2],
                            cube[0][0][0], cube[0][0][1], cube[0][0][2],
                            cube[3][2][0], cube[3][1][0], cube[3][0][0],
                            cube[5][0][0], cube[5][0][1], cube[5][0][2]);
        printf("*-----------*-----------*-----------*-----------*\n");
        printf("| %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |\n",
                            cube[1][0][1], cube[1][1][1], cube[1][2][1],
                            cube[0][1][0], cube[0][1][1], cube[0][1][2],
                            cube[3][2][1], cube[3][1][1], cube[3][0][1],
                            cube[5][1][0], cube[5][1][1], cube[5][1][2]);
        printf("*-----------*-----------*-----------*-----------*\n");
        printf("| %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |\n",
                            cube[1][0][0], cube[1][1][0], cube[1][2][0],
                            cube[0][2][0], cube[0][2][1], cube[0][2][2],
                            cube[3][2][2], cube[3][1][2], cube[3][0][2],
                            cube[5][2][0], cube[5][2][1], cube[5][2][2]);
        printf("*-----------*-----------*-----------*-----------*\n");
        printf("            | %c | %c | %c |            \n",
                            cube[4][2][2], cube[4][2][1], cube[4][2][0]);
        printf("            *-----------*            \n");
        printf("            | %c | %c | %c |            \n",
                            cube[4][1][2], cube[4][1][1], cube[4][1][0]);
        printf("            *-----------*           \n");
        printf("            | %c | %c | %c |            \n",
                            cube[4][0][2], cube[4][0][1], cube[4][0][0]);
        printf("            *-----------*            \n");
    }

    bool solved() {
        if (cube == startcube ) {
            return true;
        } else {
            return false;
        }
    }

    int run_sequence(sequence &s){
        int num_turns = 0;
        do {
            for (int i = 0; i < s.size(); i++) {
                move(s[i].side,s[i].clockwise);
                num_turns++;
            }
        } while (!solved());

        return num_turns;
    };
};

#endif