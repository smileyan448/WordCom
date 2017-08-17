% Reture the clustering result intwo different formats
% algorithmResult: each line contains cluster members for its corresponding cluster
% Z: n*1, list cluster label for each node
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
        label(a)=label(a)+1;
        algorithmResult(a,label(a))=j;
    end
end
