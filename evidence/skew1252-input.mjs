// Verify the two sets in Karoui's order-1252 skew construction.
import assert from 'node:assert/strict';
const order=625, degree=4, modulus=5;
const digits=Array.from({length:order},(_,x)=>
  Array.from({length:degree},(_,j)=>Math.floor(x/modulus**j)%modulus));
const encode=a=>a.reduce((s,x,i)=>s+x*modulus**i,0);
let logs, polynomial;
for(let c=1;c<order&&!logs;c++){
  const coefficients=digits[c], candidate=new Int16Array(order).fill(-1);
  let value=1, k=0;
  for(;value!==0 && candidate[value]===-1;k++){
    candidate[value]=k;
    const v=digits[value];
    value=encode(coefficients.map((a,i)=>((i?v[i-1]:0)+a*v[3])%modulus));
  }
  if(k===624 && value===1){logs=candidate;polynomial=coefficients;}
}
assert(logs);
const neg=x=>encode(digits[x].map(v=>(5-v)%5));
function difference(u,v){return encode(digits[u].map((a,i)=>(a-v[i]+5)%5));}
const subs=Array.from({length:625},(_,u)=>Uint16Array.from({length:625},(_,v)=>difference(u,digits[v])));
for(const multiplier of [1,3,5,7,9,11,13,15]){
  const words=[[4,5,6,7,8,9,10,11],[0,1,2,3,4,5,6,7]].map(indices=>
    Array.from({length:625},(_,x)=>x!==0&&indices.includes((multiplier*logs[x])%16)?-1:1));
  assert(words[0].every((v,x)=>x===0||v===-words[0][neg(x)]));
  const valid=Array.from({length:625},(_,shift)=>{
    let s=0;for(let x=0;x<625;x++){
      const y=subs[x][shift];s+=words[0][x]*words[0][y]+words[1][x]*words[1][y];
    }
    return s===(shift===0?1250:-2);
  }).every(Boolean);
  if(valid){
    console.log('GF(5^4) defining coefficients (ascending):',polynomial,'log multiplier:',multiplier);
    console.log('Skewness and all 625 summed periodic correlations checked.');
    process.exit(0);
  }
}
throw Error('no primitive orientation verified');
