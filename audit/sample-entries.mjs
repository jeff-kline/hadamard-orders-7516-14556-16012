import fs from 'node:fs';
import path from 'node:path';
import assert from 'node:assert/strict';

const work = process.argv[2];
for (const [name, order] of [
    ['order7516', 7516], ['order14556', 14556],
    ['order16012', 16012], ['alternate7516', 7516],
]) {
    const matrix = fs.readFileSync(path.join(work, name + '.packed'));
    const stride = Math.ceil(order / 8);
    assert.equal(matrix.length, order * stride);
    const signedEntry = (row, col) => 1 - 2 * ((matrix[row * stride + (col >> 3)] >> (7 - (col & 7))) & 1);
    const indices = [0, 1, 22, 23, 24, 25, 47, 48, order >> 1, order - 3, order - 2, order - 1];
    let dotProducts = 0;
    for (const i of indices) {
        for (const j of indices.filter(j => j <= i)) {
            let product = 0;
            for (let col = 0; col < order; ++col) {
                product += signedEntry(i, col) * signedEntry(j, col);
            }
            assert.equal(product, i === j ? order : 0);
            ++dotProducts;
        }
    }
    console.log(`${name}: passed ${dotProducts} independent dense Gram entries`);
}
