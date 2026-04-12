#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>

// exercice 1 - 1
size_t folding_string_hash(std::string const& s, size_t max){
    size_t hash(0);
    for (size_t i {0}; i<s.size(); i++)
    {
        // hash+=s[i];
        // hash%=max;
        // je fais les sommes asci en faisant le module de la somme à chaque tour pour éviter que ca sorte de la boucle
        hash=(hash+s[i])%max;
    }    
    return hash;
}

// exercice 1 - 2
size_t folding_string_ordered_hash(std::string const& s, size_t max){
    size_t hash(0);
    for (size_t i {0}; i<s.size(); i++)
    {
        hash=(hash+s[i]*(i+1))%max;
    }
}

int main(){
    std::string str{0};
    std::cout <<"Entre une string : ";
    std::cin>>str;
    folding_string_hash(str,30);
    folding_string_ordered_hash(str,30);
    return 0;
}

