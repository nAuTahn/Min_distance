#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define F first
#define S second
typedef long long ll;
typedef pair<ll,ll> pll;

ll N;
//delta=+oo
ll delta = LLONG_MAX;
pll points[200069];

bool cmpy(const pll &a, const pll &b) {
    return a.S < b.S;
}

//square distance
ll dis(pll a, pll b) {
    return (b.F - a.F) * (b.F - a.F) + (b.S - a.S) * (b.S - a.S);
}

ll bruteforce(int l, int r) {
    for(int i = l; i <= r; i++)
        for(int j = i + 1; j <= r; j++)
            delta = min(delta, dis(points[i], points[j]));
    return delta;
}

ll solve(ll l, ll r) {
    if(r - l + 1 <= 3)
        return bruteforce(l, r);

    ll mid = (ll)(l + r) / 2;

    delta = min({delta, solve(l, mid), solve(mid + 1, r)});

    vector <pll> str;
    for(ll i = l; i <= r; i++)
        if(abs(points[i].F - points[mid].F) * abs(points[i].F - points[mid].F) < delta)
            str.pb(points[i]);

    //sort y
    sort(str.begin(), str.end(), cmpy);

    ll siz = str.size();
    for(ll i = 0; i < siz - 1; i++) {
        ll j = i + 1, dy = str[j].S - str[i].S;
        while(j < siz && dy * dy < delta) {
            delta = min(delta, dis(str[i], str[j]));
            j++;
        }
    }
    return delta;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    for(int i = 1; i <= N; i++)
        cin >> points[i].F >> points[i].S;

    sort(points + 1, points + N + 1); //sort x

    cout << fixed << setprecision(9) << sqrt(solve(1, N));
    return 0;
}
