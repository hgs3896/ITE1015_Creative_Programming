#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

enum GAME_STATE {BLACKJACK = 21, INPUT_ERROR = -1, EXCEED = 0};

inline int dist ( int pos, int how_far )
{
    return BLACKJACK - ( pos + how_far );
}

int blackjack ( const string * arr, int N )
{
    int sum = 0;
    bool A = false;
    for ( int i = 0; i < N; ++i ) {
        int number;
        try {
            number = stoi ( arr[i] );
            if ( number < 2 || number > 10 ) return INPUT_ERROR;
        } catch ( const invalid_argument& ia ) {
            if ( arr[i] == "J" || arr[i] == "Q" || arr[i] == "K" )
                number = 10;
            else if ( arr[i] == "A" )
                number = 0, A = true;
            else return INPUT_ERROR;
        } catch ( const out_of_range& re ) {
            number = 0;
        }
        sum += number;
    }

    if ( sum > BLACKJACK ) return EXCEED;

    if ( A ) {
        if ( dist ( sum, 1 ) < 0 )
            return EXCEED;
        else if ( dist ( sum, 11 ) < 0 )
            return sum + 1;
        else
            return sum + 11;
    }
    return sum;
}
int main ( void )
{
    while ( true ) {
        string buf;
        cin >> buf;

        int N;
        try {
            N = stoi ( buf );
        } catch ( const invalid_argument& ia ) {
            break;
        }

        if ( N <= 0 )
            break;

        string *arr = new string[N];
        for ( int i = 0; i < N; ++i )
            cin >> arr[i];

        int result = blackjack ( arr, N );
        
        if ( result == BLACKJACK ) {
            cout << "BlackJack" << endl;
		}else if (result == EXCEED) {
			cout << "Exceed" << endl;
		}else if ( 0 < result && result < BLACKJACK ) {
            cout << result << endl;
        }

        delete[] arr;
        arr = nullptr;
		if (result == INPUT_ERROR) break;
    }
    return 0;
}