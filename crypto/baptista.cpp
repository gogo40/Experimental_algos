/*

Autor: Péricles Lopes Machado
Encriptador usando teoria do caos (Algoritmo de Baptista)

References:

Baptista, M.S.,  Cryptography with chaos, 23 March 1998, Physics Letters A 240, pp 50-54 

*/

#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

double random(double a, double b) {
    double r = double(rand()) / RAND_MAX;
    return a + r * (b - a);
}

int nextCipher(double& Xo, double Xmin, double eps, double b, char c, int No, double eta) {
    double X = Xo; 
    int n = 0;

    while (true) {
        char s = static_cast<char>((X - Xmin)/eps);
        double k = random(0, 1);
        if (s == c and n >= No and k >= eta) {
            Xo = X;
            return n;
        }
        ++n;
        X = b * X * (1 - X);
    }
}

char nextChar(double& Xo, double Xmin, double eps, double b, int n) {
    double X = Xo;
    
    while (n > 0) {
        X = b * X * (1 - X);
        --n;
    }

    Xo = X;

    return static_cast<char>((X-Xmin)/eps);
}

void encrypt(vector<int>& msg, const string& s, double Xo, double Xmin, double eps, double b, int No, double eta) {
    for (int i = 0; i < s.size(); ++i) {
        msg.push_back(nextCipher(Xo, Xmin, eps, b, s[i], No, eta));
    }
}

void uncrypt(string& s, const vector<int>& msg, double Xo, double Xmin, double eps, double b) {
    for (int i = 0; i < msg.size(); ++i) {
        s+=nextChar(Xo, Xmin, eps, b, msg[i]);
    }
}

int main()
{
    int mode;
    double Xo, Xmin, eps, b;
    string in;
    vector<int> msg;
    int No;
    double eta;

    printf("Modo (1 para encriptar, 2 para desencriptar)?\n");
    cin >> mode;
    
    printf("Xo?\n");
    cin >> Xo;

    printf("Xmin?\n");
    cin >> Xmin;

    printf("eps?\n");
    cin >> eps;

    printf("b?\n");
    cin >> b;
    
    if (mode == 1) {
        printf("No?\n");
        cin >> No;

        printf("Eta?\n");
        cin >> eta;

        printf("Texto?\n");
        scanf("\n");
        getline(cin, in);

        cout<<"Texto lido = <"<<in<<">\n";

        encrypt(msg, in, Xo, Xmin, eps, b, No, eta);
        
        printf("Texto cifrado:\n");
        
        cout <<"____________________"<<endl;
        cout << "Tamanho = " << msg.size() << endl;
        for (int i = 0; i < msg.size(); ++i) {
            cout << msg[i] << " ";
        }
        cout << endl;
        cout <<"____________________"<<endl;
    } else {
        int N;
        printf("Tamanho?\n");
        cin >> N;

        printf("Mensagem?\n");
        for (int i = 0; i < N; ++i) {
            int x;
            cin >> x;
            msg.push_back(x);
        }

        in = "";
        uncrypt(in, msg, Xo, Xmin, eps, b);

        printf("Texto desencriptado:\n");
        cout <<"____________________"<<endl;
        cout << in << endl;
        cout <<"____________________"<<endl;
    }

    printf("Aperte enter para sair...\n");
    scanf("%*[^\n]");
    return 0;
}


