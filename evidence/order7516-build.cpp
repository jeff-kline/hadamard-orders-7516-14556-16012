// Standalone packed generator. Compile with c++ -std=c++17 -O3.
#include <array>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>
using Word = std::vector<int>;
using Pair = std::array<Word,2>;
// Defaults reproduce the certified order-7516 witness.
#ifndef TRANSFER_PRIME
#define TRANSFER_PRIME 1877
#endif
#ifndef FIELD_RADICAND
#define FIELD_RADICAND 3
#endif
constexpr int q=TRANSFER_PRIME, w=q+3, n=(q+1)/2, t=q+2, order=4*t, bytes=(order+7)/8;
void require(bool pass,const char *why) { if (!pass) throw std::runtime_error(why); }
struct Block { int a,b,c,d; };
constexpr Block I{1,0,0,1}, R{0,-1,1,0}, F{1,1,1,-1};
Block operator+(Block x,Block y) { return {x.a+y.a,x.b+y.b,x.c+y.c,x.d+y.d}; }
Block operator*(int s,Block x) { return {s*x.a,s*x.b,s*x.c,s*x.d}; }
Block operator*(Block x,Block y) {
    return {x.a*y.a+x.b*y.c,x.a*y.b+x.b*y.d,x.c*y.a+x.d*y.c,x.c*y.b+x.d*y.d};
}
Block transpose(Block x) { return {x.a,x.c,x.b,x.d}; }
Block half(Block x) {
    require(!(x.a%2 || x.b%2 || x.c%2 || x.d%2),"nonintegral block");
    return {x.a/2,x.b/2,x.c/2,x.d/2};
}
std::vector<Block> conference(const char *path) {
    // Check the input directly as a ternary Gram before compressing it.
    std::ifstream in(path);
    std::vector<std::string> lines(w);
    constexpr int ww=(w+63)/64;
    using Mask=std::array<uint64_t,ww>;
    std::vector<Mask> nonzero(w),negative(w);
    for (int i=0;i<w;++i) {
        require(static_cast<bool>(std::getline(in,lines[i])) && lines[i].size()==w,"weighing row length");
        for (int j=0;j<w;++j) {
            char ch=lines[i][j]; require(ch=='0' || ch=='+' || ch=='-',"weighing alphabet");
            uint64_t bit=UINT64_C(1)<<(j%64);
            if (ch!='0') nonzero[i][j/64]|=bit;
            if (ch=='-') negative[i][j/64]|=bit;
        }
        for (int k=0;k<=i;++k) {
            int product=0;
            for (int a=0;a<ww;++a) {
                uint64_t common=nonzero[i][a]&nonzero[k][a];
                uint64_t diff=common&(negative[i][a]^negative[k][a]);
                product+=__builtin_popcountll(common)-2*__builtin_popcountll(diff);
            }
            require(product==(i==k ? q+1 : 0),"weighing Gram");
        }
    }
    require(in.peek()==std::ifstream::traits_type::eof() && !in.bad(),"trailing weighing data");
    std::cout<<"W("<<w<<','<<q+1<<") exact full Gram passed\n";
    auto gs=[&](int i,int j) { char v=lines[i][j]; return v=='0' ? 0 : (v=='+' ? 1 : -1); };
    using Indices=std::array<int,2>;
    std::map<Indices,int> group;
    std::vector<Indices> rows,cols;
    std::vector<int> uses(w);
    for (int r=0;r<w;++r) {
        Indices holes{};
        int count=0;
        for (int c=0;c<w;++c) if (gs(r,c)==0) {
            require(count<2,"too many holes"); holes[count++]=c;
        }
        require(count==2,"too few holes");
        auto it=group.find(holes);
        if (it==group.end()) {
            group[holes]=static_cast<int>(rows.size());
            rows.push_back({r,-1}); cols.push_back(holes);
            for (int c:holes) require(++uses[c]==1,"reused column");
        } else {
            int &second=rows[it->second][1];
            require(second==-1,"more than two rows per hole pair"); second=r;
        }
    }
    require(rows.size()==n+1,"incorrect conference size");
    for (auto r:rows) require(r[1]>=0,"unpaired row");
    auto cell=[&](int i,int j) {
        auto r=rows[i],c=cols[j];
        return half(Block{gs(r[0],c[0]),gs(r[0],c[1]),gs(r[1],c[0]),gs(r[1],c[1])}*F);
    };
    std::vector<Block> core(n*n),left(n),right(n);
    for (int i=0;i<n;++i) { left[i]=transpose(cell(i,n)); right[i]=transpose(cell(n,i)); }
    for (int i=0;i<n;++i) for (int j=0;j<n;++j) core[i*n+j]=left[i]*cell(i,j)*right[j];
    return core;
}
struct Field { int x,y; };
Field multiply(Field a,Field b) {
    return {(a.x*b.x+FIELD_RADICAND*a.y*b.y)%q,(a.x*b.y+a.y*b.x)%q};
}
Field power(Field a,int k) {
    Field p{1,0};
    for (;k;k/=2) { if(k%2) p=multiply(p,a); a=multiply(a,a); }
    return p;
}
Pair yamada() {
    Word chi(q,-1); chi[0]=0;
    for (int x=1;x<q;++x) chi[x*x%q]=1;
    const Field generator{4,1}, step=power(generator,4);
    Field beta=power(generator,n),alpha{1,0}; Pair pair;
    for (int k=0;k<n;++k) {
        pair[0].push_back(chi[2*beta.x%q]); pair[1].push_back(chi[2*alpha.x%q]);
        beta=multiply(beta,step); alpha=multiply(alpha,step);
    }
    return pair;
}
int main(int argc,char **argv) {
    if (argc!=3) { std::cerr<<"usage: order7516-build weighing.txt output.packed\n"; return 2; }
    const auto core=conference(argv[1]); const auto mn=yamada();
    std::vector<uint8_t> packed(static_cast<size_t>(order)*bytes,0);
    uint64_t count=0,negative=0;
    auto write_cell=[&](int r,int c,Block z) {
        Block h=z*F;
        std::array<int,4> signs{h.a,h.b,h.c,h.d};
        for (int k=0;k<4;++k) {
            int x=signs[k]; require(x==1 || x==-1,"non-sign in final matrix");
            if (x<0) {
                const int col=2*c+k%2;
                packed[static_cast<size_t>(2*r+k/2)*bytes+col/8]|=0x80u>>(col%8);
                ++negative;
            }
        }
        count+=4;
    };
    for (int r=0;r<t;++r) for (int c=0;c<t;++c) {
        Block x,y;
        if (r==0) { x=I; y=c==0 ? I : R; }
        else if (c==0) { x=-1*I; y=-1*R; }
        else {
            int i=(r-1)%n,j=(c-1)%n,shift=(j-i+n)%n;
            int p=(r-1)/n==(c-1)/n ? 1 : -1;
            int a=p*mn[0][shift]+(i==j),b=p*mn[1][shift];
            x=half((a+b)*I+(a-b)*R);
            y=i==j ? p*I : core[i*n+j];
        }
        Block twisted=half(transpose(I+R)*y*(I+R));
        write_cell(r,c,x); write_cell(r,t+c,y);
        write_cell(t+c,r,transpose(twisted)); write_cell(t+c,t+r,-1*transpose(x));
    }
    require(count==static_cast<uint64_t>(order)*order,"wrong number of sign entries");
    std::ofstream out(argv[2],std::ios::binary); out.exceptions(std::ios::badbit|std::ios::failbit);
    out.write(reinterpret_cast<const char*>(packed.data()),packed.size()); out.close();
    std::cout<<"order="<<order<<" sign_entries="<<count<<" negative="<<negative
             <<" positive="<<count-negative<<" bytes="<<packed.size()<<'\n';
}
