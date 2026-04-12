#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <fstream>

enum class Direction{
    Haut, //y+1
    Bas, //y-1
    Gauche, //x-1
    Droite //x+1
};

struct Position{
    int x;
    int y;
};

namespace std {
    template <>
    struct hash<Position> {
        std::size_t operator()(const Position& pos) const {
            return std::hash<int>()(pos.x) ^ std::hash<int>()(pos.y);
        }
    };
}

struct WalkResult {
    Position final_position;
    size_t steps_taken;
    std::unordered_set<Position> visited_positions;
};

struct Input_Structure{
    Position initPosGarde;
    Direction initDirectionGarde;
    std::vector<Position> obstacle;
};

struct GuardState{
    Position initPosGarde;
    Direction initDirectionGarde;
    std::unordered_set<GuardState> etat_guard;
};

// namespace std {
//     template <>
//     struct hash<GuardState> {
//         std::size_t operator()(const GuardState& gua) const {
//             return std::hash<int>()(gua.initPosGarde.x) ^ std::hash<int>()(gua.initPosGarde.y);
//         }
//     };
// }

bool operator==(Position const& a, Position const& b) {
    return a.x == b.x && a.y == b.y;
}
bool operator==(GuardState const& a, GuardState const& b) {
    return a.etat_guard == b.etat_guard;
}

void operator<<(std::ostream& out, Position const& a) {
    out<<"x = "<<a.x<<"\n";
    out<<"y = "<<a.y<<"\n";
}

Position operator+=(Position a, Position b) {
    Position sommeAB;
    sommeAB.x = a.x += b.x;
    sommeAB.y = a.y += b.y;
    return sommeAB; 
}

Position operator+(Position const& a, Direction const& deplacement) {
    Position newA=a;
    switch (deplacement)
    {
    case Direction::Haut :
            newA.y=newA.y-1;
        break;
    case Direction::Bas :
            newA.y=newA.y+1;
        break;
    case Direction::Gauche :
            newA.x=newA.x-1;
        break;
    case Direction::Droite :
            newA.x=newA.x+1;
        break;
    default:
        break;
    }
    return newA;
}
void operator+=(Position& a, Direction const& deplacement) {
    a=a+deplacement;
}

Direction turn_right(Direction deplacement){
    switch(deplacement){
        case Direction::Haut : 
            deplacement = Direction::Droite;
            break;

        case Direction::Bas :
            deplacement = Direction::Gauche;
            break;

        case Direction::Gauche :
            deplacement = Direction::Haut;
            break;

        case Direction::Droite :
            deplacement = Direction::Bas;
            break;

        default:
            break;
    }
    return deplacement;
}

int maxLine{0};
int maxCol{0};
Input_Structure read_input(std::istream& fichier){
    Input_Structure Carte;
    int lineCounter{0};
    for (std::string line{}; std::getline(fichier, line, '\n') and line != "";) {
        maxCol=line.size()-1;
        for (size_t i = 0; i < line.size(); i++)
        {
            switch(line[i]){
                case '#':
                    Carte.obstacle.push_back({static_cast<int>(i),lineCounter});
                    break;

                case '<':
                    Carte.initPosGarde={static_cast<int>(i),lineCounter};
                    Carte.initDirectionGarde=Direction::Gauche;
                    break;

                case '>':
                    Carte.initPosGarde={static_cast<int>(i),lineCounter};
                    Carte.initDirectionGarde=Direction::Droite;
                    break;

                case '^':
                    Carte.initPosGarde={static_cast<int>(i),lineCounter};
                    Carte.initDirectionGarde=Direction::Haut;
                    break;

                case 'v':
                    Carte.initPosGarde={static_cast<int>(i),lineCounter};
                    Carte.initDirectionGarde=Direction::Bas;
                    break;

                default:
                    break;
            }
        }
        lineCounter++;
        maxLine=lineCounter-1;
    }
    return Carte;
};

// QUESTION 3
// 2.

WalkResult skibidi(Input_Structure Carte){
    WalkResult donneFinal;
    while(Carte.initPosGarde.x<maxLine and Carte.initPosGarde.x>0 and Carte.initPosGarde.y<maxCol and Carte.initPosGarde.y>0){
        if(std::find(Carte.obstacle.begin(),Carte.obstacle.end(),Carte.initPosGarde+Carte.initDirectionGarde)!=Carte.obstacle.end()){
            Carte.initDirectionGarde=turn_right(Carte.initDirectionGarde);
        }
        Carte.initPosGarde+=Carte.initDirectionGarde;
        donneFinal.steps_taken++;
        donneFinal.visited_positions.insert(Carte.initPosGarde);
    }
    donneFinal.final_position=Carte.initPosGarde;
    return donneFinal;
}


int main(){
    std::ifstream carte("../../src/carte.txt");
    Input_Structure CarteExemple=read_input(carte);
    WalkResult ResultatCarteExemple=skibidi(CarteExemple);
    std::cout<<ResultatCarteExemple.visited_positions.size()<<"\n";

    std::ifstream carte2("../../src/input_guard_patrol.txt");
    Input_Structure CarteExemple2=read_input(carte2);
    WalkResult ResultatCarteExemple2=skibidi(CarteExemple2);
    std::cout<<ResultatCarteExemple2.visited_positions.size()<<"\n";
    return 0;
}

