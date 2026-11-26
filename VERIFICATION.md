# Verifying version 0.1.0

Run the following command from the root of the extracted package. It checks the SHA-256 manifest, compiles the row verifiers and reads all three archived matrices. It also checks the small weighing-matrix controls and Karoui’s order-1252 input. It requires Make, a C++17 compiler with a population-count intrinsic, Node.js, gzip and shasum. The row checks run sequentially on one thread.

```sh
make verify
```

| Order | Unordered pairs of distinct rows | Hamming distance of every pair |
|---:|---:|---:|
| 7516 | 28,241,370 | 3758 |
| 14556 | 105,931,290 | 7278 |
| 16012 | 128,184,066 | 8006 |

In each case the squared row norm equals the order. The distance is half the order for every distinct pair, so the off-diagonal inner products are zero. The verifiers’ exact expected output is in [expected-rows.txt](audit/expected-rows.txt).

To reproduce the matrices from their inputs, run the command blocks in [Matrix certificates](evidence/CERTIFICATES.md) from the evidence directory, in order and in the same shell. They also generate and check the second construction at 7516. After these blocks, the following command checks 78 selected Gram entries per matrix by summing individual signed products.

```sh
node ../audit/sample-entries.mjs "$work"
```

The audit used Apple Clang 21.0.0 and Node.js 24.22.3 on x86-64. The four larger orders in the paper follow from theorems. The [audit record](AUDIT.md) identifies the inputs checked for each consequence.

## Rebuild the paper

From the release root, run the following commands. The Makefile sets the timestamp and runs pdfLaTeX twice. With pdfTeX 1.40.22 (TeX Live 2021), the six-page PDF in the tagged archive has SHA-256 `79f5e7c8bec3063d022b49fd18fe83c5aaa1c7d0ee65a99aaa48a2b2219eddb1`. The reading copy on `main`, which displays the assigned DOI, has SHA-256 `0459a20367eeb7dafc815ae12494afc57f5a8e157731bb43953140de2730ea27`.

```sh
make paper
shasum -a 256 -c MANIFEST.sha256
```

## Permanent archive

Zenodo lists Jeffery Kline as creator and November 26, 2026 (UTC) as the publication date for v0.1.0. The registered resource type is software and the license is GNU GPL v3.0 only. [Zenodo record](https://zenodo.org/records/24549453) · [Tag](https://github.com/jeff-kline/hadamard-orders-7516-14556-16012/tree/v0.1.0)

| Artifact | Bytes | SHA-256 |
|---|---:|---|
| GitHub API tag ZIP, downloaded twice before release, and the published Zenodo file `jeff-kline/hadamard-orders-7516-14556-16012-v0.1.0.zip` | 21,274,545 | `ba17a90ab81c64ab2cbd8170b5fde7eec2b47c8fbc97a7d402c19b7bdeda74d9` |
| Locally generated `local-tag.zip` from two deterministic Git exports | 21,273,505 | `3343e097b82ff2df4f52e6aa6f97e0fcae2cf6168d094bdf8cb2a20e906d2c26` |

The public file matched Zenodo’s MD5 checksum, `35f446a1a0106fe21c3e188a8324c81b`, and a bytewise comparison with the pinned GitHub API tag ZIP. Its internal manifest covers all 34 payload files.
