# Prior constructions and the November 25 comparison

| Order | What the comparison supports |
|---:|---|
| 7516 | An explicit matrix at an order listed as open in Egan et al., Table 5, November 3. Version 60 of the Hadamard Matrix Explorer still lists it among its 82 missing orders. The search located no earlier full construction. |
| 14556 | The explicit matrix halves a documented earlier construction at 29112 with the same odd part. Priority remains unresolved. |
| 16012 | An explicit instance of the author's November 24 theorem. The older complex-Golay construction gives 32024 with the same odd part. Priority before November 24 remains unresolved. |
| 30068 and 58228 | Miyamoto's theorem applies immediately to the completed matrices at 7516 and 14556. Historical priority for the outputs remains unresolved. |
| 64012 | A second instance of the November 24 theorem. The older complex-Golay construction gives 128024 at the same odd part. Priority before November 24 remains unresolved. |
| 80092 | The skew-core theorem applies to Karoui's order-1252 seed. An earlier Yamada route would require a skew matrix of order 10012. The search located no such input. Priority remains unresolved. |

## 7516 and 30068

Egan, Kotsireas, London and Ó Catháin list 1879 in the open-order row for 4p. The November version of Math74 lists 7516 directly. Kumar's frozen frontier lists 7516 and identifies two sufficient inputs at 940, a skew Hadamard matrix and a quaternary conference matrix. The release instead uses the symmetric conference matrix of order 118 supplied by Kumar, who credits Ho for earlier existence. Sources reviewed included the three catalogues, Kumar's public construction list, and searches for the full order, its quarter-order, and its required weighing parameters in papers and public code. [Survey, Table 5](https://arxiv.org/html/2610.27175v2#S4.T5) · [Math74, orders 7001–8000](https://www.math74.com/Hadamard/07/index.html) · [Kumar, pinned frontier](https://github.com/vatskishan03/Hadamard/blob/d885022144ba6bf4efa8315e14871a3736947527/FRONTIER.md#L208) · [Kumar's 34 constructions](https://generalised.si/research/hadamard-matrices)

Gysin and Seberry's Table 6 has a blank construction entry at parameter 470, corresponding to a weighing matrix of order 1880 and weight 1878. In their Golay construction the two candidate lengths would be 469 and 467. The binary Golay sum-of-two-squares condition fails for both. The release uses a different pair of blocks in Seberry and Yamada's conference construction. The missing table entry and survey listing bound the historical claim to the sources checked. [Gysin and Seberry, Theorems 6–7 and Table 6](https://documents.uow.edu.au/~jennie/WEBPDF/1995_05.pdf) · [Seberry and Yamada, §8](https://documents.uow.edu.au/~jennie/WEBPDF/175_1992.pdf)

At 30068 the two direct Paley fields would have orders 30067 = 107 × 281 and 15033 = 3 × 5011. Both have two distinct prime factors. The ordinary Miyamoto construction requires precisely an order-7516 matrix and the prime 7517. This gives an existence consequence from our first matrix. Math74's catalogue ends at 10000 and provides no priority comparison at 30068. [Construction rules](https://www.math74.com/Hadamard/notation.html) · [Miyamoto](https://doi.org/10.1016/0097-3165(91)90008-5)

## Other historical routes

The detailed checks give the earlier theorems, missing inputs and source-access limitations, including the unverified Handbook cell at odd part 4003 and the two special T-matrix cases of Lou, Xia and Xia. [14556, 58228 and 80092](PRIOR-14556.md) · [16012 and 64012](PRIOR-16012.md)

## Later work on the weighing input, 25 November 2026

The search used the exact parameters W(1880,1878), the family W(4n,4n−2), the term “near skew” and the citing works returned by OpenAlex for Gysin and Seberry (1995). Their 1998 follow-up gives four sequences of length 66 and hence W(264,262) in Example 8, p. 154. Their generalized cyclotomy also permits a search at composite length 470. Applying it there would require four sequences with the required correlations. I found no published instance at that length. Kharaghani’s family from Bush-type matrices has weight divisible by four, which excludes 1878. [Gysin and Seberry (1998), Example 8](https://combinatorialpress.com/article/jcmcc/Volume%20027/vol-27-paper%2012.pdf#page=12) · [OpenAlex citing records](https://api.openalex.org/works?filter=cites:W794776163) · [Kharaghani](https://doi.org/10.37236/1479)

Two elementary tests narrow the comparison. In a nontrivial tensor product, a defect in one factor contributes at least the order of the other to the total defect. If both factors have a defect, the total is at least the sum of their orders minus one. Thus the only possible factorization at defect two is H(2) times W(940,939), up to order of factors. That input is equivalent to a skew Hadamard matrix of order 940, already identified by Kumar. In the standard construction from two ordinary circulants, applying the Gram identity to the all-ones vector requires integer row sums satisfying x²+y²=1878. Reduction modulo three forces both sums to be multiples of three, whereas nine does not divide 1878. Four-circulant searches, negacyclic arrays and other orthogonal-design substitutions remain possible. This search found no earlier supply of W(1880,1878) in the sources checked. [Gysin and Seberry (1995), Definition 2 and Theorem 6](https://documents.uow.edu.au/~jennie/WEBPDF/1995_05.pdf) · [Two-sequence constructions](https://doi.org/10.1016/S0378-3758(99)00006-3)
