function [Qvalue] = Qfunction(network,result)
%compute the mudularity of partitioned communities.
[hangnew,lienew]=size(network);
for i=1:hangnew
    m=network([i],[1]);
    n=network([i],[2]);
    A([m],[n])=1;
    A(n,m)=1;
end;
[K,lielie]=size(result);
[hang,lie]=size(A);
e=zeros(K,K);
edge=0;
for i=1:K
    for j=1:lielie
        if result([i],[j])~=0
            temp=result([i],[j]);
            idx2([temp])=i;
        else
            break;
        end;
    end;
end;
for i=2:hang
    for j=1:i-1
        if A([i],[j])==1
            edge=edge+1;
            m=idx2([i]);
            n=idx2([j]);
            e([m],[n])=e([m],[n])+1;
            if m~=n
                e([n],[m])=e([m],[n]);
            end;
        end;
    end;
end;
e=e/edge;
Tr=0;
for ii=1:K
    Tr=e([ii],[ii])+Tr;
end;
r=e*e;
fan=0;
for i=1:K
    for j=1:K
        fan=fan+r([i],[j]);
    end;
end;
Qvalue=Tr-fan;