#include <iostream>
#include <stdlib.h>
#include <string>

struct pozitie
{
    int x,y;
};
class Piesa
{
    private:
        std::string Culoare;
        std::string Tip;
        pozitie P;
    public:
        Piesa(std::string new_culoare,std::string new_tip,pozitie new_p)
        :Culoare(new_culoare),Tip(new_tip),P(new_p){}
        std::string getpiesa()
        {
            return Tip;
        }
        std::string getculoare()
        {
            return Culoare;
        }
        pozitie getpoz()
        {
            return P;
        }
        void setPoz(int newPx,int newPy)
        {
            P.x=newPx;
            P.y=newPy;
        }
};

class tablasah
{
    public:
        void asezpiese(Piesa *mat[8][8])
        {
            mat[0][0]=new Piesa("N","T",{1,1});
            mat[0][1]=new Piesa("N","C",{1,2});
            mat[0][2]=new Piesa("N","N",{1,3});
            mat[0][3]=new Piesa("N","K",{1,4});
            mat[0][4]=new Piesa("N","Q",{1,5});
            mat[0][5]=new Piesa("N","N",{1,6});
            mat[0][6]=new Piesa("N","C",{1,7});
            mat[0][7]=new Piesa("N","T",{1,8});

            for(int i=0;i<8;i++){
                mat[1][i]=new Piesa("N","P",{2,i+1});
                mat[6][i]=new Piesa("A","P",{7,i+1});
            }
            mat[7][0]=new Piesa("A","T",{8,1});
            mat[7][1]=new Piesa("A","C",{8,2});
            mat[7][2]=new Piesa("A","N",{8,3});
            mat[7][3]=new Piesa("A","Q",{8,4});
            mat[7][4]=new Piesa("A","K",{8,5});
            mat[7][5]=new Piesa("A","N",{8,6});
            mat[7][6]=new Piesa("A","C",{8,7});
            mat[7][7]=new Piesa("A","T",{8,8});

            for(int i=2;i<6;i++)
                for(int j=0;j<=8;j++)
                    mat[i][j]=NULL;
        }
        void afistabla(Piesa *mat[8][8])
        {
            for(int i=0;i<3;i++){
                for(int j=0;j<36;j++)
                    if(j%4==1&&i%3==1&&j>4)
                        std::cout<<char('a'+j/4-1);
                    else
                        std::cout<<"*";
                std::cout<<"\n";
            }
            for(int i=0;i<24;i++){
                for(int j=0;j<36;j++)
                {
                    if(j<4){
                        if(i%3==1&&j%4==1)
                            std::cout<<i/3+1;
                        else
                            std::cout<<"*";
                    }
                    else
                    {
                        if((j%4==1||j%4==2)&&i%3==1&&j>=4&&mat[i/3][(j-4)/4]!=0){
                            if(j%4==1)
                                std::cout<<mat[i/3][(j-4)/4]->getculoare();
                            if(j%4==2)
                                std::cout<<mat[i/3][(j-4)/4]->getpiesa();
                        }
                        else
                        {
                            if((j/4+(i/3-1))%2==0)
                                std::cout<<" ";
                            else
                                std::cout<<"#";
                        }
                    }
                }
                std::cout<<"\n";
            }
        }
};

class joc
{
    Piesa *mat[8][8];
    public:
        int finaljoc()
        {
            return 1;
        }
        int conversiemutare(pozitie &a,pozitie &b,std::string m)
        {
            int sem1=0,sem2=0;
            std::string sep=" ,.;:";
            for(int i=0;i<m.length();i++)
            {
                if(sep.rfind(m[i]))
                {
                    if('a'<=m[i]&&m[i]<='h')
                    {
                        if(sem1==0)
                            a.x=m[i]-'a'+1;
                        else
                            b.x=m[i]-'a'+1;
                        sem1++;
                    }
                    else
                    {
                        if('1'<=m[i]&&m[i]<='8')
                        {
                           if(sem2==0)
                                a.y=m[i]-'1'+1;
                           else
                                b.y=m[i]-'1'+1;
                           sem2++;
                        }
                        else
                        {
                            std::cout<<"MUTARE INVALIDA !!!";
                            return 0;
                        }
                    }
                }
            }
            if(sem1!=2||sem2!=2)
            {
                std::cout<<"MUTARE INVALIDA !!!";
                return 0;
            }
            return 1;
        }

        int mutarevalida(pozitie ms,pozitie mf,int rj)
        {
            if(mat[ms.x][ms.y]==NULL)
            {
                std::cout<<"MUTARE INVALIDA 4!!!";
                return 0;
            }
            if((rj==-1&&mat[ms.x][ms.y]->getculoare()=="N")||(rj==1&&mat[ms.x][ms.y]->getculoare()=="A")){
                std::cout<<"MUTARE INVALIDA 3!!!";
                return 0;
            }

            return 1;
        }

        joc()
        {
            std::string numejuc1,numejuc2;
            std::cout<<"Nume jucator 1:";
            std::cin>>numejuc1;

            std::cout<<"Nume jucator 2:";
            std::cin>>numejuc2;

            system("cls");
            tablasah t;
            t.asezpiese(mat);
            int randjucator=-1;
            do
            {
                t.afistabla(mat);
                std::string mutare;
                std::cout<<"Randul jucatorului "<<(randjucator<0?numejuc1:numejuc2);
                pozitie mutarestart,mutarefinal;
                do
                {
                    std::cout<<"\nIntroduceti o mutare:";
                    std::getline(std::cin>>std::ws,mutare);
                }while(!conversiemutare(mutarestart,mutarefinal,mutare)||!mutarevalida(mutarestart,mutarefinal,randjucator));

            }while(!finaljoc());
        }
};
int main()
{
    joc start;
}
