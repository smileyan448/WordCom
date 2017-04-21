result1=[];%manual-the result on subset
result2=[];%manual-the result on whole set after mapping the feature from the subset
result3=[];%auto-the result on subset
result4=[];%auto-the result on whole set after mapping the feature from the subset
%% name the original file and extract the ground truth
filename1=sprintf('%s', 'PreProcess\\Tweet_10');
filepath =sprintf('%s_cc.txt', filename1);
realzd2=load(filepath);
realzd = realzd2(:,2);
ccd=criterion(realzd2);
K=size(ccd,1);

%% sampling the original file
ratio = sprintf('%s', '50');
sampling = sprintf('PreProcess\\sampling.exe %s %s', filename1, ratio);
dos(sampling);
disp('1: sampling is done.');

%% read the sample file
filename=sprintf('%s_%s', filename1, ratio);
readsample = sprintf('PreProcess\\PrePro.exe %s', filename);
dos(readsample);
disp('2: sample file extract is finished');

%% Input:term-doc matrix X

filepath =sprintf('%s_matrix.txt', filename);
X=load(filepath);
X=X';

%% load the ground truth of sampling
filepath =sprintf('%s_cc.txt', filename);
realz2=load(filepath);
realz = realz2(:,2);
cc=criterion(realz2);
K=size(cc,1);


%% generate the feature mapping from the sample file to original file

generate = sprintf('PreProcess\\mapping.exe %s %s', filename1, filename);
dos(generate);

disp('3: feature extraction using features in sample is done'); 

filepath =sprintf('%s_sample_matrix.txt', filename);
D=load(filepath);


%% step 1: construct term-correlation matrix S
C = similarity(X, 'PMI');    % word-context matrix 

% [I J v]=find(C>0);
% A=sparse(I,J,v);

%clear C;
%K_rank_D;
auto = 0;  
if auto
    [cl, qq, cen1, cl2, qq2, N_inf,cen2]=K_rank_D_manual(C,cc,4,0);
%% automatically selected centers
else
    [cl2, qq2, N_inf,cen2]=K_rank_D(C,cc,4,1);
end
alpha=0.5;
beta=0.1;
%result=[];
%% select the centers manually
      
N_inf=N_inf';        
X=X';

if auto
        qqz=zeros(length(cl),K);

        %cl=cl';

        for i=1:K
        ind=find(cl==i);
        %qqz(ind,i)=cl(ind,1)-i+1;%without weights
        qqz(ind,i)=cl(ind,1)-i+alpha*N_inf(ind,1)+(1-alpha);
        end

        qqz=cen1+beta*qqz;

        %% compute the custer membership by long common terms between a text and a term cluster

        Y0=X*qqz;
        [qq0 cl0] = returnLabel(Y0,K);


        result1(size(result1,1)+1,:)= [accuracy(qq0,cc),NMI(qq0,cc),evalClustering(cl0,realz)];
        Z=D*qqz;
        [qqd0 cld0] = returnLabel(Z,K);
        result2(size(result2,1)+1,:)= [accuracy(qqd0,ccd),NMI(qqd0,ccd),evalClustering(cld0,realzd)];
        
        
end
%% select the centers automatically
%cl2=cl2';
qqz=zeros(length(cl2),K);
  
for i=1:K
    ind=find(cl2==i);
    %qqz(ind,i)=cl2(ind,1)-i+1;
    qqz(ind,i)=cl2(ind,1)-i+alpha*N_inf(ind,1)+(1-alpha);
end

  
qqz=cen2+beta*qqz;


%% compute the custer membership by long common terms between a text and a term cluster
Y=X*qqz;
[qqt clt] = returnLabel(Y,K);
result3(size(result3,1)+1,:)= [accuracy(qqt,cc),NMI(qqt,cc),evalClustering(clt,realz),length(cl2)];

disp('4: clustering on sample set is done');


U=zeros(length(cl2),K);
for i=1:K
      ind=find(cl2==i);
        %qqz(ind,i)=cl(ind,1)-i+1;
      U(ind,i)=cl2(ind,1)-i+N_inf(ind,1)+1;
end

%% Extract the top 20 words in each clusters
[B, IX] = sort(U', 2, 'descend');
filepath =sprintf('%s_topicwords.txt', filename);
dlmwrite(filepath,IX, '\t');
readtopwords = sprintf('PreProcess\\PrePro.exe %s %d %d', filename, K, 1);
dos(readtopwords);

disp('5: outputting the top 20 words is done.');

%% Project the original file on the sampled feature space and compute the cluster memberships

Z=D*qqz;
[qqd cld] = returnLabel(Z,K);
result4(size(result4,1)+1,:)= [accuracy(qqd,ccd),NMI(qqd,ccd),evalClustering(cld,realzd),length(cl2)];

disp('6: map and partition to the whole data is done');
