%normalize the volumns of a matrix
%ѡ��ͬ�ľ����һ������
function norm_m=matrix2norm(X,flag)
n=size(X,1);
if flag==1% �к�Ϊ1
    norm_m = X./repmat((sum(X)+eps),n,1);  
elseif flag==2%norm
    a= sqrt(sum(bsxfun(@times,X,X)));
    norm_m=bsxfun(@rdivide,X,a+eps);
elseif flag==3%(x-min)/(max-min)
    for i=1:n
        X(:,i)=(X(:,i)-min(X(:,i)))/(max(X(:,i))-min(X(:,i))+eps);
    end   
    norm_m=X;
else
    norm_m=X;
end 