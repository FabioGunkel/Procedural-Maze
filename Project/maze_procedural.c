#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <time.h>
using namespace std;


typedef struct sala sala;
//estrutura mapa, tem o grid, as salas e os corredores
typedef struct mapa{
  vector <vector <struct grid> > map;
  vector <struct sala> salas;
  vector <int> conectadas;
  vector <struct corredor> corredores;  
}mapa;


//estrutura grid, é uma célula da matriz que é o mapa.
typedef struct grid{

char espaco;
 

}grid;



 struct sala{
    
    
    int x1, x2, y1, y2;
    bool conectada;
    
    
};
//estrutura corredor, é a ligação entre duas salas.
typedef struct corredor{
    
    sala sala1;
    sala sala2;
    
}corredor;




void printa(mapa grid, int gridtam ){
int i,j;
for(i=0;i<gridtam;i++){
        for(j=0;j<gridtam;j++){
            if (grid.map[i][j].espaco =='X'){
            cout << "X" << " ";    
            }
            else{
            cout << grid.map[i][j].espaco<< " ";
            }
        }
        cout <<endl;
    
    }

}
bool liga(mapa &map, int saidax,int saiday,int chegadax,int chegaday, int lado);
bool gera_portas(mapa &map, int corredor, int irmao);
corredor gera_corredor(mapa &map, int corredor);

sala gera_sala(mapa &map, int h, int w, int tmin, int tmax){
    
    int x, y, x1, y1, i, j;
    bool falhou;
    falhou = false;
    sala salada;

    if (tmax == 0){
       x = 1; 
       y = 1;    
    }
    else{
    x = rand() % tmax + tmin +1;
    y = rand() % tmax + tmin +1;
    }
    x1 = rand() % (h-3 - x) +2;
    y1 = rand() % (w-3 - y) +2;
    
    for(i=0; i<map.salas.size();i++){
        if((map.salas[i].x1 <= x1 && map.salas[i].x2 >= x1 )|| (map.salas[i].x1>= x1 && map.salas[i].x1 <= (x1+x)) ){
            if((map.salas[i].y1 <= y1 && map.salas[i].y2 >= y1 )|| (map.salas[i].y1>= y1 && map.salas[i].y1 <= (y1+y)) ){
                falhou = true;
            }
        }
    }
    
    

    if(!falhou){
        salada.x1=x1;
        salada.x2=x1+x;
        salada.y1=y1;
        salada.y2=y1+y;
        salada.conectada = false;
      map.salas.push_back(salada);
      for(i=0;i<x;i++){
          for(j=0;j<y;j++){
             map.map[(i+x1)][(j+y1)].espaco = ' '; 
          }
      }
      return salada;
    }
    else{
        return gera_sala(map, h, w, tmin, tmax);
    }
    
    
    
}
//gera mapa, parâmetros são: número de salas, o próprio mapa, a largura e a altura do mapa.
void gera( int salas, mapa &map, int h, int w){
    int i, j;
   for(i=0;i<h;i++) 
        for(j=0;j<w;j++){
            map.map[i][j].espaco = 'X';
        }

    for(i=0;i<salas;i++){
    
      map.salas.push_back(gera_sala(map,h,w,3, 30));
      //map.salas.push_back(gera_sala(map,h,w,1, 0));
    }
    map.salas[0].conectada = true;
    map.conectadas.push_back(0);
    
    for(i=1;i<map.salas.size();i++){
     map.corredores.push_back(gera_corredor(map, i));
    }
    
    
    
}

void copy_sala(sala &sala1, sala sala2){
    
    sala1.x1 = sala2.x1;
    sala1.x2 = sala2.x2;
    sala1.y1 = sala2.y1;
    sala1.y2 = sala2.y2;
    sala1.conectada = sala2.conectada;
}
corredor gera_corredor(mapa &map, int corredor){
    struct corredor cor;
    struct sala sal;
    int irmao;
    bool cond;
    bool cond2;
    cond = false;
    
  //  if(map.salas[corredor].conectada==false){
        while(!cond){
            
            irmao = rand() % map.conectadas.size();
            
            irmao = map.conectadas[irmao];
            //cout<<"Tentativa com:"<< irmao <<endl;
        
        if(map.salas[irmao].conectada){
          //cond2 =  gera_portas(map, corredor, irmao);
          cond2 = true;
          if (cond2){
              map.conectadas.push_back(corredor);
              map.salas[corredor].conectada = true;
              copy_sala(cor.sala1, map.salas[corredor]);
              copy_sala(cor.sala2, map.salas[irmao]);
            //cout<<"conectou";
            return cor;
          }
        }
        
        }
  //  }
  return cor;
}

bool gera_portas(mapa &map, int corredor, int irmao){
    int i, j, saidax, saiday, chegadax, chegaday, lado;
    struct corredor ctemp;
 //   if(map.salas[corredor].x1 < map.salas[irmao].x1){
   //     if(map.salas[corredor].y1 < map.salas[irmao].y1){
            lado = rand() % 2;
            if(lado==1){
            saidax = rand() % (map.salas[corredor].x2 - map.salas[corredor].x1) + map.salas[corredor].x1 +1;
            //se a sala destino estiver a cima
            if(map.salas[corredor].y1>map.salas[irmao].y1){
                saiday = map.salas[corredor].y1;
            }
            //caso o contrário
            else{
                saiday = map.salas[corredor].y2;
            }
            chegadax = map.salas[irmao].x1;
            chegaday = rand() % (map.salas[corredor].y2 - map.salas[corredor].y1) + map.salas[corredor].y1 +1;
            
            } else{
                
            saiday = rand() % (map.salas[corredor].y2 - map.salas[corredor].y1) + map.salas[corredor].y1 +1;
            saidax = map.salas[corredor].x2;
            chegadax = rand() % (map.salas[corredor].x2 - map.salas[corredor].x1) + map.salas[corredor].x1 +1;
            chegaday = map.salas[irmao].y1;
            
            }
          if(liga(map, saidax,saiday,chegadax,chegaday,lado)){
                map.salas[corredor].conectada = true;
                map.conectadas.push_back(corredor);
                return true;
            }
            else{
                return false;
            }  
            
   //     }
  //  }
}

bool liga(mapa &map, int saidax,int saiday,int chegadax,int chegaday, int lado){
    int tempx, tempy, i;
    if(saiday > chegaday){
        tempy = chegaday;
        chegaday = saiday;
        saiday = tempx;
    }
    if(saidax > chegadax){
        tempx = chegadax;
        chegadax = saidax;
        saidax = tempx;
    }
    switch (lado){
        
    //caso saia verticalmente
    case 0:
           /*
           for(i=(saiday+1);i<=chegaday;i++){
               if( map.map[saidax][i].espaco == ' '){
                   return false;
                  ;
               }
            }
            for(i=(saidax+1);i<chegadax;i++){
                if(map.map[i][chegaday].espaco == ' ')
                    return false;
                  
            }
            */
            for(i=saiday;i<=chegaday;i++){
                map.map[saidax][i].espaco = ' ';
            }
            for(i=(saidax+1);i<chegadax;i++){
                map.map[i][chegaday].espaco = ' ';
            }
            
            return true;
    break;
    
    //caso saia horizontalmente
    case 1:
            /*
            for(i=(saidax+1);i<=chegadax;i++){
               if( map.map[i][saiday].espaco == ' '){
                   return false;
               }
            }
            for(i=(saiday+1);i<chegaday;i++){
                if(map.map[chegadax][i].espaco == ' ')
                    return false;
            }
            */
            for(i=(saidax+1);i<=chegadax;i++){
                map.map[i][saiday].espaco = ' ';
            }
            for(i=(saiday+1);i<chegaday;i++){
                map.map[chegadax][i].espaco = ' ';
            }
            
            return true;
    break;
    
    }
   
    
}
int main(){
    //cria variáveis para loop e o tamanho do grid
    int i, j, gridtam;
    //seta o tamanho do grid
    gridtam = 100;
    //cria um grid temporário para ser usado na alocação de um vetor de grids
    grid temp;
    //seta o espaço ' ' como default para todos os grids.
    temp.espaco = ' ';
    //cria um mapa.
    mapa map;
    
    vector <grid> vtemp(gridtam);
    vector <vector <grid> > mapa(gridtam);
        int random; 
    time_t seconds; 
    time(&seconds); 

    srand((unsigned int) seconds); 
    
    
    for (i = 0;i<gridtam;i++){
        vtemp[i]=temp;
    
    }
    for (i=0;i<gridtam;i++)
        map.map.push_back(vtemp);
    
    gera(10, map, gridtam, gridtam);
    
    
    printa(map, gridtam);
    
return 0;
}