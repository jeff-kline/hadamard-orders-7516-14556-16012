// Exact checks for the two choices of core in the bordered eight-block array.
import assert from 'node:assert/strict';
const square = (n, f) => Array.from({length:n}, (_,i) => Array.from({length:n}, (_,j) => f(i,j)));
const transpose = a => square(a.length,(i,j)=>a[j][i]);
const dot = (r,s) => r.reduce((sum,x,k)=>sum+x*s[k],0);
const gram = (a,b=a) => square(a.length,(i,j)=>dot(a[i],b[j]));
const equal = (a,b) => JSON.stringify(a)===JSON.stringify(b);
const eye = (n,k) => square(n,(i,j)=>i===j?k:0);
const slots = square(8,()=>0);
for(let i=0;i<8;i++){slots[i][0]=i+1;slots[i][i]=1;if(i)slots[0][i]=-i-1;}
for(const line of [[1,2,3],[1,4,5],[1,7,6],[2,4,6],[2,5,7],[3,4,7],[3,6,5]]){
  for(let j=0;j<3;j++){
    const a=line[j],b=line[(j+1)%3],c=line[(j+2)%3];
    slots[c][b]=a+1;slots[c][a]=-b-1;
  }
}
const local = (r,c,f) => square(4,(i,j)=>f(slots[i+r][j+c]));
const conjugate=[1,-1,-1,-1];
for(let i=0;i<4;i++)for(let j=0;j<4;j++){
  assert.equal(slots[i+4][j+4],conjugate[i]*conjugate[j]*slots[j][i]);
}
const scalarPart = s => Math.sign(s)*([2,0,-1,-1][Math.abs(s)-5]);
const antiPart = s => Math.sign(s)*([0,2,1,1][Math.abs(s)-5]);
const F=local(0,4,antiPart), G=local(4,0,antiPart);
assert.deepEqual(gram(F),eye(4,6));assert.deepEqual(gram(G),eye(4,6));
for(let h=1;h<=4;h++){
  const coefficient=s=>Math.abs(s)===h?Math.sign(s):0;
  const l=local(0,0,coefficient),r=local(4,4,coefficient);
  assert.deepEqual(gram(l,G),gram(F,r).map(row=>row.map(x=>x===0?0:-x)));
}
const idTest = h => equal(gram(h),eye(4,4));
const rows = Array.from({length:16},(_,k)=>Array.from({length:4},(_,j)=>(k>>j)&1?1:-1));
function findSignBlock(t){
  for(const a of rows)for(const b of rows)if(!dot(a,b))
    for(const c of rows)if(!dot(a,c)&&!dot(b,c))
      for(const d of rows){
        const h=[a,b,c,d];
        if(!idTest(h))continue;
        const v=gram(h,t);
        if(equal(v,transpose(v)))return h;
      }
  throw Error('missing sign block');
}
const coreSigns = square(8,()=>0);
for(const [r,c] of [[0,4],[4,0]]){
  const t=local(r,c,scalarPart);
  assert.deepEqual(gram(t),eye(4,6));
  const h=findSignBlock(t);
  console.log('offset',r,c,'T',JSON.stringify(t),'H',JSON.stringify(h));
  for(let i=0;i<4;i++)for(let j=0;j<4;j++)coreSigns[i+r][j+c]=h[i][j];
}
function verify(q,quartet,skew,twist){
  const n=q.length,m=2*n+1;
  const w=square(8*m,(row,col)=>{
    const i=Math.floor(row/m),j=Math.floor(col/m),a=row%m,b=col%m;
    const s=slots[i][j],sign=Math.sign(s),h=Math.abs(s)-1;
    if(!a&&!b)return sign*(h<6?1:0);
    if(!a||!b)return sign*(h===4?-1:1);
    const x=Math.floor((a-1)/2),y=Math.floor((b-1)/2);
    const p=(a+b)%2?-1:1,delta=Number(x===y);
    if(h<4) return sign*p*(i>=4 && twist ? quartet[h][y][x] : quartet[h][x][y]);
    const v=(skew?coreSigns[i][j]:sign)*q[x][y];
    if(h===4)return v+sign*delta;
    if(h===5)return v+sign*p*delta;
    return v+sign*(p-1)*delta/2;
  });
  assert(w.flat().every(x=>[-1,0,1].includes(x)));
  return equal(gram(w),eye(8*m,8*m-2));
}
// At n=3 the Paley skew conference core is Q. Three copies of J-2I
// and one copy of J have total squared sum 12 I. A common column
// permutation of order 3 makes three coefficients nonsymmetric.
const q3=[[0,1,-1],[-1,0,1],[1,-1,0]];
const b3=Array.from({length:4},(_,h)=>square(3,(i,j)=>h<3&&i===(j+1)%3?-1:1));
assert(!equal(b3[0],transpose(b3[0])));
assert(verify(q3,b3,true,true));
assert(!verify(q3,b3,false,true));
assert(!verify(q3,b3,true,false));
// n=5 has Paley symmetric core. Find a small symmetric circulant quartet
// for this test and apply a noncentral row sign and column permutation.
const n=5;
const q5=square(n,(i,j)=>[0,1,-1,-1,1][(j-i+n)%n]);
const words=[];
for(const a of [-1,1])for(const b of [-1,1])for(const c of [-1,1])words.push([a,b,c,c,b]);
const autocorr=(a,t)=>a.reduce((s,x,i)=>s+x*a[(i+t)%n],0);
let b5;
outer:for(const a of words)for(const b of words)for(const c of words)for(const d of words){
  const set=[a,b,c,d];
  if([1,2].every(t=>set.reduce((s,w)=>s+autocorr(w,t),0)===0)){
    b5=set.map(w=>square(n,(i,j)=>(i===0?-1:1)*w[(j+1-i+n)%n]));
    break outer;
  }
}
assert(b5 && b5.some(b=>!equal(b,transpose(b))));
assert(verify(q5,b5,false,true));
assert(!verify(q5,b5,false,false));
console.log('Full integer Gram: W(56,54), W(88,86); all three negative controls fail as predicted.');
