%adjust kmeans
%K is the number of clusters
function [U,x,cen]=D_kmeans(new_matrix,K,id)
x=[];
n=size(new_matrix,1);%get the size of samples
%id=randperm(n,K);
%selet the initial centroids
cen=new_matrix(:,id);
N=0;
%get the initial assignment
 a=new_matrix'*cen;
 b=sum(bsxfun(@times,cen,cen));
 temp=bsxfun(@minus,b,2*a);
 [~,min_id]=min(temp,[],2);
clear temp;
%calculate the initial value of the objective function
cha_initial=0;

  for k=1:K
     idd= min_id==k;
     cha=bsxfun(@minus,new_matrix(:,idd),cen(:,k));
     cha_initial=cha_initial+sum(sum(cha.*cha));
  end 
 disp(cha_initial);
%repeat until the assignment keep unchanged
ch=1;
count=0;
shangci=cha_initial;
while (count < 100 && ch > 1e-6)   
%while(cha<1e-6)
 %update the centroids from the t-time assignment
for j=1:K
     id= min_id==j;    
     cen(:,j)=mean(new_matrix(:,id),2); 
end
 %get each point's assignment
 a=new_matrix'*cen;
 b=sum(bsxfun(@times,cen,cen));
 temp=bsxfun(@minus,b,2*a);
 [~,min_id]=min(temp,[],2);
 clear temp;

 

 % print the objective value
 cha_new=0;
 for k=1:K
     idd= min_id==k;
     cha=bsxfun(@minus,new_matrix(:,idd),cen(:,k));
     cha_new=cha_new+sum(sum(cha.*cha));
  end 
 ch=abs(cha_new-shangci);
 shangci=cha_new;
 x(length(x)+1)=cha_new;
%  [~  , ~, NMI]=infoeval(min_id,min_id_last); 
% if NMI==1
%     N=N+1;
% end
%min_id_last=min_id;
 count=count+1;
end

%disp the finial value of the objective function
disp('final value is:');
disp(count);
     U(:,1)=1:n;
     U(:,2)=min_id;        
end