#include"code.h"
#include<unordered_map>

int main(){
    cout << "How many trials?";
    int y;
    cin>>y;

    while(y--){
        ifstream fs("input.txt");
        ifstream data("arduino.txt");
        Machine *building[count_lines("input.txt")];
        
        for (int i=0; i<count_lines("input.txt"); i++){  
        building[i] = new Machine(fs);}
   
        parse_arduino(data, building, "arduino.txt");

        cout<< "What do you want?" << endl;
        string input;
        int number;
        cin >> input;
        if (input=="simulate"){
            building[1]->run();}
        if (input=="schedule"){
            for (int h=0; h<count_lines("input.txt"); h++){
                cout << "* " << building[h]->return_type() << " " << building[h]->return_id() << endl;
            }
            cout<< "What is the ID of the laundry machine you'd like to check its availability?" << endl;
            cin >> number;
            building[number]->show_time();}
        }
        }
    
    
    
    
    
    




