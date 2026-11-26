// Independent single-threaded verifier of a row-major binary sign matrix.
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>
#ifndef HADAMARD_ORDER
#define HADAMARD_ORDER 7516
#endif
constexpr int order=HADAMARD_ORDER, bytes=(order+7)/8, words=(order+63)/64;
using RowWord=std::uint64_t;
int distance(const RowWord *a,const RowWord *b) {
    int d=0;
    for (int k=0;k<words;++k) d+=__builtin_popcountll(a[k]^b[k]);
    return d;
}
int main(int argc,char **argv) {
    if (argc!=2) { std::cerr<<"usage: order7516-verify input.packed\n"; return 2; }
    std::ifstream in(argv[1],std::ios::binary);
    std::vector<RowWord> matrix(static_cast<size_t>(order)*words,0);
    std::uint64_t negative=0;
    for (int i=0;i<order;++i) {
        RowWord *row=matrix.data()+i*words;
        auto raw=reinterpret_cast<char*>(row);
        if (!in.read(raw,bytes) || (raw[bytes-1]&15)) {
            std::cerr<<"bad row length or nonzero padding at row "<<i<<'\n'; return 1;
        }
        for (int k=0;k<words;++k) negative+=__builtin_popcountll(row[k]);
    }
    if (in.peek()!=std::ifstream::traits_type::eof() || in.bad()) {
        std::cerr<<"unexpected trailing bytes or input error\n"; return 1;
    }
    std::uint64_t pairs=0;
    constexpr int tile=24;
    for (int ib=0;ib<order;ib+=tile) for (int jb=0;jb<=ib;jb+=tile) {
        for (int i=ib;i<std::min(order,ib+tile);++i) {
            const auto a=matrix.data()+i*words;
            for (int j=jb;j<std::min(i,jb+tile);++j) {
                int d=distance(a,matrix.data()+j*words);
                if (d!=order/2) {
                    std::cerr<<"rows="<<i<<','<<j<<" distance="<<d<<" product="<<order-2*d<<'\n'; return 1;
                }
                ++pairs;
            }
        }
    }
    if (pairs!=static_cast<std::uint64_t>(order)*(order-1)/2) return 1;
    std::cout<<"order="<<order<<" negative="<<negative<<" diagonal="<<order
             <<" unordered_distinct_row_pairs="<<pairs<<" distance="<<order/2<<" off_diagonal_gram=0\n";
}
