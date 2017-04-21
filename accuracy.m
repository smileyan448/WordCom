function[accuracy]=accuracy(result,criterion)
[hang1,lie1]=size(result);
[hang2,lie2]=size(criterion);
totle=0;
for i=1:hang1
    for j=1:lie1
        if result([i],[j])~=0
           totle=totle+1;
           for m=1:hang2
               for n=1:lie2
                   if criterion([m],[n])==result([i],[j])
                       new([i],[j])=m;
                       break;
                   end;
               end;
           end;
        end;
    end;
end;
%num=0;
c=0;
for i=1:hang2
    for j=1:hang1
        num=0;
        for k=1:lie1
            if new([j],[k])==i
                num=num+1;
            end;
        end;
        new2([i],[j])=num;
    end;
end;
sum=0;
[hang3,lie3]=size(new2);
while(1)
    [C, row] = max(new2);
    [C2, col] = max(C);
    if C2==0
        break;
    else
        sum=sum+C2;
        row = row(col);
        col = col;
        for i=1:hang3
            new2([i],[col])=0;
        end;
        for j=1:lie3
            new2([row],[j])=0;
        end;
    end;
end;
accuracy=sum/totle;
