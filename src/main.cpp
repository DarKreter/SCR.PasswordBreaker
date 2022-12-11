#include <iostream>
#include <md5.hpp>

using namespace std;

int main()
{
    cout << "Using OpenSSL version " << SSL_Version() << endl;

    cout << md5("yeah") << endl;

    return 0;
}

// 56609ab6ba04048adc2cbfafbe745e10
// 56609ab6ba04048adc2cbfafbe745e10 - woman
// 29814d7ba6b9db8d5ab57fd57ceb9c1a - yeah
// 29814d7ba6b9db8d5ab57fd57ceb9c1a