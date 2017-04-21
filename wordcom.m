%%Read the original file

filename=sprintf('%s', 'PreProcess\\Tweet_10');
readfile = sprintf('PreProcess\\PrePro.exe %s', filename);
dos(readfile);

%% Load:term-doc matrix X
filepath =sprintf('%s_matrix.txt', filename);
X=load(filepath);
X=X';


%% Load the ground truth
filepath =sprintf('%s_cc.txt', filename);
realz2=load(filepath);
realz = realz2(:,2);
cc=criterion(realz2);
K=size(cc,1);


%% step 1: construct term-correlation matrix S
C = similarity(X, 'PMI');    % word-context matrix 

%[I J v]=find(C>0);
%A=sparse(I,J,v);

%clear C;
%% Step 2: word comunity detection
auto=1;
if ~auto
    %return the two group of results, one is from manually selected centers and
    %the other is from automatically selected centers for comparing their
    %difference
    [cl, qq, cen1, cl2, qq2, N_inf,cen2]=K_rank_D_manual(C,cc,4,auto);
else
    [cl2, qq2, N_inf,cen2]=K_rank_D(C,cc,4,auto);    
end
alpha=0.5;
beta=0.05;
result=[];

%% Step 3: select the centers and form concept vectors
%auto = 1;        
N_inf=N_inf';        
X=X';
if ~auto
        qqz=zeros(length(cl),K);

        %cl=cl';

        for i=1:K
        ind=find(cl==i);
        %qqz(ind,i)=cl(ind,1)-i+1;%without weights
        qqz(ind,i)=cl(ind,1)-i+alpha*N_inf(ind,1)+(1-alpha);
        end

        qqz=(1-beta)*cen1+beta*qqz;

%% Step 4: compute the custer membership by long common terms between a text and a term cluster

        Y0=X*qqz;
        [qq0 cl0] = returnLabel(Y0,K);
        result(size(result,1)+1,:)= [accuracy(qq0,cc),NMI(qq0,cc),evalClustering(cl0,realz)];   
        
end
%% select the centers automatically
%test the sensitivity of alpha and beta
%for alpha=0.1:0.1:1.0
%    for beta=0.01:0.01:0.2
        %cl2=cl2';
        qqz=zeros(length(cl2),K);

        for i=1:K
            ind=find(cl2==i);
            %qqz(ind,i)=cl2(ind,1)-i+1;
            qqz(ind,i)=cl2(ind,1)-i+alpha*N_inf(ind,1)+(1-alpha);
        end
        qqz=(1-beta)*cen2+beta*qqz;

%% compute the custer membership by long common terms between a text and a term cluster

Y=X*qqz;
[qqt clt] = returnLabel(Y,K);
result(size(result,1)+1,:)= [accuracy(qqt,cc),NMI(qqt,cc),evalClustering(clt,realz)];


%    end
%end
% 
% 
% % step 3: solve term-topic matrix V
% X=X';
% U=qqz;
% lambda2 = 0.1;  % smoothing coefficient
% V = pinv(U'*U + lambda2 * eye(K) )*U'*X; 
% V=V';
% [qq2 cl] = returnLabel(V,K);
% q=1:length(cl);
% q(2,:)=cl;
% qq=criterion(q');
% 
% result(size(result,1)+1,:)= [accuracy(qq,cc),NMI(qq,cc),evalClustering(cl,realz)];
% if auto
%     cl2=cl;
% end

%% Extract the top 20 words in each clusters
U=zeros(length(cl2),K);
for i=1:K
      ind=find(cl2==i);
        %qqz(ind,i)=cl(ind,1)-i+1;
      U(ind,i)=cl2(ind,1)-i+N_inf(ind,1)+1;
end
[B, IX] = sort(U', 2, 'descend');
%[B, IX] = sort(qqz', 2, 'descend');
filepath =sprintf('%s_topicwords.txt', filename);
dlmwrite(filepath,IX, '\t');
readtopwords = sprintf('PreProcess\\PrePro.exe %s %d 1', filename, K);
dos(readtopwords);

