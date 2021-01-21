#include "base64.hxx"

using namespace std;

int main(void)
{
    Base64 b;
    string encoded = b.encode("Hello");
    
    cout << encoded << endl;
    cout << b.decode(encoded) << endl;

    return (0);
}