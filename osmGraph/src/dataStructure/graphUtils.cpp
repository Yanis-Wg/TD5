#include "graphUtils.hpp"
#include "weightedGraph.hpp"

#include <vector>
#include <unordered_map>
#include <functional>
#include <queue>
#include <set>
#include <stack>
#include <algorithm>

using DataStructure::WeightedGraph;
using DataStructure::IDType;

void DFS(WeightedGraph const& graph, IDType const start, std::function<void(IDType const)> const& callback, std::function<bool(IDType const)> const& should_explore_neighbors) {
    std::set<IDType> visited {};
    std::stack<IDType> to_visit {};
    to_visit.push(start);
    // tant que la pile des nodes à visiter n'est pas vide alors
    while (!to_visit.empty()) {
        // on créer une constante de type auto qui est le derniere élément de la pile "à visiter"
        auto const current { to_visit.top() };
        // on supprime cet élément de la pile
        to_visit.pop();
        // si la pile "visité" contient déjà l'élément on passe à l'itération suivante de la boucle while
        if (visited.contains(current)) {
            continue;
        }
        // sinon on insère dans la pile "visité" l'élément current
        visited.insert(current);
        callback(current);

        if (should_explore_neighbors(current)) {
            for (auto const& edge : graph.get_neighbors(current)) {
                to_visit.push(edge.to);
            }
        }
    }
}

void print_DFS(WeightedGraph const& graph, IDType const start) {
    /* TODO */
}


template<class T>
using min_priority_queue = std::priority_queue<T, std::vector<T>, std::greater<T>>;

// map of node id to pair of cost and parent node id (for path reconstruction)
std::unordered_map<IDType, std::pair<float, IDType>> Dijkstra(WeightedGraph const& graph, IDType const start, IDType const end) {
    // Création d'un tableau à trois entrées "IDType", "Pair" et "IDType"
    std::unordered_map<IDType, std::pair<float, IDType>> distances {};
    // priority queue of pair of current cost from starting node and current node id
    // this will sort node base on the cost (as pair are ordered with lexicographical order)
    min_priority_queue<std::pair<float, IDType>> to_visit {};
    // On commence par ajouter le sommet de départ dans la file des sommets à visiter.
    to_visit.push({0.0f, start});

    /* TODO */
    while(!to_visit.empty()){
        auto const current { to_visit.top() };
        if(current.second==end){
            break;
        }
        
        // on supprime cet élément de la pile
        to_visit.pop();

        // voisins de current
        auto const& neighbors = graph.get_neighbors(current.second);

        // ajout des voisins à la piles "à visiter" et au tableau associatif distance
        for(size_t i{0};i<neighbors.size();i++){
            // permet de calculer le poids du voisin/sa distance en fonction de current
            float newDistance=current.first+neighbors[i].weight;

            // si le voisin est déjà dans le tableau distance alors
            if(distances.contains(neighbors[i].to)) {
                // si sa distance est supérieur à celle existante on saute le tour de boucle
                if (distances[neighbors[i].to].first<newDistance)
                {
                    continue;
                } 
                // sinon
                // on ajoute à la pile "à visiter" la nouvelle distance et l'id du voisins pour reformer la "paire"
                to_visit.push({newDistance,neighbors[i].to});
                distances[neighbors[i].to] = {newDistance, current.second};
            }
            else{
                to_visit.push({newDistance,neighbors[i].to});
                distances[neighbors[i].to] = {newDistance, current.second};
            }
        }
    }
    return distances;
}

std::vector<IDType> reconstruct_path(std::unordered_map<IDType, std::pair<float, IDType>> const& distances, IDType const start, IDType const end) {
    std::vector<IDType> path { };
    IDType current_node { end };
    while (current_node != start) {
        path.push_back(current_node);

        auto const find_current_node { distances.find(current_node) };
        if(find_current_node == distances.end()) {
            // if we reach a node that is not in the distances map, it means that there is no path from start to end
            return {};
        }
        else {
            // we update the current node to its parent node
            current_node = find_current_node->second.second;
        }
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());
    return path;
}

std::vector<IDType> dijkstra_path(WeightedGraph const& graph, IDType const start, IDType const end) {
    return reconstruct_path(Dijkstra(graph, start, end), start, end);
}