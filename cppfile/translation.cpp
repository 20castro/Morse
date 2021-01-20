#include "translation.h"

const char letterCast (const char& c){
    if (64 < c < 91){ return c + 32; }
    else{ return c; }
}

std::map <char, int> buildMap (){
    std::map <char, int> dict;
    dict [32] = 0;
    for (char c = 97; c < 123; c++){ dict[c] = 1; }
    for (char c = 48; c < 57; c++){ dict [c] = 1; }
    {
        std::string tiFifth ("98765");
        for (auto it = tiFifth.begin (); it != tiFifth.end (); ++it){ dict[*it] <<= 1; }
        std::string taFifth ("01234");
        for (auto it = taFifth.begin (); it != taFifth.end (); ++it){ dict[*it] <<= 1; dict[*it] += 1; }
    }
    {
        std::string tiFourth ("8z7cb6plfh45");
        for (auto it = tiFourth.begin (); it != tiFourth.end (); ++it){ dict[*it] <<= 1; }
        std::string taFourth ("09qyxj12v3");
        for (auto it = taFourth.begin (); it != taFourth.end (); ++it){ dict[*it] <<= 1; dict[*it] += 1; }
    }
    {
        std::string tiThird ("gqz7dxb6rlsvh345");
        for (auto it = tiThird.begin (); it != tiThird.end (); ++it){ dict[*it] <<= 1; }
        std::string taThird ("o098kycwjp1uf2");
        for (auto it = taThird.begin (); it != taThird.end (); ++it){ dict[*it] <<= 1; dict[*it] += 1; }
    }
    {
        std::string tiSecond ("nkdycxb6iusfvh2345");
        for (auto it = tiSecond.begin (); it != tiSecond.end (); ++it){ dict[*it] <<= 1; }
        std::string taSecond ("mogqz0987awrjpl1");
        for (auto it = taSecond.begin (); it != taSecond.end (); ++it){ dict[*it] <<= 1; dict[*it] += 1; }
    }
    {
        std::string tiFirst  ("eaiwrusjplfvh12345");
        for (auto it = tiFirst.begin (); it != tiFirst.end (); ++it){ dict[*it] <<= 1; }
        std::string taFirst ("tmnogkdqzycxb06789");
        for (auto it = taFirst.begin (); it != taFirst.end (); ++it){ dict[*it] <<= 1; dict[*it] += 1; }
    }
    return dict;
}

Tree* buildTree (){
    Tree null (0);
    Tree c0 ('0');
    Tree c1 ('1');
    Tree c2 ('2');
    Tree c3 ('3');
    Tree c4 ('4');
    Tree c5 ('5');
    Tree c6 ('6');
    Tree c7 ('7');
    Tree c8 ('8');
    Tree c9 ('9');
    Tree h (&c5, &c4, 'h');
    Tree v (&null, &c3, 'v');
    Tree f ('f');
    Tree n1 (&null, &c2, 0);
    Tree l ('l');
    Tree p ('p');
    Tree j (&null, &c1, 'j');
    Tree b (&c6, &null, 'b');
    Tree x ('x');
    Tree c ('c');
    Tree y ('y');
    Tree z (&c7, &null, 'z');
    Tree q ('q');
    Tree n2 (&c8, &null, 0);
    Tree n3 (&c9, &c0, 0);
    Tree s (&h, &v, 's');
    Tree u (&f, &n1, 'u');
    Tree r (&l, &null, 'r');
    Tree w (&p, &j, 'w');
    Tree d (&b, &x, 'd');
    Tree k (&c, &y, 'k');
    Tree g (&z, &q, 'g');
    Tree o (&n2, &n3, 'o');
    Tree i (&s, &u, 'i');
    Tree a (&r, &w, 'a');
    Tree n (&d, &k, 'n');
    Tree m (&g, &o, 'm');
    Tree e (&i, &a, 'e');
    Tree t (&n, &m, 't');
    return &Tree (&e, &t, 0);
}