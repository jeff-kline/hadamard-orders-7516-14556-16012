# Screening the conference-core constructions

Kumar's pinned frontier contains 120 ordinary orders from 2396 through 11996, including 83 below 10000. Of these, 24 have the form $h=64n+28$ with positive integer $n$, including 17 below 10000. The outer transfer also requires $q=16n+5$ prime. Its condition $q\equiv1\pmod4$ is automatic here. Only two rows pass the order and prime tests. [Kumar's pinned frontier](https://github.com/vatskishan03/Hadamard/blob/d885022144ba6bf4efa8315e14871a3736947527/FRONTIER.md)

| $h$ | Core order $n$ | Outer prime $q$ | Conference-core test |
|---:|---:|---:|---|
| 7516 | 117 | 1877 | Kumar's symmetric conference matrix of order 118 supplies the core. |
| 8860 | 138 | 2213 | An order-138 core cannot have zero row sums, since every row contains 137 signs. |

For $n=138$, the would-be source conference matrix has order $n+1=139$. Any two distinct rows of such a matrix have 137 common nonzero positions, so their inner product is odd. This obstruction applies to either symmetry type. For the symmetric theorem, a normalized symmetric core also requires $n\equiv1\pmod4$ when $n>1$. Each row of the core has $(n-1)/2$ minus signs. In comparing rows $i$ and $j$, discard columns $i$ and $j$. Symmetry ensures the two truncated rows still have the same number of minus signs, so their disagreement count is even. The core Gram prescribes inner product $-1$ on their $n-2$ common sign positions, which requires $(n-1)/2$ disagreements.

The symmetric theorem also requires four pairwise commuting symmetric sign matrices $B_i$ of order $n$ with $\sum_i B_i^2=4nI_n$. The quaternion theorem allows a symmetric or skew core with zero diagonal, signs elsewhere, zero row and column sums and Gram $nI_n-J_n$. It requires an order-$4n$ Hadamard matrix of the specified quaternion block form. The Paley supplier used in the paper obtains that block form when $4n-1$ is a prime power. The numerical screen uses the conditions common to both theorems. The explicit order-7516 constructions supply the remaining inputs. [Theorems and constructions](../paper/main.pdf) · [Certificate commands](CERTIFICATES.md)

## Reproduce the count

Download the pinned public frontier and verify its file digest before parsing the numeric rows. The parser checks that each row's second column is a quarter of its first and that the first column is strictly increasing.

```sh
work=$(mktemp -d)
curl -fLsS https://raw.githubusercontent.com/vatskishan03/Hadamard/d885022144ba6bf4efa8315e14871a3736947527/FRONTIER.md \
  -o "$work/FRONTIER.md"
printf '%s  %s\n' e67e681689e3a02a3426d8c70800244bb7e2b6eb0f024987fa7ca0ff63f0e9bd "$work/FRONTIER.md" |
  shasum -a 256 -c &&
node - "$work/FRONTIER.md" <<'JS'
const assert = require('node:assert/strict');
const fs = require('node:fs');

const frontier = fs.readFileSync(process.argv[2], 'utf8');
const orders = [];
for (const [, first, second] of frontier.matchAll(/^\|\s*(\d+)\s*\|\s*(\d+)\s*\|/gm)) {
    const order = Number(first);
    assert.equal(order, 4 * Number(second));
    assert(order > (orders.at(-1) ?? 0));
    orders.push(order);
}

function isPrime(q) {
    if (q < 2) return false;
    for (let d = 2; d * d <= q; ++d) {
        if (q % d === 0) return false;
    }
    return true;
}

const below10000 = orders.filter(order => order < 10000);
const matching = orders.filter(order => order > 28 && order % 64 === 28);
const primeRows = matching.map(order => {
    const n = (order - 28) / 64;
    return [order, n, 16 * n + 5];
}).filter(([, , q]) => isPrime(q));
const coreRows = primeRows.filter(([, n]) => n % 2 === 1);

assert.deepEqual([orders.length, orders[0], orders.at(-1)], [120, 2396, 11996]);
assert.equal(below10000.length, 83);
assert.equal(matching.length, 24);
assert.equal(matching.filter(order => order < 10000).length, 17);
assert.deepEqual(primeRows, [[7516, 117, 1877], [8860, 138, 2213]]);
assert.deepEqual(coreRows, [[7516, 117, 1877]]);
console.log('Prime rows [order, n, q]:', primeRows);
console.log('Prime rows with odd core order:', coreRows);
JS
```
