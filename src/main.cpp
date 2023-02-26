
#include <iostream>
#include <fstream>

using namespace std;

typedef union
{
    unsigned long int dat;
    unsigned char ary[4];
    struct
    {
        char b1;
        char b2;
        char b3;
        char b4;
    } byte;
} dword;

typedef unsigned long int t_key;

class Hex2Text
{
private:
    string readFrom;
    t_key key;

public:
    Hex2Text(string readFrom, t_key key)
    {
        this->readFrom = readFrom;
        this->key = key;
    }

    bool convert(string writeTo)
    {
        ifstream fin(this->readFrom.c_str(), ios::in);

        if (!fin)
        {
            cout << "Can't open the file:" << this->readFrom;
            return false;
        }

        ofstream fout;
        fout.open(writeTo.c_str(), ios::out | ios::binary | ios::trunc);

        while (!fin.eof())
        {
            dword src;
            fin.read((char *)&src, sizeof(dword));
            src.dat = src.dat ^ this->key;

            streamsize gcount = fin.gcount();
            if (1 <= gcount)
            {
                fout.write(&src.byte.b1, sizeof(char));
            }
            if (2 <= gcount)
            {
                fout.write(&src.byte.b2, sizeof(char));
            }
            if (3 <= gcount)
            {
                fout.write(&src.byte.b3, sizeof(char));
            }
            if (4 <= gcount)
            {
                fout.write(&src.byte.b4, sizeof(char));
            }
        }

        fin.close();
        return true;
    }
};

class Text2Hex
{
private:
    string readFrom;
    t_key key;

public:
    Text2Hex(string readFrom, t_key key)
    {
        this->readFrom = readFrom;
        this->key = key;
    }

    bool convert(string writeTo)
    {
        ifstream fin(this->readFrom.c_str(), ios::in | ios::binary);

        if (!fin)
        {
            cout << "Can't open the file:" << this->readFrom;
            return false;
        }

        ofstream fout;
        fout.open(writeTo.c_str(), ios::out | ios::trunc);

        while (!fin.eof())
        {
            dword src;
            fin.read((char *)&src, sizeof(dword));
            src.dat = src.dat ^ this->key;

            streamsize gcount = fin.gcount();
            if (1 <= gcount)
            {
                fout.write(&src.byte.b1, sizeof(char));
            }
            if (2 <= gcount)
            {
                fout.write(&src.byte.b2, sizeof(char));
            }
            if (3 <= gcount)
            {
                fout.write(&src.byte.b3, sizeof(char));
            }
            if (4 <= gcount)
            {
                fout.write(&src.byte.b4, sizeof(char));
            }
        }

        fin.close();

        return true;
    }
};

t_key create_hash_key(string key)
{
    t_key hash = 0;

    size_t len = key.length();
    for (int i = 0; i < len; i++)
    {
        hash = ((t_key)hash * (t_key)124901413 + (t_key)key[i]);
    }

    return hash;
}

int main(int argc, char *argv[])
{
    t_key hash = create_hash_key(string(argv[1]));

    if (string(argv[2]) == "h2t")
    {
        Hex2Text h2t(string(argv[3]), hash);
        h2t.convert(string(argv[3]) + ".bin");
    }
    else
    {
        Text2Hex t2h(string(argv[3]), hash);
        t2h.convert(string(argv[3]) + ".txt");
    }

    return 0;
}
