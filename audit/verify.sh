#!/bin/sh
# Run from the release root with a C++17 compiler, Node.js and gzip.
set -eu
scratch=$(mktemp -d)
trap 'rm -rf "$scratch"' EXIT
for order in 7516 14556 16012; do
    gzip -dc "evidence/order$order.packed.gz" > "$scratch/order$order.packed"
    case "$order" in
        16012) source=evidence/order16012-verify.cpp ;;
        *) source=evidence/order7516-verify.cpp ;;
    esac
    "${CXX:-c++}" -O3 -std=c++17 -DHADAMARD_ORDER="$order" "$source" -o "$scratch/verify"
    "$scratch/verify" "$scratch/order$order.packed" >> "$scratch/rows.txt"
done
diff audit/expected-rows.txt "$scratch/rows.txt"
cat "$scratch/rows.txt"
node evidence/conference-core-extension.mjs
node evidence/skew1252-input.mjs
