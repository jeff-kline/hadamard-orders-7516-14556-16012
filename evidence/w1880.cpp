// Construct and check the real weighing input W(1880,1878).
// Usage: w1880 conference118.txt [output-W.txt]
#include <array>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;
constexpr int prime=233, n=117, block=235, sizeW=1880;
void check(bool valid,const string &why){if(!valid) throw runtime_error(why);}
struct Field {int x,y;};
Field multiply(Field a,Field b){
    return {(a.x*b.x+3*a.y*b.y)%prime,(a.x*b.y+a.y*b.x)%prime};
}
Field power(Field a,int k){
    Field result{1,0};
    while(k){if(k%2)result=multiply(result,a);a=multiply(a,a);k/=2;}
    return result;
}
using Matrix=vector<vector<int>>;
Matrix core(const char* path){
    ifstream in(path);
    vector<string> rows;
    for(string row;in>>row;) rows.push_back(row);
    check(rows.size()==n+1,"conference order");
    for(auto &row:rows) check(row.size()==n+1,"conference row");
    Matrix q(n,vector<int>(n));
    for(int i=0;i<n;i++) for(int j=0;j<n;j++){
        const char entry=rows[i+1][j+1];
        check(entry=='+' || entry=='-' || entry=='0',"core alphabet");
        q[i][j]=entry=='+'?1:entry=='-'?-1:0;
        check((q[i][j]==0)==(i==j),"core holes");
    }
    for(int i=0;i<n;i++){
        int sum=0;
        for(int j=0;j<n;j++){
            check(q[i][j]==q[j][i],"core transpose");
            sum+=q[i][j];
            int dot=0;
            for(int k=0;k<n;k++)dot+=q[i][k]*q[j][k];
            check(dot==(i==j?n:0)-1,"core Gram");
        }
        check(sum==0,"core row sum");
    }
    return q;
}
array<vector<int>,2> yamada(){
    array<int,prime> character; character.fill(-1); character[0]=0;
    for(int x=1;x<prime;x++) character[x*x%prime]=1;
    check(character[3]==-1,"quadratic extension");
    Field generator{3,1}, a=power(generator,n), b{1,0}, step=power(generator,4);
    const int groupOrder=prime*prime-1;
    check(groupOrder==16*9*13*29,"factorization");
    for(auto divisor:{2,3,13,29}){
        Field t=power(generator,groupOrder/divisor);
        check(t.x!=1 || t.y!=0,"primitive element");
    }
    array<vector<int>,2> words;
    for(int j=0;j<n;j++){
        words[0].push_back(character[2*a.x%prime]);
        words[1].push_back(character[2*b.x%prime]);
        a=multiply(a,step);b=multiply(b,step);
    }
    for(int j=0;j<n;j++){
        int sum=0;
        for(int h=0;h<2;h++){
            const auto &w=words[h];
            check(w[j]==w[(n-j)%n],"Yamada symmetry");
            check((w[j]==0)==(h==0 && j==0),"Yamada holes");
            for(int k=0;k<n;k++) sum+=w[k]*w[(k+j)%n];
        }
        check(sum==(j==0?prime:0),"Yamada Gram");
    }
    return words;
}
int coefficient(int h,int row,int col,const Matrix &q,const array<vector<int>,2> &w){
    if(row==0 && col==0) return h>=6?0:1;
    if(row==0 || col==0) return h==4?-1:1;
    const int i=(row-1)/2,j=(col-1)/2;
    const int id=i==j, parity=(row%2==col%2)?1:-1, lag=(j-i+n)%n;
    switch(h){
        case 0:return (w[0][lag]+id)*parity;
        case 1:return (w[0][lag]-id)*parity;
        case 2:case 3:return w[1][lag]*parity;
        case 4:return q[i][j]+id;
        case 5:return q[i][j]+id*parity;
        default:return q[i][j]+id*(parity-1)/2;
    }
}
// L_{e_i} e_j for the real octonions. Store signed, one-based coefficients.
array<array<int,8>,8> octonionArray(){
    array<array<int,8>,8> slots{};
    for(int h=0;h<8;h++){slots[h][0]=h+1;slots[h][h]=1;}
    for(int h=1;h<8;h++)slots[0][h]=-(h+1);
    const int lines[][3]={{1,2,3},{1,4,5},{1,7,6},{2,4,6},{2,5,7},{3,4,7},{3,6,5}};
    for(const auto &line:lines)for(int j=0;j<3;j++){
        int a=line[j],b=line[(j+1)%3],c=line[(j+2)%3];
        slots[c][b]=a+1;slots[c][a]=-(b+1);
    }
    for(const auto &row:slots)for(int s:row)check(s!=0,"octonion cell");
    return slots;
}
int main(int argc,char** argv){
    check(argc==2 || argc==3,"usage: w1880 conference118.txt [output-W.txt]");
    auto q=core(argv[1]);auto words=yamada();auto slots=octonionArray();
    constexpr int packed=(sizeW+63)/64;
    struct Row{array<uint64_t,packed> pos{},neg{};vector<int> holes;};
    vector<Row> W(sizeW);
    ofstream output;
    if(argc==3){output.open(argv[2]);check(output.good(),"output file");}
    for(int i=0;i<sizeW;i++){
        for(int j=0;j<sizeW;j++){
            int s=slots[i/block][j/block];
            int value=(s>0?1:-1)*coefficient(abs(s)-1,i%block,j%block,q,words);
            check(abs(value)<=1,"weighing alphabet");
            if(value) (value>0?W[i].pos:W[i].neg)[j/64] |= uint64_t(1)<<(j%64);
            else W[i].holes.push_back(j);
            if(argc==3)output.put(value>0?'+':value<0?'-':'0');
        }
        if(argc==3)output.put('\n');
        check(W[i].holes.size()==2,"weighing row weight");
    }
    if(argc==3){output.close();check(output.good(),"write weighing matrix");}
    for(int i=0;i<sizeW;i++)for(int j=0;j<i;j++){
        int diff=0, overlap=0;
        for(int k=0;k<packed;k++)
            diff+=__builtin_popcountll((W[i].pos[k]&W[j].neg[k])|(W[i].neg[k]&W[j].pos[k]));
        for(int x:W[i].holes)for(int y:W[j].holes)overlap+=(x==y);
        check(sizeW-4+overlap-2*diff==0,"weighing off-diagonal Gram");
    }
    cout<<"W(1880,1878): ternary entries and all "<<sizeW*(sizeW+1)/2<<" Gram entries on and below diagonal verified\n";
}
