#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

class incapere{
        int index,zile[367];
    public:
    incapere():index(0){for(int i=1;i<366;++i)zile[i]=0;}
    incapere(const incapere& x){
        this->index=x.index;
        for(int i=1;i<366;++i)this->zile[i]=x.zile[i];
    }
    int get_id_zi(int i);
    int get_index();
    void set_index(int val);
    void set_id_zi(int i,int val);
    virtual int get_capacitate_maxima()=0;
    virtual int get_capacitate_minima()=0;
};
int incapere::get_id_zi(int i){return zile[i];}
int incapere::get_index(){return index;}
void incapere::set_id_zi(int i,int val){zile[i]=val;}
void incapere::set_index(int val){index=val;}

class camera:public incapere{
        static int capacitate_maxima,capacitate_minima;
    public:
        int get_capacitate_maxima();
        int get_capacitate_minima(){return capacitate_minima;}
        camera& operator=(camera x);
};
int camera::capacitate_maxima=2;
int camera::capacitate_minima=1;
int camera::get_capacitate_maxima(){return capacitate_maxima;}
camera& camera::operator=(camera x){
    set_index(x.get_index());
    for(int i=1;i<366;++i)set_id_zi(i,x.get_id_zi(i));
    return *this;
}

class apartament:public incapere{
        static int capacitate_maxima,capacitate_minima;
    public:
        apartament(){
            set_index(0);
            for(int i=1;i<366;++i)set_id_zi(i,0);
        }
        apartament(camera x){
            set_index(x.get_index());
            for(int i=1;i<366;++i)set_id_zi(i,x.get_id_zi(i));
        }
        int get_capacitate_maxima();
        int get_capacitate_minima();
        apartament& operator=(apartament x);
};
int apartament::capacitate_maxima=4;
int apartament::capacitate_minima=1;
int apartament::get_capacitate_maxima(){return capacitate_maxima;}
int apartament::get_capacitate_minima(){return capacitate_minima;}
apartament& apartament::operator=(apartament x){
    set_index(x.get_index());
    for(int i=1;i<366;++i)set_id_zi(i,x.get_id_zi(i));
    return *this;
}

class sala_scena:public incapere{
        static const int capacitate_maxima=13;
        static const int capacitate_minima=1;
    public:
        int get_capacitate_maxima(){return capacitate_maxima;}
        int get_capacitate_minima(){return capacitate_minima;}
        sala_scena& operator=(sala_scena x);
    };
sala_scena& sala_scena::operator=(sala_scena x){
    set_index(x.get_index());
    for(int i=1;i<366;++i)set_id_zi(i,x.get_id_zi(i));
    return *this;
}

class sala_individuala:public incapere{
        static int capacitate_maxima;
        static int capacitate_minima;
    public:
        sala_individuala(){
            set_index(0);
            for(int i=1;i<366;++i)set_id_zi(i,0);
        }
        sala_individuala(sala_scena x){
            set_index(x.get_index());
            for(int i=1;i<366;++i)set_id_zi(i,x.get_id_zi(i));
        }
        int get_capacitate_maxima();
        int get_capacitate_minima();
        sala_individuala& operator=(sala_individuala x);
};
int sala_individuala::capacitate_maxima=8;
int sala_individuala::capacitate_minima=4;
int sala_individuala::get_capacitate_maxima(){return capacitate_maxima;}
int sala_individuala::get_capacitate_minima(){return capacitate_minima;}
sala_individuala& sala_individuala::operator=(sala_individuala x){
    set_index(x.get_index());
    for(int i=1;i<366;++i)set_id_zi(i,x.get_id_zi(i));
    return *this;
}

class hotel{
        int nr_apartamente,nr_camere,nr_sali_indiv,nr_sali_scena,nr_restaurant,loc_restaurant[367];
        incapere *incaperi[120];
        friend istream& operator>>(istream& in,hotel &h){
                in>>h.nr_apartamente;
                if(h.nr_apartamente<1){
                    cout<<"EROARE! Numarul de apartamente din hotel nu poate sa fie mai mic sau egal decat 0. Numarul acestora a fost automat setat la 1.\n";
                    h.nr_apartamente=1;
                }
                in>>h.nr_camere;
                if(h.nr_camere<1){
                    cout<<"EROARE! Numarul de camere din hotel nu poate sa fie mai mic sau egal decat 0. Numarul acestora a fost automat setat la 1.\n";
                    h.nr_camere=1;
                }
                in>>h.nr_sali_indiv;
                if(h.nr_sali_indiv<1){
                    cout<<"EROARE! Numarul de sali individuale din hotel nu poate sa fie mai mic sau egal decat 0. Numarul acestora a fost automat setat la 1.\n";
                    h.nr_sali_indiv=1;
                }
                in>>h.nr_sali_scena;
                if(h.nr_sali_scena<1){
                    cout<<"EROARE! Numarul de sali de tip scena din hotel nu poate sa fie mai mic sau egal decat 0. Numarul acestora a fost automat setat la 1.\n";
                    h.nr_sali_scena=1;
                }
                in>>h.nr_restaurant;
                apartament placeholder_a;camera placeholder_c;
                if(h.nr_restaurant>=h.nr_apartamente*placeholder_a.get_capacitate_maxima()+h.nr_camere*placeholder_c.get_capacitate_maxima()){
                    cout<<"EROARE! Numarul de locuri de la restaurantul din hotel nu poate sa fie mai mare sau egal degat capacitatea maxima de cazare a hotelului. Numarul acestora a fost automat setat la capacitatea maxima a hotelului-1.\n";
                    h.nr_restaurant=h.nr_apartamente*placeholder_a.get_capacitate_maxima()+h.nr_camere*placeholder_c.get_capacitate_maxima()-1;
                }
            int t=0;
            for(int i=0;i<h.nr_apartamente;++i){h.incaperi[i+t]=new apartament;h.incaperi[i+t]->set_index(i+1);}
            t+=h.nr_apartamente;
            for(int i=0;i<h.nr_camere;++i){h.incaperi[i+t]=new camera;h.incaperi[i+t]->set_index(i+1);}
            t+=h.nr_camere;
            for(int i=0;i<h.nr_sali_indiv;++i){h.incaperi[i+t]=new sala_individuala;h.incaperi[i+t]->set_index(i+1);}
            t+=h.nr_sali_indiv;
            for(int i=0;i<h.nr_sali_scena;++i){h.incaperi[i+t]=new sala_scena;h.incaperi[i+t]->set_index(i+1);}
            return in;
        }
        hotel(){}
        hotel(const hotel& )=delete;
        hotel& operator=(const hotel& x)=delete;
        ~hotel(){
            int t=nr_apartamente+nr_camere+nr_sali_indiv+nr_sali_scena;
            for(int i=0;i<t;++i)
                if(incaperi[i])delete incaperi[i];
        }
    public:
        static hotel& get_instanta() {
            static hotel instanta;
            return instanta;
        }
        static void eliberare() {
            get_instanta().~hotel();
        }
        int get_nr_apartamente();
        int get_nr_camere();
        int get_nr_sali_indiv();
        int get_nr_sali_scena();
        int get_nr_restaurant();
        int get_loc_restaurant(int i);
        void set_loc_restaurant(int i,int val);
        void ocupare_eliberare(int i,int prima_zi,int nr_zile,int val){for(int j=prima_zi;j<prima_zi+nr_zile;++j)incaperi[i-1]->set_id_zi(j,val);}
        int get_tip_incapere(int i){
            if(dynamic_cast<apartament*>(incaperi[i-1]))return 1;
            if(dynamic_cast<camera*>(incaperi[i-1]))return 2;
            if(dynamic_cast<sala_individuala*>(incaperi[i-1]))return 3;
            if(dynamic_cast<sala_scena*>(incaperi[i-1]))return 4;
        }
        int get_capacitate_maxima(int i){return incaperi[i]->get_capacitate_maxima();}
        int get_capacitate_minima(int i){return incaperi[i]->get_capacitate_minima();}
        int get_id_zi(int i,int zi){return incaperi[i]->get_id_zi(zi);}
        int get_index(int i){return incaperi[i]->get_index();}
};
int hotel::get_loc_restaurant(int i){return loc_restaurant[i];}
void hotel::set_loc_restaurant(int i,int val){loc_restaurant[i]=val;}
int hotel::get_nr_apartamente(){return nr_apartamente;}
int hotel::get_nr_camere(){return nr_camere;}
int hotel::get_nr_sali_indiv(){return nr_sali_indiv;}
int hotel::get_nr_sali_scena(){return nr_sali_scena;}
int hotel::get_nr_restaurant(){return nr_restaurant;}

class data_base{
        int id,ziua_minima,nr_participanti,nr_zile,nr_micdejun,tip_sala,nr_camere,nr_apartamente,nr_indiv,*incaperi;
        char participanti[50][200];
        friend istream& operator>>(istream& in,data_base &base){
            int cont=0;
            char s[50];
            try{
                in>>base.nr_participanti>>base.nr_zile;
            if(base.nr_participanti<1)throw 1;
            if(base.nr_zile<1)throw 1;
            if(base.nr_zile>10)throw 1;
            }
            catch(int){
                if(base.nr_participanti<1){
                    cout<<"Numar de participanti invalid! Va fi setat automat la 1!\n";
                    base.nr_participanti=1;
                }
                if(base.nr_zile<1){
                    cout<<"Numarul de zile este invalid. Va fi setat automat la 1!\n";
                    base.nr_zile=1;
                }
                if(base.nr_zile>10){
                    cout<<"Numarul de zile este invalid. Va fi setat automat la 10!\n";
                    base.nr_zile=10;
                }
            }
            in.get();
            for(int i=0;i<base.nr_participanti;++i){
                in.getline(s,200);
                strcpy(base.participanti[i],s);
                cont+=s[strlen(s)-1]-'0';
            }
            base.nr_micdejun=cont;
            in>>cont;
            if(cont==1)in>>base.tip_sala;
        }
        friend ostream& operator<<(ostream& out,data_base& base){
            hotel& hotelul=hotel::get_instanta();
            out<<"Cererea grupului cu id-ul "<<base.id<<" va fi onorata in ziua a "<<base.ziua_minima<<"-a\n"<<"Acestea sunt detaliile:\n";
            for(int i=0;i<base.nr_participanti;++i)out<<base.participanti[i]<<"\n";
            if(base.tip_sala==0){
                out<<"Acest grup a rezervat urmatoarele sali de tip individuale: ";
                for(int i=0;i<base.nr_indiv;++i)out<<hotelul.get_index(base.incaperi[base.nr_apartamente+base.nr_camere+i])<<" ";
                return out<<"\n\n";
            }
            else
                if(base.tip_sala==1)out<<"Acest grup a rezervat urmatoarea sala de tip scena: "<<hotelul.get_index(base.incaperi[base.nr_apartamente+base.nr_camere])<<"\n\n";
                else return out<<"\n";
        }
    public:
        data_base():tip_sala(-1),nr_apartamente(0),nr_indiv(0),nr_camere(0),id(-2),ziua_minima(1){
            incaperi=new int[100];
        }
        data_base(const data_base& x){
            id=x.id;
            tip_sala=x.tip_sala;
            nr_apartamente=x.nr_apartamente;
            nr_camere=x.nr_camere;
            nr_indiv=x.nr_indiv;
            nr_micdejun=x.nr_micdejun;
            ziua_minima=x.ziua_minima;
            nr_zile=x.nr_zile;
            nr_participanti=x.nr_participanti;
            incaperi=new int[100];
            for(int i=0;i<nr_apartamente+nr_camere+nr_indiv+1;++i)incaperi[i]=x.incaperi[i];
            for(int i=0;i<nr_participanti;++i)strcpy(participanti[i],x.participanti[i]);
        }
        ~data_base(){
            if(incaperi)delete[]incaperi;
        }
        data_base operator=(const data_base x);
        int get_nr_participanti();
        int get_nr_zile();
        int get_id();
        void set_id(int val);
        int get_tip_sala();
        int get_nr_micdejun();
        int get_ziua_minima();
        void set_ziua_minima(int val);
        int get_nr_apartamente();
        void set_nr_apartamente(int val);
        int get_nr_camere();
        void set_nr_camere(int val);
        int get_nr_sali_indiv();
        void set_nr_sali_indiv(int val);
        char *get_participanti_line(int i);
        void set_participanti_line(int i, char sir[200]);
        int get_id_incapere(int i){return incaperi[i];}
        void asezare(int idul);
        void anulare();
};
data_base data_base::operator=(const data_base x){
    id=x.id;
    tip_sala=x.tip_sala;
    nr_apartamente=x.nr_apartamente;
    nr_camere=x.nr_camere;
    nr_indiv=x.nr_indiv;
    nr_micdejun=x.nr_micdejun;
    ziua_minima=x.ziua_minima;
    nr_zile=x.nr_zile;
    nr_participanti=x.nr_participanti;
    if(incaperi)delete[] incaperi;
    incaperi=new int[nr_indiv+nr_apartamente+nr_camere+2]; 
    for(int i=0;i<nr_apartamente+nr_camere+nr_indiv+1;++i)incaperi[i]=x.incaperi[i];
    for(int i=0;i<nr_participanti;++i)strcpy(participanti[i],x.participanti[i]);
    return *this;
}
int data_base::get_id(){return id;}
void data_base::set_id(int val){id=val;}
int data_base::get_tip_sala(){return tip_sala;}
int data_base::get_nr_micdejun(){return nr_micdejun;}
int data_base::get_ziua_minima(){return ziua_minima;}
void data_base::set_ziua_minima(int val){ziua_minima=val;}
int data_base::get_nr_apartamente(){return nr_apartamente;}
void data_base::set_nr_apartamente(int val){nr_apartamente=val;}
int data_base::get_nr_camere(){return nr_camere;}
void data_base::set_nr_camere(int val){nr_camere=val;}
int data_base::get_nr_sali_indiv(){return nr_indiv;}
void data_base::set_nr_sali_indiv(int val){nr_indiv=val;}
int data_base::get_nr_zile(){return nr_zile;}
int data_base::get_nr_participanti(){return nr_participanti;}
char* data_base::get_participanti_line(int i){return participanti[i];}
void data_base::set_participanti_line(int i, char sir[200]){strcpy(participanti[i],sir);}

void liber(int tip,int &nr,int zi_minima,int &min_mai_mare,int lista[30],int nr_zile){
    hotel& hotelul=hotel::get_instanta();
    int i,j,k,bun,start,limita;
    if(tip==1){start=0;limita=start+hotelul.get_nr_apartamente();}
    else
        if(tip==2){start=hotelul.get_nr_apartamente();limita=start+hotelul.get_nr_camere();}
        else
            if(tip==3){start=hotelul.get_nr_apartamente()+hotelul.get_nr_camere();limita=start+hotelul.get_nr_sali_indiv();}
    for(i=start;i<limita;++i){
        bun=1;
        for(j=zi_minima;j<366-nr_zile;++j){
            bun=1;
            for(k=j;k<j+nr_zile;++k)
                if(hotelul.get_id_zi(i,k)!=0)bun=0;
            if(bun==1)break;
        }
        if(j==zi_minima)lista[nr++]=i;
        else
            if(j<min_mai_mare)min_mai_mare=j;
    }
}
void liber(int tip,int zi_minima,int &min_mai_mare,int &memorare,int nr_zile,int optional){
    hotel& hotelul=hotel::get_instanta();
    int i,j,k,bun,start,limita;
    if(tip==4){
        start=hotelul.get_nr_apartamente()+hotelul.get_nr_camere()+hotelul.get_nr_sali_indiv();limita=start+ hotelul.get_nr_sali_scena();
        for(i=start;i<limita;++i){
            bun=1;
            for(j=zi_minima;j<366-nr_zile;++j){
                bun=1;
                for(k=j;k<j+nr_zile;++k)
                    if(hotelul.get_id_zi(i,k)!=0)bun=0;
                if(bun==1)break;
        }
        if(j==zi_minima)memorare=i;
        else
            if(j<min_mai_mare)min_mai_mare=j;
        }
    }
    else if(tip==0){
        for(j=zi_minima;j<366-nr_zile;++j){
            bun=1;
            for(k=j;k<j+nr_zile;++k)
                if(hotelul.get_loc_restaurant(k)+optional>hotelul.get_nr_restaurant())bun=0;
            if(bun==1)break;
            }
        if(j!=zi_minima){
            memorare=0;
            if(j<min_mai_mare)min_mai_mare=j;
        }
    }
}
void alegere(int &i,int &j,int nr_cam,int nr_apart,int nr_participanti){
    hotel& hotelul=hotel::get_instanta();
    int bun=0;
    for (j=0;j<=nr_cam;++j){
        for (i=0;i<=nr_apart;++i)
            if(hotelul.get_capacitate_maxima(0)*i+hotelul.get_capacitate_maxima(hotelul.get_nr_apartamente())*j>=nr_participanti){
                bun=1;
                break;
            }
        if (bun==1&&hotelul.get_capacitate_maxima(0)*i+hotelul.get_capacitate_maxima(hotelul.get_nr_apartamente())*j>=nr_participanti)
            break;
    }
}
void data_base::asezare(int idul){
    hotel& hotelul=hotel::get_instanta();
    int zi_minima=1,gasit=0,accept=1,apartam[30],came[30],sala_indivi[10],salascena,nr_apart=0,nr_cam=0,nr_individ=0;
    int nr_sali_necesare=tip_sala==1?1:((nr_participanti%hotelul.get_capacitate_maxima(hotelul.get_nr_apartamente()+hotelul.get_nr_camere()))==0?nr_participanti/hotelul.get_capacitate_maxima(hotelul.get_nr_apartamente()+hotelul.get_nr_camere()):(nr_participanti/hotelul.get_capacitate_maxima(hotelul.get_nr_apartamente()+hotelul.get_nr_camere()))+1);
    if((tip_sala==0&&nr_participanti<hotelul.get_capacitate_minima(hotelul.get_nr_apartamente()+hotelul.get_nr_camere()))||(tip_sala==0&&nr_sali_necesare>hotelul.get_nr_sali_indiv())||nr_participanti>hotelul.get_capacitate_maxima(0)*hotelul.get_nr_apartamente()+hotelul.get_capacitate_maxima(hotelul.get_nr_apartamente())*hotelul.get_nr_camere()){
        accept=0;
        throw 0;
    }
    if((nr_participanti<=hotelul.get_nr_apartamente()*(hotelul.get_capacitate_maxima(0))+hotelul.get_nr_camere()*(hotelul.get_capacitate_maxima(hotelul.get_nr_apartamente())))&&accept){
        id=idul;
        while(gasit==0){
            int i,j,k,bun,min_mai_mare=366;nr_apart=0,nr_cam=0,nr_individ=0,salascena=0;
            liber(hotelul.get_tip_incapere(1),nr_apart,zi_minima,min_mai_mare,apartam,nr_zile);
            liber(hotelul.get_tip_incapere(1+hotelul.get_nr_apartamente()),nr_cam,zi_minima,min_mai_mare,came,nr_zile);
            accept=1;
            if(tip_sala!=-1){
                if(tip_sala==0){
                    liber(hotelul.get_tip_incapere(1+hotelul.get_nr_apartamente()+hotelul.get_nr_camere()),nr_individ,zi_minima,min_mai_mare,sala_indivi,nr_zile);
                    if(nr_individ<nr_sali_necesare)accept=0;
                }
                else{
                    liber(hotelul.get_tip_incapere(1+hotelul.get_nr_apartamente()+hotelul.get_nr_camere()+hotelul.get_nr_sali_indiv()),zi_minima,min_mai_mare,salascena,nr_zile,0);
                    if(salascena==0)accept=0;
                }
            }
            liber(0,zi_minima,min_mai_mare,accept,nr_zile,nr_micdejun);
            if((nr_apart*hotelul.get_capacitate_maxima(0)+nr_cam*hotelul.get_capacitate_maxima(hotelul.get_nr_apartamente())>=nr_participanti)&&accept){
                gasit=1;
                i=j=0;
                alegere(i,j,nr_cam,nr_apart,nr_participanti);
                nr_apartamente=i;
                nr_camere=j;
                if(tip_sala==0)nr_indiv=nr_sali_necesare;
                ziua_minima=zi_minima;
                int t=0;
                for(int k=0;k<nr_apartamente;++k){
                    incaperi[k+t]=apartam[k];
                    hotelul.ocupare_eliberare(incaperi[k+t]+1,ziua_minima,nr_zile,id);
                }
                t+=nr_apartamente;
                for(int k=0;k<nr_camere;++k){
                    incaperi[k+t]=came[k];
                    hotelul.ocupare_eliberare(incaperi[k+t]+1,ziua_minima,nr_zile,id);
                }
                t+=nr_camere;
                if(tip_sala==0)
                    for(int k=0;k<nr_indiv;++k){
                        incaperi[k+t]=sala_indivi[k];
                        hotelul.ocupare_eliberare(incaperi[k+t]+1,ziua_minima,nr_zile,id);
                    }
                if(tip_sala==1){
                    incaperi[t]=salascena;
                    hotelul.ocupare_eliberare(incaperi[t]+1,ziua_minima,nr_zile,id);
                }
                for(i=ziua_minima;i<ziua_minima+nr_zile;++i)hotelul.set_loc_restaurant(i,hotelul.get_loc_restaurant(i)+nr_micdejun);
                int membri=0;
                i=1;
                while(i<=nr_apartamente+nr_camere){
                    int loc=1;
                    while(membri<nr_participanti&&loc<=hotelul.get_capacitate_maxima(i-1)){
                        char s[200]="\0";
                        int c;
                        strcpy(s,participanti[membri]);
                        c=s[strlen(s)-1]-'0';
                        strcpy(s+strlen(s)-1,s+strlen(s));
                        if(hotelul.get_tip_incapere(incaperi[i-1]+1)==1)strcat(s,"este cazat/a in apartamentul nr-ul ");
                        else strcat(s,"este cazat/a in camera nr-ul ");
                        s[strlen(s)]=hotelul.get_index(incaperi[i-1])+'0';
                        s[strlen(s)+1]='\0';
                        strcat(s,". Acesta/Aceasta ia micul dejun ");
                        if(c==1)strcat(s,"la restaurant.");
                        else strcat(s,"in camera.");
                        set_participanti_line(membri,s);
                        membri++;loc++;
                    }
                    i++;
                }
            }
            else zi_minima=min_mai_mare;
        }
    }
}
void data_base::anulare(){
    hotel& hotelul=hotel::get_instanta();
    id=-1;
    int t=nr_apartamente+nr_camere;
    if(tip_sala==1)t++;
    else if(tip_sala==0)t+=nr_indiv;
    for(int i=0;i<t;++i)hotelul.ocupare_eliberare(incaperi[i]+1,ziua_minima,nr_zile,0);
    for(int j=ziua_minima;j<ziua_minima+nr_zile;++j)
        hotelul.set_loc_restaurant(j,hotelul.get_loc_restaurant(j)-nr_micdejun);
    int i=0, y=hotelul.get_tip_incapere(incaperi[0]+1);
    while(i<t){
        int cont=0;
        while(i<t&&y==hotelul.get_tip_incapere(incaperi[i]+1)){
            cont++;
            i++;
        }
        if(cont!=0)
            {cout<<"Grupul avea rezervata/rezervate "<<cont<<" incapere/incaperi de tip ";
            if(y==1)cout<<"apartament\n";
            else
                if(y==2)cout<<"camera\n";
                else
                    if(y==3)cout<<"sala individuala\n";
                    else
                        cout<<"sala scena\n";
        }
        if(i<t)
            y=hotelul.get_tip_incapere(incaperi[i]+1);
    }
    cout<<"\n";
}
void introducere_date(int index,data_base &grup){
    try{grup.asezare(index);}
    catch(int){cout<<"Cererea grupului cu id-ul "<<index<<" nu este valida!\n\n";}
    if(grup.get_id()!=-2){
        cout<<grup;
    }
}
void scoatere(int id,int index,data_base grupuri[50]){
    int gasit=0;
    for(int i=0;i<index-1;++i)if(grupuri[i].get_id()==id)gasit=1;
    if(gasit==1){
        cout<<"Grupul cu id-ul "<<id<<" si-a anulat rezervarea! \nDetalii: \n";
        grupuri[id-1].anulare();   
    }
    else
        throw 1;
}
void afisare(int index,data_base grupuri[50]){
    for(int i=0;i<41;++i)cout<<"-";
    cout<<"\n\n";
    cout<<"Aceasta este starea actuala a bazei de date:\n\n";
    for(int i=0;i<index-1;++i)
        if(grupuri[i].get_id()!=-2&&grupuri[i].get_id()!=-1){
            cout<<grupuri[i];
        }
        else
            if(grupuri[i].get_id()==-2)
                cout<<"Cererea grupului cu id-ul "<<i+1<<" nu este valida!\n\n";
            else
                cout<<"Grupul cu id-ul "<<i+1<<" si-a anulat rezervarea!\n\n";
    for(int i=0;i<41;++i)cout<<"-";
    cout<<"\n\n";
}
int main(int argc, char* argv[]){
    hotel& hotelul=hotel::get_instanta();
    data_base grupuri[50];
    int x,index=1;
    istream *in;
    if(argc==1)in=&cin;
    else{
        fstream *fin=new fstream(argv[1]);
        in=fin;
    }
    ifstream init("init.in");
    init>>hotelul;
    if(argc==1)cout<<"Pentru noi rezervari va rugam sa introduceti datele in urmatoarea ordine:\nNumarul de persoane\nNumarul de zile\nNumele persoanelor ce fac parte din grup urmate de 0 daca doresc sa ia masa in camera sau de 1 daca doresc sa o ia la restaurant\n<Exemplu: Popescu Raluca 1>\nCifra 1 daca doriti sa rezervati sala sau 0 altfel\nIn cazul in care se doreste sala, va trebui sa introduceti si ce tip de sala doriti, cifra 1 pentru sala de tip scena sau 0 pentru cea de tip individuala.\n\n";
    if(argc==1)cout<<"Introduceti de la tastatura valoarea 1 daca doriti sa introduceti o cerere pentru un grup nou, sau valoarea 0, daca doriti sa anulati rezervarea unui grup!\n";
    *in>>x;
    while(x!=-1){
        if(x==1){
            *in>>grupuri[index-1];
            introducere_date(index,grupuri[index-1]);
            ++index;
        }
        else 
            if(x==0){
                int id;
                *in>>id;
                try{scoatere(id,index,grupuri);}
                catch(int){cout<<"Grupul cu id-ul "<<id<<" nu exista!\n\n";}
            }
            else
                afisare(index,grupuri);
        if(argc==1)cout<<"Introduceti de la tastatura valoarea 1 daca se mai doreste introducerea unei cereri pentru un nou grup, valoarea 0, daca se doreste anularea undei rezervari, valoarea 2, daca se doreste vizualizarea starii bazei de date, sau valoarea -1, daca doriti ca programul sa se incheie!\n";
        *in>>x;
    }
    sala_scena exemplu_schimbare_tip;
    exemplu_schimbare_tip.set_index(23);
    for(int i=1;i<24;++i)exemplu_schimbare_tip.set_id_zi(i,2*i);
    sala_individuala schimbata(exemplu_schimbare_tip);
    hotel::eliberare();
    return 0;
}
