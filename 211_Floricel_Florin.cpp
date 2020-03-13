#include <iostream>
#include <string.h>
#include <windows.h>
using namespace std;

class nod{
    private:
        char val;
        nod *urm;
    public:
        friend class coada_de_caractere;
        nod(){
            val='\0';
            urm=NULL;
        }
};

class coada_de_caractere{
    private:
        nod *prim,*ultim;
    public:
        coada_de_caractere(){
            prim=NULL;
            ultim=NULL;}
        coada_de_caractere(coada_de_caractere&);
        ~coada_de_caractere();
        inline void push(char c);
        char pop();
        void afisare(ostream &out);
        int isempty();
        friend ostream &operator<<(ostream &out,coada_de_caractere &c);
        friend istream &operator>>(istream &in,coada_de_caractere &c);
        friend coada_de_caractere &operator+(coada_de_caractere &c1, coada_de_caractere &c2);
        friend coada_de_caractere &operator-(coada_de_caractere &c1, coada_de_caractere &c2);
};

coada_de_caractere::coada_de_caractere(coada_de_caractere &c){
    prim=NULL; ultim=NULL;
    nod *q=c.prim;
    while(q!=NULL){
            push(q->val);
            q=q->urm;
    }
}
coada_de_caractere::~coada_de_caractere(){
   nod *q;
   q=prim;
   while(prim!=NULL){
        prim=prim->urm;
        delete q;
        q=prim;
   }
}

void coada_de_caractere::push(char c){
    nod *q=new nod;
    q->val=c;
    if (ultim==NULL){
            prim=q;
            ultim=q;}
    else{
            ultim->urm=q;
            ultim=q;
    }
}
char coada_de_caractere::pop(){
    char k='\0';
    if (prim!=NULL){
        k=prim->val;
        nod *q=prim;
        prim=prim->urm;
        delete q;
        if (prim==NULL)
            ultim=NULL;
    }
    return k;
}

void coada_de_caractere::afisare(ostream &out){
    nod *q=prim;
    while(q!=NULL){
            out<<q->val;
            q=q->urm;
    }
}

int coada_de_caractere::isempty(){
    if (prim!=NULL)
        return 0;
    return 1;
}
ostream &operator<<(ostream &out, coada_de_caractere &c){
    c.afisare(out);
    return out;
}
istream &operator>>(istream &in, coada_de_caractere &c){
    char k[100];
    in>>k;
    for(unsigned int i=0;i<strlen(k);i++){
            if (k[i]=='\0')
                break;
            c.push(k[i]);
    }
    return in;
}
coada_de_caractere &operator+(coada_de_caractere &c1, coada_de_caractere &c2){
    coada_de_caractere *c= new coada_de_caractere;
    coada_de_caractere c3(c2);
    char k;
    while(c1.isempty()==0){
        k=c1.pop();
        (*c).push(k);
    }
    while(c3.isempty()==0){
        k=c3.pop();
        (*c).push(k);
    }
    c1.prim=(*c).prim;
    c1.ultim=(*c).ultim;
    return c1;
}
coada_de_caractere &operator-(coada_de_caractere &c1, coada_de_caractere &c2){
    coada_de_caractere c3(c1);
    coada_de_caractere c4(c2);
    coada_de_caractere *c5= new coada_de_caractere;
    char k1,k2;
    while (c3.isempty()==0 && c4.isempty()==0){
            k1=c3.pop();
            k2=c4.pop();
            if ((int)k1>(int)k2)
                c5->push(k1);
            else
                (*c5).push(k2);
    }
    return *c5;
}



void menu_output(){
    cout<<"Floricel Florin 211 - Tema 5 - Coada de caractere"<<endl<<endl;
    cout<<"\t\t\tMENIU:"<<endl;
    cout<<"================================================="<<endl;
    cout<<"1. Creare coada de caractere"<<endl;
    cout<<"2. Afisare coada de caractere"<<endl;
    cout<<"3. Concatenare cozi de caractere (cu suprascriere)"<<endl;
    cout<<"4. Diferenta dintre cozi de caractere (fara suprascriere)"<<endl;
    cout<<"0. Iesire."<<endl<<endl;
}
void menu(){
    int option=0,k=0,k2,nr_coada=-1,ok=0;
    coada_de_caractere *coada;
    do{
        menu_output();
        cout<<"Introduceti numarul actiunii: ";
        cin>>option;
        if (option==1){
            if (ok==1) cout<<"Ai creat deja cozile";
            else{
                int nr_cozi;
                cout<<"Introduceti numarul de cozi pentru citire:";
                cin>>nr_cozi;
                coada=new coada_de_caractere[nr_cozi];
                for(int i=0;i<nr_cozi;i++){
                    nr_coada++;
                    cout<<"Introduceti integral, fara spatii, coada"<<nr_coada<<": ";
                    cin>>coada[nr_coada];
                }
                ok=1;
            }
        }
        if (option==2){
            if (nr_coada==-1)
                cout<<"Nu ai creat nici o coada";
            else{
                cout<<"Cozi create: ";
                for(int i=0;i<=nr_coada;i++)
                    cout<<i<<" ";
                cout<<endl<<"Introduceti numarul cozii pentru afisare: ";
                cin>>k;
                if (k<0||k>nr_coada)
                    cout<<"Coada nu exista";
                else{
                    cout<<"Coada"<<k<<": ";
                    cout<<coada[k];
                }
            }
        }
        if (option==3){
                if (nr_coada<1)
                    cout<<"Nu sunt cel putin doua cozi create";
                else{
                    cout<<"Cozi create: ";
                    for(int i=0;i<=nr_coada;i++)
                        cout<<i<<" ";
                    cout<<endl<<"Introduceti numarul cozilor pentru concatenare: "<<endl;
                    cin>>k;
                    cout<<"+"<<endl;
                    cin>>k2;
                    if (k<0||k>nr_coada||k2<0||k2>nr_coada)
                        cout<<"Selectie coada invalida";
                    else cout<<"= "<<coada[k]+coada[k2];
                }
        }
        if (option==4){
            if (nr_coada<1)
                    cout<<"Nu sunt cel putin doua cozi create";
                else{
                    cout<<"Cozi create: ";
                    for(int i=0;i<=nr_coada;i++)
                        cout<<i<<" ";
                    cout<<endl<<"Introduceti numarul cozilor pentru diferenta: "<<endl;
                    cin>>k;
                    cout<<"-"<<endl;
                    cin>>k2;
                    if (k<0||k>nr_coada||k2<0||k2>nr_coada)
                        cout<<"Selectie coada invalida";
                    else cout<<"= "<<coada[k]-coada[k2];
                }
        }
        if (option==0)
            cout<<"\nEXIT\n";
        if (option<0||option>4)
            cout<<"\nSelectie invalida\n";
        cout<<endl;
        system("pause");
        system("cls");
    }
    while (option!=0);
}
int main(){
    menu();
return 0;}
