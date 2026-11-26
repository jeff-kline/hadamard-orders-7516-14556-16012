# Matrix certificates

The three compressed files contain row-major binary sign matrices. Each row starts on a byte boundary and has no header. From the most significant bit to the least significant, a set bit denotes −1 and a clear bit denotes +1. Each row ends with four zero padding bits. The verifiers check the length and padding before computing every distinct row-pair distance. Rows of order $h$ have squared norm $h$, and distinct rows at distance $h/2$ have inner product zero.

| Order | Bytes per row | Uncompressed SHA-256 | Packed file |
|---:|---:|---|---|
| 7516 | 940 | `571809922d530728cdebee7a36de6a8a82434517ac64010dd7cce5f97903423d` | [order7516.packed.gz](order7516.packed.gz) |
| 14556 | 1820 | `096f99567ff50648acbd3ad4ec11af496d52d5a3ffed897e21e9ee89430fbc0d` | [order14556.packed.gz](order14556.packed.gz) |
| 16012 | 2002 | `36e7d11265ad137e2a8ef544adb656d525284c553c03e1b22283671ead272004` | [order16012.packed.gz](order16012.packed.gz) |

## Check the three stored matrices

Run the code blocks from this evidence directory in the same shell. Use a C++17 compiler supporting the GCC/Clang population-count intrinsic. The check runs on one thread. If supported, adding `-march=native` to the compiler command may speed up the population counts.

```sh
work=$(mktemp -d)
gzip -dc order7516.packed.gz > "$work/order7516.packed"
gzip -dc order14556.packed.gz > "$work/order14556.packed"
gzip -dc order16012.packed.gz > "$work/order16012.packed"
printf '%s  %s\n' \
  571809922d530728cdebee7a36de6a8a82434517ac64010dd7cce5f97903423d "$work/order7516.packed" \
  096f99567ff50648acbd3ad4ec11af496d52d5a3ffed897e21e9ee89430fbc0d "$work/order14556.packed" \
  36e7d11265ad137e2a8ef544adb656d525284c553c03e1b22283671ead272004 "$work/order16012.packed" |
  shasum -a 256 -c
c++ -std=c++17 -O3 order7516-verify.cpp -o "$work/verify7516"
c++ -std=c++17 -O3 -DHADAMARD_ORDER=14556 order7516-verify.cpp -o "$work/verify14556"
c++ -std=c++17 -O3 order16012-verify.cpp -o "$work/verify16012"
"$work/verify7516" "$work/order7516.packed"
"$work/verify14556" "$work/order14556.packed"
"$work/verify16012" "$work/order16012.packed"
```

The verifier output is as follows. [Shared order 7516 and 14556 verifier source](order7516-verify.cpp) · [Order 16012 verifier source](order16012-verify.cpp)

```text
order=7516 negative=28241370 diagonal=7516 unordered_distinct_row_pairs=28241370 distance=3758 off_diagonal_gram=0
order=14556 negative=105931290 diagonal=14556 unordered_distinct_row_pairs=105931290 distance=7278 off_diagonal_gram=0
order=16012 negative=128184066 diagonal=16012 unordered_distinct_row_pairs=128184066 distance=8006 off_diagonal_gram=0
```

## Regenerate order 7516

Kumar's pinned order-118 conference matrix is included as [conference118.txt](conference118.txt). The first builder uses its normalized core and Yamada’s pair from prime 233 to produce the weighing matrix. The second checks the full intermediate Gram and uses the weighing transfer at prime 1877. [Pinned seed](https://github.com/vatskishan03/Hadamard/blob/d885022144ba6bf4efa8315e14871a3736947527/search/data/conference118_5fe566972f21790b.txt) · [Weighing builder](w1880.cpp) · [Hadamard builder](order7516-build.cpp) · [Paper and proof](../paper/main.pdf)

```sh
cp conference118.txt "$work/conference118.txt"
printf '%s  %s\n' \
  5fe566972f21790b2f42bcb0cc6b5f4454c07289d7e7eb414a68795fa28bce12 "$work/conference118.txt" |
  shasum -a 256 -c
c++ -std=c++17 -O3 w1880.cpp -o "$work/w1880"
c++ -std=c++17 -O3 order7516-build.cpp -o "$work/build7516"
"$work/w1880" "$work/conference118.txt" "$work/w1880.txt"
printf '%s  %s\n' \
  5b95f5a4006ebca6cc265265202fa2efc034d03064b3cba4ed645fef0dcca516 "$work/w1880.txt" |
  shasum -a 256 -c
"$work/build7516" "$work/w1880.txt" "$work/regenerated7516.packed"
cmp "$work/order7516.packed" "$work/regenerated7516.packed"
```

## Regenerate order 16012

The builder contains the length-ten Golay pair. It combines three copies by Turyn’s product, forms the weighing input by the one-symbol padding rule and the Goethals–Seidel array, and applies the transfer at prime 4001. [Order 16012 builder](order16012-build.cpp) · [Paper](../paper/main.pdf)

```sh
c++ -std=c++17 -O3 order16012-build.cpp -o "$work/build16012"
"$work/build16012" "$work/regenerated16012.packed"
cmp "$work/order16012.packed" "$work/regenerated16012.packed"
```

Each successful `cmp` exits with status zero and prints nothing.

## Regenerate order 14556

The projective-line generator rearranges the Paley matrix of order 908 into quaternion blocks and combines them with a skew Paley core of order 227. The transfer program checks the full Gram of the resulting weighing matrix and uses the prime 3637 to produce the packed Hadamard matrix. These commands require Node.js and the same C++17 compiler used above. [Quaternion input generator](quaternion-input.mjs) · [Transfer program](order7516-build.cpp)

```sh
node quaternion-input.mjs "$work/w3640.txt"
printf '%s  %s\n' \
  18d05c2e2ee5f7ba90909161239c5744f4ecbaf4d852287a9102eef415d8533a "$work/w3640.txt" |
  shasum -a 256 -c
c++ -std=c++17 -O3 -DTRANSFER_PRIME=3637 -DFIELD_RADICAND=2 order7516-build.cpp -o "$work/build14556"
"$work/build14556" "$work/w3640.txt" "$work/regenerated14556.packed"
cmp "$work/order14556.packed" "$work/regenerated14556.packed"
node conference-core-extension.mjs
```

The last program checks the order-four coefficient identities and the full integer Grams for two smaller weighing matrices, with deliberately incorrect substitutions as controls. [Coefficient checks](conference-core-extension.mjs)

## A second construction at 7516

With Kumar's pinned seed from the order-7516 instructions, the quaternion input at the prime 467 supplies another construction. The verifier checks the second file on its own. Equivalence of the two matrices is undetermined.

```sh
node quaternion-input.mjs "$work/alternate-w1880.txt" "$work/conference118.txt"
"$work/build7516" "$work/alternate-w1880.txt" "$work/alternate7516.packed"
printf '%s  %s\n' \
  482eb09a5ae9145e55ee8a6986da2397df7953eae91005be86c12b0be7498218 "$work/alternate-w1880.txt" \
  92d0ed748cb4073046518a0e1c375b5c8f690b6e814fe36f5e556b77f0078ffa "$work/alternate7516.packed" |
  shasum -a 256 -c
"$work/verify7516" "$work/alternate7516.packed"
```

## The theorem consequences

Miyamoto at the primes 7517 and 14557 gives 30068 and 58228 respectively from the stored matrices at 7516 and 14556. The Golay pair of length 4000 and the prime 16001 give 64012. For 80092, the quaternion construction uses a skew matrix of order 1252 and the primes 5003 and 20021. The following program reconstructs Karoui's two sets in the field of 625 elements. It checks the skewness of the first set and the summed autocorrelation at all 625 shifts. The four final Hadamard orders follow by theorem. [Karoui’s construction](https://arxiv.org/abs/2602.16089) · [Input checker](skew1252-input.mjs)

```sh
node skew1252-input.mjs
```
