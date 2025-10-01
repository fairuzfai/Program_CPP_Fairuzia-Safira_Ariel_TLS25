#include <iostream>
using namespace std;

int main()
{
    int waktu;
    cin >> waktu;

    int x = waktu % 103;

    if (x < 20)
        cout << "Hijau\n";
    else if (x < 23)
        cout << "Kuning\n";
    else
        cout << "Merah\n";

    return 0;
}
