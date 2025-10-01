#include <iostream>
#include <string>
using namespace std;

bool isVowel(char c)
{
    char d = c;
    if (d >= 'A' && d <= 'Z')
        d = d - 'A' + 'a'; // lowercase
    return (d == 'a' || d == 'e' || d == 'i' || d == 'o' || d == 'u');
}

// Reverse string in-place (user-defined)
void reverseString(string &s)
{
    int i = 0, j = (int)s.size() - 1;
    while (i < j)
    {
        char tmp = s[i]; // tmp untuk nyimpan
        s[i] = s[j];
        s[j] = tmp;
        i++;
        j--;
    }
}

string intToString(int x)
{
    if (x == 0)
        return "0";
    string t = "";
    int n = x;
    while (n > 0)
    {
        int d = n % 10;
        t.push_back(char('0' + d));
        n /= 10;
    }
    // t currently reversed, balik supaya urut normal
    reverseString(t);
    return t;
}

int stringToInt(const string &s)
{
    int res = 0;
    for (size_t i = 0; i < s.size(); ++i)
    {
        res = res * 10 + (s[i] - '0');
    }
    return res;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    char mode;
    if (!(cin >> mode))
        return 0; // kebalikannya
    if (mode == 'E')
    {
        // ENCRYPT
        string word;
        cin >> word; // kata input (no spaces)
        if (word.empty())
        {
            cout << "\n";
            return 0;
        }

        // simpan ASCII dari huruf pertama
        int asciiFirst = (int)word[0];

        // hilangkan vokal, simpan konsonan dalam urutan asli
        string cons = "";
        for (size_t i = 0; i < word.size(); ++i)
        {
            if (!isVowel(word[i]))
                cons.push_back(word[i]);
        }

        // balik semua huruf (user-defined)
        reverseString(cons);
        int m = (int)cons.size();

        // posisi sisip = ceil(m/2)
        int insertPos = (m + 1) / 2;

        // ubah asciiFirst ke string digit secara matematis
        string asciiDigits = intToString(asciiFirst);

        // bangun sandi: cons[0..insertPos-1] + asciiDigits + cons[insertPos..end]
        string result = "";
        if (insertPos > 0)
            result += cons.substr(0, insertPos);
        result += asciiDigits;
        if (insertPos < m)
            result += cons.substr(insertPos);

        cout << result << '\n';
    }
    else if (mode == 'D')
    {
        // DECRYPT (partial reconstruction)
        string pwd;
        cin >> pwd; // sandi (single token)
        if (pwd.empty())
        {
            cout << "\n";
            return 0;
        }

        // Temukan substring digit (ASCII) — asumsikan ada tepat 1 blok digit
        int startDigit = -1, endDigit = -1;
        for (int i = 0; i < (int)pwd.size(); ++i)
        {
            if (pwd[i] >= '0' && pwd[i] <= '9')
            {
                if (startDigit == -1)
                    startDigit = i;
                endDigit = i + 1;
            }
        }
        if (startDigit == -1)
        {
            // Tidak menemukan angka -> tidak valid menurut format mesin
            cout << "Invalid password format (no ASCII digits found)\n";
            return 0;
        }

        string left = pwd.substr(0, startDigit);
        string digits = pwd.substr(startDigit, endDigit - startDigit);
        string right = pwd.substr(endDigit);

        // Concatenate left+right -> ini adalah reversed consonant string
        string revCons = left + right;

        // Balik agar dapat consonant-original dalam urutan semula
        reverseString(revCons);
        string consOriginal = revCons; // konsonan dari kata asli

        // Konversi digits -> ascii int
        int asciiFirst = stringToInt(digits);
        char firstChar = (char)asciiFirst;

        // Best-effort reconstruct:
        // jika consOriginal non-empty dan char pertama sama dengan firstChar -> gunakan consOriginal
        // else prefix firstChar sebelum consOriginal
        string reconstructed;
        if (!consOriginal.empty() && consOriginal[0] == firstChar)
        {
            reconstructed = consOriginal;
        }
        else
        {
            reconstructed = string(1, firstChar) + consOriginal;
        }

        // Output: partial reconstructed original + some info
        cout << reconstructed << '\n';
        // (opsional: tampilkan detail)
        // cout << "Consonants only: " << consOriginal << '\n';
        // cout << "Recovered first char from ASCII: " << firstChar << '\n';
    }
    else
    {
        cerr << "Mode tidak dikenali. Gunakan 'E' untuk encrypt atau 'D' untuk decrypt.\n";
    }

    return 0;
}
