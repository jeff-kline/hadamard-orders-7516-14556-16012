# Hadamard matrices of orders 7516, 14556 and 16012

**Release candidate 0.1.0, November 25, 2026.** [Paper PDF](paper/main.pdf) · [LaTeX source](paper/main.tex) · [Certificates and reproduction instructions](evidence/CERTIFICATES.md)

We construct real Hadamard matrices of orders **7516, 14556 and 16012** and verify the inner product of every pair of rows in each stored matrix. All three use the same earlier theorem, which takes a weighing matrix with two zeros per row to a Hadamard matrix. A change to Seberry and Yamada’s array supplies the weighing matrix at 7516. A skew conference core and the quaternion symmetry of a Paley matrix supply it at 14556. A binary Golay pair supplies it at 16012. The 2026 survey of Egan, Kotsireas, London and Ó Catháin lists 7516 as open. Historical priority at 14556 and 16012 remains unresolved. [Weighing-matrix transfer](https://doi.org/10.5281/zenodo.24519197) · [Survey, Table 5](https://arxiv.org/html/2610.27175v2#S4.T5)

## What is new

Seberry and Yamada constructed eight full sign blocks. Two of them have the form $I-A$ and $I+A$. Replacing both by $A$ preserves commutation and reduces the sum of their squares by exactly $2I$. Gysin and Seberry had previously constructed weighing matrices with this deficit from binary Golay pairs. [Seberry and Yamada](https://documents.uow.edu.au/~jennie/WEBPDF/175_1992.pdf) · [Gysin and Seberry, Theorem 7](https://ajc.maths.uq.edu.au/pdf/12/ocr-ajc-v12-p157.pdf#page=6)

- **7516.** The two-block substitution takes a symmetric conference matrix of order $n+1$ and four commuting symmetric sign matrices of order $n$ with squared sum $4nI$ to a real weighing matrix of order $16n+8$ and weight $16n+6$. At $n=117$, this gives the required weighing matrix of order 1880 and weight 1878. [Matrix and certificate](evidence/CERTIFICATES.md#regenerate-order-7516)
- **14556.** The extended construction admits a skew conference core and four coefficient matrices that together form a Hadamard matrix in quaternion block form. A skew Paley core of order 227 and a Paley matrix of order 908 give the weighing matrix of order 3640 and weight 3638. The transfer applies at the prime 3637. [Matrix and certificate](evidence/CERTIFICATES.md#regenerate-order-14556)
- **16012.** A binary Golay pair of length 1000 gives a weighing matrix of order 4004 and weight 4002 by the published Golay construction. The transfer at the prime 4001 gives the third certified matrix. [Matrix and certificate](evidence/CERTIFICATES.md#regenerate-order-16012)

The November 24 Golay corollary already implies 16012. Its explicit matrix and complete row certificate are supplied here.

## Four further orders

| Ordinary order | Evidence |
|---:|---|
| **30068** | Miyamoto’s theorem applied to 7516 at the prime 7517. |
| **58228** | Miyamoto’s theorem applied to 14556 at the prime 14557. |
| **64012** | The Golay construction at length 4000 and the prime 16001. |
| **80092** | The skew-core construction uses Karoui’s order-1252 matrix and the primes 5003 and 20021. The input checker verifies skewness and all 625 summed correlation values of Karoui’s two sets. |

These four orders follow by theorem. Their historical priority remains open. [Miyamoto](https://www.sciencedirect.com/science/article/pii/0097316591900085) · [Karoui’s skew matrix](https://arxiv.org/abs/2602.16089) · [Reproduce the input checks](evidence/CERTIFICATES.md#the-theorem-consequences)

## Earlier work

Kumar identified 7516 as a target and supplied the symmetric conference matrix of order 118, crediting J. Y. Z. Ho with its earlier existence. Yamada’s circulants from the prime 233 supply the remaining input for the first construction. Gysin and Seberry’s Table 6 has a blank construction cell for the weighing matrix used here. [Kumar’s frontier](https://github.com/vatskishan03/Hadamard/blob/d885022144ba6bf4efa8315e14871a3736947527/FRONTIER.md#L208) · [Kumar’s historical comparison](https://generalised.si/research/skew-symmetric-hadamard) · [Gysin and Seberry, Table 6](https://documents.uow.edu.au/~jennie/WEBPDF/1995_05.pdf#page=15)

At odd part 3639, a composition of earlier constructions gives 29112. At odd part 4003, Craigen, Holzmann and Kharaghani’s Corollary 16 gives 32024. The matrices at 14556 and 16012 halve these respective benchmarks. The 2006 handbook entry for 4003 and the detailed hypotheses in Lou, Xia and Xia’s 2019 T-matrix paper remain unverified. [Seberry and Yamada, Corollary 29](https://documents.uow.edu.au/~jennie/WEBPDF/139_1990.pdf) · [Historical product rules](https://www.math74.com/Hadamard/notation) · [Craigen, Holzmann and Kharaghani](https://doi.org/10.1016/S0012-365X(01)00162-5) · [Handbook, Table 1.53 preview](https://books.google.com/books?id=S9FA9rq1BgoC&pg=PA278) · [Lou, Xia and Xia](https://doi.org/10.17654/DM021020163)

The November 24 Golay corollary already implies 16012 and 64012. The older Golay construction also gives 128024 at the odd part of 64012. The renewed search located no earlier construction for 7516, which both the November survey and version 60 of Math74 list as open. The other historical comparisons remain bounded by the sources examined. [Prior-art review](evidence/PRIOR-WORK.md)

## Morning construction record

The original packed files carry Chicago timestamps of **8:13:07 a.m. for 16012**, **8:21:04 a.m. for 7516**, and **9:03:45 a.m. for 14556** on November 25, 2026. Each original matches the archived matrix digest. These times document local possession of the explicit matrices. [Dated record](evidence/CHRONOLOGY.md)

## Check the matrices

| Order | Compressed sign matrix | Distinct row pairs checked | Distance for every pair |
|---:|---|---:|---:|
| 7516 | [Download](evidence/order7516.packed.gz) | 28,241,370 | 3758 |
| 14556 | [Download](evidence/order14556.packed.gz) | 105,931,290 | 7278 |
| 16012 | [Download](evidence/order16012.packed.gz) | 128,184,066 | 8006 |

A second construction at order 7516 replaces the order-117 circulants with quaternion blocks from the Paley matrix at 467. The instructions reproduce its distinct file digest and verify its complete Gram matrix. Equivalence to the first matrix remains undetermined. [All verification commands](evidence/CERTIFICATES.md)

To reproduce the frozen PDF, set the build timestamp and run pdfLaTeX twice. The archive includes a SHA-256 manifest for the manuscript, matrices, input data and checkers.

```sh
cd paper
export SOURCE_DATE_EPOCH=1795622400
export FORCE_SOURCE_DATE=1
export TZ=UTC
pdflatex -halt-on-error -interaction=nonstopmode main.tex
pdflatex -halt-on-error -interaction=nonstopmode main.tex
```

## Release and reuse

The [audit record](AUDIT.md) gives the mathematical and numerical checks and the remaining priority questions. The [verification record](VERIFICATION.md) describes how to reproduce the candidate. Original material is distributed under [GPL-3.0-only](LICENSE). The conference seed carries its upstream [Apache license and attribution](THIRD-PARTY.md). [Citation metadata](CITATION.cff) · [Correction policy](CORRECTIONS.md)

## Role of AI

AI assisted the derivations, the computer verification, the literature search and the exposition under the author’s direction. The supporting records document separate AI checks of the block identities and the matrix certificates. Independent expert peer review remains outstanding.
