%获取每个节点的类标，按类别分行;获取每个节点的类标Z,n*1
function [algorithmResult Z] = returnLabel(R, K)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
    for i=1:length(R);
       max=1; 
       for j=1:K;
          if (R(i,j)>R(i,max) );
                max=j;
          end;
       end;
       Z(i,1)=max;
    end;
    [hang,lie]=size(Z);
    num=0;
    labelNum=K;
    label(labelNum)=0;
    for j=1:hang
        a=Z(j,1);
        label(a)=label(a)+1;%每维存储第i类的元素个数,类a个数加1
        algorithmResult(a,label(a))=j;
    end
end