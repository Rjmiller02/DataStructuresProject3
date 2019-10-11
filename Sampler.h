//
// Created by rj on 4/24/19.
//

#ifndef PROJECT4_SAMPLER_H
#define PROJECT4_SAMPLER_H


class Sampler {

  public:
        Sampler(int n){
             size = n;
             items = new int [size];

            for(int i=0; i<n; i++){
                items[i] = i;
            }
        }

        ~Sampler(){delete[](items);}

        int getSample(){
            std::srand(time(NULL));

            int i = rand() % size;
            int e = items[i];
            size--;
            items[i] = items[size];


            return e;
        }

private:
        int size;
        int* items;



};


#endif //PROJECT4_SAMPLER_H
