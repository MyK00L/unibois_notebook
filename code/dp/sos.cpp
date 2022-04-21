// // SOS DP O(N*2^N)
// // F[mask] = sum(A[i]) | i & mask = i
for(int i = 0; i<(1<<N); ++i) F[i] = A[i];
for(int i = 0;i < N; ++i) for(int mask = 0; mask < (1<<N); ++mask){
	if(mask & (1<<i))
		F[mask] += F[mask^(1<<i)];
}


// // mobius function O(N*2^N)
// // same as above but with inverted sign in sum based on parity of 1bits (inclusion-exclusion)
for(int mask = 0; mask < (1 << N); mask++) if(__builtin_popcount(mask) % 2) f[mask] *= -1;
for(int i = 0; i < N; i++) {
	for(int mask = 0; mask < (1 << N); mask++) {
		if((mask & (1 << i)) != 0) {
			f[mask] += f[mask ^ (1 << i)];
		}
	}
}
for(int mask = 0; mask < (1 << N); mask++) if(__builtin_popcount(mask) % 2) f[mask] *= -1;
for(int mask = 0; mask < (1 << N); mask++)  mu[mask] = f[mask];

// // Subset Sum Convolution: take all possible ways to partition set s into two disjoint partitions and sum over product of f on one partition and g on the complement of that partition.
// // O(N*N*2^N)
// Make fhat[][] = {0} and ghat[][] = {0}
for(int mask = 0; mask < (1 << N); mask++) {
	fhat[__builtin_popcount(mask)][mask] = f[mask];
	ghat[__builtin_popcount(mask)][mask] = g[mask];
}
// Apply zeta transform on fhat[][] and ghat[][]
for(int i = 0; i < N; i++) {
	for(int j = 0; j < N; j++) {
		for(int mask = 0; mask < (1 << N); mask++) {
			if((mask & (1 << j)) != 0) {
				fhat[i][mask] += fhat[i][mask ^ (1 << j)];
				ghat[i][mask] += ghat[i][mask ^ (1 << j)];
			}
		}
	}
}
// Do the convolution and store into h[][] = {0}
for(int mask = 0; mask < (1 << N); mask++) {
	for(int i = 0; i < N; i++) {
		for(int j = 0; j <= i; j++) {
			h[i][mask] += fhat[j][mask] * ghat[i - j][mask];
		}
	}
}
// Apply inverse SOS dp on h[][]
for(int i = 0; i < N; i++) {
	for(int j = 0; j < N; j++) {
		for(int mask = 0; mask < (1 << N); mask++) {
			if((mask & (1 << j)) != 0) {
				h[i][mask] -= h[i][mask ^ (1 << j)];
			}
		}
	}
}
for(int mask = 0; mask < (1 << N); mask++)  fog[mask] = h[__builtin_popcount(mask)][mask];

