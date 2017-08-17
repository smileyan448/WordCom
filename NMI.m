function[value]=NMI(result,criterionsingle) 
%the clustering result of an algorithm, n*1 matrix: n colums of labels;£¬criterionsingle: the ground truth clusters, n*1 matrix;
%[criterionsingle] = criterion();
[hangP,lieP]=size(result);
[hangT,lieT]=size(criterionsingle);
for i=1:hangT
    for j=1:hangP
        num=0;
        for m=1:lieT
            if criterionsingle(i,m)~=0
                for n=1:lieP
                    if result(j,n)==criterionsingle(i,m)
                        num=num+1;
                        break;
                    end;
                end;
            else
                break;
            end;
        end;
        N(i,j)=num;
    end;
end;
vertexnum=0;
for i=1:hangP
    for j=1:lieP
        if result(i,j)~=0
            vertexnum=vertexnum+1;
        else
            break;
        end;
    end;
end;
fenzi=0;
for i=1:hangT
    for j=1:hangP
        temp1=N(i,j)*vertexnum;
        temp2=0;
        temp3=0;
        for m=1:hangP
            temp2=temp2+N(i,m);
        end;
        for n=1:hangT
            temp3=temp3+N(n,j);
        end;
        temp4=temp1/(temp2*temp3);
        if temp4==0
            temp4=temp4+10^(-6);
        end;
        temp4=log(temp4)/log(2);
        temp4=temp4*N(i,j);
        fenzi=fenzi+temp4;
    end;
end;
fenmu1=0;
for i=1:hangT
    temp=0;
    for m=1:hangP
        temp=temp+N(i,m);
    end;
    if temp==0
        temp=temp+10^(-6);
    end;
    temp2=temp*log2(temp/vertexnum);
    fenmu1=fenmu1+temp2;
end;
fenmu2=0;
for j=1:hangP
    temp=0;
    for n=1:hangT
        temp=temp+N(n,j);
    end;
    if temp==0
        temp=temp+10^(-6);
    end;
    temp2=temp*log2(temp/vertexnum);
    fenmu2=fenmu2+temp2;
end;
value=(-2)*fenzi/(fenmu1+fenmu2);

        
        
        
            
            