%Signal propogation
%adj: the adjacency matrix of a network
function vec=adj2vec(adj)
n=size(adj,1);
v=adj+speye(n,n);
v=sparse(v);
vec=v*v*v;
%vec=vec-diag(diag(vec))+eye(n);

%normalization
% s=sum(vec);
% for i=1:length(s)
%     vec(:,i)=vec(:,i)/s(i);
% end
%vec=bsxfun(@rdivide,vec,sum(vec));
vec=matrix2norm(vec,2);
end