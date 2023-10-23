// Type your code here, or load an example.
#include <iostream>
#include<vector>

enum class Etat {
	libre,robot,arbre,obstacle
};

std::ostream& operator<<(std::ostream& s, Etat& e){
    switch(e){
        case Etat::libre:
            s<<"libre";
            break;
        case Etat::robot:
            s<<"robot";
            break;
        case Etat::arbre:
            s<<"arbre";
            break;
        case Etat::obstacle:
            s<<" mur ";
            break;
    };
    return s;
}
























class Environment {
    public:
        int size_x;
        int size_y;
	    std::vector<std::vector<Etat>> map_etat;

        Environment(int size_x,int size_y){
            this->size_x=size_x;
            this->size_y=size_y;

            for (int y=0;y<size_y;y++){
                this->map_etat.push_back({});
                for(int x=0;x<size_x;x++){
                    this->map_etat[y].push_back(Etat::libre);
                }
            }
        }
};

std::ostream& operator<<(std::ostream& s,Environment& map){
    for (int y=0; y<map.size_y; y++){
        for(int x=0; x<map.size_x; x++){
            s<<map.map_etat[y][x] << " | ";
            
        }
        s<<std::endl;
    };
    return s;
}























class Robot {
    public:
        int id;
        int pos_x;
        int pos_y;
        Robot(int id,Environment& map,int pos_x,int pos_y){
            this->id=id;
            this->pos_x=pos_x;
            this->pos_y=pos_y;
            map.map_etat[pos_y][pos_x]=Etat::robot;
        }
        
        int get_id(){
            return this->id;
        }
        int get_pos_x(){
            return this->pos_x;
        }
        int get_pos_y(){
            return this->pos_y;
        }





        void planter(Environment& map){
            //par défaut après avoir planter le robot se décale sur la droite
            if(this->pos_x<=map.size_x-2 and map.map_etat[this->pos_y][this->pos_x+1]==Etat::libre){
                map.map_etat[this->pos_y][this->pos_x]=Etat::arbre;
                map.map_etat[this->pos_y][this->pos_x+1]=Etat::robot;
                this->pos_x=this->pos_x+1;
            }
            //si ce c'est pas possible, il monte
            else if(this->pos_y>=1 and map.map_etat[this->pos_y-1][this->pos_x]==Etat::libre){
                map.map_etat[this->pos_y][this->pos_x]=Etat::arbre;
                map.map_etat[this->pos_y-1][this->pos_x]=Etat::robot;
                this->pos_y=this->pos_y-1;
            }
            //si ce n'est pas possible, il va vers la gauche
            else if (this->pos_x>=1 and map.map_etat[this->pos_y][this->pos_x-1]==Etat::libre){
                map.map_etat[this->pos_y][this->pos_x]=Etat::arbre;
                map.map_etat[this->pos_y][this->pos_x-1]=Etat::robot;
                this->pos_x=this->pos_x-1;
            }
            //si ce n'est pas possible, il descent
            else if(this->pos_y<=map.size_y-2 and map.map_etat[this->pos_y+1][this->pos_x]==Etat::libre){
                map.map_etat[this->pos_y][this->pos_x]=Etat::arbre;
                map.map_etat[this->pos_y+1][this->pos_x]=Etat::robot;
                this->pos_y=this->pos_y+1;
            }
            //si aucun de ces mouvement n'est possible alors le robot ne peut pas planter
            else{
                std::cout<<"impossible de planter ici"<<std::endl;
            }

        }







        void deplacer(Environment& map, int dir){
            if(dir==0){
                //déplacement vers le haut 
                if(this->pos_y>=1 and map.map_etat[this->pos_y-1][this->pos_x]==Etat::libre){
                    map.map_etat[this->pos_y-1][this->pos_x]=Etat::robot;
                    map.map_etat[this->pos_y][this->pos_x]=Etat::libre;
                    this->pos_y=this->pos_y-1;
                }
                else{
                    std::cout <<"déplacement impossible" <<std::endl;
                }
            }
            else if(dir==1){
                //déplacement vers la droite
                if(this->pos_x<=map.size_x-2 and map.map_etat[this->pos_y][this->pos_x+1]==Etat::libre){
                    map.map_etat[this->pos_y][this->pos_x+1]=Etat::robot;
                    map.map_etat[this->pos_y][this->pos_x]=Etat::libre;
                    this->pos_x=this->pos_x+1;
                }
                else{
                    std::cout <<"déplacement impossible" <<std::endl;
                }
            }
            else if(dir==2){
                //déplacement vers le bas
                if(this->pos_y<=map.size_y-2 and map.map_etat[this->pos_y+1][this->pos_x]==Etat::libre){
                    map.map_etat[this->pos_y+1][this->pos_x]=Etat::robot;
                    map.map_etat[this->pos_y][this->pos_x]=Etat::libre;
                    this->pos_y=this->pos_y+1;
                }
                else{
                    std::cout <<"déplacement impossible" <<std::endl;
                }
            }
            else if(dir==3){
                //déplacement vers la gauche
                if(this->pos_x>=1 and map.map_etat[this->pos_y][this->pos_x-1]==Etat::libre){
                    map.map_etat[this->pos_y][this->pos_x-1]=Etat::robot;
                    map.map_etat[this->pos_y][this->pos_x]=Etat::libre;
                    this->pos_x=this->pos_x-1;
                }
                else{
                    std::cout <<"déplacement impossible" <<std::endl;
                }
            }
            else{
                std::cout <<"déplacement non reconnu"<< std::endl;
            }

        }

};





























int main(int argc, char**argv){
    int n=5;
    Environment* map = new Environment(n,n);
    Robot* robot1 = new Robot(1,*map,0,0);
    std::cout << *map << std::endl;   
    for(int i=0;i<(n*n)-1;i++){
        robot1->planter(*map);
    }
    std::cout << *map << std::endl;

}
