%transform the n*2 (node label, cluster lable) to
%stand_c: each line contains the cluster mebers for an corresponding cluster
%stand_com: n*1, only list the cluster label for each node
function [stand_C,stand_com]=criterion(community)
n=unique(community(:,2));%community rearrangement
m=length(n);%number of communities
N=0;
stand_com=community;
for ii=1:m
     if length(community(:,2)==n(ii))>N
            N=length(find(community(:,2)==n(ii)));       
     end    
end
transfer=vertcat(n',1:m);
transfer=transfer';
for k=1:size(stand_com,1)
    index= transfer(:,1)==stand_com(k,2);
    stand_com(k,2)=transfer(index,2);
end
    detect=zeros(m,N);
    for jj=1:m
        detect(jj,1:length(find(community(:,2)==n(jj))))=community((community(:,2)==n(jj)>0),1);
    end   
    index= detect(:,1)==0;
    detect(index,:)=[];
    stand_C=detect; 
    
end
