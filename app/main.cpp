#include <iostream>
#include "../code/KDTree.h"

using namespace std;

int main(){
    vector<array<float, 2>> ghost_towns = {
        {38.7036419f,-106.3452481f},
        {38.9847154,-106.4408599},
        {39.1068016f,-106.6035702f},
        {37.932293f,-107.570046f},
        {39.7968022f,-105.5257985f},
        {38.959158f,-106.989767f}
    };
    vector<string> labels = {"St. Elmo", "Winfield", "Independence", "Animas Forks", "Nevadaville", "Gothic"};
    KDTree tree;
    for (int i=0; i<ghost_towns.size(); i++){
         kd_node* new_node = tree.init_node(ghost_towns[i], labels[i]);
         tree.insert(new_node, 0);
    }
    int choice;
    cout << "Welcome to Spooky KD Trees! Colorado is famous for its many popular ghost towns. https://www.uncovercolorado.com/ has compiled the best ghost towns in the state. Would you like to view the ghost towns in the list (type '1') or find the closest ghost towns to you? (type '2'): " << endl;
    cin >> choice;
    if (choice == 1){
        cout << "Here are the top 6 ghost towns in Colorado according to Uncover Colorado:" << endl;
        for (int i=0; i<ghost_towns.size(); i++){
            kd_node* town = tree.get_node(tree.get_root(), ghost_towns[i], 0);
            cout << town->label << ". Coordinates: " << town->coordinates[0] << ", " << town->coordinates[1] << endl;
        }
    }
    else if (choice == 2){
        float x;
        float y;
        cout << "Type in a coordinate to find the nearest ghost town to you. " << endl;
        cout << "Starting with x: " << endl;
        cin >> x;
        cout << "Now y: " << endl;
        cin >> y;
        array<float, 2> coords = {x, y};
        kd_node* result = tree.knn(tree.get_root(), coords, 0);
        kd_node* secondB = tree.secondBest(tree.get_root(), coords, 0);
        cout << "The closest ghost town to you is "<< result->label<<". The second best is "<<secondB->label<<". Happy haunting!" << endl;
    }
    else{
        cout << "Uh oh, something's been spooked! Please run the program again and enter the number 1 or 2 when prompted." << endl;
    }
    return 0;
}
