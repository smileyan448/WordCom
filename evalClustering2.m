function [PWF]=evalClustering2(Z,realZ)
%% W adjacent matrix
%% K number of cluters
%% Z returned community label 1:K
%% realZ real label 1:K
%% Modu modularity
%% Ncut
%% NMI normalized mutual information
%% PWF pairwise F measure

PWF=[];

%% Compute F measure
if isempty(realZ)==0 
    n = length(Z);
    num_corr = 0;
    num_esti = 0;
    num_real = 0;
    for i = 1:n
        t_Z = ones(n, 1)*Z(i) - Z;
        t_realZ = ones(n, 1)*realZ(i) - realZ;
        t_Z(i) = 1;
        t_realZ(i) = 1;
        ind_esti = find(t_Z == 0);
        ind_real = find(t_realZ == 0);
        ind_corr = intersect(ind_esti, ind_real);
        num_esti = num_esti + length(ind_esti);
        num_real = num_real + length(ind_real);
        num_corr = num_corr + length(ind_corr);
    end

%     t1 = repmat(Z, 1,n);
%     t2 = repmat(Z', n, 1);
%     pair_relation_esti=t1 - t2;
%     pair_relation_real=repmat(realZ, 1,n)-repmat(realZ', n, 1);
%     
%     pair_relation_esti=pair_relation_esti+diag(ones(1,n));
%     pair_relation_real=pair_relation_real+diag(ones(1,n));    
% 
%     ind_esti=find(pair_relation_esti==0);
%     ind_real=find(pair_relation_real==0);
%     ind_corr=intersect(ind_esti, ind_real);
    if num_esti > 0
        Pre=num_corr/num_esti;
    else
        Pre=0;
    end
    if num_real > 0
       Rec=num_corr/num_real;
    else
        Rec=0;
    end
    if Pre+Rec>0
        PWF=(2*Pre*Rec)./(Pre+Rec);
    else
        PWF=0;
    end
end

end




