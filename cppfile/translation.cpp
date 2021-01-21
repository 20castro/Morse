#include "../include/translation.h"

const char letterCast (const char& c){
    if (64 < c and c < 91){ return c + 32; }
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

const char* buildTree (){
    return "!etianmsurwdkgohvf!l!pjbxcyzq!!54!3!!!2!!!!!!!16!!!!!!!7!!!8!90";
}