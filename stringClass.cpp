#include <iostream>
using namespace std;

class String
{
private:
    char *str;

public:
    String() // void 생성자
    {
        str = NULL;
    }
    String(const char *mystr) // 생성자
    {
        str = new char[strlen(mystr) + 1];
        strcpy(str, mystr);
    }
    String(const String &ref) // 복사생성자
    {
        str = new char[strlen(ref.str) + 1];
        strcpy(str, ref.str);
    }
    String &operator=(const String &ref) // 대입연산자
    {
        if (str != NULL)
            delete[] str; // str = new char[strlen(mystr) + 1]; 이기에 배열형태로 delete
        str = new char[strlen(ref.str) + 1];
        strcpy(str, ref.str);
        return *this;
    }
    String operator+(String &ref)
    {
        char *newStr = new char[strlen(str) + strlen(ref.str) + 1];
        strcat(newStr, str);
        strcat(newStr, ref.str);
        String ret(newStr); // 생성자 함수 보면 알겠지만, 새로운 메모리를 할당해서 복사하는 방식이야.
        delete[] newStr;    // 따라서, 더이상 newStr이 가리키는 곳은 필요 없어져서 삭제 해야돼.
        return ret;         // 반환형이 참조자 형태일 수가 없지. 얘는 함수가 끝나면 사라지니까.
    }
    String &operator+=(String &ref)
    {
        char *newStr = new char[strlen(str) + strlen(ref.str) + 1];
        strcat(newStr, str);
        strcat(newStr, ref.str);
        if (str != NULL)
            delete[] str;
        str = newStr; // 이제 newStr 필요없으니까 삭제해도 되지 않나? 안돼.
        return *this; // 새로운 메모리 할당을 한후에 값을 복사한게 아니라 지금 대입을 한거기때문에 newStr이 할당한 공간을 삭제하면 str이 가리키는곳도 사라지지.
    }
    bool operator==(String &ref)
    {
        return !strcmp(str, ref.str);
    }
    friend ostream &operator<<(ostream &, const String &);
    friend istream &operator>>(istream &, String &);

    ~String() // 소멸자
    {
        if (str != NULL)
            delete[] str;
    }
};
ostream &operator<<(ostream &os, const String &ref)
{
    os << ref.str;
    return os;
}
istream &operator>>(istream &is, String &ref)
{
    char temp[1000];
    is >> temp;
    ref = String(temp); // ref는 NULL 이라서 대입하기전에 따로 delete 하지 않았음.
    return is;
}

int main()
{
    String str1 = (char *)"I like "; // 문자열을 인자로 받는 생성자
    String str2 = (char *)"string class";
    String str3 = str1 + str2; // operator+, 복사생성자
    cout << str1 << endl;      // operator<<
    cout << str2 << endl;
    cout << str3 << endl;
    str1 += str2;     // operator +=
    if (str1 == str3) // operator ==
        cout << "동일 문자열!" << endl;
    else
        cout << "동일하지 않은 문자열!" << endl;
    String str4; // 보이드 생성자.
    cout << "문자열 입력: ";
    cin >> str4; // operator >>
    cout << "입력한 문자열: " << str4 << endl;
    return 0;
}