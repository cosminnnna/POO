#include <iostream>
#include <vector>
using namespace std;


class Vector {
    ///membri privati pentru vectorul propriuzis si numarul de elemente
private:
    int Nr_elem;
    double* v;

public:
    ///constructor pentru initializarea cu un numar dat pe toate componentele
    Vector (double x, int nr){
        Nr_elem = nr;
        auto *vector_nou = new double [nr];
        for (int i=0; i<nr; i++)
            vector_nou[i] = x;
        v = vector_nou;
    }

    /// constructor pentru initializare
    Vector (){
        Nr_elem = 1;
        v = new double [1];
    }

    /// constructor pentru copiere
    Vector (const Vector &vector_){
        auto *vector_nou = new double [vector_.Nr_elem];
        Nr_elem = vector_.Nr_elem;

        for (int i=0; i< Nr_elem; i++)
            vector_nou[i] = vector_.v[i];

        v = vector_nou;
    }


    ///destructor
    ~Vector() {
        delete[] v;
    }


    ///metoda-operator public de atribuire
    Vector& operator=(const Vector &vector_) {
        // if (this!= &vector_) //test pt a evita atribuire de tipul obiect=obiect

        delete[] v;
        auto *vector_nou = new double [vector_.Nr_elem];
        Nr_elem = vector_.Nr_elem;

        for(int i=0; i<Nr_elem;i++)
            vector_nou[i]=vector_.v[i];
        v = vector_nou;

        return *this;
    }

    ///metoda reactualizare elemente
    void reactualizare (double x, int nr){
        delete[] v;
        Nr_elem = nr;
        auto *vector_nou = new double [nr];

        for (int i=0; i<nr; i++)
            vector_nou[i] = x;

        v = vector_nou;
    }


    ///getter nr elemente
    int getNr_elem() const{
        return Nr_elem;
    }
    ///setter nr elemente
    void setNr_elem (int a){
        Nr_elem = a;
    }

    ///geter vector
    double* getv () const {
        return v;
    }

    ///setter vector
    void setv (Vector vector_) {
        delete[] v;
        int size_v = vector_.getNr_elem();
        v = new double [size_v];
        for (int i=1; i<= size_v; i++)
            v[i] = vector_.v[i];
    }

///operatorii friend supraincarcare: <<, >>, +, -, +=, ==, !=


    ///supraincarcare operator <<
    friend ostream &operator<<(ostream& os, Vector& vector);

    ///supraincarcare operator >>
    friend istream &operator >> (istream &is, Vector &vector);

    ///supraincarcare operator +
    friend Vector operator + (Vector& vector1, Vector& vector2);


    ///supraincarcare operator -
    friend Vector operator - (Vector& vector1, Vector& vector2);

    ///operatori comparare - nu friend

    void operator += (Vector& vector1) {
        if (Nr_elem == vector1.Nr_elem) {
            for (int i = 0; i< vector1.Nr_elem; i++)
                v[i] += vector1.v[i];

        }
    }

    void operator -= (Vector& vector1) {
        if (Nr_elem == vector1.Nr_elem) {
            for (int i = 0; i< vector1.Nr_elem; i++)
                v[i] -= vector1.v[i];

        }
    }

    bool operator == (Vector &alt_vector){
        if (Nr_elem == alt_vector.Nr_elem) return true;
        else return false;
    }

    bool operator != (Vector &alt_vector){
        if (Nr_elem == alt_vector.Nr_elem)
            return true;
        else return false;
    }


///functia friend lenght
    friend int lenght ();

///metoda pentru citirea a n obiecte
    void citire (){
        int n;
        cout << "numarul de obiecte care vor fi cititte este";
        cin >> n;
        for (int i=0; i<n; i++) {
            cin >> Nr_elem;
            for (int j = 1; j <= Nr_elem; j++)
                cin >> v[j];
        }

    }

///metoda pentru afisare
    void afisare(){
        cout << "numarul de obiecte care vor fi afisate este ";
        cout << Nr_elem;
        cout << "vectorul este: ";
        for (int j = 0; j < Nr_elem; j++)
            cout << v[j];
    }

    double maximul (){
        double max = 0;
        for (int i = 0; i<Nr_elem; i++)
            if (max < v[i])
                max = v[i];
        return max;
    }

};


ostream &operator<<(ostream &os, Vector &vector) {
    if (!vector.v) {
        os << "Not initialized\n";
        return os;
    }

    //os << vector.Nr_elem << '\n';

    for(int i = 0; i < vector.Nr_elem; i++)
        os << vector.v[i] << " ";

    return os;
}

istream &operator >> (istream &is, Vector &vector) {
    int nr_elem, x;
    cout << endl << "Nr. elemente:";
    is >> nr_elem;
    vector.Nr_elem = nr_elem;

    cout << "Elementele:";
    for (int i=0; i < nr_elem; i++) {
        is >> x;
        vector.v[i] = x;
    }

    return is;
}

Vector operator + (Vector& vector1, Vector& vector2) {
    Vector suma(0, vector1.getNr_elem());
    //Vector suma;
    if (vector1.Nr_elem == vector2.Nr_elem) {
        suma.Nr_elem = vector1.Nr_elem;
        for (int i = 0; i < vector1.Nr_elem; i++)
            suma.v[i] = vector1.v[i] + vector2.v[i];

    }
    else if (vector1.Nr_elem != vector2.Nr_elem)
        cout << "EROARE: vectorii cititi nu au acelasi numaru de elemente.  ";

    return suma;
}

Vector operator - (Vector& vector1, Vector& vector2) {
    Vector dif;
    if (vector1.Nr_elem == vector2.Nr_elem) {
        dif.Nr_elem = vector1.Nr_elem;
        for (int i = 0; i< vector2.Nr_elem; i++)
            dif.v[i] = vector1.v[i] - vector2.v[i];

    }
    return dif;
}


int lenght (){
    Vector x;
    return x.getNr_elem();
}

int main(){

    //instanta vectorului de tip vector<Vec>
    vector<Vector> vec;

    cout << endl;
    cout << "Programul curent poate efectua urmatoarele comenzi:"<<endl;
    cout << "0. Calculeaza suma element cu element a N vectori cititi." <<endl;
    cout << "1. Calculeaza elementul maxim din N vectori cititi." << endl;


    int R;
    cout << endl <<"Introdu numarul vectorilor cititi:";
    cin >> R;


    ///citirea vectorilor///
    for (int i=0; i < R; i++) {
        Vector v1;
        cout << endl;
        cout << "Se citeste vectorul " << i+1 << "...";
        cin >> v1;
        vec.push_back(v1);
    }

    cout << endl;

    Vector suma = vec[0]; //obiectul va retine suma

    //calculul pt suma
    for (int i = 1; i < R; i++)
        suma = suma + vec[i];


    cout << "Suma vectorilor element cu element este: ";
    cout << suma << "." << endl;

    double maxxim = 0;
    for (int i = 0; i < R; i++)
        if(maxxim < vec[i].maximul())
            maxxim = vec[i].maximul();

    cout << "Elemntul maxim din vectorii cititi este: ";
    cout << maxxim << "." << endl;


    return 0;
}
