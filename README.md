# A Hadamard matrix of order 7516 and constructions at 14556 and 16012

**Status: version 0.1.0 admitted November 26, 2026.** Cite the [version DOI](https://doi.org/10.5281/zenodo.24549453) for [release v0.1.0](https://github.com/jeff-kline/hadamard-orders-7516-14556-16012/releases/tag/v0.1.0). The [concept DOI](https://doi.org/10.5281/zenodo.24549452) follows the latest version. Admission records the project’s review and archive checks. Independent expert peer review remains outstanding. [Admission record](ADMISSION.md)

[Paper PDF](paper/main.pdf) · [LaTeX source](paper/main.tex) · [Certificates and reproduction instructions](evidence/CERTIFICATES.md)

We construct a real Hadamard matrix of order **7516**, an order listed as open in the November 3 survey of Egan, Kotsireas, London and Ó Catháin. Replacing two blocks in Seberry and Yamada’s array gives a weighing matrix of order 1880 and weight 1878. Our November 24 transfer theorem takes it to order 7516. A quaternion extension gives order **14556**, half the order of a known construction at the same odd part. For **16012** we give an explicit matrix covered by our earlier Golay corollary. Every row inner product has been checked in all three matrices. [Survey, Table 5](https://arxiv.org/html/2610.27175v2#S4.T5) · [Our transfer theorem](https://doi.org/10.5281/zenodo.24519197)

## What is new

Seberry and Yamada constructed eight full sign blocks. Two of them have the form $I-A$ and $I+A$. Replacing both by $A$ preserves commutation and reduces the sum of their squares by exactly $2I$. Gysin and Seberry had previously constructed weighing matrices with this deficit from binary Golay pairs. [Seberry and Yamada](https://documents.uow.edu.au/~jennie/WEBPDF/175_1992.pdf) · [Gysin and Seberry, Theorem 7](https://ajc.maths.uq.edu.au/pdf/12/ocr-ajc-v12-p157.pdf#page=6)

- **7516.** The two-block substitution takes a symmetric conference matrix of order $n+1$ and four commuting symmetric sign matrices of order $n$ with squared sum $4nI$ to a real weighing matrix of order $16n+8$ and weight $16n+6$. At $n=117$, this gives the required weighing matrix of order 1880 and weight 1878. [Matrix and certificate](evidence/CERTIFICATES.md#regenerate-order-7516)
- **14556.** The extended construction admits a skew conference core and four coefficient matrices that together form a Hadamard matrix in quaternion block form. A skew Paley core of order 227 and a Paley matrix of order 908 give the weighing matrix of order 3640 and weight 3638. The transfer applies at the prime 3637. [Matrix and certificate](evidence/CERTIFICATES.md#regenerate-order-14556)
- **16012.** A binary Golay pair of length 1000 gives a weighing matrix of order 4004 and weight 4002 by the published Golay construction. The transfer at the prime 4001 gives the third certified matrix. [Matrix and certificate](evidence/CERTIFICATES.md#regenerate-order-16012)

Of the 120 orders on Kumar’s pinned frontier, these two conference-core constructions reach exactly **7516**. Only 7516 and 8860 pass the output-order and prime tests. At 8860 each row of the required core would contain 137 signs, whose sum cannot be zero. [Reproduce the frontier screen](evidence/FRONTIER-SCREEN.md)

## Four further orders

| Ordinary order | Evidence |
|---:|---|
| **30068** | Miyamoto’s theorem applied to 7516 at the prime 7517. |
| **58228** | Miyamoto’s theorem applied to 14556 at the prime 14557. |
| **64012** | The Golay construction at length 4000 and the prime 16001. |
| **80092** | The skew-core construction uses Karoui’s order-1252 matrix and the primes 5003 and 20021. The input checker verifies skewness and all 625 summed correlation values of Karoui’s two sets. |

These four orders follow by theorem. [Miyamoto](https://www.sciencedirect.com/science/article/pii/0097316591900085) · [Karoui’s skew matrix](https://arxiv.org/abs/2602.16089) · [Reproduce the input checks](evidence/CERTIFICATES.md#the-theorem-consequences)

## Earlier work

Kumar identified 7516 as a target and supplied the symmetric conference matrix of order 118, crediting J. Y. Z. Ho with its earlier existence. Yamada’s circulants from the prime 233 supply the remaining input for the first construction. Gysin and Seberry’s Table 6 has a blank construction cell for the weighing matrix used here. [Kumar’s frontier](https://github.com/vatskishan03/Hadamard/blob/d885022144ba6bf4efa8315e14871a3736947527/FRONTIER.md#L208) · [Kumar’s historical comparison](https://generalised.si/research/skew-symmetric-hadamard) · [Gysin and Seberry, Table 6](https://documents.uow.edu.au/~jennie/WEBPDF/1995_05.pdf#page=15)

At odd part 3639, a composition of earlier constructions gives 29112. At odd part 4003, Craigen, Holzmann and Kharaghani’s Corollary 16 gives 32024. The matrices at 14556 and 16012 halve these respective benchmarks. The 2006 handbook entry for 4003 and the detailed hypotheses in Lou, Xia and Xia’s 2019 T-matrix paper remain unverified. [Seberry and Yamada, Corollary 29](https://documents.uow.edu.au/~jennie/WEBPDF/139_1990.pdf) · [Historical product rules](https://www.math74.com/Hadamard/notation) · [Craigen, Holzmann and Kharaghani](https://doi.org/10.1016/S0012-365X(01)00162-5) · [Handbook, Table 1.53 preview](https://books.google.com/books?id=S9FA9rq1BgoC&pg=PA278) · [Lou, Xia and Xia](https://doi.org/10.17654/DM021020163)

Our earlier Golay corollary also covers 64012. The dated comparison found no earlier construction for 7516. Historical priority for the other six orders remains open, including priority before our transfer theorem at 16012 and 64012. [Prior-art review](evidence/PRIOR-WORK.md)

## Check the matrices

| Order | Compressed sign matrix | Distinct row pairs checked | Distance for every pair |
|---:|---|---:|---:|
| 7516 | [Download](evidence/order7516.packed.gz) | 28,241,370 | 3758 |
| 14556 | [Download](evidence/order14556.packed.gz) | 105,931,290 | 7278 |
| 16012 | [Download](evidence/order16012.packed.gz) | 128,184,066 | 8006 |

A second construction at order 7516 replaces the order-117 circulants with quaternion blocks from the Paley matrix at 467. The instructions reproduce its distinct file digest and verify its complete Gram matrix. Equivalence to the first matrix remains undetermined. [All verification commands](evidence/CERTIFICATES.md)

From the repository root, run `make verify` to check the stored matrices and inputs, and `make paper` to rebuild the PDF. The input checks require Node.js. [Dependencies and verification](VERIFICATION.md)

## Release and reuse

The [audit record](AUDIT.md) gives the mathematical and numerical checks and the remaining priority questions. The [verification record](VERIFICATION.md) describes how to reproduce the release. Original material is distributed under [GPL-3.0-only](LICENSE). The conference seed carries its upstream [Apache license and attribution](THIRD-PARTY.md). [Citation metadata](CITATION.cff) · [Correction policy](CORRECTIONS.md)

## Role of AI

AI assisted the derivations, the computer verification, the literature search and the exposition under the author’s direction. The supporting records document separate AI checks of the block identities and the matrix certificates. Independent expert peer review remains outstanding.
