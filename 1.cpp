#include <iostream>
using namespace std;

int reverseDigits(int x)
{
    if (x == 0)
        return 0; // khusus jika nol

    int sign = (x < 0) ? -1 : 1; // simpan tanda
    x = x * sign;                // jadikan positif sementara

    int rev = 0;
    while (x > 0)
    {
        rev = rev * 10 + (x % 10); // ambil digit terakhir
        x /= 10;                   // buang digit terakhir
    }
    return rev * sign; // kembalikan tanda asli
}

int main()
{
    int n;
    cin >> n;

    int arr[100]; // asumsi maksimal 100 elemen
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    long long total = 0; // bisa besar, jadi pakai long long

    for (int i = 0; i < n; i++)
    {
        if (i % 2 == 0)
        {
            // indeks genap → dibalik
            arr[i] = reverseDigits(arr[i]);
        }
        // indeks ganjil → tidak diubah
        total += arr[i];
    }

    cout << total << endl;
    return 0;
}
