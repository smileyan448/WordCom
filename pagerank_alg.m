function x = pagerank_alg(G,p)
% PAGERANK  Google's PageRank
% pagerank(U,G,p) uses the URLs and adjacency matrix produced by SURFER,
% together with a damping factory p, (default is .85), to compute and plot
% a bar graph of page rank, and print the dominant URLs in page rank order.
% x = pagerank(U,G,p) returns the page ranks instead of printing.
% See also SURFER, SPY.

if nargin < 2, p = .85; end

% Eliminate any self-referential links

G = G - diag(diag(G));
  
% c = out-degree, r = in-degree

[~,n] = size(G);
c = full(sum(G,1));   % modified by G.F. so that sprintf does not get sparse input 
r = full(sum(G,2));   % (which it used to be able to handle, but no longer can)

% Scale column sums to be 1 (or 0 where there are no out links).

k = find(c~=0);
D = sparse(k,k,1./c(k),n,n);

% Solve (I - p*G*D)*x = e

e = ones(n,1);
I = speye(n,n);
x = (I - p*G*D)\e;

% Normalize so that sum(x) == 1.

x = x/sum(x);

% Bar graph of page rank.

%[value,index]=sort(x,'descend');

% shg
% bar(x)
% title('Page Rank')

% Print URLs in page rank order.

% if nargout < 1
%    [ignore,q] = sort(-x);
%    disp('     page-rank  in  out  url')
%    k = 1;
%    while (k <= n) & (x(q(k)) >= .005)
%       j = q(k);
%       disp(sprintf(' %3.0f %8.4f %4.0f %4.0f  %s', ...
%          j,x(j),r(j),c(j),U{j}))
%       k = k+1;
%    end
% end

