%通过signal_processing，将邻接矩阵转化为向量空间
%adj 网络G的邻接矩阵
function vec=adj2vec(adj)
n=size(adj,1);
v=adj+speye(n,n);
v=sparse(v);
vec=v*v*v;
%vec=vec-diag(diag(vec))+eye(n);

%进行列标准化，则生成的矩阵中每个列为一个样本，列中的元素值表示其对各个节点的影响程度
% s=sum(vec);
% for i=1:length(s)
%     vec(:,i)=vec(:,i)/s(i);
% end
%vec=bsxfun(@rdivide,vec,sum(vec));
vec=matrix2norm(vec,2);
end