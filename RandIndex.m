function [value] = RandIndex(result,criterionsingle)
%[criterionsingle] = criterion();
[hangT,lieT]=size(criterionsingle);
[hangP,lieP]=size(result);
for i=1:hangT
    for j=1:lieT
        if criterionsingle([i],[j])~=0
            temp=criterionsingle([i],[j]);
            idx([1],[temp])=i;
        else
            break;
        end;
    end;
end;
for i=1:hangP
    for j=1:lieP
        if result([i],[j])~=0
            temp=result([i],[j]);
            idx([2],[temp])=i;
        else
            break;
        end;
    end;
end;
[hang,vertexnum]=size(idx);
a=0;
b=0;
c=0;
d=0;
for i=1:vertexnum
    for j=i+1:vertexnum
        if (idx([1],[i])==idx([1],[j]))&&(idx([2],[i])==idx([2],[j]))
            a=a+1;
        end;
        if (idx([1],[i])==idx([1],[j]))&&(idx([2],[i])~=idx([2],[j]))
            b=b+1;
        end;
        if (idx([1],[i])~=idx([1],[j]))&&(idx([2],[i])==idx([2],[j]))
            c=c+1;
        end;
        if (idx([1],[i])~=idx([1],[j]))&&(idx([2],[i])~=idx([2],[j]))
            d=d+1;
        end;
    end;
end;
value=(a+d)/(a+b+c+d);

