LL Solve() {
	// if ( n < M ) ERROR
	LL r = int( sqrt( (double)n ) ) ;
	while ( (r+1) * (r+1) <= n ) r ++ ;
	// assert r*r <= n and (r+1)**2 > n

	list<LL> V ;
	for ( int i = 1 ; i <= r ; i ++ ) V.push_back( (LL)(n / i) ) ;
	for ( int i = int(n/r) - 1 ; i >= 1 ;i -- ) V.push_back( (LL)i ) ;
	for ( int i = 0 ; i < M ; i ++ ) _INV[i] = INV(i) ;

	Factorial[0] = 1 ;
	for ( auto x : V ) S[x] = x ;
	for ( auto x : V ) F[x] = x ;

	for ( int i = 1 ; i <= M-1 ; i ++ ) Factorial[i] = (Factorial[i-1] * (LL)i) % M ;
	for ( auto x : V )
		S[x] = x - 1LL - (LL)(x / M) ;
	for ( auto x : V )
		if ( x % M == 0 )
			F[x] = POW( Factorial[M-1] , (LL)(x / M) ) ;
		else
			F[x] = (POW(Factorial[M-1] , (LL)(x / M)) * Factorial[x % M]) % M ;

	for ( LL p = 2 ; p <= r ; p ++ )
		if ( S[p] > S[p-1] && p != M ) {
			LL sp = S[p-1] ;
			LL fp = F[p-1] ;
			LL p2 = p * p ;
			for ( auto v : V ) {
				if ( v < p2 ) break ;
				S[v] -= (S[v/p] - sp) ;
				F[v] = F[v] * _INV[ POW((LL)p , (S[v/p] - sp) % (M-1)) * F[v/p] * _INV[fp % M] % M ] % M ;
			}
		}
	return F[n] ;
}
