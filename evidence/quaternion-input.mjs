// Emit the exact weighing input using normalized projective quaternion orbits.
import { createHash } from 'node:crypto';
import fs from 'node:fs';
import assert from 'node:assert/strict';
if(process.argv.length!==3 && process.argv.length!==4)throw Error("usage: node quaternion-input.mjs weighing.txt [pinned-conference118.txt]");
const seed=process.argv[3] && fs.readFileSync(process.argv[3]);
let symmetricCore;
if(seed){
  assert.equal(createHash("sha256").update(seed).digest("hex"),"5fe566972f21790b2f42bcb0cc6b5f4454c07289d7e7eb414a68795fa28bce12");
  symmetricCore=seed.toString("utf8").trim().split(/\s+/).slice(1).map(r=>Array.from(r.slice(1),x=>x==="+"?1:x==="-"?-1:0));
  assert.equal(symmetricCore.length,117);
}
const n=symmetricCore?117:227,p=4*n-1,m=2*n+1;
const mod=(x,q)=>(x%q+q)%q;
function character(q) {
  const c=Array(q).fill(-1); c[0]=0;
  for(let x=1;x<q;x++)c[(x*x)%q]=1;
  return c;
}
const chi=character(p),inner=character(n);
const inv=Array(p).fill(0);
for(let x=1;x<p;x++)for(let y=1;y<p;y++)if(x*y%p===1){inv[x]=y;break;}
let a,b;
outer:for(a=0;a<p;a++)for(b=0;b<p;b++)if((a*a+b*b+1)%p===0)break outer;
assert(a<p);
const line=([x,y])=>mod(y,p)===0?p:mod(x*inv[mod(y,p)],p);
const marked=new Set(),bases=[];
for(let k=0;k<=p;k++){
  if(marked.has(k))continue;
  const [x,y]=k===p?[1,0]:[k,1];
  const kx=mod(a*x+b*y,p),ky=mod(b*x-a*y,p);
  // Quaternion basis 1,-J,-K,-JK on a representative; J(x,y)=(y,-x).
  const vec=[[x,y],[-y,x],[-kx,-ky],[-ky,kx]];
  for(const v of vec){const id=line(v);assert(!marked.has(id));marked.add(id);}
  bases.push(vec);
}
assert.equal(bases.length,n);assert.equal(marked.size,p+1);
const eye=(x,y)=>Number(x===y);
const slot=Array.from({length:8},()=>Array(8).fill(0));
for(let i=0;i<8;i++){slot[i][0]=i+1;slot[i][i]=1;if(i)slot[0][i]=-i-1;}
for(const plane of [[1,2,3],[1,4,5],[1,7,6],[2,4,6],[2,5,7],[3,4,7],[3,6,5]])
  for(let k=0;k<3;k++){
    const i=plane[k],j=plane[(k+1)%3],h=plane[(k+2)%3];
    slot[h][j]=i+1;slot[h][i]=-j-1;
  }
function paley(i,s,j,t){
  const [x,y]=bases[i][s],[u,v]=bases[j][t];
  return chi[mod(x*v-y*u,p)]+eye(i,j)*eye(s,t);
}
const B=Array.from({length:4},(_,h)=>Array.from({length:n},(_,x)=>Int8Array.from(bases,(_,y)=>paley(x,h,y,0))));
for(let s=0;s<4;s++)for(let t=0;t<4;t++)for(let i=0;i<n;i++)for(let j=0;j<n;j++){
  const e=slot[s][t];assert.equal(Math.sign(e)*B[Math.abs(e)-1][i][j],paley(i,s,j,t));
}
const top=[[-1,-1,-1,-1],[1,-1,1,-1],[1,1,-1,-1],[1,-1,-1,1]];
const bottom=[[-1,-1,-1,-1],[1,-1,-1,1],[1,-1,1,-1],[1,1,-1,-1]];
function entry(i,j,r,c){
  const e=slot[i][j],h=Math.abs(e)-1,sign=Math.sign(e);
  if(!r&&!c)return sign*(h<6?1:0);
  if(!r||!c)return sign*(h===4?-1:1);
  const x=(r-1)>>1,y=(c-1)>>1,parity=(r+c)%2?-1:1;
  if(h<4)return sign*parity*(i>=4?B[h][y][x]:B[h][x][y]);
  const u=symmetricCore ? sign*symmetricCore[x][y]
                        : (i<4?top[i][j-4]:bottom[i-4][j])*inner[mod(y-x,n)];
  if(h===4)return u+sign*eye(x,y);
  if(h===5)return u+sign*parity*eye(x,y);
  return u+sign*(parity-1)*eye(x,y)/2;
}
const file=fs.openSync(process.argv[2],'w');
try{
  const row=Buffer.alloc(8*m+1);row[8*m]=10;
  for(let i=0;i<8;i++)for(let r=0;r<m;r++){
    let holes=0;
    for(let j=0;j<8;j++)for(let c=0;c<m;c++){
      const s=entry(i,j,r,c);
      assert(s===-1||s===0||s===1);if(!s)holes++;
      row[j*m+c]=s===0?48:s<0?45:43;
    }
    assert.equal(holes,2);fs.writeSync(file,row);
  }
}finally{fs.closeSync(file);}
console.log('W input written; all Paley quaternion blocks, entries and row weights checked.');
